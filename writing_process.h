#pragma once
#include "process.h"
#include "expressions.h"

class WritingProcess : public Process {
private:
	Expression expr;

public:
	WritingProcess(int pid, const std::string& exprStr);
	void execute() override;
	std::string getType() const override;
};