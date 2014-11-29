#!/usr/bin/python

import sys

def readfile(name):
	line = ''
	with open(name) as f1:
		line=f1.read().replace('\n','')
	return line


for i in range(1,len(sys.argv)):
	line = readfile(sys.argv[i])
	print hex(int(line, 2))
