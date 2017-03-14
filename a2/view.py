#!/usr/bin/python3
import sys,time
import os

def isAuthor (filename,username):
	search = username + " "
	fp = open(filename)
	line = fp.readline()
	while line:
		if search in line:
			fp.close()
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

#def getPostStart(lastRead,postLocations):
#	if(lastRead==0):
#		return 0
#	start = int(postLocations[int(lastRead)-1])+1
#	return start

def countPosts(filename):
	fp = open(filename)
	count=0
	line = fp.readline()
	while line:
		if("Sender: " in line):
			count=count+1
		line = fp.readline()

	fp.close()
	return count

def modifyUserFile(filename, username, readPosts):
	fpR = open(filename)
	tempFile = filename+"temp"
	fpW = open(tempFile,"w")

	line  = fpR.readline()
	while line:
		if(username not in line):
			fpW.write(line)
		else:
			newRead = int(line[len(username)+1:])
			newRead = newRead + readPosts
			fpW.write(username+" "+str(newRead))
		line = fpR.readline()	
	fpR.close()
	fpW.close()
	os.remove(filename)
	os.rename(tempFile,filename)

def nextPostStart(filename,lastRead):
	if(int(lastRead) ==0):
		return 0
	post = 0
	toRead=0
	end = 0;
	fp = open(filename)
	line =fp.readline()
	while line:
		if("Sender: " in line):
			post = post + 1
		
		if(post>int(lastRead)):
			fp.close()
			return toRead -1

		toRead = toRead +1
		line = fp.readline()

	fp.close()
	return end



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

start = nextPostStart(streamFile,lastRead)
print (start)
c = 'x'
print(chr(27) + "[2J")
print ("Stream: ",ui)
while c!="q":
	if(c=="m"):
		modifyUserFile(userFile,user,countPosts(streamFile))
	if(c=="s"):
		print (', '.join(usersStreams))
	
	newlines = (countNewLines(streamFile,0))
	if(newlines<23):
		fp = open(streamFile)
		line = fp.readline()
		while line:
			print(line[:len(line)-1])
			line = fp.readline()
		fp.close
		modifyUserFile(userFile,user,countPosts(streamFile))
		
		for i in range(23-newlines):
			print (" ")
	else:
		print("do stuff for more than 23 lines")
	print ("Pg Dn    Pg Up    O-order toggle    M-Mark all    S-Stream    C-Check for new", end='')

	c = input()
