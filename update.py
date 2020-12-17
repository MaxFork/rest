
from subprocess import run, PIPE
import sys

def run_command(string):
    print(string)
    run(string, shell=True, stdout=sys.stdout, stderr=sys.stderr)

run_command('git add .')
run_command('git commit -am "update"')
