# Issues with mocking

- generic_defintions.h file points to specific HW class
- HAL.h uses HARDWARE_TARGET_PLATFORM defined in generic_definitions.h
to include specific platform and create a HW_Vx. hwi variable. If this was passed in via constructor or in HAL::Init(), includes and hard-wiring could be avoided
- Clas HW doesn't contain only pure virtual functions, should be made into an interface

