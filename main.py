
import collections
from grammar import *
import pprint
from printf import *
import sys
import re

keywords_pattern = '[a-z]+'

match_keyword_pattern = lambda string: re.fullmatch(keywords_pattern, string)

for name, keyword in keywords.items():
    if not match_keyword_pattern(keyword):
        printf_line('keyword for name \'{}\' does not match pattern {!r}',
            name, keywords_pattern)
        sys.exit(1)

new_list = lambda *args: list(args)

class TestNode:
    __slots__ = ['test', 'next']
    def __init__(self, test, next = None):
        if next is None:
            next = new_list()
        self.test = test
        self.next = next

    def __repr__(self):
        if self.next:
            return 'Test({!r}, next = {!r})'.format(self.test, self.next)
        return 'Test({!r})'.format(self.test)

    def append(self, value):
        self.next.append(value)

class JobNode:
    __slots__ = ['job', 'next']
    def __init__(self, job, next = None):
        if next is None:
            next = new_list()
        self.job = job
        self.next = next

    def __repr__(self):
        if self.next:
            return 'Job({!r}, next = {!r})'.format(self.job, self.next)
        return 'Job({!r})'.format(self.job)

class Node:
    __slots__ = ['data', 'next']
    def __init__(self, data, next = None):
        if next is None:
            next = new_list()
        self.data = data
        self.next = next

    def __repr__(self):
        if self.next:
            return 'Node({}, next = {})'.format(self.data, self.next)
        return 'Node({})'.format(self.data)

    def __eq__(self, other):
        if isinstance(other, Node):
            return self.data == other.data
        return NotImplemented

root = new_list()

def append_list_if_not_exist(ls, value):
    try:
        index = ls.index(value)
    except ValueError:
        ls.append(value)
    else:
        return ls[index]
    return value

for name, keyword in keywords.items():
    node = append_list_if_not_exist(root, Node('EQ:' + keyword[0]))
    if node.next == []:
        node.next = Node('SET_START_INDEX')
    node = node.next

    for ch in keyword[1:]:
        node = append_list_if_not_exist(node.next, Node('EQ:' + ch))

root = {
    'EQ:a': [
        'SET_START_INDEX', {
            'EQ:s': []
        }
    ],
}

root = {}

def update_if_not_exist(d, key, value):
    try:
        return d[key]
    except KeyError:
        d[key] = value
    return value

root['END'] = ['RETURN_NULL_TOKEN']
root['DEFAULT'] = ['SET_START_INDEX', 'ERROR_UNKNOWN_CHAR']

for name, keyword in keywords.items():
    node = update_if_not_exist(root, 'EQ:' + keyword[0], ['SET_START_INDEX', {}])
    node = node[1]
    for ch in keyword[1:-1]:
        node = update_if_not_exist(node, 'EQ:' + ch, {})
    node = update_if_not_exist(node, 'EQ:' + keyword[-1], ['SET_END_INDEX',
        'RETURN_' + name.upper() + '_TOKEN'])


def print_node_tree(node, prefix = '.-'):
    if isinstance(node, dict):
        pass

pprint.pprint(root)
