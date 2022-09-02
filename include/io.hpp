#ifndef IO
#define IO

#include<deque>
#ifdef SYNC_IO
#include<mutex>
#endif
#include<string>
#include<cstdio>
#include<cstring>

#if __cplusplus >= 202002L
#include<concepts>
#endif

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

#endif
