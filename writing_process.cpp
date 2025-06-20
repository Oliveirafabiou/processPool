#include "writing_process.h"
#include <fstream>
#include <iostream>

WritingProcess::WritingProcess(int pid, const std::string& exprStr) : Process(pid), expr(exprStr) {};

void WritingProcess::execute() {
	std::ofstream file("arquivos/computation.txt", std::ios::app);

	if (!file) {
		std::cerr << "Erro ao abrir arquivo de gravação. " << std::endl;
		return;
	}

	file << expr.toString() << std::endl;
	file.close();

	std::cout << "Processo de Gravação [" << pid << "]: expressão '" << expr.evaluate() << "' gravada com sucesso." << std::endl;
};

std::string WritingProcess::getType() const {
	return "Writing";
};

std::string WritingProcess::getExpressionString() const {
	return expr.toString();
}