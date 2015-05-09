# C-Associative-Array

### Associative Array Library in C

Associative Array implementation in pure C.  Store and retrieve any type of data, from integers, to structs, to function pointers, to a key consisting of a char*.

### Basic Usage

Creating a new Associative Array:
```C

/*
  Usage:
  AssocArray* AssocArray_New(void);
*/

AssocArray *array;
array = AssocArray_New();

```

Setting a key of an Associative Array:
```C

/*
  Usage:
  void AssocArray_SetKey(AssocArray *array, char *key, void* value);
*/

int number;
number = 4;
AssocArray_SetKey(array, "test", &number);

```

Alternatively, you can create a blank key in the Associative Array:
```C

/*
  Usage:
  void AssocArray_AddKey(AssocArray *array, char *key);
*/

AssocArray_AddKey(array, "test");

```
Please note that setting a key will create the new key, in the event that the key does not exist already.


Getting a value assigned a key of an Associative Array:
```C

/*
  Usage:
  void* AssocArray_GetKey(AssocArray *array, char *key);
*/

int number;
number = *(void*) AssocArray_GetKey(array, "test");

```

Removing a key from an Associative Array:
```C

/*
  Usage:
  void AssocArray_RemoveKey(AssocArray *array, char *key);
*/

AssocArray_RemoveKey(array, "test");

```

Destroying an Associative Array:
```C

/*
  Usage:
  void AssocArray_Destroy(AssocArray *array);
*/

AssocArray_Destroy(array);

```


More usage examples are located in "main.c" in the repository.
