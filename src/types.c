#include "types.h"
#include "array.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

//Static functions declarations 
static size_t get_element_string_representation_size(T_element e);

//Function definitions:
void T_print(char *prefix, T_element e, char *suffix)
{
    char *tmp_str;
    tmp_str = T_to_string(e);
    printf("%s%s%s", prefix, tmp_str, suffix);
    free(tmp_str);
}

char *T_to_string(T_element e)
/*
 * Description: this function returns a allocated string with the string representation
 * for the element 'e'. The user must free the returned string after using it.
 * This function has a debugging purpose.
 */
{
	//Variables:
	char *result;
	char *error_msg;
    char *tmp_str;
    size_t string_size = get_element_string_representation_size(e);
    T_element tmp_element;
    int i;

    /* Allocate memory for the string representation */
    result = calloc(string_size + 1, sizeof *result);
    if (!result)
    {
        error_msg = "calloc: error while allocating memory for string_size";
        goto error;
    }


	//Compare the values:
	switch (e.type)
	{
		case UNSIGNED_INTEGER:
            snprintf(result, string_size + 1, "%u", e.value.u_i);
			break;
		case INTEGER:
            snprintf(result, string_size + 1, "%d", e.value.i);
			break;
		case FLOATING_POINT:
            snprintf(result, string_size + 1, "%g", e.value.f_p);
			break;
		case BOOL:
            snprintf(result, string_size + 1, "%s", e.value.b ? "true":"false");
			break;
		case CHAR:
            snprintf(result, string_size + 1, "\'%c\'", e.value.c);
			break;
		case STRING:
            snprintf(result, string_size + 1, "\"%s\"", e.value.str->str);
			break;
		case ARRAY:
            result[0] = '\0';
            strcat(result, "[");
            if(A_get_length(e) > 0)
            {
                tmp_element = A_get_element_at_index(0, e);
                tmp_str = T_to_string(tmp_element);
                strncat(result, tmp_str, string_size - strlen(result));
                free(tmp_str);
                tmp_str = NULL;
            }
            for(i = 1; i < A_get_length(e); i++)
            {
                strcat(result, ", ");
                tmp_element = A_get_element_at_index(i, e);
                tmp_str = T_to_string(tmp_element);
                strncat(result, tmp_str, string_size - strlen(result));
                free(tmp_str);
                tmp_str = NULL;
            }
            strcat(result, "]");
            break;
		case NULL_TYPE:
            snprintf(result, string_size + 1, "NULL");
			break;
		default:
			error_msg = "T_to_string() is not implemented for the desired type.";
			goto error;
			break;
			
	}
	return result;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

bool T_is_equal(T_element e1, T_element e2)
/**
 * Description: This function returns true if e1 is equal to e2. It returns false 
 * otherwise.
 *
 * Input: (T_element) e1, e2 --> Elements that will be compared for equality.
 *
 * Output: (bool) --> Boolean that says if e1 is equal to e2.
 */
{
	//Variables:
	bool result;
	char *error_msg;
    int i;

	//Check if they have different type:
	if (e1.type != e2.type) return false;

	//Compare the values:
	switch (e1.type)
	{
		case UNSIGNED_INTEGER:
			result = (e1.value.u_i == e2.value.u_i);
			break;
		case INTEGER:
			result = (e1.value.i == e2.value.i);
			break;
		case CHAR:
			result = (e1.value.c == e2.value.c);
			break;
		case STRING:
			result = (strcmp(e1.value.str->str, e2.value.str->str) == 0);
			break;
		case BOOL:
			result = (e1.value.b == e2.value.b);
			break;
		case ARRAY:
            if (A_get_length(e1) != A_get_length(e2)) result = false;
            else 
            {
                result = true;
                for(i = 0; i < A_get_length(e1); i++)
                {
                    if(!T_is_equal(A_get_element_at_index(i, e1), A_get_element_at_index(i, e2)))
                    {
                        result = false;
                        break;
                    }
                }
            }
            break;
		case NULL_TYPE:
			result = true;
			break;
		case FLOATING_POINT:
		case DICT:
			error_msg = "Comparison for equality is not implemented.";
			goto error;
			break;
		default:
			break;
			
	}
	return result;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}


void T_free_element(T_element *e)
/*
 * Description: this function must be called after using a group element to free
 * the allocated memory. For individual elements, it is optional.
 */
{
	//Variables:
	char *error_msg;

	//Free the values:
	switch (e->type)
	{
        //Individual elements:
		case UNSIGNED_INTEGER:
		case INTEGER:
		case FLOATING_POINT:
		case BOOL:
		case CHAR:
			e->type = NULL_TYPE;
			break;
        //Group elements:
        /*
		case STRING:
        */
		case ARRAY:
			A_delete_array(&(e->value.arr));
			e->type = NULL_TYPE;
			if(e->value.arr)
			{
				error_msg = "Problems while deleting the array.";
				goto error;
			}
			break;
        /*
		case VECTOR:
		case LINKED_LIST:
		case STACK:
		case DICT:
		case SET:
        */
		case NULL_TYPE:
			error_msg = "Calling T_free_element for a NULL_TYPE element.";
			goto error;
			break;
		default:
			error_msg = "Calling T_free_element for an element with unkown type.";
			goto error;
			break;
	}

result:
	return;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

/*Static functions definitions*/
static size_t get_element_string_representation_size(T_element e)
/*
 * Description: this function calculates the number of chars necessary to represent
 * 'e' as a string.
 */
{
	//Variables:
	size_t result = 0;
	char *error_msg;
    int i;

	//Compare the values:
	switch (e.type)
	{
		case UNSIGNED_INTEGER:
            if(e.value.u_i == 0) result = 1;
            else result = (size_t) log10((double) e.value.u_i) + 1;
			break;
		case INTEGER:
            if(e.value.i == 0) result = 1;
            else result = (size_t) log10((double) (e.value.i > 0 ? e.value.i : - e.value.i)) + 2;
			break;
		case FLOATING_POINT:
			result = 40; //Guaranteedly greater than the maximum
			break;
		case BOOL:
			result = sizeof "false" - 1;
			break;
		case CHAR:
			result = 3;
			break;
		case STRING:
			result = 2 + e.value.str->length;
			break;
		case ARRAY:
            result = 0;
            for(i = 0; i < A_get_length(e); i++)
            {
                result += 2 + get_element_string_representation_size(A_get_element_at_index(i, e));
            }
            break;
		case NULL_TYPE:
			result = sizeof "NULL" - 1;
			break;
		default:
			error_msg = "Not able to calculate the size of the string representation for the given element.";
			goto error;
			break;
			
	}
	return result;
error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

