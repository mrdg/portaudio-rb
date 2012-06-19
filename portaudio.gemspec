Gem::Specification.new do |s|
  s.name    = 'portaudio'
  s.version = '0.0.1'
  s.summary     = "PortAudio Ruby C extension"

  s.authors  = ["Menno de Gier"]
  s.email    = 'mrdegier@gmail.com'
  s.homepage = 'https://github.com/mrdg/portaudio'

  s.add_development_dependency 'rake-compiler'
  s.files         = `git ls-files`.split($\)
  s.executables   = s.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  s.test_files    = s.files.grep(%r{^(test|spec|features)/})
  s.require_paths = ["lib"]
  s.extensions = ["ext/portaudio/extconf.rb"]
end
