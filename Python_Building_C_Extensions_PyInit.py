# Python Building C and C++ Extensions.
# A C extension for CPython is a shared library (e.g. a .so file on Linux, .pyd on Windows), which exports an initialization function.
#
# To be importable, the shared library must be available on PYTHONPATH, and must be named after the module name, with an appropriate extension.
# When using distutils, the correct filename is generated automatically.
# 
# The initialization function has the signature:
# 
# PyObject* PyInit_modulename(void): 
# It returns either a fully-initialized module, or a PyModuleDef instance. See Initializing C modules for details.
#

# 
# For modules with ASCII-only names, the function must be named PyInit_<modulename>, with <modulename> replaced by the name of the module.
# When using Multi-phase initialization, non-ASCII module names are allowed.
# In this case, the initialization function name is PyInitU_<modulename>, with <modulename> encoded using Python’s punycode encoding with hyphens replaced
# by underscores.
# 

def initfunc_name(name):

    try:
        suffix = b'_' + name.encode('ascii')

    except UnicodeEncodeError:
        suffix = b'U_' + name.encode('punycode').replace(b'-', b'_')

    return b'PyInit' + suffix
