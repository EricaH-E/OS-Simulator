#ifndef HARD_DISK_H
#define HARD_DISK_H

#include <iostream>
#include <queue>

using namespace std;

class Disk 
{
public:
	// Constructor
	explicit Disk();

	// queue management 
	void request_usage(int process, string filename, int level); // pushes new job on queue if busy

	//@return: pid of process that has finished using the queue 
	unsigned int request_done();


	int returntolevel();
 
	// displays disk and current process using disk , and also queue
	void disk_state (); 


private:
	struct JOB
	{
		JOB( unsigned int p , string j, int l): process(p), filename(j), level(l) {}
		unsigned int process;//stores process number (PID);
		string filename; // stores name of file requested 
		int level; // stores level in ready queue
	};

// status of harddisk
bool Busy = false;

// jobs waiting 
std:: queue<JOB>jobs; //: node in front is what is using the disk  

void Print(queue<JOB> job);// prints copy of disk queue
};



#endif
