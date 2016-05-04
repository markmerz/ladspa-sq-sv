# ladspa-sq-sv
SQ Stereo/Quadraphonic decoder with shadow vector DES as LADSPA plugin.

"hilbert_stereo_####taps" plugins are modifications of SWH's "hilbert_1440" 
plugin, with more filter taps and two input channels. Those plugins are
responsible for 90-degrees phase shift necessary for SQ-decoding plugins.

"sq_decoder_nologic" plugin is naive reference implementation for SQ-decoder.
It has no directional enhancements and is rough equivalent of early "no-logic"
decoders.

"sq_decoder_shadow_vector" is implementation of SQ directional enhancement
system "Decoder for quadraphonic playback" patented by Lynn T. Olson in 1977.
It seems by vague internet sources, that this system was never actually produced 
in seventies. This method seems to be extremely sensitive to phase-shift network
quality, specially in left-center right-center separation. Phase-shifting with
analogue components is complex (pun intended:) problem and can never reach 
accuracy which is easily available with now-days digital methods and
equipment.

My idea is to build dedicated SQ-decoder from intel nuc, gigabyte brix or 
similar, so called barebone computer. It should take input from high quality
usb sound card and give 4-channel output to hdmi output, which will be connected
to modern receiver. I haven't tried this setup yet, I'll update this readme when
i do. I'm still saving up for receiver and good speakers :)

One way to use those plugins is with ecasound:
LADSPA_PATH=./ladspa-sq-sv ecasound -x -i sq-test-tones.flac \
    -el:hilbert_stereo_200taps -el:sq_decoder_shadow_vector -f:,4 -o test.wav

In general, feed encoded signal to hilbert-plugins, and hilbert_plugin output
to sq-decoder-plugin.

This is for linux. My windows-programming skills are somewhat rusty for now..
It's should be trivial to port to windows and mac by someone who knows how
develop to those platforms.

-- 
With regards,
Markko Merzin <markko.merzin@gmail.com>

