#ifndef TYPES_H
#define TYPES_H

//Include libs:
#include <stdbool.h>
#include <stdlib.h>

//Declaration of types:

typedef enum 
{
    //Individual elements:
    UNSIGNED_INTEGER,
    INTEGER,
    FLOATING_POINT,
    BOOL,
    CHAR,
    //Group elements:
    STRING,
    ARRAY, //Array of generic elements. Fixed size
    VECTOR, //Like an array, but with variable capacity
    LINKED_LIST,
    STACK,
    DICT,  //Dict of generic elements
    SET,
    NULL_TYPE
} T_data_type;

//Hash type
typedef size_t T_hash_type;

//Types of data structure
/*Basic types (they do not need to be allocated)*/
typedef unsigned int T_unsigned_integer;
typedef int T_integer;
typedef double T_floating_point;
typedef bool T_bool;
typedef char T_char;
/*Struct types (they need to be initialized/allocated)*/
struct T_string;
struct T_array;
struct T_vector;
struct T_linked_list;
struct T_stack;
struct T_dict;
struct T_set;

//Define the basic data structure element
typedef struct 
{
    union {
        T_unsigned_integer u_i;
        T_integer i;
        T_floating_point f_p;
        T_bool b;
        T_char c;
        struct T_string *str; 
        struct T_array *arr;
        struct T_vector *vctr;
        struct T_linked_list *lk;
        struct T_stack *stck;
        struct T_dict *dct;
        struct T_set *set
    } value;
    T_data_type type;
}T_element;


typedef struct
{
    char *str;
    size_t length;
    size_t capacity;
}T_string;

typedef struct
{
    T_element *array;
    size_t length;
} T_array;

typedef struct
{
    T_element *vector;
    size_t length;
    size_t capacity;
} T_vector;


struct T_linked_list_element 
{
    T_element element;
    struct T_linked_list_element *next_element;
};
typedef struct T_linked_list_element; 

typedef struct 
{
    T_linked_list_element *head;
    size_t length;
}T_linked_list;

typedef struct
{
    T_linked_list *aux_linked_list;
}T_stack;

typedef struct 
{
        struct T_linked_list *table;
        size_t table_length;
        size_t num_of_items;
}T_dict;

typedef struct
{
    T_dict *dict;
}T_set;


//Function declarations:
char *T_to_string(T_element e);
bool T_is_equal(T_element e1, T_element e2);
void T_free_element(T_element *e);


#endif
