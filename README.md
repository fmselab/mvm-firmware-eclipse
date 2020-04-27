# mvm-firmware-eclipse

this is a temporary repository to compile and execute the MVM in eclipse. 

What you  need:

* pull the files. the firmware is a submodule: I had to remove some files to force the use the mock versions. 
When we will have a proper build system it will be easy. Some .cpp files are excluded from build. I added some includes.


* you need eclipse with the CDT (tool for C++ development) 

* you need a c++ compiler

* boost test libraries are needed to compile and run the tests  


works under windows with cygwin. 

No hardware is required, only the  software. The goal is to perform unit tests.