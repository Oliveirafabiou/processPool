#include "computing_process.h"

ComputingProcess::ComputingProcess(int pid, const std::string& exprStr) : Process(pid), expr(exprStr) {};

void ComputingProcess::execute() {
	std::cout << "Processo de Cálculo [" << pid << "]: " << expr.toString() << " = " << expr.evaluate() << std::endl;
};

std::string ComputingProcess::getType() const {
	return "Computing";
};

std::string ComputingProcess::getExpressionString() const {
	return expr.toString();
}

