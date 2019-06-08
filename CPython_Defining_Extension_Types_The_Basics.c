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

#include <Python.h>

typedef struct {
    PyObject_HEAD

    /* Type-specific fields go here. */

} CustomObject;

static PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "custom.Custom",
    .tp_doc = "Custom objects",
    .tp_basicsize = sizeof(CustomObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "custom",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_custom(void)

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
