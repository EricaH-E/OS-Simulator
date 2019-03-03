
#include "RAM.h"
#include <utility>


RAM:: RAM(unsigned int cap, unsigned int  page, unsigned int sp ): capacity(cap),page_size(page), space(sp) 
{ }

unsigned int RAM:: new_process()
{
 unsigned int pid = pcount;

	if( framecount < space )
	{

		if(vacant.empty())
		{
			PCB X(framecount,pcount,timestamp);
			Processes.push_back(std::move(X));
			pcount ++;
			timestamp++;
			framecount++;
			return pid;
		}
		else
		{
			unsigned int framenum = vacant.front();//reusues frames from terminated processes
			vacant.pop();
			PCB X(framenum,pcount,timestamp);
			auto it = Processes.emplace(Processes.begin()+ framenum ,std::move(X));
			pcount++;
			timestamp++;
			framecount++;
			return pid;


		} 

	}

	else // lru
	{
		unsigned int lru= 0; // index of  LRU in Processes
		for(auto i=0; i< Processes.size();  i++)
		{
			if(Processes[i].access_time < Processes[lru].access_time)
			{
				lru = i; 
			}
		}
		unsigned int framenum =Processes[lru].frame;
		PCB X(framenum,pcount,timestamp);
		Processes[lru] = std::move(X);
		timestamp++;
		pcount++;
		return pid;
	}

}

void RAM::address_access( unsigned int process ,unsigned int address)
{
	bool found = false;
	unsigned int lru = 0; // stores index of lru page in processes  vector
	unsigned int p = address / page_size;

	for(unsigned int i=0; i<Processes.size(); i++)
	{


		if( Processes[i].access_time < Processes[lru].access_time)
                	lru = i;
		if(Processes[i].pid == process && Processes[i].page== p)// page already in memory
		{
			Processes[i].access_time++;
			timestamp  ++;
			found= true;
			break;
		}
	}


	if(!found)
	{

		if(framecount < space )
		{


			if (vacant.empty())
                        {
                                PCB X(framecount,process,timestamp,p);
                                Processes.push_back(std::move(X));
                                timestamp++;
                                framecount++;
                        }
			else
                        {
                                unsigned int framenum = vacant.front();
                                vacant.pop();
                                PCB X(framenum,process,timestamp,p);
                                auto it = Processes.emplace(Processes.begin()+ framenum ,std::move(X));
                                timestamp++;
                                framecount++;
                        }
		}

		else //lru
		{
			unsigned int framenum =Processes[lru].frame;
			PCB X(framenum,process,timestamp,p);
			timestamp ++;
			Processes[lru] = std::move(X);
		}
	}

}

void RAM:: terminator(unsigned int process)
{
	//search process vector
	for(unsigned int i=0; i<Processes.size(); i++)
	{
		if( Processes[i].pid == process)
		{
			vacant.push(Processes[i].frame);
			framecount--;
			Processes.erase(Processes.begin()+ i);
			i--;
		}

	}



}

void RAM:: Print()
{

	if(Processes.empty())
		cout<<" NO PROCESS CURRENTLY IN RAM" << endl;
	else
	{
		for(auto i: Processes)
			cout<<"FRAME["<<i.frame<<"]: Process: "<<i.pid<<" Page: "<<i.page<<endl;

	}
return;
}

