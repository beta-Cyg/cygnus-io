#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

namespace cygnus{
	inline bool is_ignorable(char ch){
		return ch==' ' or ch=='\0' or ch=='\r' or ch=='\n' or ch=='\t';
	}
}

#endif
