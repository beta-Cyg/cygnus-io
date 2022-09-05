//#define SYNC_IO
#include<io.hpp>
#include<numbers>

long double a{std::numbers::pi};

int main(){
	cygnus::output.format("{:.20}",a);

	return 0;
}
