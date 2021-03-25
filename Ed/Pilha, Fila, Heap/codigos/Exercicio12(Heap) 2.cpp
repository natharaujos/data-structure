#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>
#include <cstdlib>

typedef unsigned TCodProcesso;

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    private:
        int heap;
        int prioridade;
        TCodProcesso codigo;
        int capacidade;
        int tamanho;
        int* vetorPrioridade;
        TCodProcesso* vetorCodigo;
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso ptCodigo, int ptPrioridade);
        // Verifica se a heap está vazia
        bool Vazia();
    protected:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        // Falta colocar os atributos
};

using namespace std;

Heap::Heap(int cap) {
    capacidade = cap;
    vetorPrioridade = new int[cap];
    vetorCodigo = new TCodProcesso[cap];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] vetorCodigo;
    delete[] vetorPrioridade;
}

void Heap::ArrumarDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;

    if ((esq < tamanho) and (vetorPrioridade[esq] > vetorPrioridade[maior])) {
        maior = esq;
    } 

    if ((dir < tamanho) and (vetorPrioridade[dir] > vetorPrioridade[maior])) {
        maior = dir;
    }

    if (maior != i) {
        swap(vetorCodigo[i], vetorCodigo[maior]);
        swap(vetorPrioridade[i], vetorPrioridade[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    int  p = Pai(i);

    if (vetorPrioridade[i] > vetorPrioridade[p]) {
        swap(vetorPrioridade[i], vetorPrioridade[p]);
        swap(vetorCodigo[i], vetorCodigo[p]);
        ArrumarSubindo(p);
    }
}

int Heap::Pai(int i) {
    return (i-1)/2;
}

int Heap::Esquerdo(int i) {
    return 2*i+1;
}

int Heap::Direito(int i) {
    return 2*i+2;
}

bool Heap::Retirar(TCodProcesso ptCodigo, int ptPrioridade) {
    if (Vazia()) {
        return false;
    }

    ptCodigo = vetorCodigo[0];
    ptPrioridade = vetorPrioridade[0];
    swap(vetorPrioridade[0], vetorPrioridade[tamanho-1]);
    swap(vetorCodigo[0], vetorCodigo[tamanho-1]);
    tamanho--;
    ArrumarDescendo(0);
    return true;
}

bool Heap::Vazia() {
    return (tamanho == 0);
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade) {
    if(tamanho == capacidade) {
        return false;
    }
    vetorPrioridade[tamanho] = prioridade;
    vetorCodigo[tamanho] = codigo;
    ArrumarSubindo(tamanho);
    tamanho++;

    for (int i = 0; i < tamanho; i++)
    {
        cout << vetorCodigo[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < tamanho; i++)
    {
        cout << vetorPrioridade[i] << " ";
    }

    cout << endl;
    
    return true;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(codigo, prioridade))
                    cout << codigo << ' ' << prioridade << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}