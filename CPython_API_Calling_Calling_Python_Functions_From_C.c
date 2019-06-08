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
 Calling Python Functions from C:
 So far we have concentrated on making C functions callable from Python.
 The reverse is also useful: calling Python functions from C.
 This is especially the case for libraries that support so-called “callback” functions.
 If a C interface makes use of callbacks, the equivalent Python often needs to provide a callback mechanism to the Python programmer; the implementation
 will require calling the Python callback functions from a C callback.
 Other uses are also imaginable.
 Fortunately, the Python interpreter is easily called recursively, and there is a standard interface to call a Python function.
 (I won’t dwell on how to call the Python parser with a particular string as input — if you’re interested, have a look at the implementation of the -c
 command line option in Modules/main.c from the Python source code.)
 Calling a Python function is easy.
 First, the Python program must somehow pass you the Python function object.
 You should provide a function (or some other interface) to do this.
 When this function is called, save a pointer to the Python function object (be careful to Py_INCREF() it!) in a global variable — or wherever you see fit.
 For example, the following function might be part of a module definition:
*/ 

static PyObject *my_callback = NULL;

static PyObject *

my_set_callback(PyObject *dummy, PyObject *args)

{
    PyObject *result = NULL;
    PyObject *temp;

    if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {

        if (!PyCallable_Check(temp)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");

            return NULL;

        }

        Py_XINCREF(temp);         /* Add a reference to new callback */
        Py_XDECREF(my_callback);  /* Dispose of previous callback */
        my_callback = temp;       /* Remember new callback */
        /* Boilerplate to return "None" */
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

/*
 Later, when it is time to call the function, you call the C function PyObject_CallObject().
 This function has two arguments, both pointers to arbitrary Python objects: the Python function, and the argument list.
 The argument list must always be a tuple object, whose length is the number of arguments.
 To call the Python function with no arguments, pass in NULL, or an empty tuple; to call it with one argument, pass a singleton tuple.
 Py_BuildValue() returns a tuple when its format string consists of zero or more format codes between parentheses.
*/

/*
 For example:
*/ 

int arg;

PyObject *arglist;
PyObject *result;

/*       ...      */

arg = 123;

/*       ...      */

/* Time to call the callback */

arglist = Py_BuildValue("(i)", arg);
result = PyObject_CallObject(my_callback, arglist);

Py_DECREF(arglist);

/* 
 PyObject_CallObject() returns a Python object pointer: this is the return value of the Python function.
 PyObject_CallObject() is “reference-count-neutral” with respect to its arguments.
 In the example a new tuple was created to serve as the argument list, which is Py_DECREF()-ed immediately after the PyObject_CallObject() call.
 Before you do this, however, it is important to check that the return value isn’t NULL.
 If it is, the Python function terminated by raising an exception.
 If the C code that called PyObject_CallObject() is called from Python, it should now return an error indication to its Python caller, so the interpreter
 can print a stack trace, or the calling Python code can handle the exception.
 If this is not possible or desirable, the exception should be cleared by calling PyErr_Clear().
*/

/*
 For example:
*/ 

if (result == NULL)

    return NULL; /* Pass error back */

/*        ...use result...      */

Py_DECREF(result);
 
/*
 Depending on the desired interface to the Python callback function, you may also have to provide an argument list to PyObject_CallObject().
 In some cases the argument list is also provided by the Python program, through the same interface that specified the callback function.
 It can then be saved and used in the same manner as the function object.
 In other cases, you may have to construct a new tuple to pass as the argument list.
 The simplest way to do this is to call Py_BuildValue().
 For example, if you want to pass an integral event code, you might use the following code:
*/ 

PyObject *arglist;

/*          ...          */

arglist = Py_BuildValue("(l)", eventcode);

result = PyObject_CallObject(my_callback, arglist);

Py_DECREF(arglist);

if (result == NULL)

    return NULL; /* Pass error back */

/* Here maybe use the result */

Py_DECREF(result);
 
/*
 Note the placement of Py_DECREF(arglist) immediately after the call, before the error check!
 Also note that strictly speaking this code is not complete: Py_BuildValue() may run out of memory, and this should be checked.
 You may also call a function with keyword arguments by using PyObject_Call(), which supports arguments and keyword arguments.
 As in the above example, we use Py_BuildValue() to construct the dictionary.
*/ 

PyObject *dict;

/*                  ...                 */

dict = Py_BuildValue("{s:i}", "name", val);

result = PyObject_Call(my_callback, NULL, dict);

Py_DECREF(dict);

if (result == NULL)
    return NULL; /* Pass error back */

/* Here maybe use the result */

Py_DECREF(result);
