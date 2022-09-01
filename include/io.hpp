#ifndef IO
#define IO

#include<deque>
#include<string>
#include<cstdio>
#include<cstring>
//#include<iostream>
#include<concepts>
#include<exception>

#include<fmt/format.h>

#include"io_exception.hpp"
#include"io_concepts.hpp"
#include"io_base.hpp"
#include"io_mutex.hpp"
#include"io_functions.hpp"
#include"buffer.hpp"
#include"writer.hpp"
#include"reader.hpp"
#include"stream_base.hpp"
#include"stream.hpp"

namespace cygnus{
	template<typename T,const char* mode,const size_t buffer_size,typename... Args>
	auto& print(ostream<T,mode,buffer_size>& os,fmt::format_string<Args...>format,Args&&...v){
		//debug
		//std::cout<<fmt::format(format,v...);
		return os(fmt::format(format,v...));
	}
}

#endif
