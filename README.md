# CPython_Extension
The following scripts are written to demonstrate how to extend the Python Programming language with C and C++. 
To support extensions, the Python API (Application Programmers Interface) defines a set of functions, macros and variables that provide access to most aspects of the Python run-time system. 
The Python API is incorporated in a C source file by including the header "Python.h".  The compilation of an extension module depends on its intended use as well as on your system setup.  
Note:  The C extension interface is specific to CPython, and extension modules do not work on other Python implementations. In many cases, it is possible to avoid writing C extensions and preserve portability to other implementations. For example, if your use case is calling C library functions or system calls, you should consider using the ctypes module or the cffi library rather than writing custom C code. 
These modules let you write Python code to interface with C code and are more portable between implementations of Python than writing and compiling a C extension module. 
Compiled and presented by Vakindu Philliam.
