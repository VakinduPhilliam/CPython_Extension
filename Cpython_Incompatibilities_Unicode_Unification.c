/*
 Cpython Incompatibilities
 This document endeavors to document Python C-API incompatibilities between Python 2 and Python 3 and how they can be worked around.
*/

/*
 Changes to Object APIs
 Python 3 merged together some types with similar functions while cleanly separating others.
*/

/* 
 str/unicode Unification
 Python 3’s str() type is equivalent to Python 2’s unicode(); the C functions are called PyUnicode_* for both. 
 The old 8-bit string type has become bytes(), with C functions called PyBytes_*. 
 Python 2.6 and later provide a compatibility header, bytesobject.h, mapping PyBytes names to PyString ones. 
 For best compatibility with Python 3, PyUnicode should be used for textual data and PyBytes for binary data. 
 It’s also important to remember that PyBytes and PyUnicode in Python 3 are not interchangeable like PyString and PyUnicode are in Python 2. 
 The following example shows best practices with regards to PyUnicode, PyString, and PyBytes.
*/ 

#include "stdlib.h"
#include "Python.h"
#include "bytesobject.h"

/* text example */

static PyObject *
say_hello(PyObject *self, PyObject *args) {
    PyObject *name, *result;

    if (!PyArg_ParseTuple(args, "U:say_hello", &name))
        return NULL;

    result = PyUnicode_FromFormat("Hello, %S!", name);

    return result;
}

/* just a forward */

static char * do_encode(PyObject *);

/* bytes example */

static PyObject *
encode_object(PyObject *self, PyObject *args) {
    char *encoded;

    PyObject *result, *myobj;

    if (!PyArg_ParseTuple(args, "O:encode_object", &myobj))
        return NULL;

    encoded = do_encode(myobj);

    if (encoded == NULL)
        return NULL;
    result = PyBytes_FromString(encoded);

    free(encoded);
    return result;
}
