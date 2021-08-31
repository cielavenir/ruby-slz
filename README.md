## slz

a (quick) binding for http://www.libslz.org/

```
require 'slz'

o = Slz::Deflate.new()
o.deflate('hello')
o.flush()
```

the stream is compatible with zlib deflate.
