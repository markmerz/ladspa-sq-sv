
#define         _ISOC9X_SOURCE  1
#define         _ISOC99_SOURCE  1
#define         __USE_ISOC99    1
#define         __USE_ISOC9X    1

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ladspa.h"

#include HILBERT_STEREO_H

#define HILBERT_LEFT_INPUT              0
#define HILBERT_RIGHT_INPUT             1
#define HILBERT_LEFT_OUTPUT0            2
#define HILBERT_RIGHT_OUTPUT0           3
#define HILBERT_LEFT_OUTPUT90           4
#define HILBERT_RIGHT_OUTPUT90          5
#define HILBERT_LATENCY                 6


static LADSPA_Descriptor *hilbertDescriptor = NULL;

typedef struct {
    LADSPA_Data *left_input;
    LADSPA_Data *right_input;
    LADSPA_Data *left_output0;
    LADSPA_Data *left_output90;
    LADSPA_Data *right_output0;
    LADSPA_Data *right_output90;
    LADSPA_Data *latency;
    LADSPA_Data *left_delay;
    LADSPA_Data *right_delay;
    unsigned int left_dptr;
    unsigned int right_dptr;
} Hilbert;

const LADSPA_Descriptor *ladspa_descriptor(unsigned long index) {

    switch (index) {
        case 0:
            return hilbertDescriptor;
        default:
            return NULL;
    }
}

static void cleanupHilbert(LADSPA_Handle instance) {
    Hilbert *plugin_data = (Hilbert *) instance;
    free(plugin_data->left_delay);
    free(plugin_data->right_delay);
    free(instance);
}

static void connectPortHilbert(LADSPA_Handle instance, unsigned long port, LADSPA_Data *data) {
    Hilbert *plugin;

    plugin = (Hilbert *) instance;
    switch (port) {
        case HILBERT_LEFT_INPUT:
            plugin->left_input = data;
            break;
        case HILBERT_RIGHT_INPUT:
            plugin->right_input = data;
            break;
        case HILBERT_LEFT_OUTPUT0:
            plugin->left_output0 = data;
            break;
        case HILBERT_LEFT_OUTPUT90:
            plugin->left_output90 = data;
            break;
        case HILBERT_RIGHT_OUTPUT0:
            plugin->right_output0 = data;
            break;
        case HILBERT_RIGHT_OUTPUT90:
            plugin->right_output90 = data;
            break;
        case HILBERT_LATENCY:
            plugin->latency = data;
            break;
    }
}

static LADSPA_Handle instantiateHilbert(const LADSPA_Descriptor *descriptor, unsigned long s_rate) {
    Hilbert *plugin_data = (Hilbert *) calloc(1, sizeof (Hilbert));
    LADSPA_Data *left_delay = NULL;
    LADSPA_Data *right_delay = NULL;
    unsigned int left_dptr;
    unsigned int right_dptr;

    left_delay = calloc(D_SIZE, sizeof (LADSPA_Data));
    right_delay = calloc(D_SIZE, sizeof (LADSPA_Data));

    left_dptr = 0;
    right_dptr = 0;

    plugin_data->left_delay = left_delay;
    plugin_data->right_delay = right_delay;
    plugin_data->left_dptr = left_dptr;
    plugin_data->right_dptr = right_dptr;

    return (LADSPA_Handle) plugin_data;
}

static void runHilbert(LADSPA_Handle instance, unsigned long sample_count) {
    Hilbert *plugin_data = (Hilbert *) instance;

    /* Input (array of floats of length sample_count) */
    const LADSPA_Data * const left_input = plugin_data->left_input;
    const LADSPA_Data * const right_input = plugin_data->right_input;

    /* 0deg output (array of floats of length sample_count) */
    LADSPA_Data * const left_output0 = plugin_data->left_output0;
    LADSPA_Data * const right_output0 = plugin_data->right_output0;

    /* 90deg output (array of floats of length sample_count) */
    LADSPA_Data * const left_output90 = plugin_data->left_output90;
    LADSPA_Data * const right_output90 = plugin_data->right_output90;

    LADSPA_Data * left_delay = plugin_data->left_delay;
    LADSPA_Data * right_delay = plugin_data->right_delay;
    unsigned int left_dptr = plugin_data->left_dptr;
    unsigned int right_dptr = plugin_data->right_dptr;
    
    *(plugin_data->latency) = LATENCY;

    unsigned long pos;
    unsigned int i;
    float left_hilb;
    float right_hilb;

    for (pos = 0; pos < sample_count; pos++) {
        left_delay[left_dptr] = left_input[pos];
        right_delay[right_dptr] = right_input[pos];
        left_hilb = 0.0f;
        right_hilb = 0.0f;
        for (i = 0; i < NZEROS / 2; i++) {
            left_hilb += (xcoeffs[i] * left_delay[(left_dptr - i * 2) & (D_SIZE - 1)]);
            right_hilb += (xcoeffs[i] * right_delay[(right_dptr - i * 2) & (D_SIZE - 1)]);
        }

        left_output0[pos] = left_delay[(left_dptr - LATENCY) & (D_SIZE - 1)];
        left_output90[pos] = left_hilb;

        right_output0[pos] = right_delay[(right_dptr - LATENCY) & (D_SIZE - 1)];
        right_output90[pos] = right_hilb;

        left_dptr = (left_dptr + 1) & (D_SIZE - 1);
        right_dptr = (right_dptr + 1) & (D_SIZE - 1);
    }

    plugin_data->left_dptr = left_dptr;
    plugin_data->right_dptr = right_dptr;
}

