import sys, json, re

{
  "directory": "/tmp/build/bundle/debug/grib_api/src",
  "command": "/usr/bin/gcc  -DHAVE_GRIB_API_CONFIG_H -Dgrib_api_EXPORTS -fPIC -pipe -pedantic -O0 -g -fPIC -I/tmp/build/bundle/debug/grib_api/fortran/modules -I/tmp/build/bundle/debug/grib_api -I/home/ma/mak/Dropbox/work/odbserver_bundle/grib_api/src -I/tmp/build/bundle/debug/grib_api/src -I/usr/local/apps/netcdf/3.6.3/GNU/4.8.1/include -I/usr/local/apps/python/2.7.8-01/include/python2.7    -o CMakeFiles/grib_api.dir/grib_api_version.c.o   -c /tmp/build/bundle/debug/grib_api/src/grib_api_version.c",
  "file": "/tmp/build/bundle/debug/grib_api/src/grib_api_version.c"
}


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


cmake_commands = '/var/tmp/build/bundle/debug/compile_commands.json'
cmds = json.loads(open(cmake_commands).read())
for cmd in cmds:
    options = parseCommand(cmd)

    output = options['o']
    input = options['c']

    #if not output.endswith('.o'): print output
    if not fileHasMain(input):
        print input 
