#ifndef IO_EXCEPTION_HPP
#define IO_EXCEPTION_HPP

namespace cygnus{
	class io_exception:public std::exception{
	private:
		std::string What;
	public:
		io_exception()=delete;

		explicit io_exception(std::string&& _what):What(_what){}

		const char* what()const noexcept override{
			return What.c_str();
		}
	};
}

#endif
