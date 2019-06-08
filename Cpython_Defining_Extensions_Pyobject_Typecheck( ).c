/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 In order to learn how to implement any specific method for your new data type, get the CPython source code.
 Go to the Objects directory, then search the C source files for tp_ plus the function you want (for example, tp_richcompare).
 You will find examples of the function you want to implement.
 When you need to verify that an object is a concrete instance of the type you are implementing, use the PyObject_TypeCheck() function.
 A sample of its use might be something like the following:
*/ 

if (!PyObject_TypeCheck(some_object, &MyType)) {
    PyErr_SetString(PyExc_TypeError, "arg #1 not a mything");

    return NULL;

}
