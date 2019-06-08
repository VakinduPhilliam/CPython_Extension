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
 Errors and Exceptions:
 You can also define a new exception that is unique to your module.
 For this, you usually declare a static object variable at the beginning of your file:
*/ 

static PyObject *SpamError;
 
/*
 and initialize it in your module’s initialization function (PyInit_spam()) with an exception object (leaving out the error checking for now):
*/ 

PyMODINIT_FUNC

PyInit_spam(void)
{

    PyObject *m;

    m = PyModule_Create(&spammodule);

    if (m == NULL)
        return NULL;

    SpamError = PyErr_NewException("spam.error", NULL, NULL);

    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);

    return m;
}

/*
 The spam.error exception can be raised in your extension module using a call to PyErr_SetString() as shown below:
*/ 

static PyObject *

spam_system(PyObject *self, PyObject *args)
{
    const char *command;

    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;

    sts = system(command);

    if (sts < 0) {
        PyErr_SetString(SpamError, "System command failed");

        return NULL;

    }

    return PyLong_FromLong(sts);

}
