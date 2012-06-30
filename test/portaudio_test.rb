require 'test/unit'
require 'portaudio'

class PortAudioTest < Test::Unit::TestCase

  def test_buffer_size
    size = 512
    buffer = PortAudio::Buffer.new(size)
    assert_equal buffer.size, size
  end

  def test_tone
    PortAudio.init
    stream = PortAudio::Stream.new
    buffer = PortAudio::Buffer.new

    time = 0.0
    step = 1.0 / PortAudio.sample_rate
    30.times do

      buffer.fill do
        sample = Math.sin(time * 2 * Math::PI * 440.0)
        time += step

        sample
      end

      stream.write buffer
    end

    stream.close

    print "\nDid you hear a sine wave? [ y / n ] "
    answer = gets
    assert_equal answer.strip, 'y'
  end

end
