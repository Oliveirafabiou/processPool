#include "reading_process.h"
#include <fstream>
#include <iostream>

ReadingProcess::ReadingProcess(int pid, std::queue<Process*>& fila, int& nextPid) : Process(pid), fila(fila), nextPid(nextPid) {};

void ReadingProcess::execute() {
	std::ifstream file("arquivos/computation.txt");
	if (!file) {
		std::cerr << "Erro ao abrir arquivo de leitura." << std::endl;
		return;
	}

	std::string line;
	int count = 0;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			Process* novo = new ComputingProcess(nextPid++, line);
			fila.push(novo);
			count++;
		}
	}
	file.close();

	std::ofstream clear("arquivos/computation.txt", std::ios::trunc);
	clear.close();

	std::cout << "Processo de Leitura [" << pid << "]: " << count << " processo(s) carregado(s) e arquivo limpo." << std::endl;
};

std::string ReadingProcess::getType() const {
	return "Reading";
};