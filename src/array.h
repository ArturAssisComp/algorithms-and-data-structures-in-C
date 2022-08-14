#ifndef ARRAY_H
#define ARRAY_H

//Libs
#include "types.h"
#include <stdlib.h>


//Declarations of functions:
T_element A_create_array(size_t sz);
void      A_delete_array(T_array **p_arr);
size_t    A_get_length(T_element e);
T_element A_get_element_at_index(size_t i, T_element e_array);
void      A_set_element_at_index(size_t i, T_element element, T_element e_array);
#endif

