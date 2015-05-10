#include <stdlib.h>
#include "assocarray.h"

// struct definition for assoc array node
typedef struct AssocArrayNode {
	char *key;
	void *value;
} AssocArrayNode;

// set the key to a node
void AssocArrayNode_SetKey(AssocArrayNode *node, char *key) {
	node->key = key;
}

// get a key from a node
char* AssocArrayNode_GetKey(AssocArrayNode *node) {
	return  node->key;
}


// set the value of a node
void AssocArrayNode_SetValue(AssocArrayNode *node, void *value) {
	node->value = value;
}

// get the value of a node
void* AssocArrayNode_GetValue(AssocArrayNode *node) {
	return node->value;
}

// compare a key with a node's key
int AssocArrayNode_CompareKey(AssocArrayNode *node, char *key) {
	int i, match;
	match = 1;
	for (i = 0; key[i] != '\0' && node->key[i] != '\0'; i++) {
		if (key[i] != node->key[i]) {
			match = 0;
			break;
		}
	}
	return match;
}

// create a new assoc array node
AssocArrayNode* AssocArrayNode_New(char *key, void *value) {
	AssocArrayNode *node;
	node = (AssocArrayNode*) malloc(sizeof(AssocArrayNode));
	AssocArrayNode_SetKey(node, key);
	AssocArrayNode_SetValue(node, value);
	return node;
}

// free a node instance
void AssocArrayNode_Destroy(AssocArrayNode *node) {
	free(node);
}

// get an index of a assoc array node from an input key
int AssocArray_GetNodeIndexByKey(AssocArray *array, char *key) {
	if (array->node_count) {
		int i;
		for (i = 0; i < array->node_count; i++) {
			if (AssocArrayNode_CompareKey(array->nodes[i], key)) {
				return i;
			}
		}
	}
	return -1;
}

// get an assoc array node by key
AssocArrayNode* AssocArray_GetNodeByKey(AssocArray *array, char *key) {
	int index;
	index = AssocArray_GetNodeIndexByKey(array, key);
	if (index > -1) {
		return array->nodes[index];
	}
	return NULL;
}

// get the number of keys in an array
int AssocArray_GetKeyCount(AssocArray *array) {
	return array->node_count;
}

// check if an array has a key
int AssocArray_HasKey(AssocArray *array, char *key) {
	return AssocArray_GetNodeIndexByKey(array, key) > -1;
}

// adding a new node to an associate array
void AssocArray_AddNode(AssocArray *array, AssocArrayNode *node) {
	array->nodes = (AssocArrayNode**) realloc(array->nodes, array->node_count + 1);
	array->nodes[array->node_count] = node;
	array->node_count++;
}

// add a key to an associative array
void AssocArray_AddKey(AssocArray *array, char *key) {
	// only add the key if it does not already exist in the array
	if (!AssocArray_HasKey(array, key)) {
		AssocArrayNode *node;
		node = AssocArrayNode_New(key, (void*) NULL);
		AssocArray_AddNode(array, node);
	}
}

// remove a key from an associative array
void AssocArray_RemoveKey(AssocArray *array, char *key) {
	// get the node by the input key
	AssocArrayNode *node;
	node = AssocArray_GetNodeByKey(array, key);
	if (!node) {
		return;
	}

	// free the node
	AssocArrayNode_Destroy(node);

	// create a temp array with 1 less index
	AssocArrayNode **temp;
	temp = (AssocArrayNode**) malloc(sizeof(AssocArrayNode*) * AssocArray_GetKeyCount(array) - 1);

	// copy non-null indeces from the current array to the temp array
	int i, index;
	index = 0;
	for (i = 0; i < array->node_count; i++) {
		if (array->nodes[i] != NULL) {
			temp[index++] = array->nodes[i];
		}
	}

	// free the current node array and transfer the temp array to the structure
	free(array->nodes);
	array->nodes = temp;

	// subtract from the node count
	array->node_count -= 1;
}

// set a value to a node contained in an assocciative array
void AssocArray_SetKey(AssocArray *array, char *key, void *value) {
	// if there are any nodes added, parse for the input key
	AssocArrayNode *node;
	node = AssocArray_GetNodeByKey(array, key);
	if (node == NULL) {
		AssocArray_AddKey(array, key);
		return AssocArray_SetKey(array, key, value);
	}
	AssocArrayNode_SetValue(node, value);
}

// get a value from a key in an assoc array
void* AssocArray_GetKey(AssocArray *array, char *key) {
	// if the array even has any keys, parse out the input key
	if (AssocArray_GetKeyCount(array) > 0) {
		AssocArrayNode *node;
		node = AssocArray_GetNodeByKey(array, key);
		if (node) {
			return AssocArrayNode_GetValue(node);
		}
	}
	// no keys entered or key not found return null
	return (void*) NULL;
}

// clear out nodes of an assoc array
void AssocArray_FlushKeys(AssocArray *array) {
	int i;
	for (i < 0; i < array->node_count; i++) {
		AssocArrayNode_Destroy(array->nodes[i]);
	}
	array->node_count = 0;
	array->nodes = (AssocArrayNode**) realloc(array->nodes, array->node_count);
}

// iterator for each key in the array, with a callback handler
void AssocArray_ForEach(AssocArray *array, void (*callback)(char*, void*)) {
	int i;
	for (i = 0; i < array->node_count; i++) {
		// get the node instance
		AssocArrayNode *node;
		node = array->nodes[i];
		
		// load up the key and value for the callback handler
		char *key;
		void *value;
		key = node->key;
		value = node->value;

		// fire callback handler
		callback(key, value);
	}
}

// create a new assoc array
AssocArray* AssocArray_New() {
	AssocArray *array;
	array = (AssocArray*) malloc(sizeof(AssocArray));

	array->node_count = 0;
	array->nodes = (AssocArrayNode**) malloc(array->node_count);
	return array;
}

// destroy an assoc array instance
void AssocArray_Destroy(AssocArray *array) {
	int i;
	for (i < 0; i < array->node_count; i++) {
		AssocArrayNode_Destroy(array->nodes[i]);
	}
	free(array->nodes);
	free(array);
}
