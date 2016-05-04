
CFPLAGS=-Wall -O3 -fPIC 
# CFPLAGS=-Wall -g -fPIC 
CC=gcc
PLUGINDIR=/usr/lib64/ladspa

all: sq_decoder_nologic.so sq_decoder_shadow_vector.so hilbert_stereo_200taps.so hilbert_stereo_800taps.so hilbert_stereo_2000taps.so

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

install: all
	(if [ -d $(PLUGINDIR) ]; then cp sq_decoder_nologic.so sq_decoder_shadow_vector.so $(PLUGINDIR); else echo No plugins directory; false;fi)

uninstall: deinstall

deinstall:
	rm -f $(PLUGINDIR)/sq_decoder_nologic.so $(PLUGINDIR)/sq_decoder_shadow_vector.so

