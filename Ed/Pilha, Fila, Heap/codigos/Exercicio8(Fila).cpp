#include <iostream>
#include <cstring>

using namespace std;

class noh
{

    friend class fila;

private:
    string mValor;
    noh *mProximo;

public:
    noh(string valor);
};

noh::noh(string valor)
{

    mValor = valor;
    mProximo = NULL;
}

class fila
{

private:
    noh *Inicio;
    noh *Fim;
    int mTamanho;

public:
    fila();
    ~fila();
    unsigned tamanho();
    void enfileira(string valor);
    void limpaFila();
    string desenfileira();
    string getInicio();
    bool vazia();
    void imprimeFila();
    void removerCarro(string valor);
    //void verifica(string cor);
};

fila::fila()
{

    Inicio = NULL;
    Fim = NULL;
    mTamanho = 0;
}

fila::~fila()
{

    limpaFila();
}

void fila::limpaFila()
{

    while (mTamanho > 0)
    {

        desenfileira();
    }
}

unsigned fila::tamanho()
{

    return mTamanho;
}

bool fila::vazia()
{

    return (mTamanho == 0);
}

void fila::enfileira(string valor)
{

    noh *novo = new noh(valor);
    if (mTamanho == 0)
    {

        Inicio = novo;
    }
    else
    {

        Fim->mProximo = novo;
    }
    Fim = novo;
    mTamanho++;
}

string fila::desenfileira()
{

    string valor = Inicio->mValor;
    noh *temp = Inicio;
    Inicio = Inicio->mProximo;
    delete temp;
    mTamanho--;
    if (mTamanho == 0)
    {

        Fim = NULL;
    }
    return valor;
}

string fila::getInicio()
{

    string value = Inicio->mValor;
    return value;
}

/*void fila::copiarFila(fila *fila) {

    unsigned tam;
    tam = this->tamanho()+2;

    copy(this, this+tam,fila);
}*/

void fila::imprimeFila()
{

    noh *aux;
    aux = Inicio;

    while (aux != NULL)
    {

        cout << aux->mValor << endl;
        aux = aux->mProximo;
    }
}

void fila::removerCarro(string valor)
{

    fila filaAux;
    bool naFila = false;
    int tamInicial = this->tamanho();
    int cont = 0;
    string carRemoved;

    while (not naFila and cont < tamInicial)
    {

        if (this->getInicio() == valor)
        {

            naFila = true;
            carRemoved = this->desenfileira();
        }

        else
        {

            filaAux.enfileira(this->desenfileira());
        }
        cont++;
    }

    while (not filaAux.vazia())
    {

        this->enfileira(filaAux.desenfileira());
    }

    if (not naFila)
    {

        cout << "NAO ENCONTRADO" << endl;
    }

    else
    {

        cout << cont << endl;
        this->imprimeFila();
    }
}

int main()
{

    fila fila1;

    string option;
    string placaCarro;

    while (option != "S")
    {

        cin >> option;

        if (option == "E")
        {
            cin >> placaCarro;
            fila1.enfileira(placaCarro);
        }

        else if (option == "D")
        {
            cin >> placaCarro;

            fila1.removerCarro(placaCarro);
        }
    }

    return 0;
}