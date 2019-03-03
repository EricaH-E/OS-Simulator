#ifndef  RAM_H_ 
#define  RAM_H_

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class RAM
{
 public:
        explicit  RAM(unsigned int cap, unsigned int page , unsigned int  sp);

        //@return: pid of  new process created
        unsigned int new_process();

        // deallocates memory of terminated process
        void terminator(unsigned int process);

        /*@param: pid of process 
          @param: address to access in process
        */
        void address_access( unsigned int process, unsigned int address);

	//Prints  current state of memory i.e frame number, process and page number
        void Print();

 private:
        unsigned int pcount = 1; //keeps track of the number  of processes
        unsigned int  timestamp = 0; // keeps track of  when process is accessed
        const unsigned int capacity; 
        const unsigned int page_size;
        const unsigned int space; //store the max available frames in cpu
        unsigned int framecount = 0;// tracks the number of used frames

	//Object to simulate a pcb and track info of each frame and proccess 
        struct PCB
        {
                PCB(unsigned int f, unsigned int x, unsigned int y, unsigned int z=0): frame(f), pid(x), access_time(y), page(z){}
                unsigned int frame; 
                unsigned int pid;
                unsigned int page;
                unsigned int access_time;

        };

        vector<PCB> Processes;// stores each  PCB object
        queue<unsigned int> vacant;// stores the indices of released frames from terminated processes

};

#endif






