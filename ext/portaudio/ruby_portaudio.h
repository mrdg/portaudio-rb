#include <ruby.h>
#include <portaudio.h>

#include <stream.h>
#include <buffer.h>

#define SAMPLE_RATE   (44100.0)
#define DEFAULT_BUFFER_SIZE  (1024)

#define ERROR_INITIALIZING    ("Error initializing PortAudio")
#define ERROR_OPENING_STREAM  ("Could not open audio stream")
#define ERROR_STARTING_STREAM ("Could not start audio stream")
#define ERROR_WRITING_STREAM  ("Could not write to audio stream")
#define ERROR_STOP_STREAM     ("Error while stopping stream")
#define ERROR_CLOSE_STREAM    ("Error while closing stream")

extern VALUE mPortAudio;
extern VALUE cPortAudioError;

void raise_if_error(PaError err, const char *message);

