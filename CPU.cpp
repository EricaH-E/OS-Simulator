
#include "CPU.h"

CPU:: CPU() {}


void CPU:: request_usage(unsigned int pid, int lvl)
{
	if(lvl==1)
		level0.push(Process(pid));
	else if (lvl == 2)
		level1.push(Process(pid));
	else if(lvl == 3)
		level2.push(Process(pid));
}


void CPU:: quantum()
{

	if(cpu_state() == -1)
		return;	

	if (!level0.empty())
    	{
      		Process X =level0.front();
        	level0.pop();
        	level1.push(std::move(X));
    	}
    
	else if (!level1.empty())
    	{
        	if(level1.front().quantam == 1)//two time quantams have passed in current level
        	{
            		Process X = level1.front();
            		level2.push(std::move(X));
            		level1.pop();
        	}
        	else
        	{
            		level1.front().quantam++;
        	}
    	}
    	else
        	cout<< "LEVEL 0 AND LEVEL 1 ARE EMPTY"<<endl;
}



unsigned int CPU:: terminator()
{
	if (!level0.empty())
	{
		unsigned int  pid = level0.front().process;
		level0.pop();
		return pid;
	}
	else if (!level1.empty())
	{
		unsigned int pid = level1.front().process;
		level1.pop();
		return pid;
	}
	else  if (!level2.empty())
	{
		unsigned int pid = level2.front().process;
		level2.pop();
		return pid;

	}
	else 
	{
		cerr<<"ERROR: TERMINATE CALLED ON IDLE CPU" <<endl;
		return -1;
	}
}


unsigned int CPU:: cpu_state()
{
	if(!level0.empty())
		return level0.front().process;
	else if (!level1.empty())
		return level1.front().process;
	else if(!level2.empty())
		return level2.front().process;
	else
	{ 
		cerr<< "CPU IS IDLE!" << endl;
		return -1;

	}


}

int  CPU:: current_level()
{
	if(!level0.empty())
        {
		level0.pop();
		return 1;
	}
        else if (!level1.empty())
        {
		level1.pop();
		return 2;

	}
        else if(!level2.empty())
        {
		level2.pop();
		return 3;
	}
}

void CPU:: Print()
{

	
	if ( !level0.empty() )
	{
		cout<< "LEVEL 0:" << endl;
		cout << "PROCESS CURRENTLY USING CPU: Process " << level0.front().process <<endl;
		queue<Process>copy = level0;
		copy.pop();
		cout<< "Processes Waiting:" << endl;
		Printer(copy);
		if (!level1.empty())
		{
			cout<< "LEVEL 1:"<<endl;
			copy = level1;
			Printer(copy);
		}
		if(!level2.empty())
		{
			cout<< "LEVEL 2:"<<endl;
			copy = level2;
			Printer(copy);
		}
		
	}
	else if (!level1.empty() )
	{
		cout<< "LEVEL 0: EMPTY"<<endl;
		cout<< "LEVEL 1:"<<endl;
		cout<< "PROCESS CURRENTLY USING CPU: Process " << level1.front().process<<endl;
		queue<Process>copy = level1;
		copy.pop();
		cout<< "Processes Waiting:"<<endl;
		Printer(copy);
		if(!level2.empty())
		{
			cout<<"LEVEL 2:"<< endl;
			copy = level2;
			Printer(copy);
		}
	}
	else if (!level2.empty())
	{
		cout<< "LEVEL 0: EMPTY"<<endl;
		cout<< "LEVEL 1: EMPTY"<<endl;
		cout<< "LEVEL 2:"<<endl;
		cout<< "PROCESS CURRENTLY USING CPU: Process " << level2.front().process<<endl;
		queue<Process>copy = level2;
		copy.pop();
		cout<< "Processes Waiting:"<<endl;

		if (copy.empty())
			cout<< "NONE" <<endl;
		else
			Printer(copy);

	}
	else
		cout<< " CPU IS IDLE" << endl;

}


void CPU:: Printer(queue<Process> q)
{
	while(!q.empty())
	{
		cout<< "Process "<<q.front().process <<endl;
		q.pop();
		
	}
cout<< endl;
}

