#include "process.h"

Process::Process(int pid)
{
	this->pid = pid;
};

int Process::getPid() const {
	return pid;
};
