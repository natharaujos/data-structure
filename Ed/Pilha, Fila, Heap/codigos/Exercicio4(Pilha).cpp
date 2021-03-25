#include <iostream>

using namespace std;

class noh {

    friend class pilha;
    private:
        char mValor;
        noh* mProximo;
    
    public:
        noh(char valor);
};

noh::noh(char valor) {

    mValor = valor;
    mProximo = NULL;
}

class pilha {

    private:
        noh* mTopo;
        int mTamanho;
    
    public:
        pilha();
        ~pilha();
        unsigned tamanho();
        void empilha(char valor);
        void limpaPilha();
        char desempilha();
        bool vazia();
};

pilha::pilha() {
    
    mTopo = NULL;
    mTamanho = 0;
}

pilha::~pilha() {
    
    limpaPilha();
}

void pilha::limpaPilha() {

    while(mTamanho > 0) {

        desempilha();
    }
}

unsigned pilha::tamanho() {

    return mTamanho;
}

bool pilha::vazia() {

    return (mTamanho == 0);
}

void pilha::empilha(char valor) {

    noh* novo = new noh(valor);
    novo->mProximo = mTopo;
    mTopo = novo;
    mTamanho++;
}

char pilha::desempilha() {

    char valor = mTopo->mValor;
    noh* temp = mTopo;
    mTopo = mTopo->mProximo;
    delete temp;
    mTamanho--;
    return valor;
}

int main() {

    pilha aA;
    pilha cC;

    char caractere;

    unsigned numBs = 0;
    unsigned contAs = 0;
    unsigned contCs = 0;

    do {
        
        cin >> caractere;
        
        if(caractere != 'X') {

            if(caractere == 'A') {

                aA.empilha('A');
                contAs++;
            }

            else if (caractere == 'C') {

                cC.empilha('C');
                contCs++;
            }

            else if (caractere == 'B') {

                numBs++;
            }
        }
    } while(caractere != 'X');

    bool verifica = ((aA.tamanho() > 0) and (cC.tamanho() > 0));
    int aux = 0;

    if(numBs==1) {    
    
        while(verifica) {                

            if(not aA.vazia()) {

                aA.desempilha();
                    
                    if(not cC.vazia()) {
            
                        cC.desempilha();

                        if(not cC.vazia()) {

                            cC.desempilha();
                        }

                        else {
                            
                            aux++;
                            verifica = false;
                        }
                    }

                verifica = ((aA.tamanho() > 0) and (cC.tamanho() > 0));
            }  
        }   
    }

    if(contAs > 0 and contCs > 0) {

        if((aA.tamanho()) == 0 and (cC.tamanho()) == 0 and aux == 0) {

            cout << "sim ";
        }

        else {

            cout << "nao ";
        }
    }

    else {

        cout << "nao ";
    }

    cout << aA.tamanho() << " " << cC.tamanho();
}