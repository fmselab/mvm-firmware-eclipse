#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4
using namespace std;

// main method that runs the desired test cases
int mmmain( int argc, char* argv[] ) {
  // global setup...

  int result = Catch::Session().run();

  // global clean-up...

  return result;
}
