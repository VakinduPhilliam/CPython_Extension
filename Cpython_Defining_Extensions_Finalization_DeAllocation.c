/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Finalization and De-allocation
 destructor tp_dealloc;
 This function is called when the reference count of the instance of your type is reduced to zero and the Python interpreter wants to reclaim it.
 If your type has memory to free or other clean-up to perform, you can put it here.
 The object itself needs to be freed here as well.
*/

/*
 Here is an example of this function:
*/ 

static void

newdatatype_dealloc(newdatatypeobject *obj)

{
    free(obj->obj_UnderlyingDatatypePtr);

    Py_TYPE(obj)->tp_free(obj);

}
 
/*
 One important requirement of the deallocator function is that it leaves any pending exceptions alone.
 This is important since deallocators are frequently called as the interpreter unwinds the Python stack; when the stack is unwound due to an exception
 (rather than normal returns), nothing is done to protect the deallocators from seeing that an exception has already been set.
 Any actions which a deallocator performs which may cause additional Python code to be executed may detect that an exception has been set.
 This can lead to misleading errors from the interpreter.
 The proper way to protect against this is to save a pending exception before performing the unsafe action, and restoring it when done.
 This can be done using the PyErr_Fetch() and PyErr_Restore() functions:
*/ 

static void

my_dealloc(PyObject *obj)
{
    MyObject *self = (MyObject *) obj;
    PyObject *cbresult;

    if (self->my_callback != NULL) {
        PyObject *err_type, *err_value, *err_traceback;

        /* This saves the current exception state */

        PyErr_Fetch(&err_type, &err_value, &err_traceback);

        cbresult = PyObject_CallObject(self->my_callback, NULL);

        if (cbresult == NULL)
            PyErr_WriteUnraisable(self->my_callback);

        else
            Py_DECREF(cbresult);

        /* This restores the saved exception state */

        PyErr_Restore(err_type, err_value, err_traceback);

        Py_DECREF(self->my_callback);

    }

    Py_TYPE(obj)->tp_free((PyObject*)self);

}
 
/*
 Note:
 There are limitations to what you can safely do in a deallocator function.
 First, if your type supports garbage collection (using tp_traverse and/or tp_clear), some of the object’s members can have been cleared or finalized by the
 time tp_dealloc is called.
 Second, in tp_dealloc, your object is in an unstable state: its reference count is equal to zero.
 Any call to a non-trivial object or API (as in the example above) might end up calling tp_dealloc again, causing a double free and a crash.
 Starting with Python 3.4, it is recommended not to put any complex finalization code in tp_dealloc, and instead use the new tp_finalize type method.
*/