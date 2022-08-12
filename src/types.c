#include "types.h"
#include "dict.h"
#include "array.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


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

	//Check if they have different type:
	if (e1.type != e2.type) return result false;

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
            if (e1.length != e2.length) result = false;
            else 
            {
                result = true;
                for(i = 0; i < e1.length; i++)
                {
                    if(!T_is_equal(A_get_element_at_index(i, e1), A_get_element_at_index(i, e2))
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
{
	//Variables:
	char *error_msg;
	T_linked_list *current_linked_list;
	int i;

	//Free the values:
	switch (e->type)
	{
		case UNSIGNED_INTEGER:
		case INTEGER:
		case CHAR:
		case STRING:
		case BOOL:
		case FLOATING_POINT:
			e->type = NULL_TYPE;
			break;
		case DICT:
			e->type = NULL_TYPE;
			D_delete_dict(&(e->value.dct));
			if(e->value.dct)
			{
				error_msg = "Problems while deleting the dict.";
				goto error;
			}
			break;
		case ARRAY:
			e->type = NULL_TYPE;
			A_delete_array(&(e->value.arr));
			if(e->value.arr)
			{
				error_msg = "Problems while deleting the array.";
				goto error;
			}
			break;
		case NULL_TYPE:
			error_msg = "Calling T_free_element for a NULL_TYPE element.";
			goto error;
			break;

		default:
			break;
			
	}

result:
	return;

error:
	fprintf(stderr, error_msg);
	exit(EXIT_FAILURE);
}

