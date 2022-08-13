#ifndef ARRAY_H
#define ARRAY_H

//Libs
#include "types.h"
#include <stdlib.h>


//Declarations of functions:
T_element A_create_array(size_t sz);
void      A_delete_array(T_element *e);
size_t    A_get_length(T_element e);
T_element A_get_element_at_index(size_t i, T_element e);
void      A_set_element_at_index(size_t i, T_element e);
#endif
