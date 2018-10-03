
#ifdef SOX_LADSPA_PLUGIN_HACK

#define PLUGIN_ID 3833
#define PLUGIN_NAME "hilbert_stereo_200taps_soxhack"

#else

#define PLUGIN_ID 3830
#define PLUGIN_NAME "hilbert_stereo_200taps"

#endif

#define GAIN_ADJUST 0.6355
#define D_SIZE 256
#define NZEROS 200
#define LATENCY 99

static float xcoeffs[] = {
    +0.0008103736f, +0.0008457886f, +0.0009017196f, +0.0009793364f,
    +0.0010798341f, +0.0012044365f, +0.0013544008f, +0.0015310235f,
    +0.0017356466f, +0.0019696659f, +0.0022345404f, +0.0025318040f,
    +0.0028630784f, +0.0032300896f, +0.0036346867f, +0.0040788644f,
    +0.0045647903f, +0.0050948365f, +0.0056716186f, +0.0062980419f,
    +0.0069773575f, +0.0077132300f, +0.0085098208f, +0.0093718901f,
    +0.0103049226f, +0.0113152847f, +0.0124104218f, +0.0135991079f,
    +0.0148917649f, +0.0163008758f, +0.0178415242f, +0.0195321089f,
    +0.0213953037f, +0.0234593652f, +0.0257599469f, +0.0283426636f,
    +0.0312667947f, +0.0346107648f, +0.0384804823f, +0.0430224431f,
    +0.0484451086f, +0.0550553725f, +0.0633242001f, +0.0740128560f,
    +0.0884368322f, +0.1090816773f, +0.1412745301f, +0.1988673273f,
    +0.3326528346f, +0.9997730178f, -0.9997730178f, -0.3326528346f,
    -0.1988673273f, -0.1412745301f, -0.1090816773f, -0.0884368322f,
    -0.0740128560f, -0.0633242001f, -0.0550553725f, -0.0484451086f,
    -0.0430224431f, -0.0384804823f, -0.0346107648f, -0.0312667947f,
    -0.0283426636f, -0.0257599469f, -0.0234593652f, -0.0213953037f,
    -0.0195321089f, -0.0178415242f, -0.0163008758f, -0.0148917649f,
    -0.0135991079f, -0.0124104218f, -0.0113152847f, -0.0103049226f,
    -0.0093718901f, -0.0085098208f, -0.0077132300f, -0.0069773575f,
    -0.0062980419f, -0.0056716186f, -0.0050948365f, -0.0045647903f,
    -0.0040788644f, -0.0036346867f, -0.0032300896f, -0.0028630784f,
    -0.0025318040f, -0.0022345404f, -0.0019696659f, -0.0017356466f,
    -0.0015310235f, -0.0013544008f, -0.0012044365f, -0.0010798341f,
    -0.0009793364f, -0.0009017196f, -0.0008457886f, -0.0008103736f,
};

