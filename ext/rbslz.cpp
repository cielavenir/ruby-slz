#include <rice/rice.hpp>

extern "C" {
#include "libslz/src/slz.h"
}

class slz_compressobj{
    slz_stream strm;
    std::string out;
    int outsize;
public:
    slz_compressobj(int level=1, int format=SLZ_FMT_DEFLATE): outsize(0){
        slz_init(&strm, level, format);
    }

	Rice::String compress(Rice::String obj){
		int tempoutsize = obj.length()+obj.length()/16;
        if(outsize < tempoutsize){
            outsize = tempoutsize;
            out.reserve(outsize);
        }
        //out.resize(tempoutsize);
        size_t written = 0;
		written = slz_encode(&strm, &out[0], obj.c_str(), obj.length(), 1);
        //out.resize(written);
        //return py::bytes(out.data(), written);
		return Rice::Builtin_Object<T_STRING>(Rice::detail::protect(rb_str_new, (const char*)out.data(), (long)written));
	}

	Rice::String flush(){
		int tempoutsize = 12;
        if(outsize < tempoutsize){
            outsize = tempoutsize;
            out.reserve(outsize);
        }
        //out.resize(tempoutsize);
        size_t written = 0;
		written = slz_finish(&strm, &out[0]);
        //out.resize(written);
        //return py::bytes(out.data(), written);
		return Rice::Builtin_Object<T_STRING>(Rice::detail::protect(rb_str_new, (const char*)out.data(), (long)written));
	}

};

extern "C"
void Init_slz()
{
	auto module = Rice::define_module("Slz")
	.const_set("SLZ_FMT_GZIP", Rice::detail::to_ruby((int)SLZ_FMT_GZIP))
    .const_set("SLZ_FMT_ZLIB", Rice::detail::to_ruby((int)SLZ_FMT_ZLIB))
    .const_set("SLZ_FMT_DEFLATE", Rice::detail::to_ruby((int)SLZ_FMT_DEFLATE))
	;

    Rice::define_class_under<slz_compressobj>(module,"Deflate")
      .define_constructor(Rice::Constructor<slz_compressobj, int, int>(), Rice::Arg("level")=1, Rice::Arg("format")=(int)SLZ_FMT_DEFLATE)
      .define_method("deflate", &slz_compressobj::compress)
	.define_method("flush", &slz_compressobj::flush)
	;
}
