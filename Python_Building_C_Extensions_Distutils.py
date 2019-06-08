# Python Building C and C++ Extensions with distutils
# Extension modules can be built using distutils, which is included in Python.
# Since distutils also supports creation of binary packages, users don’t necessarily need a compiler and distutils to install the extension.
#

# 
# A distutils package contains a driver script, setup.py.
# This is a plain Python file, which, in the most simple case, could look like this:
# 

from distutils.core import setup, Extension

module1 = Extension('demo',
                    sources = ['demo.c'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
