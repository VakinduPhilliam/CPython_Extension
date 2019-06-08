/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Weak Reference Support:
 One of the goals of Python’s weak reference implementation is to allow any type to participate in the weak reference mechanism without incurring the
 overhead on performance-critical objects (such as numbers). 

 For an object to be weakly referencable, the extension type must do two things:
 1.Include a PyObject* field in the C object structure dedicated to the weak reference mechanism.
   The object’s constructor should leave it NULL (which is automatic when using the default tp_alloc).
 2.Set the tp_weaklistoffset type member to the offset of the aforementioned field in the C object structure, so that the interpreter knows how to access
   and modify that field.
 
 Concretely, here is how a trivial object structure would be augmented with the required field:
*/ 

typedef struct {
    PyObject_HEAD

    PyObject *weakreflist;  /* List of weak references */

} TrivialObject;
 
/*
 And the corresponding member in the statically-declared type object:
*/ 

static PyTypeObject TrivialType = {
    PyVarObject_HEAD_INIT(NULL, 0)

    /* ... other members omitted for brevity ... */

    .tp_weaklistoffset = offsetof(TrivialObject, weakreflist),

};

/* 
 The only further addition is that tp_dealloc needs to clear any weak references (by calling PyObject_ClearWeakRefs()) if the field is non-NULL:
*/ 

static void

Trivial_dealloc(TrivialObject *self)

{

    /* Clear weakrefs first before calling any destructors */

    if (self->weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *) self);

    /* ... remainder of destruction code omitted for brevity ... */

    Py_TYPE(self)->tp_free((PyObject *) self);

}
