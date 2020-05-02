# mvm-firmware-unittests

This is a temporary repository to compile and execute the MVM together with its unit tests.

For sw integration tests see: https://github.com/fmselab/mvm-firmware 

It contains the unit tests written for the classes of MVM above HAL, using catch2.  It is an eclipse project.
 
What you  need:

* pull the files. the firmware is a submodule: I had to remove some files to force the use the mock versions. 
When we will have a proper build system it will be easy. Some .cpp files are excluded from build. I added some includes.


* you need eclipse with the CDT (tool for C++ development) 

* you need a c++ compiler


works under windows (with cygwin or  mingw) 

No hardware is required, only the  software. The goal is to perform unit tests.

### coverage information

to collect the coverage information:

-fprofile-arcs -ftest-coverage --coverage  
