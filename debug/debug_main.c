#include "../src/types.h"
#include "../src/array.h"
#include <stdio.h>


int main(void)
{
    char *str;
    T_element e, tmp_e;
    printf("1 - Printing unsigned integer: 123\n");
    e = (T_element){.value.u_i = 123, .type = UNSIGNED_INTEGER};
    T_print("-> ", e, "\n");

    printf("2 - Printing integer: 123\n");
    e = (T_element){.value.i = 123, .type = INTEGER};
    T_print("-> ", e, "\n");

    printf("3 - Printing floating point: 1334.34564\n");
    e = (T_element){.value.f_p = 1334.34563, .type = FLOATING_POINT};
    T_print("-> ", e, "\n");

    printf("4 - Printing bool: false\n");
    e = (T_element){.value.b = false, .type = BOOL};
    T_print("-> ", e, "\n");

    printf("5 - Printing char: 'r'\n");
    e = (T_element){.value.c = 'r', .type = CHAR};
    T_print("-> ", e, "\n");

    printf("6 - Printing array: [1, 2, 'e', 12.3]\n");
    e = A_create_array(4);
    T_print("-> ", e, "\n");
    A_set_element_at_index(0, (T_element){.value.i=1, .type=INTEGER}, e);
    T_print("-> ", e, "\n");
    A_set_element_at_index(1, (T_element){.value.u_i=2, .type=UNSIGNED_INTEGER}, e);
    T_print("-> ", e, "\n");
    A_set_element_at_index(2, (T_element){.value.c='e', .type=CHAR}, e);
    T_print("-> ", e, "\n");
    A_set_element_at_index(3, (T_element){.value.f_p=12.3, .type=FLOATING_POINT}, e);
    T_print("-> ", e, "\n");
    T_free_element(&e);

    printf("7 - Printing array: [1, [2, -223, 1,223e-13], 'e', 12.3]\n");
    tmp_e = A_create_array(3);
    A_set_element_at_index(0, (T_element){.value.i=1, .type=INTEGER}, tmp_e);
    A_set_element_at_index(1, (T_element){.value.i=-223, .type=INTEGER}, tmp_e);
    A_set_element_at_index(2, (T_element){.value.f_p=1.223e-13, .type=FLOATING_POINT}, tmp_e);

    e = A_create_array(4);
    A_set_element_at_index(0, (T_element){.value.i=1, .type=INTEGER}, e);
    A_set_element_at_index(1, tmp_e, e);
    A_set_element_at_index(2, (T_element){.value.c='e', .type=CHAR}, e);
    A_set_element_at_index(3, (T_element){.value.f_p=12.3, .type=FLOATING_POINT}, e);

    T_print("-> ", e, "\n");
    T_free_element(&e);

    return 0;
}
