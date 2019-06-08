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
 Thin Ice:
 There are a few situations where seemingly harmless use of a borrowed reference can lead to problems.
 These all have to do with implicit invocations of the interpreter, which can cause the owner of a reference to dispose of it.
*/

/* 
 The first and most important case to know about is using Py_DECREF() on an unrelated object while borrowing a reference to a list item.
*/

/*
 For instance:
*/ 

void

bug(PyObject *list)
{

    PyObject *item = PyList_GetItem(list, 0);

    PyList_SetItem(list, 1, PyLong_FromLong(0L));
    PyObject_Print(item, stdout, 0); /* BUG! */

}

/*  
 This function first borrows a reference to list[0], then replaces list with the value 0, and finally prints the borrowed reference.
 Looks harmless, right? But it’s not!
 Let’s follow the control flow into PyList_SetItem().
 The list owns references to all its items, so when item 1 is replaced, it has to dispose of the original item 1.
 Now let’s suppose the original item 1 was an instance of a user-defined class, and let’s further suppose that the class defined a __del__() method.
 If this class instance has a reference count of 1, disposing of it will call its __del__() method.
 Since it is written in Python, the __del__() method can execute arbitrary Python code. Could it perhaps do something to invalidate the reference to item in
 bug()? You bet!
 Assuming that the list[1] passed into bug() is accessible to the __del__() method, it could execute a statement to the effect of del list[0], and assuming
 this was the last reference to that object, it would free the memory associated with it, thereby invalidating item.
*/

/* 
 The solution, once you know the source of the problem, is easy: temporarily increment the reference count.
 The correct version of the function reads:
*/ 

void
no_bug(PyObject *list)

{
    PyObject *item = PyList_GetItem(list, 0);

    Py_INCREF(item);
    PyList_SetItem(list, 1, PyLong_FromLong(0L));

    PyObject_Print(item, stdout, 0);
    Py_DECREF(item);

}

/*
 The second case of problems with a borrowed reference is a variant involving threads.
 Normally, multiple threads in the Python interpreter can’t get in each other’s way, because there is a global lock protecting Python’s entire object space.
 However, it is possible to temporarily release this lock using the macro Py_BEGIN_ALLOW_THREADS, and to re-acquire it using Py_END_ALLOW_THREADS.
 This is common around blocking I/O calls, to let other threads use the processor while waiting for the I/O to complete.
 Obviously, the following function has the same problem as the previous one:
*/ 

void
bug(PyObject *list)

{
    PyObject *item = PyList_GetItem(list, 0);

    Py_BEGIN_ALLOW_THREADS

/*    ...some blocking I/O call...       */

    Py_END_ALLOW_THREADS

    PyObject_Print(item, stdout, 0); /* BUG! */

}
