#include "../src/types.h"
#include "../src/array.h"
#include <stdio.h>


int main(void)
{
    char *str;
    T_element e;
    printf("1 - Printing unsigned integer: 123\n");
    e = (T_element){.value.u_i = 123, .type = UNSIGNED_INTEGER};
    str = T_to_string(e);
    printf("-> %s\n", str);
    free(str);
    

    return 0;
}
