#include "HardDisk.h"
#include <utility>

Disk :: Disk (){}


void Disk:: request_usage(int process, string  filename, int level)
{
	JOB X(process, filename, level);
	jobs.push(std::move(X));

	if(!Busy)
		Busy = true;

}

unsigned int Disk:: request_done()
{
	if(!jobs.empty())
	{
		int pnum = (jobs.front()).process;
		if(jobs.empty())
                	Busy = false;
		return pnum;
	}
	else
		return -1;
}

int Disk:: returntolevel()
{
	if(!jobs.empty())
        {
                int level= (jobs.front()).level;
                jobs.pop();
                if(jobs.empty())
                        Busy = false;
                return level;;
        }
}

void Disk:: disk_state()
{
	if(Busy)
	{
		queue<JOB>copy = jobs;
		Print(copy);
	}
	else
		cout<< "IDLE"<<endl; 

}

void Disk:: Print(queue<JOB> job)
{
	cout<< "Current Process Using Disk: " << job.front().process<<" Filename:"<<job.front().filename<< endl;
	job.pop();
	// iterate through the queue
	cout<< "Processes Waiting:" << endl;
	while(!job.empty())
	{
		cout<< "Process:"<<job.front().process<< "  Filename:" <<job.front().filename << endl;
		job.pop();
	}
} 

