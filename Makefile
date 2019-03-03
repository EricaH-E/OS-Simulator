#Erica Hendrick-Elliston
#Section 1
#CSCI 340

all: OS_Simulator

OS_Simulator:main.cpp RAM.cpp CPU.cpp HardDisk.cpp
	g++ -std=c++11  -o  OS_Simulator  main.cpp RAM.cpp CPU.cpp HardDisk.cpp  
