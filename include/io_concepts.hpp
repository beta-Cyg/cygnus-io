#ifndef IO_CONCEPTS_HPP
#define IO_CONCEPTS_HPP

namespace cygnus{
	typedef unsigned char byte;

	typedef char status_type;

	constexpr char
		in[]{"r"},
		bin[]{"r+b"},
		win[]{"r, ccs=utf-8"},
		out[]{"w"},
		bout[]{"w+b"},
		wout[]{"w, ccs=utf-8"},
		add[]{"a"},
		wadd[]{"a, ccs=utf-8"},
		badd[]{"a+b"},
		xout[]{"w+x"},
		wxout[]{"w+x, ccs=utf-8"},
		err[]{"stderr"};
	
	constexpr size_t max_buffer_size=1048576;

	constexpr bool is_same_str(const char* s1,const char* s2){
		int item=0;
		while(true){
			if(s1[item]=='\0' or s2[item]=='\0')
				return s1[item]==s2[item];
			if(s1[item]!=s2[item])
				return false;
			++item;
		}
		return true;
	}

	template<const size_t buffer_size>
	concept is_under_limit=buffer_size<=max_buffer_size;

	template<typename T>
	concept is_stream_type=
		std::same_as<T,char> or
		std::same_as<T,wchar_t> or
		std::same_as<T,byte>;
/*
	template<const char* mode>
	concept is_in_mode=
		is_same_str(mode,in) or
		is_same_str(mode,"r+") or
		is_same_str(mode,bin) or
		is_same_str(mode,"r+b");
	
	template<const char* mode>
	concept is_out_mode=
		is_same_str(mode,out) or
		is_same_str(mode,"w+") or
		is_same_str(mode,bout) or
		is_same_str(mode,"w+b") or
		is_same_str(mode,xout) or
		is_same_str(mode,"w+x") or
		is_same_str(mode,add) or
		is_same_str(mode,"a+") or
		is_same_str(mode,badd) or
		is_same_str(mode,"a+b");
*/
}

#endif
