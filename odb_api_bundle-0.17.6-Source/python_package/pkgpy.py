# -*- coding: utf-8 -*-
# http://clang.llvm.org/docs/JSONCompilationDatabase.html

import sys, json, re, os, shutil, fnmatch
from setuptools import setup, Extension


{
  "directory": "/tmp/build/bundle/debug/grib_api/src",
  "command": "/usr/bin/gcc  -DHAVE_GRIB_API_CONFIG_H -Dgrib_api_EXPORTS -fPIC -pipe -pedantic -O0 -g -fPIC -I/tmp/build/bundle/debug/grib_api/fortran/modules -I/tmp/build/bundle/debug/grib_api -I/home/ma/mak/Dropbox/work/odbserver_bundle/grib_api/src -I/tmp/build/bundle/debug/grib_api/src -I/usr/local/apps/netcdf/3.6.3/GNU/4.8.1/include -I/usr/local/apps/python/2.7.8-01/include/python2.7    -o CMakeFiles/grib_api.dir/grib_api_version.c.o   -c /tmp/build/bundle/debug/grib_api/src/grib_api_version.c",
  "file": "/tmp/build/bundle/debug/grib_api/src/grib_api_version.c"
}

CMAKE_BUILD_DIRECTORY = '/tmp/build/odb_api_bundle/debug/'
SETUP_PY = """
import os
from setuptools import setup, Extension

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

cpp_sources = %(packaged_cpp_sources)s
    
odb_api_module = Extension('odb_api', 
                           define_macros = [('ODB_API_MAJOR_VERSION', '0'),
                                            ('ODB_API_MINOR_VERSION', '16')],
                           include_dirs = ['/usr/local/include'],
                           sources = cpp_sources) 

setup(
    name = "odb_api",
    version = "0.16.0",
    author = "Piotr Kuchta",
    author_email = "software.support@ecmwf.int",
    license = 'Apache License, Version 2.0',
    url = 'https://software.ecmwf.int/wiki/display/ODBAPI/',
    download_url = 'https://software.ecmwf.int/wiki/display/ODBAPI/Releases',
    packages = ['odb'],
    description = ("ECMWF ODB API Python interface"),
    keywords = "ECMWF ODB API odb_api",
    long_description = read('README'),
    classifiers = [
        "Development Status :: 4 - Beta",
        "Topic :: Utilities",
        "License :: OSI Approved :: Apache 2.0",
    ],
    ext_modules = [odb_api_module],
)

"""


def param(s, options = []):
    for p in options:
        if s.startswith('-' + p):
            return p
    return None

param_options = "D f O I o c W".split()
flag_options = "g pipe pedantic".split()

def paramOption(s): return param(s, options = param_options)
def flagOption(s): return param(s, options = flag_options)

def parseCommand(cmd):
    l = cmd['command'].split()
    command = l[0].split('/')[-1] # "g++" or "gcc"
    options = {}
    i = 0
    while i < len(l):
        w = l[i] 
        if w.startswith('-'):
            if not paramOption(w) and not flagOption(w):
                print 'Unknown option ' + w + " in \n" + cmd['command']
                sys.exit(1)

            param = paramOption(w)

            if param:
                if '-' + param == w:
                    options [param] = l[i + 1]
                    i += 1
                elif w.startswith('-' + param):
                    options [param] = l[i][len('-' + param):]

        i += 1
    return options

def removeComments(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE)
    return re.sub(pattern, replacer, text)

def fileHasMain(fn):
    main_re = re.compile(r'\b(main)\b')
    with open(fn) as f:
        lines = removeComments(f.read()).splitlines()
        for line in lines:
            if main_re .search(line):
                rhs = line.split('main')[1]
                if '(' in rhs and ')' in rhs:
                    #print fn,':', line
                    return True
    return False

def package_source_files(files, package_source_files_directory = 'odb'):
    try: os.makedirs(package_source_files_directory)
    except: pass # assume it failed because it already exists
    # shutil.rmtree(path[, ignore_errors[, onerror]])¶
    for f in files:
        print '',f
        shutil.copy(f, package_source_files_directory)


def compile_commands(file_name = os.path.join(CMAKE_BUILD_DIRECTORY, 'compile_commands.json')):
    return [c for c in json.loads(open(file_name).read())
                if not c[u'directory'].endswith(u'ecbuild/cmake')
                and not fileHasMain(c['file'])
                ]

cmds = compile_commands() 
cpp_sources = [str(c['file']) for c in cmds]

python_sources = [str(os.path.join(CMAKE_BUILD_DIRECTORY, 'odb_api/src/python/odb/', f)) for f in os.listdir(os.path.join(CMAKE_BUILD_DIRECTORY,'odb_api/src/python/odb/')) if fnmatch.fnmatch(f, '*.py')]
print '\n'.join(python_sources)

package_source_files(python_sources, package_source_files_directory = 'odb')
package_source_files(cpp_sources, package_source_files_directory = 'odb_api')

packaged_cpp_sources = [os.path.join('odb_api',f) for f in os.listdir('odb_api')]
print packaged_cpp_sources

with open('setup.py','w') as f:
    f.write(SETUP_PY % locals())
