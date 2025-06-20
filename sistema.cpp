#include "sistema.h"
#include "computing_process.h"
#include "writing_process.h"
#include "reading_process.h"
#include "printing_process.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Sistema::Sistema() {
    nextPid = 1;
}

Sistema::~Sistema() {
    while (!fila.empty()) {
        delete fila.front();
        fila.pop();
    }
}

void Sistema::menu() {
    int opcao;

    do {
        std::cout << "\n=== MENU DO SISTEMA ===\n";
        std::cout << "1. Criar novo processo\n";
        std::cout << "2. Executar próximo processo\n";
        std::cout << "3. Executar processo por PID\n";
        std::cout << "4. Salvar fila em arquivo\n";
        std::cout << "5. Carregar fila de arquivo\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha: ";
        std::cin >> opcao;

        switch (opcao) {
        case 1: criarProcesso(); break;
        case 2: executarProximo(); break;
        case 3: executarPorPid(); break;
        case 4: salvarFila(); break;
        case 5: carregarFila(); break;
        case 0: std::cout << "Encerrando...\n"; break;
        default: std::cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}


void Sistema::criarProcesso() {
    int tipo;
    std::cout << "\nTipo de processo a criar:\n";
    std::cout << "1. Computing (Calculo)\n";
    std::cout << "2. Writing (Gravacao)\n";
    std::cout << "3. Reading (Leitura de arquivo)\n";
    std::cout << "4. Printing (Imprimir fila)\n";
    std::cout << "Escolha: ";
    std::cin >> tipo;

    std::cin.ignore();

    Process* novo = nullptr;

    switch (tipo) {
    case 1: {
        std::string exprStr;
        std::cout << "Digite a expressao (ex: 5 + 2): ";
        std::getline(std::cin, exprStr);
        novo = new ComputingProcess(nextPid, exprStr);
        break;
    }
    case 2: {
        std::string exprStr;
        std::cout << "Digite a expressao para gravar: ";
        std::getline(std::cin, exprStr);
        novo = new WritingProcess(nextPid, exprStr);
        break;
    }
    case 3:
        novo = new ReadingProcess(nextPid, fila, nextPid);
        break;

    case 4:
        novo = new PrintingProcess(nextPid, fila);
        break;

    default:
        std::cout << "Tipo invalido.\n";
        return;
    }

    fila.push(novo);
    std::cout << "Processo criado com PID " << nextPid << " e tipo " << novo->getType() << ".\n";
    nextPid++;
}


void Sistema::executarProximo() {
    if (fila.empty()) {
        std::cout << "Fila de processos vazia.\n";
        return;
    }

    Process* proc = fila.front();
    fila.pop();

    std::cout << "Executando processo PID " << proc->getPid() << " (" << proc->getType() << "):\n";
    proc->execute();

    delete proc;
}



void Sistema::executarPorPid() {
    if (fila.empty()) {
        std::cout << "Fila de processos vazia.\n";
        return;
    }

    int pidBusca;
    std::cout << "Digite o PID do processo a executar: ";
    std::cin >> pidBusca;

    std::queue<Process*> novaFila;
    bool encontrado = false;

    while (!fila.empty()) {
        Process* proc = fila.front();
        fila.pop();

        if (!encontrado && proc->getPid() == pidBusca) {
            std::cout << "Executando processo PID " << proc->getPid() << " (" << proc->getType() << "):\n";
            proc->execute();
            delete proc;
            encontrado = true;
        }
        else {
            novaFila.push(proc);
        }
    }

    fila = novaFila;

    if (!encontrado) {
        std::cout << "PID nao encontrado na fila.\n";
    }
}



void Sistema::salvarFila() {
    std::ofstream file("dados/processos.dat");

    if (!file) {
        std::cerr << "Erro ao abrir arquivo para salvar.\n";
        return;
    }

    std::queue<Process*> copia = fila;
    while (!copia.empty()) {
        Process* proc = copia.front();
        copia.pop();

        file << proc->getType() << ";" << proc->getPid();

        // Se for Computing ou Writing, salvar a expressão
        if (proc->getType() == "Computing") {
            ComputingProcess* cp = dynamic_cast<ComputingProcess*>(proc);
            file << ";" << cp->getExpressionString();
        }
        else if (proc->getType() == "Writing") {
            WritingProcess* wp = dynamic_cast<WritingProcess*>(proc);
            file << ";" << wp->getExpressionString();
        }
        else {
            file << ";";
        }

        file << std::endl;
    }

    std::cout << "Fila salva com sucesso.\n";
}


void Sistema::carregarFila() {
    std::ifstream file("dados/processos.dat");

    if (!file) {
        std::cerr << "Erro ao abrir arquivo para carregar.\n";
        return;
    }

    while (!fila.empty()) {
        delete fila.front();
        fila.pop();
    }

    std::string tipo, linha;
    int pidArquivo;
    std::string exprStr;
    char separador;

    while (std::getline(file, linha)) {
        std::istringstream ss(linha);
        std::getline(ss, tipo, ';');
        ss >> pidArquivo;
        ss.ignore();

        std::getline(ss, exprStr);

        Process* novo = nullptr;

        if (tipo == "Computing") {
            novo = new ComputingProcess(pidArquivo, exprStr);
        }
        else if (tipo == "Writing") {
            novo = new WritingProcess(pidArquivo, exprStr);
        }
        else if (tipo == "Reading") {
            novo = new ReadingProcess(pidArquivo, fila, nextPid);
        }
        else if (tipo == "Printing") {
            novo = new PrintingProcess(pidArquivo, fila);
        }

        if (novo) {
            fila.push(novo);
            if (pidArquivo >= nextPid) {
                nextPid = pidArquivo + 1;
            }
        }
    }

    std::cout << "Fila carregada com sucesso.\n";
}