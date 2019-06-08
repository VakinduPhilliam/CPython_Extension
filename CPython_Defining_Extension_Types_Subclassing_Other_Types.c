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
 Subclassing other types
 It is possible to create new extension types that are derived from existing types.
 It is easiest to inherit from the built in types, since an extension can easily use the PyTypeObject it needs.
 It can be difficult to share these PyTypeObject structures between extension modules.
 In this example we will create a SubList type that inherits from the built-in list type.
 The new type will be completely compatible with regular lists, but will have an additional increment() method that increases an internal counter:
*/

#include <Python.h>

typedef struct {
    PyListObject list;
    int state;
} SubListObject;

static PyObject *

SubList_increment(SubListObject *self, PyObject *unused)
{
    self->state++;

    return PyLong_FromLong(self->state);

}

static PyMethodDef SubList_methods[] = {
    {"increment", (PyCFunction) SubList_increment, METH_NOARGS,
     PyDoc_STR("increment state counter")},
    {NULL},
};

static int

SubList_init(SubListObject *self, PyObject *args, PyObject *kwds)
{
    if (PyList_Type.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    self->state = 0;

    return 0;
}

static PyTypeObject SubListType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "sublist.SubList",
    .tp_doc = "SubList objects",
    .tp_basicsize = sizeof(SubListObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) SubList_init,
    .tp_methods = SubList_methods,
};

static PyModuleDef sublistmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "sublist",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_sublist(void)
{
    PyObject *m;
    SubListType.tp_base = &PyList_Type;

    if (PyType_Ready(&SubListType) < 0)
        return NULL;

    m = PyModule_Create(&sublistmodule);

    if (m == NULL)
        return NULL;

    Py_INCREF(&SubListType);

    PyModule_AddObject(m, "SubList", (PyObject *) &SubListType);

    return m;
}
