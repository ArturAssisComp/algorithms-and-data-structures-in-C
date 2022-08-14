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
    //Special type
    GENERIC,
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
struct T_generic;

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
        struct T_set *set;
        struct T_generic *gen;
    } value;
    T_data_type type;
}T_element;


struct T_string
{
    char *str;
    size_t length;
    size_t capacity;
};
typedef struct T_string T_string;

struct T_array
{
    T_element *array;
    size_t length;
};
typedef struct T_array T_array;

struct T_vector
{
    T_element *vector;
    size_t length;
    size_t capacity;
};
typedef struct T_vector T_vector;


struct T_linked_list_element 
{
    T_element element;
    struct T_linked_list_element *next_element;
};
typedef struct T_linked_list_element T_linked_list_element; 

struct T_linked_list 
{
    T_linked_list_element *head;
    size_t length;
};
typedef struct T_linked_list T_linked_list;

struct T_stack
{
    T_linked_list *aux_linked_list;
};
typedef struct T_stack T_stack;

struct T_dict
{
        struct T_linked_list *table;
        size_t table_length;
        size_t num_of_items;
};
typedef struct T_dict T_dict;

struct T_set
{
    T_dict *dict;
};
typedef struct T_set T_set;


struct T_generic
{
    void *gen; //The user must cast this object before using it.
    size_t code; //This code an be used by the user to customize the behavior of this generic object.
    bool memory_allocated; //If true, gen will be freed in the G_delete_generics function.
};
typedef struct T_generic T_generic;

//Function declarations:
void T_print(char *prefix, T_element e, char *suffix);
char *T_to_string(T_element e);
bool T_is_equal(T_element e1, T_element e2);
void T_free_element(T_element *e);


#endif
