#ifndef CTEST_H
#define CTEST_H

#include "interface.h"

extern "C" {

void* init();
Robot_output run(void*,Robot_input);
void destroy(void*);

}

#endif
