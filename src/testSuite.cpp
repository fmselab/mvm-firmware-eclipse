#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4
using namespace std;

// main method that runs the desired test cases
int main( int argc, char* argv[] ) {
  // global setup...
	char *argvxcatch[] = {"CMC"};
	int argcxcatch = (int) ((sizeof(argvxcatch) / sizeof(argvxcatch[0]))) - 1;
	//int result = Catch::Session().run(argcxcatch, argvxcatch); // its does not work
	int result = Catch::Session().run();

  // global clean-up...

  return result;
}
