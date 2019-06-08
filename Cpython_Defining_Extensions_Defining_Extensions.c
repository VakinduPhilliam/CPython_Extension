/*
 Cpython Defining Extensions:
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Object Presentation:
 In Python, there are two ways to generate a textual representation of an object: the repr() function, and the str() function.
 (The print() function just calls str().) These handlers are both optional.
*/ 

reprfunc tp_repr;

reprfunc tp_str;

/* 
 The tp_repr handler should return a string object containing a representation of the instance for which it is called.
*/

/*
 Here is a simple example:
*/ 

static PyObject *

newdatatype_repr(newdatatypeobject * obj)

{
    return PyUnicode_FromFormat("Repr-ified_newdatatype{{size:%d}}",
                                obj->obj_UnderlyingDatatypePtr->size);

}

/* 
 If no tp_repr handler is specified, the interpreter will supply a representation that uses the type’s tp_name and a uniquely-identifying value for the
 object.
 The tp_str handler is to str() what the tp_repr handler described above is to repr(); that is, it is called when Python code calls str() on an instance of
 your object.
 Its implementation is very similar to the tp_repr function, but the resulting string is intended for human consumption.
 If tp_str is not specified, the tp_repr handler is used instead.
*/

/* 
 Here is a simple example:
*/ 

static PyObject *
newdatatype_str(newdatatypeobject * obj)

{

    return PyUnicode_FromFormat("Stringified_newdatatype{{size:%d}}",
                                obj->obj_UnderlyingDatatypePtr->size);
}
