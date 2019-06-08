# CPython API
# To support extensions, the Python API (Application Programmers Interface) defines a set of functions, macros and variables that provide access to most
# aspects of the Python run-time system.
# The Python API is incorporated in a C source file by including the header "Python.h".
# The compilation of an extension module depends on its intended use as well as on your system setup.
#

#
# Note:
# The C extension interface is specific to CPython, and extension modules do not work on other Python implementations.
# In many cases, it is possible to avoid writing C extensions and preserve portability to other implementations.
# For example, if your use case is calling C library functions or system calls, you should consider using the ctypes module or the cffi library rather than
# writing custom C code.
# These modules let you write Python code to interface with C code and are more portable between implementations of Python than writing and compiling a C
# extension module.
# 

#
# Let’s create an extension module called spam (the favorite food of Monty Python fans…) and let’s say we want to create a Python interface to the C library
# function system(). 
# This function takes a null-terminated character string as argument and returns an integer. 
# We want this function to be callable from Python as follows:
# 

import spam

status = spam.system("ls -l")

#
# Begin by creating a file spammodule.c. (Historically, if a module is called spam, the C file containing its implementation is called spammodule.c; if the
# module name is very long, like spammify, the module name can be just spammify.c.)
#