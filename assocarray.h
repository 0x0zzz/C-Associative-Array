#ifndef _ASSOC_ARRAY_
#define _ASSOC_ARRAY_

// definitions for associative array

// forward declaration
struct AssocArrayNode;

typedef struct {
	unsigned int  node_count;
	struct AssocArrayNode **nodes;
} AssocArray;

// public functions
int AssocArray_GetKeyCount(AssocArray *array);
int AssocArray_HasKey(AssocArray *array, char *key);
void AssocArray_AddKey(AssocArray *array, char *key);
void AssocArray_SetKey(AssocArray *array, char *key, void *value);
void* AssocArray_GetKey(AssocArray *array, char *key);
void AssocArray_RemoveKey(AssocArray *array, char *key);
void AssocArray_FlushKeys(AssocArray *array);

// util functions
void AssocArray_SetKeyDestroyFunction(AssocArray *array, char *key, void (*callback)(void*));
void AssocArray_ForEach(AssocArray *array, void (*callback)(char*, void*));

// constructor, destructor for associateive array
AssocArray* AssocArray_New();
void AssocArray_Destroy(AssocArray *array);

#endif