void __attribute__((constructor)) swh_init() {
    char **port_names;
    LADSPA_PortDescriptor *port_descriptors;
    LADSPA_PortRangeHint *port_range_hints;

#define D_(s) (s)


    hilbertDescriptor =
            (LADSPA_Descriptor *) malloc(sizeof (LADSPA_Descriptor));

    if (hilbertDescriptor) {
        hilbertDescriptor->UniqueID = PLUGIN_ID;
        hilbertDescriptor->Label = PLUGIN_NAME;
        hilbertDescriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
        hilbertDescriptor->Name = D_("Hilbert transformer, two channels");
        hilbertDescriptor->Maker = "Steve Harris <steve@plugin.org.uk>, mod to two channels with more filter taps by Markko Merzin <markko.merzin@gmail.com>";
        hilbertDescriptor->Copyright = "GPL";
        hilbertDescriptor->PortCount = 7;

        port_descriptors = (LADSPA_PortDescriptor *) calloc(7, sizeof (LADSPA_PortDescriptor));
        hilbertDescriptor->PortDescriptors = (const LADSPA_PortDescriptor *) port_descriptors;

        port_range_hints = (LADSPA_PortRangeHint *) calloc(7, sizeof (LADSPA_PortRangeHint));
        hilbertDescriptor->PortRangeHints = (const LADSPA_PortRangeHint *) port_range_hints;

        port_names = (char **) calloc(7, sizeof (char*));
        hilbertDescriptor->PortNames = (const char **) port_names;

        /* Parameters for Input */
        port_descriptors[HILBERT_LEFT_INPUT] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_LEFT_INPUT] = D_("Left Input");
        port_range_hints[HILBERT_LEFT_INPUT].HintDescriptor = 0;

        port_descriptors[HILBERT_RIGHT_INPUT] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_RIGHT_INPUT] = D_("Right Input");
        port_range_hints[HILBERT_RIGHT_INPUT].HintDescriptor = 0;

        /* Parameters for 0deg output */
        port_descriptors[HILBERT_LEFT_OUTPUT0] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_LEFT_OUTPUT0] = D_("Left 0deg output");
        port_range_hints[HILBERT_LEFT_OUTPUT0].HintDescriptor = 0;

        /* Parameters for 90deg output */
        port_descriptors[HILBERT_LEFT_OUTPUT90] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_LEFT_OUTPUT90] = D_("Left 90deg output");
        port_range_hints[HILBERT_LEFT_OUTPUT90].HintDescriptor = 0;
        /* Parameters for 0deg output */
        port_descriptors[HILBERT_RIGHT_OUTPUT0] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_RIGHT_OUTPUT0] = D_("Right 0deg output");
        port_range_hints[HILBERT_RIGHT_OUTPUT0].HintDescriptor = 0;

        /* Parameters for 90deg output */
        port_descriptors[HILBERT_RIGHT_OUTPUT90] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[HILBERT_RIGHT_OUTPUT90] = D_("Right 90deg output");
        port_range_hints[HILBERT_RIGHT_OUTPUT90].HintDescriptor = 0;


        /* Parameters for latency */
        port_descriptors[HILBERT_LATENCY] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
        port_names[HILBERT_LATENCY] = D_("latency");
        port_range_hints[HILBERT_LATENCY].HintDescriptor = 0;

        hilbertDescriptor->activate = NULL;
        hilbertDescriptor->cleanup = cleanupHilbert;
        hilbertDescriptor->connect_port = connectPortHilbert;
        hilbertDescriptor->deactivate = NULL;
        hilbertDescriptor->instantiate = instantiateHilbert;
        hilbertDescriptor->run = runHilbert;
        hilbertDescriptor->run_adding = NULL;
        hilbertDescriptor->set_run_adding_gain = NULL;
    }
}

void __attribute__((destructor)) swh_fini() {
    if (hilbertDescriptor) {
        free((LADSPA_PortDescriptor *) hilbertDescriptor->PortDescriptors);
        free((char **) hilbertDescriptor->PortNames);
        free((LADSPA_PortRangeHint *) hilbertDescriptor->PortRangeHints);
        free(hilbertDescriptor);
    }
    hilbertDescriptor = NULL;

}
