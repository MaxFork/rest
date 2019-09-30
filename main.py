
import collections
import grammar

class Node:
    __slots__ = ['name', 'data', 'tests']
    def __init__(self, data = None, tests = None, job = None):
        self.name = name
        self.data = data
        if tests is None:
            tests = collections.deque()
        self.tests = tests

END = 0
DEFAULT = 1

root = Node('root')
child1 = Node('child1', ('test', END))
child2 = Node('chidl2', ('test', 'a'))

root.tests.append(child1)
root.tests.append(child2)
