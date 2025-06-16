#include "printing_process.h"
#include <iostream>

PrintingProcess::PrintingProcess(int pid, std::queue<Process*>& fila) : Process(pid), fila(fila) {};

void PrintingProcess::execute() {
	std::cout << "Processo de impressão [" << pid << "]: Conteudo atual da fila:" << std::endl;

	if (fila.empty()) {
		std::cout << "[Fila Vazia]" << std::endl;
		return;
	}

	std::queue<Process*> copia = fila;
	while (!copia.empty()) {
		Process* proc = copia.front();
		std::cout << "	PID: " << proc->getPid() << " | Tipo: " << proc->getType() << std::endl;
		copia.pop();
	}
};

std::string PrintingProcess::getType() const {
	return "Printing";
}