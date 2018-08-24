# CFPLAGS=-Wall -O3 -fPIC -msse -mfpmath=sse
CFPLAGS=-Wall -O3 -fPIC -msse -mfpmath=sse -ffast-math
# CFPLAGS=-Wall -g -fPIC 
CC=gcc
PLUGINDIR=/tmp/usr/lib64/ladspa

TARGETS=sq_decoder_nologic.so sq_decoder_shadow_vector.so hilbert_stereo_200taps.so \
	hilbert_stereo_800taps.so hilbert_stereo_2000taps.so hilbert_stereo_200taps_soxhack.so \
	hilbert_stereo_800taps_soxhack.so hilbert_stereo_2000taps_soxhack.so

all: $(TARGETS)

clean: 
	rm -f *.o *.so

sq_decoder_nologic.so: sq_decoder_nologic.c
	$(CC) $(CFPLAGS) -o sq_decoder_nologic.o -c sq_decoder_nologic.c
	$(LD) -o sq_decoder_nologic.so sq_decoder_nologic.o -shared

sq_decoder_shadow_vector.so: sq_decoder_shadow_vector.c
	$(CC) $(CFPLAGS) -o sq_decoder_shadow_vector.o -c sq_decoder_shadow_vector.c
	$(LD) -o sq_decoder_shadow_vector.so sq_decoder_shadow_vector.o -shared

hilbert_stereo_200taps.so: hilbert_stereo.c hilbert_stereo_200taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_200taps.h\" -o hilbert_stereo_200taps.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_200taps.so hilbert_stereo_200taps.o -shared

hilbert_stereo_800taps.so: hilbert_stereo.c hilbert_stereo_800taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_800taps.h\" -o hilbert_stereo_800taps.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_800taps.so hilbert_stereo_800taps.o -shared

hilbert_stereo_2000taps.so: hilbert_stereo.c hilbert_stereo_2000taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_2000taps.h\" -o hilbert_stereo_2000taps.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_2000taps.so hilbert_stereo_2000taps.o -shared

hilbert_stereo_200taps_soxhack.so: hilbert_stereo.c hilbert_stereo_200taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_200taps.h\" -DSOX_LADSPA_PLUGIN_HACK -o hilbert_stereo_200taps_soxhack.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_200taps_soxhack.so hilbert_stereo_200taps_soxhack.o -shared

hilbert_stereo_800taps_soxhack.so: hilbert_stereo.c hilbert_stereo_800taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_800taps.h\" -DSOX_LADSPA_PLUGIN_HACK -o hilbert_stereo_800taps_soxhack.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_800taps_soxhack.so hilbert_stereo_800taps_soxhack.o -shared

hilbert_stereo_2000taps_soxhack.so: hilbert_stereo.c hilbert_stereo_2000taps.h
	$(CC) $(CFPLAGS) -DHILBERT_STEREO_H=\"hilbert_stereo_2000taps.h\" -DSOX_LADSPA_PLUGIN_HACK -o hilbert_stereo_2000taps_soxhack.o -c hilbert_stereo.c
	$(LD) -o hilbert_stereo_2000taps_soxhack.so hilbert_stereo_2000taps_soxhack.o -shared

install: all
	(if [ -d $(PLUGINDIR) ]; then cp $(TARGETS) $(PLUGINDIR); else echo No plugins directory; false;fi)

uninstall: deinstall

deinstall:
	(cd $(PLUGINDIR); rm -f $(TARGETS))

