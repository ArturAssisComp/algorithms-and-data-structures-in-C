#include "types.h"
#include "array.h"
#include <stdlib.h>
#include <stdio.h>

/*
T_element A_create_array(size_t sz);
void      A_delete_array(T_array *e);
size_t    A_get_length(T_element e);
T_element A_get_element_at_index(size_t i, T_element e);
void      A_set_element_at_index(size_t i, T_element e);
*/


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


void A_delete_array(T_array **p_arr)
/*
 * Description: this function must be called to delete an T_array pointed by *p_arr.
 * It deallocates the memory that was allocated for that array. After deleting the array,
 * the pointer *p_arr is pointed to NULL;
 */
{
    int i = 0;
	char *error_msg;
    T_element tmp_e;

    T_array *arr = *p_arr;
    *p_arr = NULL;

    //Free each element
    for(; i < arr->length; i++)
    {
        tmp_e = arr->array[i];
        if(tmp_e.type != NULL_TYPE) T_free_element(&tmp_e);
    }

    free(arr->array);
    free(arr);
error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

size_t A_get_length(T_element e)
/**
 * Description: this function returns the length of the element of type array.
 * If the element is not an array, an error is raised.
 */
{
	//Variables:
	char *error_msg;

    if(e.type != ARRAY)
    {
        error_msg = "This function can not be called to an element that is not array.";
        goto error;
    }

	return e.value.arr->length;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

T_element A_get_element_at_index(size_t i, T_element e)
/*
 * Description: this function returns the element in the position i
 * from the T_element of type ARRAY "e". If the element is not of type
 * ARRAY, an error is raised and the function exits.
 * Index i must be between 0 <= i < length of 'e';
 */
{
	//Variables:
    T_element result;
	char *error_msg;

    if(e.type != ARRAY)
    {
        error_msg = "This function can not be called to an element that is not array.";
        goto error;
    }

    if(i >= e.value.arr->length)
    {
        error_msg = "Index out of bounds.";
        goto error;
    }

	return e.value.arr->array[i];

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}
