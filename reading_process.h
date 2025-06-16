#pragma once
#include "process.h"
#include "computing_process.h"
#include <string>
#include <queue>

class ReadingProcess : public Process {
private:
	std::queue<Process*>& fila;
	int& nextPid;

public:
	ReadingProcess(int pid, std::queue<Process*>& fila, int& nextPid);
	void execute() override;
	std::string getType() const override;
};