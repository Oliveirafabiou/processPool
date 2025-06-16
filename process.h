#pragma once
#include <string>

class Process {
protected:
	int pid;

public:
	Process(int pid);
	virtual ~Process() = default;

	int getPid() const;
	virtual void execute() = 0;
	virtual std::string getType() const = 0;
};