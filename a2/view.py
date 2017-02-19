#!/usr/bin/python3
import sys,time
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
		numbers.append(line[:-1])
		line = fp.readline()
	fp.close();
	return numbers

def countNewLines(filename,pos):
	fp = open(filename)
	fp.seek(pos)
	count=0
	line = fp.readline()		
	while line:
		count=count+1
		line = fp.readline()
	fp.close();
	return count

def getStreamStart(postNumber,postLocations):
	if(postNumber==0):
		return 0
	return postLocations[postNumber-1]+1


user = str(sys.argv[1])
usersStreams=[]

for file in os.listdir("."):
    if file.endswith("StreamUsers"):
        if isAuthor(file,user) == 1:
        	usersStreams.append(file[:len(file)-11])

usersStreams.append("all")

print (', '.join(usersStreams))
ui = input()

if ui not in usersStreams:
	print ("not a valid option")
	sys.exit()

if ui == "all":
	del usersStreams[-1]
	for i in range(len(usersStreams)):
		usersStreams[i] = usersStreams[i] + "StreamUsers"
	sys.exit()

streamFile = ui+"Stream"
userFile = ui+"StreamUsers"
dataFile = ui+"StreamData"

lastRead  =  getLastRead(userFile,user)

postLocations = getDataList(dataFile)
c = 'x'
print(chr(27) + "[2J")
while c!="q":
	newlines = (countNewLines(streamFile,0))
	if(newlines<23):
		fp = open(streamFile)
		line = fp.readline()
		while line:
			print(line[:len(line)-1])
			line = fp.readline()
		fp.close
	for i in range(23-newlines):
		print (" ")
	print ("Pg Dn    Pg Up    O-order toggle    M-Mark all    S-Stream    C-Check for new", end='')

	c = input()

