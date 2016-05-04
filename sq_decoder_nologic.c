#define         _ISOC9X_SOURCE  1
#define         _ISOC99_SOURCE  1
#define         __USE_ISOC99    1
#define         __USE_ISOC9X    1

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ladspa.h"

#define INPUT_LEFT_I        0
#define INPUT_RIGHT_I       1
#define INPUT_LEFT_J        2
#define INPUT_RIGHT_J       3
#define OUTPUT_LEFT_FRONT   4
#define OUTPUT_RIGHT_FRONT  5
#define OUTPUT_LEFT_BACK    6
#define OUTPUT_RIGHT_BACK   7
#define PORTCOUNT           8

static LADSPA_Descriptor* sqDecoderNologicDescriptor = NULL;

typedef struct {
    LADSPA_Data* input_left_i;
    LADSPA_Data* input_right_i;
    LADSPA_Data* input_left_j;        
    LADSPA_Data* input_right_j;
    LADSPA_Data* output_left_front;
    LADSPA_Data* output_right_front;
    LADSPA_Data* output_left_back;
    LADSPA_Data* output_right_back;
    double sqrt2over2;
} SqDecoderNologic;

const LADSPA_Descriptor* ladspa_descriptor(unsigned long index) {

    switch (index) {
        case 0:
            return sqDecoderNologicDescriptor;
        default:
            return NULL;
    }
}

static void cleanupSqDecoderNologic(LADSPA_Handle instance) {
    // SqDecoderNologic* plugin_data = (SqDecoderNologic*) instance;
    free(instance);
}

static void connectPortSqDecoderNologic(LADSPA_Handle instance, unsigned long port, LADSPA_Data *data) {
    SqDecoderNologic* plugin;

    plugin = (SqDecoderNologic *) instance;
    switch (port) {
        case INPUT_LEFT_I:
            plugin->input_left_i = data;
            break;
        case INPUT_RIGHT_I:
            plugin->input_right_i = data;
            break;
        case INPUT_LEFT_J:
            plugin->input_left_j = data;
            break;
        case INPUT_RIGHT_J:
            plugin->input_right_j = data;
            break;
        case OUTPUT_LEFT_FRONT:
            plugin->output_left_front = data;
            break;
        case OUTPUT_RIGHT_FRONT:
            plugin->output_right_front = data;
            break;
        case OUTPUT_LEFT_BACK:
            plugin->output_left_back = data;
            break;
        case OUTPUT_RIGHT_BACK:
            plugin->output_right_back = data;
            break;
    }
}

static LADSPA_Handle instantiateSqDecoderNologic(const LADSPA_Descriptor *descriptor, unsigned long s_rate) {
    SqDecoderNologic* plugin_data = (SqDecoderNologic*) calloc(1, sizeof(SqDecoderNologic)); 
    plugin_data->sqrt2over2 = sqrt(2) / 2;
    return (LADSPA_Handle) plugin_data;
}

static void runSqDecoderNologic(LADSPA_Handle instance, unsigned long sample_count) {
    SqDecoderNologic* plugin_data = (SqDecoderNologic*) instance;
    
    float input_left_i, input_right_i, input_left_j, input_right_j;
    float output_front_left, output_front_right, output_back_left, output_back_right;
    
    for (unsigned long c = 0; c < sample_count; c++) {
        input_left_i = plugin_data->input_left_i[c];
        input_right_i = plugin_data->input_right_i[c];
        input_left_j = plugin_data->input_left_j[c];
        input_right_j = plugin_data->input_right_j[c];
                                
        /* Actual algorithm */
        
        output_front_left = input_left_j;
        output_front_right = input_right_j;
        output_back_left = ((input_left_i * plugin_data->sqrt2over2) - (input_right_j * plugin_data->sqrt2over2));
        output_back_right = ((input_left_j * plugin_data->sqrt2over2) - (input_right_i * plugin_data->sqrt2over2));
        /* End of actual algorith */
        
        plugin_data->output_left_front[c] = output_front_left;
        plugin_data->output_right_front[c] = output_front_right;
        plugin_data->output_left_back[c] = output_back_left;
        plugin_data->output_right_back[c] = output_back_right;
    }    
}

