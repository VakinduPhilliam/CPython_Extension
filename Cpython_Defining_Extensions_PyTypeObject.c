/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Here is the definition of PyTypeObject, with some fields only used in debug builds omitted:
*/ 

typedef struct _typeobject {
    PyObject_VAR_HEAD

    const char *tp_name; /* For printing, in format "<module>.<name>" */

    Py_ssize_t tp_basicsize, tp_itemsize; /* For allocation */

    /* Methods to implement standard operations */

    destructor tp_dealloc;
    printfunc tp_print;

    getattrfunc tp_getattr;

    setattrfunc tp_setattr;

    PyAsyncMethods *tp_as_async; /* formerly known as tp_compare (Python 2)
                                    or tp_reserved (Python 3) */
    reprfunc tp_repr;

    /* Method suites for standard classes */

    PyNumberMethods *tp_as_number;
    PySequenceMethods *tp_as_sequence;
    PyMappingMethods *tp_as_mapping;

    /* More standard operations (here for binary compatibility) */

    hashfunc tp_hash;
    ternaryfunc tp_call;

    reprfunc tp_str;

    getattrofunc tp_getattro;

    setattrofunc tp_setattro;

    /* Functions to access object as input/output buffer */

    PyBufferProcs *tp_as_buffer;

    /* Flags to define presence of optional/expanded features */

    unsigned long tp_flags;

    const char *tp_doc; /* Documentation string */

    /* call function for all accessible objects */

    traverseproc tp_traverse;

    /* delete references to contained objects */

    inquiry tp_clear;

    /* rich comparisons */

    richcmpfunc tp_richcompare;

    /* weak reference enabler */

    Py_ssize_t tp_weaklistoffset;

    /* Iterators */

    getiterfunc tp_iter;

    iternextfunc tp_iternext;

    /* Attribute descriptor and subclassing stuff */

    struct PyMethodDef *tp_methods;
    struct PyMemberDef *tp_members;
    struct PyGetSetDef *tp_getset;
    struct _typeobject *tp_base;

    PyObject *tp_dict;

    descrgetfunc tp_descr_get;
    descrsetfunc tp_descr_set;

    Py_ssize_t tp_dictoffset;

    initproc tp_init;
    allocfunc tp_alloc;

    newfunc tp_new;

    freefunc tp_free; /* Low-level free-memory routine */

    inquiry tp_is_gc; /* For PyObject_IS_GC */

    PyObject *tp_bases;

    PyObject *tp_mro; /* method resolution order */

    PyObject *tp_cache;
    PyObject *tp_subclasses;
    PyObject *tp_weaklist;

    destructor tp_del;

    /* Type attribute cache version tag. Added in version 2.6 */

    unsigned int tp_version_tag;

    destructor tp_finalize;

} PyTypeObject;

/* 
  Now that’s a lot of methods. Don’t worry too much though – if you have a type you want to define, the chances are very good that you will only implement
  a handful of these.
  As you probably expect by now, we’re going to go over this and give more information about the various handlers.
  We won’t go in the order they are defined in the structure, because there is a lot of historical baggage that impacts the ordering of the fields.
  It’s often easiest to find an example that includes the fields you need and then change the values to suit your new type.
*/ 

const char *tp_name; /* For printing */

/* 
  The name of the type – as mentioned in the previous chapter, this will appear in various places, almost entirely for diagnostic purposes.
  Try to choose something that will be helpful in such a situation!
*/ 

Py_ssize_t tp_basicsize, tp_itemsize; /* For allocation */

/* 
  These fields tell the runtime how much memory to allocate when new objects of this type are created.
  Python has some built-in support for variable length structures (think: strings, tuples) which is where the tp_itemsize field comes in.
*/ 

const char *tp_doc;

/* 
 Here you can put a string (or its address) that you want returned when the Python script references obj.__doc__ to retrieve the doc string.
*/