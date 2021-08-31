require 'bundler/setup'
#require 'rice'
require 'mkmf-rice'

$srcs = ['ext/rbslz.cpp', 'ext/libslz/src/slz.c']
$VPATH << 'ext' << 'ext/libslz/src'
create_makefile('slz')

