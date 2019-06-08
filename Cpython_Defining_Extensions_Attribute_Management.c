/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Attribute Management:
 For every object which can support attributes, the corresponding type must provide the functions that control how the attributes are resolved.
 There needs to be a function which can retrieve attributes (if any are defined), and another to set attributes (if setting attributes is allowed).
 Removing an attribute is a special case, for which the new value passed to the handler is NULL.
 Python supports two pairs of attribute handlers; a type that supports attributes only needs to implement the functions for one pair.
 The difference is that one pair takes the name of the attribute as a char*, while the other accepts a PyObject*.
 Each type can use whichever pair makes more sense for the implementation’s convenience.
*/ 

getattrfunc  tp_getattr;        /* char * version */

setattrfunc  tp_setattr;

/* ... */

getattrofunc tp_getattro;       /* PyObject * version */

setattrofunc tp_setattro;

/* 
 If accessing attributes of an object is always a simple operation (this will be explained shortly), there are generic implementations which can be used to
 provide the PyObject* version of the attribute management functions.
 The actual need for type-specific attribute handlers almost completely disappeared starting with Python 2.2, though there are many examples which have not
 been updated to use some of the new generic mechanism that is available.
*/