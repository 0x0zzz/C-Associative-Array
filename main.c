#include <stdio.h>
#include <stdlib.h>
#include "assocarray.h"

void custom_destroy_handler(void *value) {
	free(value);
	if (value != NULL) {
		printf("Integer Array freed.\n");
	}
}

void key_value_handler(char *key, void *value) {
	printf("key: \"%s\"\n", key);
}

int main(int argc, char **argv) {
	// create new associative array
	AssocArray *array;
	array = AssocArray_New();

	// set a key to an integer
	int i;
	i = 1;
	AssocArray_SetKey(array, "test", &i);
	i = *(int*) AssocArray_GetKey(array, "test");
	printf("test: %d\n", i);

	// reassign the key's value to another integer
	i = 2;
	AssocArray_SetKey(array, "test", &i);
	i = *(int*) AssocArray_GetKey(array, "test");
	printf("test: %d\n", i);

	// reassign the key's type altogether
	float f;
	f = 10.0f;
	AssocArray_SetKey(array, "test", &f);
	f = *(float*) AssocArray_GetKey(array, "test");
	printf("test: %.1f\n", f);

	// a new key with a variable of type float
	AssocArray_SetKey(array, "string", "Strings are handled nicer!");
	char *string;
	string = AssocArray_GetKey(array, "string");
	printf("string: %s\n", string);

	// create key with value that requires custom destroy handlers
	int *int_array;
	int_array = (int*) malloc(sizeof(int) * 8);
	AssocArray_SetKey(array, "array", int_array);

	// set the custom destroy handler to properly free the allocated integer array
	AssocArray_SetKeyDestroyFunction(array, "array", &custom_destroy_handler);

	// iterate through each key and value
	AssocArray_ForEach(array, &key_value_handler);

	// destroy the array
	AssocArray_Destroy(array);
	return 0;
}
