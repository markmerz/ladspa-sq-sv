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
//#define OUTPUT_DEBUG1       8
//#define OUTPUT_DEBUG2       9
//#define OUTPUT_DEBUG3      10
//#define PORTCOUNT          11

static LADSPA_Descriptor* sqDecoderShadowVectorDescriptor = NULL;

typedef struct {
    float* buffer;
    unsigned long buffer_size;
    unsigned long current_pos;
    double sum;
} average_t;

float get_average(float sample, average_t* av_buf) {
    av_buf->sum = av_buf->sum - av_buf->buffer[av_buf->current_pos];
    av_buf->buffer[av_buf->current_pos] = sample;
    av_buf->sum = av_buf->sum + sample;

    av_buf->current_pos++;
    if (av_buf->current_pos == av_buf->buffer_size) {
        av_buf->current_pos = 0;
    }

    return (float) (av_buf->sum / (float) av_buf->buffer_size);
}

typedef struct {
    LADSPA_Data* input_left_i;
    LADSPA_Data* input_right_i;
    LADSPA_Data* input_left_j;
    LADSPA_Data* input_right_j;
    LADSPA_Data* output_left_front;
    LADSPA_Data* output_right_front;
    LADSPA_Data* output_left_back;
    LADSPA_Data* output_right_back;
//        LADSPA_Data* output_debug1;
//        LADSPA_Data* output_debug2;
//        LADSPA_Data* output_debug3;
    average_t* aCF_average;
    average_t* aCB_average;
    average_t* aLB_average;
    average_t* aRB_average;
    average_t* aLF_average;
    average_t* aRF_average;
} SqDecoderShadowVector;

const LADSPA_Descriptor* ladspa_descriptor(unsigned long index) {

    switch (index) {
        case 0:
            return sqDecoderShadowVectorDescriptor;
        default:
            return NULL;
    }
}

static void cleanupSqDecoderShadowVector(LADSPA_Handle instance) {
    SqDecoderShadowVector* plugin_data = (SqDecoderShadowVector*) instance;
   
    free(plugin_data->aCF_average->buffer);
    free(plugin_data->aCF_average);

    free(plugin_data->aCB_average->buffer);
    free(plugin_data->aCB_average);

    free(plugin_data->aLB_average->buffer);
    free(plugin_data->aLB_average);
    
    free(plugin_data->aRB_average->buffer);
    free(plugin_data->aRB_average);
    
    free(plugin_data->aLF_average->buffer);
    free(plugin_data->aLF_average);
    
    free(plugin_data->aRF_average->buffer);
    free(plugin_data->aRF_average);
    
    free(instance);
}

static void connectPortSqDecoderShadowVector(LADSPA_Handle instance, unsigned long port, LADSPA_Data *data) {
    SqDecoderShadowVector* plugin;

    plugin = (SqDecoderShadowVector *) instance;
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
//                    case OUTPUT_DEBUG1:
//                        plugin->output_debug1 = data;
//                        break;
//                    case OUTPUT_DEBUG2:
//                        plugin->output_debug2 = data;
//                        break;
//                    case OUTPUT_DEBUG3:
//                        plugin->output_debug3 = data;
//                        break;
    }
}

