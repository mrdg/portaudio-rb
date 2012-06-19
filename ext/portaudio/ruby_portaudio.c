#include "ruby_portaudio.h"

VALUE mPortAudio;
VALUE cPortAudioError;

void raise_if_error(PaError err, const char *message)
{
    if (err != paNoError) {
        rb_raise(cPortAudioError, "%s", message);
    }
}

static VALUE init() 
{
    PaError err = Pa_Initialize();
    raise_if_error(err, ERROR_INITIALIZING);

    return Qtrue;
}

static VALUE sample_rate()
{
    return rb_float_new(SAMPLE_RATE);
}


void Init_portaudio() 
{
    mPortAudio = rb_define_module("PortAudio");
    cPortAudioError = rb_define_class_under(mPortAudio, "Error", rb_eException);
    rb_define_singleton_method(mPortAudio, "init", init, 0);
    rb_define_singleton_method(mPortAudio, "sample_rate", sample_rate, 0);

    Init_stream();
    Init_buffer();
}
