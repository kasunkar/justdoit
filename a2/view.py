#!/usr/bin/python
import sys
import os

def isAuthor (filename,username):
	search = username + " "
	fp = open(filename)
	line = fp.readline()
	while line:
		if search in line:
			return 1
		line=fp.readline()
	fp.close()
	return 0

def getLastRead(filename,username):
	search = username + " "
	fp = open(filename)
	line = fp.readline()
	while line:
		if search in line:
			return line[len(search):]
		line=fp.readline()
	fp.close()
	return -1

def getDataList(filename):
	fp = open(filename)
	numbers=[]
	line = fp.readline()
	while line:
		numbers.append(line)

	return numbers


user = str(sys.argv[1])
usersStreams=[]

for file in os.listdir("."):
    if file.endswith("StreamUsers"):
        if isAuthor(file,user) == 1:
        	usersStreams.append(file[:len(file)-11])

usersStreams.append("all")

print ' '.join(usersStreams)

ui = raw_input()

if ui not in usersStreams:
	print "not a valid option"
	sys.exit()

if ui == "all":
	del usersStreams[-1]
	for i in range(len(usersStreams)):
		usersStreams[i] = usersStreams[i] + "StreamUsers"
	sys.exit()


userFile = ui+"StreamUsers"
dataFile = ui+"StreamData"

print user+ " has read"
lastRead  =  getLastRead(userFile,user)

postLocations = getDataList