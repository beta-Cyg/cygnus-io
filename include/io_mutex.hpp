#ifndef LOCK_HPP
#define LOCK_HPP

namespace cygnus{
	class io_mutex{
	private:
		io_base* obj;/*mutex is locked by the object the pointer points*/
	public:
		bool lockby(io_base* ptr){
			if(obj!=nullptr and obj!=ptr/*it means mutex hax been locked*/)
				return false;
			obj=ptr;
			return true;
		}

		bool unlockby(io_base* ptr){
			if(obj!=nullptr and obj!=ptr)return false;
			obj=nullptr;
			return true;
		}

		bool lockedby(io_base* ptr)const{
			return obj==ptr or obj==nullptr;
		}
	};

	static io_mutex in_mutex,out_mutex;
}

#endif
