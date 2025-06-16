#include "computing_process.h"
#include "writing_process.h"
#include "reading_process.h"
#include "printing_process.h"
#include <locale.h> 
#include <queue>




//int main() {
//	  setlocale(LC_ALL, "");
//    ComputingProcess proc(1, "10 + 5");
//    proc.execute(); // Deve mostrar: Processo de Cálculo [1]: 10 + 5 = 15
//    return 0;
//}


//int main() {
//	  setlocale(LC_ALL, "");
//    WritingProcess p1(2, "7*8");
//    p1.execute();
//
//    return 0;
//}



//int main() {
//    setlocale(LC_ALL, "");
//    std::queue<Process*> fila;
//    int nextPid = 100; // valor de exemplo
//
//    ReadingProcess leitor(5, fila, nextPid);
//    leitor.execute();
//
//    // Exibir o que foi adicionado na fila
//    while (!fila.empty()) {
//        Process* p = fila.front();
//        std::cout << "Adicionado: PID " << p->getPid() << " - Tipo " << p->getType() << std::endl;
//        fila.pop();
//        delete p;
//    }
//
//    return 0;
//}


int main() {
    setlocale(LC_ALL, "");
    std::queue<Process*> fila;

    // Simulando alguns processos
    fila.push(new ComputingProcess(1, "10 + 5"));
    fila.push(new ComputingProcess(2, "8 / 2"));

    PrintingProcess impressora(99, fila);
    impressora.execute();

    // Limpeza (boa prática)
    while (!fila.empty()) {
        delete fila.front();
        fila.pop();
    }

    return 0;
}