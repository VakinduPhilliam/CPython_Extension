/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Abstract Protocol Support:
 Python supports a variety of abstract ‘protocols;’ the specific interfaces provided to use these interfaces are documented in Abstract Objects Layer.
 A number of these abstract interfaces were defined early in the development of the Python implementation. In particular, the number, mapping, and sequence
 protocols have been part of Python since the beginning.
 Other protocols have been added over time.
 For protocols which depend on several handler routines from the type implementation, the older protocols have been defined as optional blocks of handlers
 referenced by the type object.
 For newer protocols there are additional slots in the main type object, with a flag bit being set to indicate that the slots are present and should be
 checked by the interpreter.
 (The flag bit does not indicate that the slot values are non-NULL.
 The flag may be set to indicate the presence of a slot, but a slot may still be unfilled.)
*/ 

PyNumberMethods   *tp_as_number;
PySequenceMethods *tp_as_sequence;
PyMappingMethods  *tp_as_mapping;

/* 
 If you wish your object to be able to act like a number, a sequence, or a mapping object, then you place the address of a structure that implements the
 C type PyNumberMethods, PySequenceMethods, or PyMappingMethods, respectively.
 It is up to you to fill in this structure with appropriate values.
 You can find examples of the use of each of these in the Objects directory of the Python source distribution.
*/ 

 hashfunc tp_hash;

/*
 This function, if you choose to provide it, should return a hash number for an instance of your data type.
*/

/*
 Here is a simple example:
*/ 

static Py_hash_t

newdatatype_hash(newdatatypeobject *obj)

{
    Py_hash_t result;

    result = obj->some_size + 32767 * obj->some_number;

    if (result == -1)
       result = -2;

    return result;

}

/* 
 Py_hash_t is a signed integer type with a platform-varying width. Returning -1 from tp_hash indicates an error, which is why you should be careful to avoid
 returning it when hash computation is successful, as seen above.
*/ 

ternaryfunc tp_call;

/* 
 This function is called when an instance of your data type is “called”, for example, if obj1 is an instance of your data type and the Python script contains
 obj1('hello'), the tp_call handler is invoked.
 
 This function takes three arguments:
 1.self is the instance of the data type which is the subject of the call. If the call is obj1('hello'), then self is obj1.
 2.args is a tuple containing the arguments to the call. You can use PyArg_ParseTuple() to extract the arguments.
 3.kwds is a dictionary of keyword arguments that were passed. If this is non-NULL and you support keyword arguments, use PyArg_ParseTupleAndKeywords() to
   extract the arguments.
 If you do not want to support keyword arguments and this is non-NULL, raise a TypeError with a message saying that keyword arguments are not supported.
*/

/* 
 Here is a toy tp_call implementation:
*/ 

static PyObject *

newdatatype_call(newdatatypeobject *self, PyObject *args, PyObject *kwds)

{
    PyObject *result;

    const char *arg1;
    const char *arg2;
    const char *arg3;

    if (!PyArg_ParseTuple(args, "sss:call", &arg1, &arg2, &arg3)) {

        return NULL;

    }

    result = PyUnicode_FromFormat(
        "Returning -- value: [%d] arg1: [%s] arg2: [%s] arg3: [%s]\n",
        obj->obj_UnderlyingDatatypePtr->size,
        arg1, arg2, arg3);

    return result;

}
 

/* Iterators */

getiterfunc tp_iter;

iternextfunc tp_iternext;

/* 
 These functions provide support for the iterator protocol.
 Both handlers take exactly one parameter, the instance for which they are being called, and return a new reference.
 In the case of an error, they should set an exception and return NULL. tp_iter corresponds to the Python __iter__() method, while tp_iternext corresponds
 to the Python __next__() method.
 
 Any iterable object must implement the tp_iter handler, which must return an iterator object. Here the same guidelines apply as for Python classes:
 > For collections (such as lists and tuples) which can support multiple independent iterators, a new iterator should be created and returned by each call
   to tp_iter.
 > Objects which can only be iterated over once (usually due to side effects of iteration, such as file objects) can implement tp_iter by returning a new
   reference to themselves – and should also therefore implement the tp_iternext handler.
 
 Any iterator object should implement both tp_iter and tp_iternext. An iterator’s tp_iter handler should return a new reference to the iterator.
 Its tp_iternext handler should return a new reference to the next object in the iteration, if there is one.
 If the iteration has reached the end, tp_iternext may return NULL without setting an exception, or it may set StopIteration in addition to returning NULL;
 avoiding the exception can yield slightly better performance.
 If an actual error occurs, tp_iternext should always set an exception and return NULL.
*/