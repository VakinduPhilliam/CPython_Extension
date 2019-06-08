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

if (!PyArg_ParseTuple(args, "s", &command))
    return NULL;

/* 
 It returns NULL (the error indicator for functions returning object pointers) if an error is detected in the argument list, relying on the exception set by
 PyArg_ParseTuple().
 Otherwise the string value of the argument has been copied to the local variable command.
 This is a pointer assignment and you are not supposed to modify the string to which it points (so in Standard C, the variable command should properly be
 declared as const char *command).
 The next statement is a call to the Unix function system(), passing it the string we just got from PyArg_ParseTuple():
*/ 

sts = system(command);

/* 
 Our spam.system() function must return the value of sts as a Python object.
 This is done using the function PyLong_FromLong().
*/ 

return PyLong_FromLong(sts);

/* 
 In this case, it will return an integer object. (Yes, even integers are objects on the heap in Python!)
 If you have a C function that returns no useful argument (a function returning void), the corresponding Python function must return None.
 You need this idiom to do so (which is implemented by the Py_RETURN_NONE macro):
*/ 

Py_INCREF(Py_None);

return Py_None;

/* 
 Py_None is the C name for the special Python object None. It is a genuine Python object rather than a NULL pointer, which means “error” in most contexts,
 as we have seen.
*/