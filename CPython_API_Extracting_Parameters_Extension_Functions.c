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
 Extracting Parameters in Extension Functions:
 The PyArg_ParseTuple() function is declared as follows:
*/ 

int PyArg_ParseTuple(PyObject *arg, const char *format, ...);

/* 
 The arg argument must be a tuple object containing an argument list passed from Python to a C function.
 The format argument must be a format string, whose syntax is explained in Parsing arguments and building values in the Python/C API Reference Manual.
 The remaining arguments must be addresses of variables whose type is determined by the format string.
 Note that while PyArg_ParseTuple() checks that the Python arguments have the required types, it cannot check the validity of the addresses of C variables
 passed to the call: if you make mistakes there, your code will probably crash or at least overwrite random bits in memory. So be careful!
 Note that any Python object references which are provided to the caller are borrowed references; do not decrement their reference count!
*/

/* 
 Some example calls:
*/ 

#define PY_SSIZE_T_CLEAN  /* Make "s#" use Py_ssize_t rather than int. */
#include <Python.h>
 

int ok;
int i, j;
long k, l;

const char *s;

Py_ssize_t size;

ok = PyArg_ParseTuple(args, ""); /* No arguments */
    /* Python call: f() */
 

ok = PyArg_ParseTuple(args, "s", &s); /* A string */
    /* Possible Python call: f('whoops!') */
 

ok = PyArg_ParseTuple(args, "lls", &k, &l, &s); /* Two longs and a string */
    /* Possible Python call: f(1, 2, 'three') */
 

ok = PyArg_ParseTuple(args, "(ii)s#", &i, &j, &s, &size);
    /* A pair of ints and a string, whose size is also returned */
    /* Possible Python call: f((1, 2), 'three') */
 

{
    const char *file;
    const char *mode = "r";

    int bufsize = 0;

    ok = PyArg_ParseTuple(args, "s|si", &file, &mode, &bufsize);

    /* A string, and optionally another string and an integer */
    /* Possible Python calls:

       f('spam')
       f('spam', 'w')

       f('spam', 'wb', 100000) */
}
 

{
    int left, top, right, bottom, h, v;

    ok = PyArg_ParseTuple(args, "((ii)(ii))(ii)",
             &left, &top, &right, &bottom, &h, &v);

    /* A rectangle and a point */
    /* Possible Python call:
       f(((0, 0), (400, 300)), (10, 10)) */

}
 

{
    Py_complex c;

    ok = PyArg_ParseTuple(args, "D:myfunction", &c);

    /* a complex, also providing a function name for errors */
    /* Possible Python call: myfunction(1+2j) */

}
