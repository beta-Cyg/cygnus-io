#define SYNC_IO
#include"../include/io.hpp"
#include<numbers>

long double a{std::numbers::pi};

int main(){
	cygnus::output.format("{:.20}\n",a);

	return 0;
}
