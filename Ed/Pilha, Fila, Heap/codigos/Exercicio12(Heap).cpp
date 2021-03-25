#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>
#include <cstdlib>

typedef unsigned TCodProcesso;

struct dado {

    int prioridade;
    TCodProcesso codigo;
};

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    private:
        dado* heap;
        int capacidade;
        int tamanho;

    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        void Inserir(dado d);
        // Retira e retorna a raiz
        dado Retirar();
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
    heap = new dado[cap];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] heap;
}

void Heap::ArrumarDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;

    if ((esq < tamanho) and (heap[esq].prioridade > heap[maior].prioridade)) {
        maior = esq;
    } 

    if ((dir < tamanho) and (heap[dir].prioridade > heap[maior].prioridade)) {
        maior = dir;
    }

    if (maior != i) {
        swap(heap[i], heap[maior]);
        ArrumarDescendo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    int  p = Pai(i);

    if (heap[i].prioridade > heap[p].prioridade) {
        swap(heap[i], heap[p]);
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

dado Heap::Retirar() {

    dado aux;
    aux = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    ArrumarDescendo(0);
    return aux;
}

bool Heap::Vazia() {
    return (tamanho == 0);
}

void Heap::Inserir(dado d) {
    if(tamanho == capacidade) {
        return;
    }
    heap[tamanho] = d;
    ArrumarSubindo(tamanho);
    tamanho++;
}

int main() {
    dado umDado;
    dado aux;
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> umDado.codigo >> umDado.prioridade;
                heap.Inserir(umDado);
                break;
            case 'o': // obter um processo do heap
                if(not heap.Vazia()) {    
                    aux = heap.Retirar();
                    cout << aux.codigo << " " << aux.prioridade << endl;
                }
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}