#ifndef BUFFER_HPP
#define BUFFER_HPP

namespace cygnus{
	typedef unsigned char byte;

	template<typename T>
	using buffer=std::deque<T>;

	template<typename T>
	T get(buffer<T>& buf){
		T result=buf.front();
		buf.pop_front();
		return result;
	}

	template<typename T>
	void clear(buffer<T>& buf){
		while(is_ignorable(buf.front()) and not buf.empty())buf.pop_front();
	}
}

#endif
