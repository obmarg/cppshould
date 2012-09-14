#!/usr/bin/env python
'''
srcgen.py

This script extracts comments in .rst format from C++ source files
and outputs them to .rst files.

Currently it uses the same file & folder structure as the input
source files for the output source files.

Usage:
    srcgen.py inputdir outputdir
'''

import os
import re
from argparse import ArgumentParser

# The file extensions recognised as source files
FILE_EXTENSIONS = ['h', 'hpp', 'cpp']

# The output file extension
OUTPUT_EXTENSION = '.rst'

# The RST comment marker
RST_COMMENT = '//!'
RST_REGEXP = re.compile('^//! ?')

# The seperator between output blocks
BLOCK_SEPERATOR = '\n\n'


def ParseFile(infile, outfile):
    '''
    Parses a file for .rst comments and outputs them if needed

    Params:
        infile - The input file
        outfile - The output file
    Returns:
        True if outfile was written to
    '''
    written = False
    inblock = False
    stripped = (line.lstrip() for line in infile)
    for line in stripped:
        if line.startswith(RST_COMMENT):
            written = inblock = True
            outfile.write(RST_REGEXP.sub('', line))
        elif inblock:
            inblock = False
            outfile.write(BLOCK_SEPERATOR)
    return written


def ProcessFile(infilename, indir, outdir):
    '''
    Processes a file into it's output file

    Params:
        infilename - The path to the input file
        indir      - The input directory
        outdir     - The output directory name
    '''
    outfilename = os.path.join(outdir, os.path.relpath(infilename, indir))
    outfilename = os.path.splitext(outfilename)[0] + OUTPUT_EXTENSION
    outdir = os.path.dirname(outfilename)
    print "Processing {0} to {1}".format(infilename, outfilename)
    with open(infilename) as infile:
        try:
            os.makedirs(outdir)
        except OSError:
            pass  # Probably just already exists
        with open(outfilename, 'w') as outfile:
            written = ParseFile(infile, outfile)
        if not written:
            os.unlink(outfilename)
            # TODO: probably want to remove directories too


def Run(indir, outdir):
    '''
    Runs the program

    Params:
        indir   - The input directory
        outdir  - The output directory
    '''
    for dirpath, x, files in os.walk(indir):
        print "Processing dir {0}".format(dirpath)
        for filename in files:
            ProcessFile(os.path.join(dirpath, filename), indir, outdir)


if __name__ == "__main__":
    parser = ArgumentParser(
            description='Parses document comments from C++ source files '
                        'into .rst files'
            )
    parser.add_argument(
            'inputdir', metavar='INPUTDIR', help='The input directory'
            )
    parser.add_argument(
            'outputdir', metavar='OUTPUTDIR', help='The output directory'
            )

    args = parser.parse_args()
    Run(args.inputdir, args.outputdir)



