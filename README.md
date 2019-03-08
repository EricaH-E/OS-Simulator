# OS-Simulator
A program that simulates the basic flow of an operating system

 TO COMPILE TYPE: make all
 
 TO RUN EXECUTABLE TYPE: ./OS_Simulator

NOTE : IN ADDITION TO LRU PROGRAM REUSES FRAMES OF TERMINATED PROCESS BEFORE
       USING A NEW FRAME IF SPACE EXIST

PROGRAM IS ALSO SPACE SENSITIVE IN ADDITION TO CASE SENSITIVE

# Valid Commands and What they do 

**A**       ‘A’ input means that a new process has been created. 

**Q**       The currently running process has spent a time quantum using the CPU. If the same process continues to use the CPU and one more Q command arrives, it means that the process has spent one more time quantum.

**t**        The process that is currently using the CPU terminates. It leaves the system immediately. 

**d number file_name**      The process that currently uses the CPU requests the hard disk #number. It wants to read or write file file_name.

**D number**    The hard disk #number has finished the work for one process.

**m address**   The process that is currently using the CPU requests a memory operation for the logical address.

**S r**     Shows what process is currently using the CPU and what processes are waiting in the ready-queue. 

**S i**     Shows what processes are currently using the hard disks and what processes are waiting to use them. 

**S m**     Shows the state of memory. 


**The following project is a class project following the professors instructions as to  what the program should do when given the commands above. The professor gave no instruction on how it should be implemented**
