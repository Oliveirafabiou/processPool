#pragma once
#include "process.h"
#include "expressions.h"
#include <iostream>

class ComputingProcess : public Process {
private:
	Expression expr;

public:
	ComputingProcess(int pid, const std::string& exprStr);
	void execute() override;
	std::string getType() const override;
};