/*
 CPython Defining Extension Types. 
 Python allows the writer of a C extension module to define new types that can be manipulated from Python code, much like the built-in str and list types.
 The code for all extension types follows a pattern, but there are some details that you need to understand before you can get started.
 This is a gentle introduction to the topic.

 The Basics:
 The CPython runtime sees all Python objects as variables of type PyObject*, which serves as a “base type” for all Python objects.
 The PyObject structure itself only contains the object’s reference count and a pointer to the object’s “type object”.
 This is where the action is; the type object determines which (C) functions get called by the interpreter when, for instance, an attribute gets looked up
 on an object, a method called, or it is multiplied by another object.
 These C functions are called “type methods”.
 So, if you want to define a new extension type, you need to create a new type object.
 This sort of thing can only be explained by example, so here’s a minimal, but complete, module that defines a new type named Custom inside a C extension
 module custom:
*/ 

/*
 Note:
 What we’re showing here is the traditional way of defining static extension types.
 It should be adequate for most uses.
 The C API also allows defining heap-allocated extension types using the PyType_FromSpec() function are not discussed here.
*/ 

/*
 Adding data and methods to the Basic example
 Let’s extend the basic example to add some data and methods.
 Let’s also make the type usable as a base class.
 We’ll create a new module, custom2 that adds these capabilities:
*/ 

#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *first; /* first name */
    PyObject *last;  /* last name */

    int number;

} CustomObject;

static void

Custom_dealloc(CustomObject *self)
{
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);

    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *

Custom_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CustomObject *self;
    self = (CustomObject *) type->tp_alloc(type, 0);

    if (self != NULL) {
        self->first = PyUnicode_FromString("");

        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->last = PyUnicode_FromString("");

        if (self->last == NULL) {
            Py_DECREF(self);

            return NULL;

        }
        self->number = 0;
    }
    return (PyObject *) self;
}

static int

Custom_init(CustomObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"first", "last", "number", NULL};

    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                     &first, &last,
                                     &self->number))
        return -1;

    if (first) {
        tmp = self->first;

        Py_INCREF(first);
        self->first = first;

        Py_XDECREF(tmp);
    }

    if (last) {
        tmp = self->last;

        Py_INCREF(last);

        self->last = last;

        Py_XDECREF(tmp);
    }
    return 0;
}

static PyMemberDef Custom_members[] = {
    {"first", T_OBJECT_EX, offsetof(CustomObject, first), 0,
     "first name"},
    {"last", T_OBJECT_EX, offsetof(CustomObject, last), 0,
     "last name"},
    {"number", T_INT, offsetof(CustomObject, number), 0,
     "custom number"},
    {NULL}  /* Sentinel */
};

static PyObject *

Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored))
{

    if (self->first == NULL) {
        PyErr_SetString(PyExc_AttributeError, "first");

        return NULL;

    }

    if (self->last == NULL) {
        PyErr_SetString(PyExc_AttributeError, "last");

        return NULL;

    }

    return PyUnicode_FromFormat("%S %S", self->first, self->last);

}

static PyMethodDef Custom_methods[] = {
    {"name", (PyCFunction) Custom_name, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom2.Custom",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(CustomObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = Custom_new,
    .tp_init = (initproc) Custom_init,
    .tp_dealloc = (destructor) Custom_dealloc,
    .tp_members = Custom_members,
    .tp_methods = Custom_methods,
};

static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "custom2",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC

PyInit_custom2(void)
{
    PyObject *m;

    if (PyType_Ready(&CustomType) < 0)

        return NULL;

    m = PyModule_Create(&custommodule);

    if (m == NULL)
        return NULL;

    Py_INCREF(&CustomType);

    PyModule_AddObject(m, "Custom", (PyObject *) &CustomType);

    return m;
}

/* 
 This version of the module has a number of changes.
 We’ve added an extra include:
*/ 

#include <structmember.h>
