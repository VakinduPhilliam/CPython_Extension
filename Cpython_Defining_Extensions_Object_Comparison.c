/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Object Comparison:
 richcmpfunc tp_richcompare;
 The tp_richcompare handler is called when comparisons are needed.
 It is analogous to the rich comparison methods, like __lt__(), and also called by PyObject_RichCompare() and PyObject_RichCompareBool().
 This function is called with two Python objects and the operator as arguments, where the operator is one of Py_EQ, Py_NE, Py_LE, Py_GT, Py_LT or Py_GT.
 It should compare the two objects with respect to the specified operator and return Py_True or Py_False if the comparison is successful, Py_NotImplemented
 to indicate that comparison is not implemented and the other object’s comparison method should be tried, or NULL if an exception was set.
*/

/* 
 Here is a sample implementation, for a datatype that is considered equal if the size of an internal pointer is equal:
*/ 

static PyObject *

newdatatype_richcmp(PyObject *obj1, PyObject *obj2, int op)

{
    PyObject *result;
    int c, size1, size2;

    /* code to make sure that both arguments are of type
       newdatatype omitted */

    size1 = obj1->obj_UnderlyingDatatypePtr->size;
    size2 = obj2->obj_UnderlyingDatatypePtr->size;

    switch (op) {

    case Py_LT: c = size1 <  size2; break;
    case Py_LE: c = size1 <= size2; break;

    case Py_EQ: c = size1 == size2; break;
    case Py_NE: c = size1 != size2; break;

    case Py_GT: c = size1 >  size2; break;
    case Py_GE: c = size1 >= size2; break;

    }

    result = c ? Py_True : Py_False;
    Py_INCREF(result);

    return result;

 }
