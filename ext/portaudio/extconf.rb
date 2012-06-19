require 'mkmf'

HEADER_DIRS = ['/usr/local/include']
LIB_DIRS    = ['/usr/local/lib']

dir_config('portaudio', HEADER_DIRS, LIB_DIRS)

unless find_header('portaudio.h')
  abort "portaudio is missing.  please install portaudio"
end

unless find_library('portaudio', 'Pa_Initialize')
  abort "libportaudio is missing.  please install libportaudio"
end

create_makefile('portaudio/portaudio')
