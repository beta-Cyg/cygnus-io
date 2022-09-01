#ifndef STREAM_HPP
#define STREAM_HPP

/*
 * todo
 * sync_stream
 * winput woutput (wide char)
 * binput boutput (binary type) (maybe support)
*/

namespace cygnus{
	template<typename value_type=char,const char* Mode=in,const size_t buffer_size=1024>
	requires is_under_limit<buffer_size>
	class istream:public stream_base{
	private:
		buffer<value_type>buf;
		reader<value_type,Mode>Reader;
	public:
		istream():Reader(stdin){}

		explicit istream(const std::string& pos):Reader(pos){}
	private:
		status_type flush(){
			buf.clear();
			return Reader.read(buf,buffer_size);
		}
	public:
		auto& operator()(char& v){
			clear(buf);
			while(buf.empty()){
				flush();
				clear(buf);
			}
			v='\0';
			while(is_ignorable(v)){
				v=get(buf);
				if(buf.empty())
					flush();
			}
			return *this;
		}

		auto& operator()(int& v){
			clear(buf);
			while(buf.empty()){
				flush();
				clear(buf);
			}
			v=0;
			bool is_front=true;
			bool is_number_front=false;
			bool is_negative=false;
			while(true){
				auto tmp=get(buf);
				if(is_front){
					if(tmp=='-'){
						is_negative=true;
						is_number_front=true;
						is_front=false;
						continue;
					}
					else if(not std::isdigit(tmp)){
						buf.push_front(tmp);
						break;
					}
					is_front=false;
				}
				if(is_number_front){
					if(not std::isdigit(tmp)){
						buf.push_front(tmp);
						if(is_negative)
							buf.push_front('-');
						break;
					}
					is_number_front=false;
				}
				if(not std::isdigit(tmp)){
					buf.push_front(tmp);
					break;
				}
				v+=tmp-'0';
				v*=10;
				if(buf.empty())
					flush();
			}
			v/=10;
			if(is_negative)v*=-1;
			return *this;
		}

		auto& operator()(std::string& v){
			clear(buf);
			while(buf.empty()){
				flush();
				clear(buf);
			}
			v.clear();
			do{
				v.push_back(get(buf));
				if(buf.empty() and v.size()==1 and is_ignorable(v.back())){
					v.pop_back();
					flush();
					continue;
				}
			}while(not is_ignorable(v.back()));
			v.pop_back();
			return *this;
		}

		template<typename Head,typename...Rest>
		auto& operator()(Head& head,Rest&...rest){
			operator()(head);
			return operator()(rest...);
		}

		//debug
		std::basic_string<value_type> getbuf(){
			if(buf.empty())return "[null]";//debug
			std::basic_string<value_type> result;
			for(auto i:buf)
				result.push_back(i);
			return result;
		}

		const char* mode(){
			return Mode;
		}
	};

	template<typename value_type=char,const char* Mode=out,const size_t buffer_size=1024>
	requires is_under_limit<buffer_size>
	class ostream:public stream_base{
	private:
		buffer<value_type>buf;
		writer<value_type,Mode>Writer;

		bool fulled(){
			return buf.size()>=buffer_size;
		}
	public:
		ostream():Writer(stdout){}

		explicit ostream(const std::string& pos):Writer(pos){}

		~ostream(){
			flush();
		}

		status_type flush(){
			status_type result=Writer.write(buf);
			buf.clear();
			return result;
		}

		auto& operator()(){
			flush();
			return *this;
		}

		auto& operator()(const char& v){
			if(fulled())flush();
			if(buf.size()<buffer_size)
				buf.push_back(v);
			return *this;
		}

		auto& operator()(const int& v){
			if(fulled())flush();
			std::basic_string<value_type> strv=std::to_string(v);
			if(buf.size()+strv.size()>buffer_size)
				flush();
			for(auto i:strv)
				buf.push_back(i);
			return *this;
		}

		auto& operator()(const double& v){
			if(fulled())flush();
			std::basic_string<value_type> strv=std::to_string(v);
			if(buf.size()+strv.size()>buffer_size)
				flush();
			for(auto i:strv)
				buf.push_back(i);
			return *this;
		}

		auto& operator()(const char* v){
			if(fulled())flush();
			if(buf.size()+std::strlen(v)>buffer_size)
				flush();
			for(std::size_t i=0;i<std::strlen(v);i++)
				buf.push_back(v[i]);
			return *this;
		}

		auto& operator()(const std::string& v){
			//debug
			//std::cout<<"v:"<<v<<std::endl;
			//std::cout<<"buf:"<<getbuf()<<std::endl;
			if(fulled())flush();
			if(buf.size()+v.size()>buffer_size)
				flush();
			for(auto i:v)
				buf.push_back(i);
			return *this;
		}

		template<typename Head,typename... Rest>
		auto& operator()(const Head& head,const Rest&... rest){
			operator()(head);
			/*debug*/
			//std::cout<<"t:"<<t<<" buf:"<<getbuf()<<std::endl;
			return operator()(rest...);
		}

		template<typename...Args>
		auto& format(fmt::format_string<Args...> fmt,Args&&...v){
			return operator()(fmt::format(fmt,v...));
		}

		//debug
		std::basic_string<value_type> getbuf(){
			if(buf.empty())return "[null]";
			std::basic_string<value_type> result;
			for(auto i:buf)
				result.push_back(i);
			return result;
		}

		const char* mode(){
			return Mode;
		}
	};
	
	static istream input;

	static ostream output;

	//static ostream error(stderr); :compile error

	//cygnus::io doesn't support standard error stream with buffer
}

#endif
