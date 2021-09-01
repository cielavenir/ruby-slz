#if RICE_VERSION >= 40000
#include <rice/rice.hpp>
#else
#include <rice/Class.hpp>
#include <rice/Constructor.hpp>
#include <rice/Module.hpp>
#include <rice/String.hpp>
#endif

extern "C" {
#include "libslz/src/slz.h"
}

#if RICE_VERSION >= 30000
#define RICE_PROTECT Rice::detail::protect
#define RICE_TORUBY Rice::detail::to_ruby
#define RICE_CTOR_PARENSL
#define RICE_CTOR_PARENSR
#else
#define RICE_PROTECT Rice::protect
#define RICE_TORUBY to_ruby
#define RICE_CTOR_PARENSL (
#define RICE_CTOR_PARENSR )
#endif

inline Rice::String MakeStringFromBuffer(const char *ptr, long len){
	return Rice::Builtin_Object<T_STRING>(RICE_PROTECT(rb_str_new, ptr, len));
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
		return MakeStringFromBuffer(out.data(), written);
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
		return MakeStringFromBuffer(out.data(), written);
	}
};

extern "C"
void Init_slz()
{
	auto module = Rice::define_module("Slz")
	.const_set("SLZ_FMT_GZIP", RICE_TORUBY((int)SLZ_FMT_GZIP))
	.const_set("SLZ_FMT_ZLIB", RICE_TORUBY((int)SLZ_FMT_ZLIB))
	.const_set("SLZ_FMT_DEFLATE", RICE_TORUBY((int)SLZ_FMT_DEFLATE))
	;

	Rice::define_class_under<slz_compressobj>(module,"Deflate")
	.define_constructor(Rice::Constructor<slz_compressobj, int, int>(), RICE_CTOR_PARENSL Rice::Arg("level")=1, Rice::Arg("format")=(int)SLZ_FMT_DEFLATE RICE_CTOR_PARENSR)
	.define_method("deflate", &slz_compressobj::compress)
	.define_method("flush", &slz_compressobj::flush)
	;
}