void __attribute__((constructor)) swh_init() {
    char **port_names;
    LADSPA_PortDescriptor *port_descriptors;
    LADSPA_PortRangeHint *port_range_hints;

    sqDecoderNologicDescriptor = (LADSPA_Descriptor*) malloc(sizeof (LADSPA_Descriptor));

    if (sqDecoderNologicDescriptor) {
        sqDecoderNologicDescriptor->UniqueID = 3827;
        sqDecoderNologicDescriptor->Label = "sq_decoder_nologic";
        sqDecoderNologicDescriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
        sqDecoderNologicDescriptor->Name = "SQ decoder with no directional logic";
        sqDecoderNologicDescriptor->Maker = "Markko Merzin <markko.merzin@gmail.com>";
        sqDecoderNologicDescriptor->Copyright = "GPL";
        sqDecoderNologicDescriptor->PortCount = PORTCOUNT;

        port_descriptors = (LADSPA_PortDescriptor *) calloc(PORTCOUNT, sizeof (LADSPA_PortDescriptor));
        sqDecoderNologicDescriptor->PortDescriptors = (const LADSPA_PortDescriptor *) port_descriptors;

        port_range_hints = (LADSPA_PortRangeHint *) calloc(PORTCOUNT, sizeof (LADSPA_PortRangeHint));
        sqDecoderNologicDescriptor->PortRangeHints = (const LADSPA_PortRangeHint *) port_range_hints;

        port_names = (char **) calloc(PORTCOUNT, sizeof (char*));
        sqDecoderNologicDescriptor->PortNames = (const char **) port_names;

        port_descriptors[INPUT_LEFT_I] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[INPUT_LEFT_I] = "Left Input I";
        port_range_hints[INPUT_LEFT_I].HintDescriptor = 0;

        port_descriptors[INPUT_RIGHT_I] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[INPUT_RIGHT_I] = "Right Input I";
        port_range_hints[INPUT_RIGHT_I].HintDescriptor = 0;

        port_descriptors[INPUT_LEFT_J] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[INPUT_LEFT_J] = "Left Input J";
        port_range_hints[INPUT_LEFT_J].HintDescriptor = 0;

        port_descriptors[INPUT_RIGHT_J] = LADSPA_PORT_INPUT | LADSPA_PORT_AUDIO;
        port_names[INPUT_RIGHT_J] = "Right Input J";
        port_range_hints[INPUT_RIGHT_J].HintDescriptor = 0;
        
        
        port_descriptors[OUTPUT_LEFT_FRONT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[OUTPUT_LEFT_FRONT] = "Left front output";
        port_range_hints[OUTPUT_LEFT_FRONT].HintDescriptor = 0;

        port_descriptors[OUTPUT_RIGHT_FRONT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[OUTPUT_RIGHT_FRONT] = "Right front output";
        port_range_hints[OUTPUT_RIGHT_FRONT].HintDescriptor = 0;

        port_descriptors[OUTPUT_LEFT_BACK] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[OUTPUT_LEFT_BACK] = "Left back output";
        port_range_hints[OUTPUT_LEFT_BACK].HintDescriptor = 0;

        port_descriptors[OUTPUT_RIGHT_BACK] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        port_names[OUTPUT_RIGHT_BACK] = "Right back output";
        port_range_hints[OUTPUT_RIGHT_BACK].HintDescriptor = 0;
       
        sqDecoderNologicDescriptor->activate = NULL;
        sqDecoderNologicDescriptor->cleanup = cleanupSqDecoderNologic;
        sqDecoderNologicDescriptor->connect_port = connectPortSqDecoderNologic;
        sqDecoderNologicDescriptor->deactivate = NULL;
        sqDecoderNologicDescriptor->instantiate = instantiateSqDecoderNologic;
        sqDecoderNologicDescriptor->run = runSqDecoderNologic;
        sqDecoderNologicDescriptor->run_adding = NULL;
        sqDecoderNologicDescriptor->set_run_adding_gain = NULL;
    }
}

void __attribute__((destructor)) swh_fini() {
    if (sqDecoderNologicDescriptor) {
        free((LADSPA_PortDescriptor *) sqDecoderNologicDescriptor->PortDescriptors);
        free((char **) sqDecoderNologicDescriptor->PortNames);
        free((LADSPA_PortRangeHint *) sqDecoderNologicDescriptor->PortRangeHints);
        free(sqDecoderNologicDescriptor);
    }
    sqDecoderNologicDescriptor = NULL;

}


