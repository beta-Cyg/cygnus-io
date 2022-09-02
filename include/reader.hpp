#ifndef READER_HPP
#define READER_HPP

namespace cygnus{
	template<typename T,const char* mode>
#if __cplusplus >= 202002L
	requires is_stream_type<T>/* and is_in_mode<mode>*/
#endif
	class reader:public io_base{
	private:
		std::FILE* ptr;
	public:
		reader()=delete;

		explicit reader(FILE* pos):ptr(pos){
			if(ptr!=stdin)throw io_exception("could not create non-std reader by constructor 'reader(FILE* pos)'");
			if(not in_mutex.lockedby(this))throw io_exception("stdin have had by another reader");
			in_mutex.lockby(this);
		}

		explicit reader(const std::string& pos){
			ptr=std::fopen(pos.c_str(),mode);
			if(ptr==nullptr)throw io_exception("open stream failed");
		}

		~reader(){
			if(std::fclose(ptr)!=0)
				throw io_exception("close stream failed");
			in_mutex.unlockby(this);
		}

		char read()const{
			if(not in_mutex.lockedby(this))throw io_exception("stdin have had by another reader");
			return std::fgetc(ptr);
		}

		char read(buffer<T>& buf,const size_t& n)const{
			char ch;
			for(size_t i=0;i<n;i++){
				ch=read();
				buf.push_back(ch);
				if(ch==EOF or ch=='\n')break;
			}
			return ch;
		}
	};
}

#endif
