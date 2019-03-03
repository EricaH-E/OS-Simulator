/* Erica Hendricks-Elliston
   CSCI 340
   Section 01
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>

#include "HardDisk.h"
#include "CPU.h"
#include "RAM.h"

using namespace std;

// void Command_Exexution (string cmd);

int main()
{

	unsigned int  Rmem, page_size, disknum;
	string command;

	// Spec Prompts
	cout<< "Enter the Amount of RAM:";
	cin>> Rmem;
	cout<< "Enter page size:";
	cin >> page_size;
	cout<< "Enter number of hard disk:";
	cin >> disknum;

//MEMORY
RAM memory(Rmem,page_size,(Rmem/page_size));

//CPU (1 CORE)
CPU cpu;

//HARD  DISK
std:: vector<Disk> disk;
Disk *CreateDisk;

for( unsigned int i=0; i<disknum; i++)
{
	// create new  instance of disk class
	CreateDisk= new Disk;
	disk.push_back(*CreateDisk);
}



/* Program Instuctiona/ Reminders*/
cout<<"PROGRAM WILL NOW LISTEN FOR COMMANDS \nWHEN YOU WISH TO END SIMULATIION ENTER: 'quit' (lower case)" << endl;
cout<<"REMINDER: COMMANDS ARE CASE SENSITIVE AND SPACE SENSITIVE (i.e. D AND d ARE DISTINT; 'D 'AND 'D' ARE DISTINCT (NO EXTRA SPACES!!))" <<endl;

string quit;
std::string::size_type sz;

 // whie program is running allow user input at any given time;
        while(true)
        {

		getline(cin, command);

		// compare command  to list of valid commands
		if (command== "A")
		{
			unsigned int np = memory.new_process();
			cpu.request_usage(np);
		}
		else if (command  == "Q")
		{
			cpu.quantum();
		}
		else if( command  == "t" ) 
		{

			int pid = cpu.terminator();
			if (pid != -1)
				memory.terminator(pid);
		}
		else if (command[0]=='d')
		{
			unsigned int dnum,x;
			string cmd= command.substr(2);
			dnum =stoi(cmd,&sz);
			string filename = cmd.substr(sz);
			unsigned int pid = cpu.cpu_state();
			if(!(dnum < disk.size())) cerr<< "INVALID DISK NUMBER; DISK NUMBERS RANGE FROM 0-"<< disk.size()-1<< endl;
			if(filename.empty())
				cerr<< "NO FILE REQUEST SPECIFIED" << endl;
			if( pid != -1 && dnum < disk.size() && !filename.empty())
			{
				int level = cpu.current_level();
				disk[dnum].request_usage(pid,filename,level);
			}
		} 
		else if (command[0]=='D') 
		{
			if(command.length()< 3)
				cerr<< "ERROR: NO DISK SPECIFIED"<<endl;
			else{ 

			unsigned int dnum =  stoi(command.substr(2),&sz);
			if(!(dnum < disk.size())) cerr<< "INVALID DISK NUMBER; DISK NUMBERS RANGE FROM 0-"<< disk.size()-1<< endl;
			else
			{
				int pnum = disk[dnum].request_done();
				if(pnum == -1 )
					cout<<"ERROR:DISK IS IDLE"<<endl;
				else
				{
					int level= disk[dnum].returntolevel();
					cpu.request_usage(pnum,level);
				}
			} 
			}

		}
		else if (command[0]=='m')
		{
			unsigned int addr = stoi(command.substr(2),&sz);
			unsigned int pid = cpu.cpu_state();
			if(pid == -1) cerr<< "ERROR: ADDRESS ACCESS CALLED ON IDLE CPU"<< endl;
			else
				memory.address_access(pid, addr);
		} 
		else if (command[0]== 'S')
		{
			if( command[2] == 'i')
			{
				unsigned int i = 0;
				for( auto x: disk){
					cout<<"DISK "<<i<<":";
					x.disk_state();
					i++;
				}
				cout << endl;
			}
			else if (command[2] == 'r')
			{
				cpu.Print();
			}
			else if(command[2] == 'm')
			{
				memory.Print();
			}
			else 
				cerr<< "ERROR: INVALID VARIATION ON S COMMAND" << endl;
		}
		else if (command == "quit") {
			break; }
		else{
			if(! command.empty())
				cerr<<"ERROR: COMMAND NOT RECOGNIZED "<< endl;
		}  
        }



return 0;

}
