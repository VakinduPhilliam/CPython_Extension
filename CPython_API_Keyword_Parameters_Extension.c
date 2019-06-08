/*
 CPython API
 To support extensions, the Python API (Application Programmers Interface) defines a set of functions, macros and variables that provide access to most
 aspects of the Python run-time system.
 The Python API is incorporated in a C source file by including the header "Python.h".
 The compilation of an extension module depends on its intended use as well as on your system setup.

 Note:
 The C extension interface is specific to CPython, and extension modules do not work on other Python implementations.
 In many cases, it is possible to avoid writing C extensions and preserve portability to other implementations.
 For example, if your use case is calling C library functions or system calls, you should consider using the ctypes module or the cffi library rather than
 writing custom C code.
 These modules let you write Python code to interface with C code and are more portable between implementations of Python than writing and compiling a C
 extension module.
 
*/

/*
 Keyword Parameters for Extension Functions:
 The PyArg_ParseTupleAndKeywords() function is declared as follows:
*/ 

int PyArg_ParseTupleAndKeywords(PyObject *arg, PyObject *kwdict,
                                const char *format, char *kwlist[], ...);

/* 
 The arg and format parameters are identical to those of the PyArg_ParseTuple() function.
 The kwdict parameter is the dictionary of keywords received as the third parameter from the Python runtime.
 The kwlist parameter is a NULL-terminated list of strings which identify the parameters; the names are matched with the type information from format from
 left to right. On success, PyArg_ParseTupleAndKeywords() returns true, otherwise it returns false and raises an appropriate exception.
*/ 

/*
 Note:
 Nested tuples cannot be parsed when using keyword arguments!
 Keyword parameters passed in which are not present in the kwlist will cause TypeError to be raised.
*/

/* 
 Here is an example module which uses keywords:
*/ 

#include "Python.h"

static PyObject *

keywdarg_parrot(PyObject *self, PyObject *args, PyObject *keywds)
{
    int voltage;

    const char *state = "a stiff";
    const char *action = "voom";

    const char *type = "Norwegian Blue";

    static char *kwlist[] = {"voltage", "state", "action", "type", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|sss", kwlist,
                                     &voltage, &state, &action, &type))
        return NULL;

    printf("-- This parrot wouldn't %s if you put %i Volts through it.\n",
           action, voltage);

    printf("-- Lovely plumage, the %s -- It's %s!\n", type, state);

    Py_RETURN_NONE;
}

static PyMethodDef keywdarg_methods[] = {

    /* The cast of the function is necessary since PyCFunction values
     * only take two PyObject* parameters, and keywdarg_parrot() takes
     * three.
     */

    {"parrot", (PyCFunction)keywdarg_parrot, METH_VARARGS | METH_KEYWORDS,
     "Print a lovely skit to standard output."},
    {NULL, NULL, 0, NULL}   /* sentinel */

};

static struct PyModuleDef keywdargmodule = {
    PyModuleDef_HEAD_INIT,
    "keywdarg",
    NULL,
    -1,
    keywdarg_methods
};

PyMODINIT_FUNC

PyInit_keywdarg(void)
{
    return PyModule_Create(&keywdargmodule);
}
