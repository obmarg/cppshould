import sys

platform = sys.platform
if platform != "win32" and platform != 'darwin':
    platform = "linux"

debug = ARGUMENTS.get( 'debug', 0 )

buildtype = 'release'

if int(debug):
    buildtype = 'debug'

installdir = Dir( 'bin' )

builddir = platform + '_x86_' + buildtype

ccflags = []
cppflags = [ ]
lflags = []
cppdefines = [ 'BOOST_FILESYSTEM_VERSION=2' ]
cpppath = [ "#include" ]
libpath = []
cc = cxx = None

libs = [ ]

if platform != 'win32':
    if int(debug):
        ccflags += [ '-g' ]
        cppflags += ccflags

if platform == 'linux':
    cppdefines += [ "_LINUX", "LINUX" ]
    cppflags += [ '-fpermissive', "-std=c++0x" ]
    libs += [ 'boost_thread' ]

if platform == 'darwin':
    cppdefines += [ "_MACOS", 'MACOS' ]
    cppflags += [ "-std=c++11" ]
    cpppath += [ '/opt/local/include' ]
    libpath += [ '/opt/local/lib' ]
    cc = 'clang'
    cxx = 'clang++'

if platform == 'win32':
    ccflags += [ '/nologo', '/W3', '/WX', '/FC', '/Z7', '/Zl' ]
    lflags += [ '/MAP', '/MANIFEST:NO', '/MACHINE:X86' ]
    if int(debug):
        ccflags += [ '/Od', '/MDd', '/RTC1' ]
        lflags += [ '/DEBUG' ]
    else:
        ccflags += [ '/O2', '/Oy-', '/MD', '/GL', '/Gy' ]
        lflags += [ '/OPT:REF', '/OPT:ICF', '/LTCG' ]

    cppflags = ccflags + [ '/EHsc', '/GR' ]
    cppdefines += [
        'WIN32', '_CONSOLE', '_WIN32_WINNT=0x0501',
        '_SCL_SECURE_NO_WARNINGS'
        ]

    buildtype = 'Release'
    if int(debug):
        buildtype = 'Debug'

if int(debug):
    cppdefines += [ '_DEBUG' ]
else:
    cppdefines += [ 'NDEBUG' ]


cppdirs = [ ]

libtargetdir = Dir( "lib/" + builddir )

libpath += [
    libtargetdir
    ]

env = Environment()


env.Append(
    CPPPATH = cpppath,
    LIBPATH=libpath,
    CPPDEFINES=cppdefines,
    CCFLAGS=ccflags,
    CXXFLAGS=cppflags,
    LINKFLAGS=lflags
    )
env.Append( CPPPATH= cppdirs )

if cc != None:
    env.Replace(
            CC=cc,
            CXX=cxx
            )

Export(
    'env',
    'libs',
    'installdir',
    'platform',
    'debug'
    )

SConscript( 'SConscript', variant_dir=builddir, duplicate=0 )

#
# Targets
#
alltargets = [
    'libs',
    'bin',
    'test'
    ]


env.Alias( 'libs', libtargetdir )
env.Alias( 'bin', installdir )
env.Alias( 'all', alltargets )

Default( 'all' )
