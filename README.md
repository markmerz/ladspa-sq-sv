# ladspa-sq-sv
SQ Stereo/Quadraphonic decoder with shadow vector DES as LADSPA plugin.

"hilbert_stereo_####taps" plugins are modifications of SWH's "hilbert_1440" 
plugin, with more filter taps and two input channels. Those plugins are
responsible for 90-degrees phase shift necessary for SQ-decoding plugins.

"hilbert_stereo_####taps_soxhack" plugins are workaround over SoX v14.4.2
limitation with ladspa plugins: it requires that plugins have same amount
of outputs as inputs.

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

One way to use those plugins is with ecasound:
LADSPA_PATH=./ladspa-sq-sv ecasound -x -i sq-test-tones.flac \
    -el:hilbert_stereo_200taps -el:sq_decoder_shadow_vector -f:,4 -o test.wav

Example usage with SoX:

with audio interface with 4 input channels:

LADSPA_PATH=./ladspa-sq-sv sox -r 192k -t alsa hw:1 -t alsa hw:0 \
    ladspa -l hilbert_stereo_800taps_soxhack ladspa -l sq_decoder_shadow_vector

with sound card with 2 input channels:

LADSPA_PATH=./ladspa-sq-sv sox -r 48k -t alsa hw:1 -t alsa hw:0 \
    remix -m 1 2 0 0 ladspa -l hilbert_stereo_200taps_soxhack ladspa -l sq_decoder_shadow_vector

In general, feed encoded signal to hilbert-plugins, and hilbert_plugin output
to sq-decoder-plugin.

My setup consists of behringer u-phoria umc404hd audio interface and intel nuc
minicomputer. Turntable is connected to audio interface and minicomputer feeds
amplifier via hdmi connector. I experimented with raspberry pi3, it runs fine
with 48k samplerate but not with 96k nor 192k rates.

I'm quite happy with plugins current performance. I's sounds way better then those
hardware SQ decoders that i have listened: sony sqd-2020 and sqd-2050. It passes
test signals flawlessly. Directional separation for 8 cardinal directions 
is infinite. :)

This is for linux. My windows-programming skills are somewhat rusty for now..
It's should be trivial to port to windows and mac by someone who knows how
develop to those platforms.

-- 
With regards,
Markko Merzin <markko.merzin@gmail.com>

