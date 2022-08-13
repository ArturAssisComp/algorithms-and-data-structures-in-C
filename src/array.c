#include "types.h"
#include "array.h"
#include <stdlib.h>
#include <stdio.h>



//Definitions of functions:
T_element A_create_array(size_t sz)
/**
 * Description: This function creates a T_element of type array with fixed size 'sz' and returns it. 
 * After using, the user must call A_delete_array unless in the situation in which this T_element will 
 * be an T_element of another T_element that will be deleted. In this situation, it will be
 * automatically deleted while deleting the container with this T_element.
 * This function exits on fail.
 *
 * Input: size_t sz -> the size of the array. 
 *
 * Output: (T_element)
 */
{
	//Variables:
    T_element e = {.type = ARRAY};
	T_array *new_array;
	char *error_msg;
    int i;

	//Allocate memory:
	new_array = malloc(sizeof *new_array);

	if(!new_array)
	{
		error_msg = "Error while allocating memory for the T_array.";
		goto error;
	}

    //Allocate memory for the array itself:
    new_array->array = calloc(sz, sizeof *new_array->array);
    if(!new_array->array)
	{
		error_msg = "Error while allocating memory for the array.";
		goto error;
	}

	//Initialize the T_array:
	new_array->length = sz;
    for(i = 0; i < sz; i++) new_array->array[i].type = NULL_TYPE;

    //connect the array to the element:
    e.value.arr = new_array;

	return e;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

