/*
 Cpython Incompatibilities
 This document endeavors to document Python C-API incompatibilities between Python 2 and Python 3 and how they can be worked around.
*/

/*
 Module initialization and state.
 Python 3 has a revamped extension module initialization system. 
 Instead of storing module state in globals, they should be stored in an interpreter specific structure. 
 Creating modules that act correctly in both Python 2 and Python 3 is tricky. 
 The following simple example demonstrates how.
*/ 

#include "Python.h"

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)

static struct module_state _state;

#endif

static PyObject *

error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;

}

static PyMethodDef myextension_methods[] = {

    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {NULL, NULL}

};

#if PY_MAJOR_VERSION >= 3

static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);

    return 0;

}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);

    return 0;

}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "myextension",
        NULL,
        sizeof(struct module_state),
        myextension_methods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_myextension(void)

#else
#define INITERROR return

void
initmyextension(void)

#endif

{

#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);

#else
    PyObject *module = Py_InitModule("myextension", myextension_methods);

#endif

    if (module == NULL)
        INITERROR;

    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("myextension.Error", NULL, NULL);

    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;

#endif

}
