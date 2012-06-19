#include "stream.h"

static PaStream *stream;
VALUE cPortAudioStream;

static VALUE stream_init(VALUE self)
{
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 1;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = 
        Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err;
    err = Pa_OpenStream(&stream, NULL, &outputParameters, SAMPLE_RATE, 
            DEFAULT_BUFFER_SIZE, paClipOff, NULL, NULL);

    raise_if_error(err, ERROR_OPENING_STREAM);

    err = Pa_StartStream(stream);
    raise_if_error(err, ERROR_STARTING_STREAM);
    return self;
}

static VALUE stream_write(VALUE self, VALUE buffer)
{
    PaError err = Pa_WriteStream(stream, get_samples(buffer), DEFAULT_BUFFER_SIZE);
    raise_if_error(err, ERROR_WRITING_STREAM);

    return Qtrue;
}

static VALUE stream_close(VALUE self)
{
    PaError err;
    err = Pa_StopStream(stream);
    raise_if_error(err, ERROR_STOP_STREAM);

    err = Pa_CloseStream(stream);
    raise_if_error(err, ERROR_CLOSE_STREAM);

    Pa_Terminate();

    return Qtrue;
}

void Init_stream()
{
    cPortAudioStream = rb_define_class_under(mPortAudio, "Stream", rb_cObject);
    rb_define_method(cPortAudioStream, "initialize", stream_init, 0);
    rb_define_method(cPortAudioStream, "close", stream_close, 0);
    rb_define_method(cPortAudioStream, "write", stream_write, 1);
}