static LADSPA_Handle instantiateSqDecoderShadowVector(const LADSPA_Descriptor *descriptor, unsigned long s_rate) {
    SqDecoderShadowVector* plugin_data = (SqDecoderShadowVector*) calloc(1, sizeof (SqDecoderShadowVector));
    
    plugin_data->aCF_average = malloc(sizeof (average_t));
    unsigned long aCF_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aCF_average->buffer = calloc(aCF_average_buffer_len, sizeof (float));
    plugin_data->aCF_average->buffer_size = aCF_average_buffer_len;
    plugin_data->aCF_average->current_pos = 0;
    plugin_data->aCF_average->sum = 0;

    plugin_data->aCB_average = malloc(sizeof (average_t));
    unsigned long aCB_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aCB_average->buffer = calloc(aCB_average_buffer_len, sizeof (float));
    plugin_data->aCB_average->buffer_size = aCB_average_buffer_len;
    plugin_data->aCB_average->current_pos = 0;
    plugin_data->aCB_average->sum = 0;

    plugin_data->aLB_average = malloc(sizeof (average_t));
    unsigned long aLB_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aLB_average->buffer = calloc(aLB_average_buffer_len, sizeof (float));
    plugin_data->aLB_average->buffer_size = aLB_average_buffer_len;
    plugin_data->aLB_average->current_pos = 0;
    plugin_data->aLB_average->sum = 0;
    
    plugin_data->aRB_average = malloc(sizeof (average_t));
    unsigned long aRB_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aRB_average->buffer = calloc(aRB_average_buffer_len, sizeof (float));
    plugin_data->aRB_average->buffer_size = aRB_average_buffer_len;
    plugin_data->aRB_average->current_pos = 0;
    plugin_data->aRB_average->sum = 0;
    
    plugin_data->aLF_average = malloc(sizeof (average_t));
    unsigned long aLF_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aLF_average->buffer = calloc(aLF_average_buffer_len, sizeof (float));
    plugin_data->aLF_average->buffer_size = aLF_average_buffer_len;
    plugin_data->aLF_average->current_pos = 0;
    plugin_data->aLF_average->sum = 0;
    
    plugin_data->aRF_average = malloc(sizeof (average_t));
    unsigned long aRF_average_buffer_len = s_rate / 20; // 20 Hz
    plugin_data->aRF_average->buffer = calloc(aRF_average_buffer_len, sizeof (float));
    plugin_data->aRF_average->buffer_size = aRF_average_buffer_len;
    plugin_data->aRF_average->current_pos = 0;
    plugin_data->aRF_average->sum = 0;
    
    return (LADSPA_Handle) plugin_data;
}

static void runSqDecoderShadowVector(LADSPA_Handle instance, unsigned long sample_count) {
    SqDecoderShadowVector* plugin_data = (SqDecoderShadowVector*) instance;

    float input_left_i, input_right_i, input_left_j, input_right_j;
    float output_front_left, output_front_right, output_back_left, output_back_right;

    float x, aCF, aCB, x_s, x_ss, y, aLB, aRB, z, aLF, aRF;

    for (unsigned long c = 0; c < sample_count; c++) {
        input_left_i = plugin_data->input_left_i[c];
        input_right_i = plugin_data->input_right_i[c];
        input_left_j = plugin_data->input_left_j[c];
        input_right_j = plugin_data->input_right_j[c];

        /* Actual algorithm */
        aCF = 0.7 * (input_left_i + input_right_i);
        aCF = get_average(fabsf(aCF), plugin_data->aCF_average);

        aCB = 0.7 * (input_left_i - input_right_i);
        aCB = get_average(fabsf(aCB), plugin_data->aCB_average);

        x = (aCF - aCB) / (aCF + aCB);

        //FIXME: shaper circuits?
        if (x > 0) {
            x_s = 0;
        } else {
            x_s = -x;            
        }

        //FIXME: shaper circuits?
        if (x < 0) {
            x_ss = 0;
        } else {
            x_ss = -x;
        }

        aLB = fabsf(0.7 * input_left_j + 0.7 * input_right_i);
        aLB = get_average(aLB, plugin_data->aLB_average);        
        aRB = fabsf(0.7 * input_right_j + 0.7 * input_left_i);
        aRB = get_average(aRB, plugin_data->aRB_average); 
        
        if (aLB > aRB) {
            y = aRB / aLB;
        } else if (aLB < aRB) {
            y = -aLB / aRB;
        } else {
            y = 0;
        }
        y = -1 * (aLB - aRB) / (aLB + aRB);
        
        aLF = fabsf(input_left_i);
        aLF = get_average(aLF, plugin_data->aLF_average);
        aRF = fabsf(input_right_i);
        aRF = get_average(aRF, plugin_data->aRF_average);
        z = (aLF - aRF) / (aLF + aRF);

        output_front_left = 0.7 * (input_left_i + x_s * (0.5 * input_right_i - 0.5 * input_left_i) + (((1 + y) / 2) * (-1) * input_right_j) + ((1 - y) / 2) * input_right_j);
        output_front_right = 0.7 * (input_right_i + x_s * (0.5 * input_left_i - 0.5 * input_right_i) + (((1 + y) / 2) * input_left_j) + ((1 - y) / 2) * (-1) * input_left_j);

        output_back_left = -x_ss * (0.25 * input_left_i + 0.25 * input_right_i - 0.25 * input_left_j - 0.25 * input_right_j) - ((1 + z) / 2) * input_right_i + ((1 - z) / 2) * input_left_j;
        output_back_right = -x_ss * (0.25 * input_left_j + 0.25 * input_right_j - 0.25 * input_left_i - 0.25 * input_right_i) - ((1 + z) / 2) * input_right_j + ((1 - z) / 2) * input_left_i;

        /* End of actual algorith */

        plugin_data->output_left_front[c] = output_front_left;
        plugin_data->output_right_front[c] = output_front_right;
        plugin_data->output_left_back[c] = output_back_left;
        plugin_data->output_right_back[c] = output_back_right;

//                plugin_data->output_debug1[c] = x;
//                plugin_data->output_debug2[c] = y;
//                plugin_data->output_debug3[c] = z;

    }
}

