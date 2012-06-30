#ifndef RUBY_PORTAUDIO_BUFFER
#define RUBY_PORTAUDIO_BUFFER

#include <ruby_portaudio.h>

void Init_buffer();

float * get_samples();
int get_buffer_size(VALUE buffer);

#endif
