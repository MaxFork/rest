
from subprocess import run, PIPE
import sys

files = [
    'main.c', 'mains.h',

    'scl.h', 'ctypes.h',

    'restypes.h', 'rescore.h', 'resfig.h', 'restokens.h',

    'make.bat', 'add.py', 'README.md',

    'design',
]


def run_command(string):
    print(string)
    run(string, shell=True, stdout=sys.stdout, stderr=sys.stderr)

run_command('git add {}'.format(' '.join(files)))
