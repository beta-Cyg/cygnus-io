#define SYNC_IO
#include"io.hpp"
#include<thread>

int main(){
	auto f=[](){
		for(int i=0;i<10;i++)
			cygnus::output("Mike\n");
	};
	std::thread(f).detach();
	std::thread(f).join();

	return 0;
}
