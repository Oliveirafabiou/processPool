#pragma once
#include <queue>
#include "process.h"

class Sistema {
private:
    std::queue<Process*> fila;
    int nextPid;

public:
    Sistema();
    ~Sistema();

    void menu();
    void criarProcesso();
    void executarProximo();
    void executarPorPid();
    void salvarFila();
    void carregarFila();
};