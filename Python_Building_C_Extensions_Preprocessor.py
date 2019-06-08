# Python Building C and C++ Extensions
# It is common to pre-compute arguments to setup(), to better structure the driver script. 
# The ext_modules argument to setup() can be a list of extension modules, each of which is an instance of the Extension.
# The instance defines an extension named demo which is build by compiling a single source file, demo.c.
# In many cases, building an extension is more complex, since additional preprocessor defines and libraries may be needed.
#

#
# This is demonstrated in the example below.
# 

from distutils.core import setup, Extension

module1 = Extension('demo',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['tcl83'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['demo.c'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       author = 'Martin v. Loewis',
       author_email = 'martin@v.loewis.de',
       url = 'https://docs.python.org/extending/building',
       long_description = '''
This is really just a demo package.
''',
       ext_modules = [module1])