void __attribute__((constructor)) swh_init() {
    char **port_names;
    LADSPA_PortDescriptor *port_descriptors;
    LADSPA_PortRangeHint *port_range_hints;

    sqDecoderShadowVectorDescriptor = (LADSPA_Descriptor*) malloc(sizeof (LADSPA_Descriptor));

    if (sqDecoderShadowVectorDescriptor) {
        sqDecoderShadowVectorDescriptor->UniqueID = 3828;
        sqDecoderShadowVectorDescriptor->Label = "sq_decoder_shadow_vector";
        sqDecoderShadowVectorDescriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
        sqDecoderShadowVectorDescriptor->Name = "SQ decoder with shadow vector directional enhancement";
        sqDecoderShadowVectorDescriptor->Maker = "Markko Merzin <markko.merzin@gmail.com>";
        sqDecoderShadowVectorDescriptor->Copyright = "GPL";
        sqDecoderShadowVectorDescriptor->PortCount = PORTCOUNT;

        port_descriptors = (LADSPA_PortDescriptor *) calloc(PORTCOUNT, sizeof (LADSPA_PortDescriptor));
        sqDecoderShadowVectorDescriptor->PortDescriptors = (const LADSPA_PortDescriptor *) port_descriptors;

        port_range_hints = (LADSPA_PortRangeHint *) calloc(PORTCOUNT, sizeof (LADSPA_PortRangeHint));
        sqDecoderShadowVectorDescriptor->PortRangeHints = (const LADSPA_PortRangeHint *) port_range_hints;

        port_names = (char **) calloc(PORTCOUNT, sizeof (char*));
        sqDecoderShadowVectorDescriptor->PortNames = (const char **) port_names;

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

        //                port_descriptors[OUTPUT_DEBUG1] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        //                port_names[OUTPUT_DEBUG1] = "Debug1 output, whatever its used for currently";
        //                port_range_hints[OUTPUT_DEBUG1].HintDescriptor = 0;
        //                
        //                port_descriptors[OUTPUT_DEBUG2] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        //                port_names[OUTPUT_DEBUG2] = "Debug2 output, whatever its used for currently";
        //                port_range_hints[OUTPUT_DEBUG2].HintDescriptor = 0;
        //                
        //                port_descriptors[OUTPUT_DEBUG3] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
        //                port_names[OUTPUT_DEBUG3] = "Debug3 output, whatever its used for currently";
        //                port_range_hints[OUTPUT_DEBUG3].HintDescriptor = 0;

        sqDecoderShadowVectorDescriptor->activate = NULL;
        sqDecoderShadowVectorDescriptor->cleanup = cleanupSqDecoderShadowVector;
        sqDecoderShadowVectorDescriptor->connect_port = connectPortSqDecoderShadowVector;
        sqDecoderShadowVectorDescriptor->deactivate = NULL;
        sqDecoderShadowVectorDescriptor->instantiate = instantiateSqDecoderShadowVector;
        sqDecoderShadowVectorDescriptor->run = runSqDecoderShadowVector;
        sqDecoderShadowVectorDescriptor->run_adding = NULL;
        sqDecoderShadowVectorDescriptor->set_run_adding_gain = NULL;
    }
}

void __attribute__((destructor)) swh_fini() {
    if (sqDecoderShadowVectorDescriptor) {
        free((LADSPA_PortDescriptor *) sqDecoderShadowVectorDescriptor->PortDescriptors);
        free((char **) sqDecoderShadowVectorDescriptor->PortNames);
        free((LADSPA_PortRangeHint *) sqDecoderShadowVectorDescriptor->PortRangeHints);
        free(sqDecoderShadowVectorDescriptor);
    }
    sqDecoderShadowVectorDescriptor = NULL;

}


