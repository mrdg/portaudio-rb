require 'rake/extensiontask'
require 'rake/testtask'

Rake::ExtensionTask.new('portaudio')

Rake::TestTask.new do |t|
  t.test_files = FileList['test/*_test.rb']
  t.verbose = true
end

Rake::Task[:test].prerequisites << :compile

task :default => [:clean, :test]
