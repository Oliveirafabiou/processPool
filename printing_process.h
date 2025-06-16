#pragma once
#include "process.h"
#include <queue>

class PrintingProcess : public Process {
private:
	std::queue<Process*>& fila;

public:
	PrintingProcess(int pid, std::queue<Process*>& fila);
	void execute() override;
	std::string getType() const override;
};