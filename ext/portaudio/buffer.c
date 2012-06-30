#include <buffer.h>

VALUE cPortAudioBuffer;

struct SampleArray {
    float *samples;
    int size;
};

float *get_samples(VALUE buffer)
{
    struct SampleArray *s_array;
    Data_Get_Struct(buffer, struct SampleArray, s_array);
    return s_array->samples;
}

int get_buffer_size(VALUE buffer)
{
    struct SampleArray *s_array;
    Data_Get_Struct(buffer, struct SampleArray, s_array);
    return s_array->size;
}

VALUE buffer_size(VALUE buffer)
{
    return INT2NUM(get_buffer_size(buffer));
}

void free_buffer(void * p)
{
    struct SampleArray *s_array = (struct SampleArray *) p;
    free(s_array->samples);
    free(s_array);
}

VALUE buffer_new(int argc, VALUE * argv, VALUE class)
{
    if (argc > 1) {
        rb_raise(rb_eArgError, "Wrong number of arguments");
    }
    struct SampleArray *s_array = malloc(sizeof(struct SampleArray));

    if (argc == 0) {
        s_array->size = DEFAULT_BUFFER_SIZE;
    } else {
        s_array->size = NUM2INT(argv[0]);
    }

    s_array->samples = malloc(sizeof(float) * s_array->size);
    VALUE tdata = Data_Wrap_Struct(class, 0, free_buffer, s_array);
    rb_obj_call_init(tdata, 0, 0);

    return tdata;
}


VALUE buffer_fill(VALUE self)
{
    float *samples = get_samples(self);
    VALUE sample;
    int i;
    for (i = 0; i < get_buffer_size(self); i++) {
        sample = rb_yield(i);
        samples[i] = NUM2DBL(sample);
    }

    return self;
}


void Init_buffer()
{
    cPortAudioBuffer = rb_define_class_under(mPortAudio, "Buffer", rb_cObject);
    rb_define_singleton_method(cPortAudioBuffer, "new", buffer_new, -1);
    rb_define_method(cPortAudioBuffer, "fill", buffer_fill, 0);
    rb_define_method(cPortAudioBuffer, "size", buffer_size, 0);
}
