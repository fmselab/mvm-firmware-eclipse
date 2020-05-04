#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4
using namespace std;

// main method that runs the desired test cases
int main( int argc, char* argv[] ) {
  // global setup...
	char *argvxcatch[] = {argv[0], "[StateMachine]"};
	//int argcxcatch = (int) ((sizeof(argvxcatch) / sizeof(argvxcatch[0]))) - 1;
	//int result = Catch::Session().run(argcxcatch, argvxcatch); // its does not work
	//cout<<argc << " 0:" << argv[0] << "  1:" << argv[1] << endl;
	int result = Catch::Session().run(2,argvxcatch);

  // global clean-up...

  return result;
}
