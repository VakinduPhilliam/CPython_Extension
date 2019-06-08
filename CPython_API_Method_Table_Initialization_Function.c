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
 The Module’s Method Table and Initialization Function:
 How spam_system() is called from Python programs.
 First, we need to list its name and address in a “method table”:
*/ 

static PyMethodDef SpamMethods[] = {
     /*          ...........     */

    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},

     /*          ...........           */

    {NULL, NULL, 0, NULL}        /* Sentinel */

};

/*
 The METH_KEYWORDS bit may be set in the third field if keyword arguments should be passed to the function.
 In this case, the C function should accept a third PyObject * parameter which will be a dictionary of keywords.
 Use PyArg_ParseTupleAndKeywords() to parse the arguments to such a function.
 The method table must be referenced in the module definition structure:
*/ 

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam",   /* name of module */
    spam_doc, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};

/* 
 This structure, in turn, must be passed to the interpreter in the module’s initialization function.
 The initialization function must be named PyInit_name(), where name is the name of the module, and should be the only non-static item defined in the
 module file:
*/ 

PyMODINIT_FUNC
PyInit_spam(void)

{

    return PyModule_Create(&spammodule);

}
