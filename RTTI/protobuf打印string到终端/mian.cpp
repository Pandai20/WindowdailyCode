#include <iostream>

#include <map>
#include <string>
#include "test.pb.h"


int main()
{
	TEST::testrequest request;
	request.set_name("panda");
	request.add_waihao("帅哥");
	request.add_waihao("靓仔");
	request.add_waihao("大帅逼");
	std::cout << request.DebugString() << std::endl;



	return 0;
}
