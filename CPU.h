#ifndef CPU_H_
#define CPU_H_

#include <iostream>
#include <queue>

using namespace std;

class CPU
{
 public:
	explicit CPU();

	//@returns pid of  terminated process
	unsigned int terminator();

	//@returns current process using cpu
	unsigned int cpu_state();

	//Prints processes in the cpu
	void Print();

	/*
	  @param: pid :process requesting to use the CPU
	  @param: lvl :designated priortiy level, default to first  level in CPU for new processes
	 */
	void request_usage(unsigned int pid, int lvl= 1);

	//@returns: current  active level  in CPU
	int  current_level();

	//indicates time quantam
	void quantum();

 private:


	struct Process
    	{
        	Process(int p, int q=0): process(p), quantam(q) {}
       	 	int process;
        	int quantam;//how long process has spent in CPU
    	};

	//Multilevel feedback queue 
	queue<Process>level0;
	queue<Process>level1;
	queue<Process>level2;

  
	bool IsBusy= false;   // CPU Status
	void Printer(queue<Process> q); //Prints a copy of busy queues in multilevel feedback queues
 
};


#endif
