/*
 CPython API
 To support extensions, the Python API (Application Programmers Interface) defines a set of functions, macros and variables that provide access to most
 aspects of the Python run-time system.
 The Python API is incorporated in a C source file by including the header "Python.h".
 The compilation of an extension module depends on its intended use as well as on your system setup.

 Note:
 The C extension interface is specific to CPython, and extension modules do not work on other Python implementations.
 In many cases, it is possible to avoid writing C extensions and preserve portability to other implementations.
 For example, if your use case is calling C library functions or system calls, you should consider using the ctypes module or the cffi library rather than
 writing custom C code.
 These modules let you write Python code to interface with C code and are more portable between implementations of Python than writing and compiling a C
 extension module.
 
*/

/*
 When embedding Python, the PyInit_spam() function is not called automatically unless there’s an entry in the PyImport_Inittab table.
 To add the module to the initialization table, use PyImport_AppendInittab(), optionally followed by an import of the module:
*/ 

int

main(int argc, char *argv[])

{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);

    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");

        exit(1);

    }

    /* Add a built-in module, before Py_Initialize */

    PyImport_AppendInittab("spam", PyInit_spam);

    /* Pass argv[0] to the Python interpreter */

    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required. */

    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */

    PyImport_ImportModule("spam");

    /*             ...            */

    PyMem_RawFree(program);

    return 0;

}
 
/*
 Note:
 Removing entries from sys.modules or importing compiled modules into multiple interpreters within a process (or following a fork() without an intervening
 exec()) can create problems for some extension modules.
 Extension module authors should exercise caution when initializing internal data structures.
*/
 