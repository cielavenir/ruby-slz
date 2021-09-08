# coding: utf-8
#require './slz'

Gem::Specification.new do |spec|
  spec.name          = "slz"
  spec.version       = '0.0.0.1' #Slz::VERSION
  spec.authors       = ["cielavenir"]
  spec.email         = ["cielartisan@gmail.com"]
  spec.description   = "a (quick) binding for http://www.libslz.org/"
  spec.summary       = "a (quick) binding for libslz"
  spec.homepage      = "http://github.com/cielavenir/ruby-slz"
  spec.license       = "MIT"

  spec.files         = `git ls-files`.split($/) + [
    *['ext/libslz/src/slz.c', 'ext/libslz/src/slz.h', 'ext/libslz/src/tables.h'],
    "LICENSE",
    "README.md",
    #"CHANGELOG.md",
  ]
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.extensions    = ["extconf.rb"]
  spec.require_paths = ["lib"]

  spec.add_dependency "rice"
  #spec.add_development_dependency "bundler", ">= 1.0"
  #spec.add_development_dependency "rake"
  spec.add_development_dependency "rspec"
end
