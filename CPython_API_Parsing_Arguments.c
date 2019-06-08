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
 Parsing arguments and building values:
 This is an example of the use of this function, taken from the sources for the _weakref helper module for weak references:
*/ 

static PyObject *

weakref_ref(PyObject *self, PyObject *args)
{

    PyObject *object;
    PyObject *callback = NULL;

    PyObject *result = NULL;

    if (PyArg_UnpackTuple(args, "ref", 1, 2, &object, &callback)) {

        result = PyWeakref_NewRef(object, callback);

    }

    return result;

}

/* 
 The call to PyArg_UnpackTuple() in this example is entirely equivalent to this call to PyArg_ParseTuple():
*/ 

# PyArg_ParseTuple(args, "O|O:ref", &object, &callback)
