## slz

a (quick) binding for http://www.libslz.org/

```
require 'slz'

o = Slz::Deflate.new()
o.deflate('hello')
o.flush()
```

the stream is compatible with zlib deflate.

## tested versions

- Ruby 2.3.7 + Rice 2.1.3
- Ruby 2.7.4 + Rice 4.0.2

other combinations might have build issues.
