/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Type-specific Attribute Management
 For simplicity, only the char* version will be demonstrated here; the type of the name parameter is the only difference between the char* and PyObject*
 flavors of the interface.
 This example effectively does the same thing as the generic example above, but does not use the generic support added in Python 2.2.
 It explains how the handler functions are called, so that if you do need to extend their functionality, you’ll understand what needs to be done.
 The tp_getattr handler is called when the object requires an attribute look-up.
 It is called in the same situations where the __getattr__() method of a class would be called.
*/
 
/*
 Here is an example:
*/ 

static PyObject *

newdatatype_getattr(newdatatypeobject *obj, char *name)
{

    if (strcmp(name, "data") == 0)

    {

        return PyLong_FromLong(obj->data);

    }

    PyErr_Format(PyExc_AttributeError,
                 "'%.50s' object has no attribute '%.400s'",
                 tp->tp_name, name);

    return NULL;

}

/* 
 The tp_setattr handler is called when the __setattr__() or __delattr__() method of a class instance would be called.
 When an attribute should be deleted, the third parameter will be NULL.
*/

/*
 Here is an example that simply raises an exception; if this were really all you wanted, the tp_setattr handler should be set to NULL.
*/ 

static int

newdatatype_setattr(newdatatypeobject *obj, char *name, PyObject *v)

{
    PyErr_Format(PyExc_RuntimeError, "Read-only attribute: %s", name);

    return -1;

}
