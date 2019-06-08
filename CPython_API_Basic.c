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
  The first line of our file can be:
*/ 

#include <Python.h>

/* 
  which pulls in the Python API (you can add a comment describing the purpose of the module and a copyright notice if you like).
*/ 

/*
  Note:
  Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard 
  headers are included.
*/ 

/*
 The next thing we add to our module file is the C function that will be called when the Python expression spam.system(string) is evaluated:
*/ 

static PyObject *

spam_system(PyObject *self, PyObject *args)

{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    sts = system(command);

    return PyLong_FromLong(sts);
}
