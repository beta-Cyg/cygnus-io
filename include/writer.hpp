#ifndef WRITER_HPP
#define WRITER_HPP

namespace cygnus{
	template<typename T,const char* mode>
#if __cplusplus >= 202002L
	requires is_stream_type<T>/* and is_out_mode<mode>*/
#endif
	class writer:public io_base{
	private:
		std::FILE* ptr;
	public:
		writer()=delete;

		explicit writer(FILE* pos):ptr(pos){
			if(ptr!=stdout)throw io_exception("could not create non-std writer by constructor 'writter(FILE* pos)'");
			if(not out_mutex.lockedby(this))throw io_exception("stdout have had by another writer");
			out_mutex.lockby(this);
		}

		explicit writer(const std::string& pos){
			ptr=std::fopen(pos.c_str(),mode);
			if(ptr==nullptr)throw io_exception("open stream failed");
		}

		~writer(){
			if(std::fclose(ptr)!=0)
					throw io_exception("close stream failed");
			out_mutex.unlockby(this);
		}

		T write(const T& ch)const{
			if(not out_mutex.lockedby(this))
				throw io_exception("stdout have had by another writer");
			return std::fputc(ch,ptr);
		}

		T write(const buffer<T>& buf)const{
			int result;
			for(auto& ch:buf){
				result=write(ch);
				if(result==EOF)
					return result;
			}
			return result;
		}
	};
}

#endif
