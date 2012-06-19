#include <buffer.h>

VALUE cPortAudioBuffer;

struct SampleArray {
    float samples[DEFAULT_BUFFER_SIZE];
};


float *get_samples(VALUE buffer)
{
    struct SampleArray *s_array;
    Data_Get_Struct(buffer, struct SampleArray, s_array);
    return s_array->samples;
}


VALUE buffer_new(VALUE class)
{
    struct SampleArray *s_array = malloc(sizeof(struct SampleArray));
    VALUE tdata = Data_Wrap_Struct(class, 0, free, s_array);
    rb_obj_call_init(tdata, 0, 0);

    return tdata;
}


VALUE buffer_fill(VALUE self)
{
    float *samples = get_samples(self);
    VALUE sample;
    int i;
    for (i = 0; i < DEFAULT_BUFFER_SIZE; i++) {
        sample = rb_yield(i);
        samples[i] = NUM2DBL(sample);
    }

    return self;
}


void Init_buffer()
{
    cPortAudioBuffer = rb_define_class_under(mPortAudio, "Buffer", rb_cObject);
    rb_define_singleton_method(cPortAudioBuffer, "new", buffer_new, 0);
    rb_define_method(cPortAudioBuffer, "fill", buffer_fill, 0);
}
