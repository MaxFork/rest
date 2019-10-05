
from subprocess import run, PIPE
import sys

files = [
    'main.c', 'mains.h',

    'scl.h', 'ctypes.h',

    'restokens.h', 'rescore.h', 'resfig.h',

    'make.bat', 'add.py', 'README.md',
]


def run_command(string):
    print(string)
    run(string, shell=True, stdout=sys.stdout, stderr=sys.stderr)

run_command('git add {}'.format(' '.join(files)))
