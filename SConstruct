import sys
import os

platform = sys.platform
if platform != "win32" and platform != 'darwin':
    platform = "linux"

debug = ARGUMENTS.get( 'debug', 0 )

buildtype = 'release'

if int(debug):
    buildtype = 'debug'

installdir = Dir( 'bin' )
depdestdir = Dir( 'build-deps' )

builddir = platform + '_x86_' + buildtype

ccflags = []
cppflags = [ ]
lflags = []
cppdefines = [ ]
cpppath = [
    "#include", '#deps/gtest-1.6.0/include', '#deps/gmock-1.6.0/include'
    ]
libpath = [ depdestdir ]
cc = cxx = None

libs = [ ]

if platform != 'win32':
    if int(debug):
        ccflags += [ '-g' ]
        cppflags += ccflags

if platform == 'linux':
    cppdefines += [ "_LINUX", "LINUX" ]
    cppflags += [ '-fpermissive', "-std=c++0x" ]

if platform == 'darwin':
    cppdefines += [ "_MACOS", 'MACOS' ]
    cppflags += [ "-std=c++11" ]
    cpppath += [ '/opt/local/include' ]
    libpath += [ '/opt/local/lib' ]
    # Macos (on lion anyway) uses an ancient gcc, so let's not use it by
    # default
    cc = 'clang'
    cxx = 'clang++'
    # Also want to use clang stdlib, as gcc 4.2 version isn't great
    cppflags.append( '-stdlib=libc++' )
    lflags.append( '-stdlib=libc++' )
    # libc++ doesn't have TR1
    cppdefines += [ 'GTEST_USE_OWN_TR1_TUPLE=1' ]

# Decide on the compiler to use
if platform != 'win32':
    cc = os.environ.get('CC', cc)
    cxx = os.environ.get('CXX', cxx)

if cc == 'clang':
    # Turn on colors for clang builds
    cppflags.append('-fcolor-diagnostics')
    lflags.append('-fcolor-diagnostics')

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
    'depdestdir',
    'platform',
    'debug'
    )

SConscript( 'SConscript', variant_dir=builddir, duplicate=0 )

#
# Targets
#
alltargets = [
    'bin'
    ]


env.Alias( 'bin', installdir )
env.Alias( 'deps', depdestdir )
env.Alias( 'all', alltargets )

Default( 'all' )
