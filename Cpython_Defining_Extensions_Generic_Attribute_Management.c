/*
 Cpython Defining Extensions
 Defining Extension Types and the various type methods you can implement and what they do.
*/

/*
 Generic Attribute Management:
 Most extension types only use simple attributes. So, what makes the attributes simple? There are only a couple of conditions that must be met:
 1.The name of the attributes must be known when PyType_Ready() is called.
 2.No special processing is needed to record that an attribute was looked up or set, nor do actions need to be taken based on the value.
*/

/*
 Note that this list does not place any restrictions on the values of the attributes, when the values are computed, or how relevant data is stored.
 When PyType_Ready() is called, it uses three tables referenced by the type object to create descriptors which are placed in the dictionary of the type
 object.
 Each descriptor controls access to one attribute of the instance object.
 Each of the tables is optional; if all three are NULL, instances of the type will only have attributes that are inherited from their base type, and should
 leave the tp_getattro and tp_setattro fields NULL as well, allowing the base type to handle attributes.
*/

/* 
 The tables are declared as three fields of the type object:
*/ 

struct PyMethodDef *tp_methods;
struct PyMemberDef *tp_members;
struct PyGetSetDef *tp_getset;

/* 
 If tp_methods is not NULL, it must refer to an array of PyMethodDef structures.
 Each entry in the table is an instance of this structure:
*/ 

typedef struct PyMethodDef {
    const char  *ml_name;       /* method name */
    PyCFunction  ml_meth;       /* implementation function */

    int          ml_flags;      /* flags */
    const char  *ml_doc;        /* docstring */

} PyMethodDef;

/* 
 One entry should be defined for each method provided by the type; no entries are needed for methods inherited from a base type.
 One additional entry is needed at the end; it is a sentinel that marks the end of the array.
 The ml_name field of the sentinel must be NULL.
*/

/* 
 The second table is used to define attributes which map directly to data stored in the instance.
 A variety of primitive C types are supported, and access may be read-only or read-write.
 The structures in the table are defined as:
*/ 

typedef struct PyMemberDef {
    const char *name;

    int         type;
    int         offset;

    int         flags;

    const char *doc;

} PyMemberDef;
