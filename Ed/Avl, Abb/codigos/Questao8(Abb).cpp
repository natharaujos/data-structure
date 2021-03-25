#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao
{
    DIR,
    ESQ
};

class Noh
{
    friend class ABB;

public:
    Noh(Dado d);
    //~Noh();
    //unsigned NroDeFolhas() const;
private:
    Dado valor;
    Noh *esq;
    Noh *dir;
    Noh *pai;
};

Noh::Noh(Dado d)
{
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

// Noh::~Noh() {
//     // implemente o Destrutor recursivo!
// }

// unsigned Noh::NroDeFolhas() const {
//     // implemente
// }

class ABB
{
public:
    ABB();
    ~ABB();
    // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
    // Pode ser Ãºtil para depurar o programa.
    void EscreverNivelANivel(std::ostream &saida);
    // Insere um dado na Ã¡rvore.
    void Inserir(Dado d);
    // Retorna o nro de folhas na Ã¡rvore.
    unsigned NroDeFolhas();
    unsigned NroDeFolhasAux(Noh *);
    void destruirRec(Noh *);
    Dado busca(Dado valor);
    Noh* buscaAux(Dado chave);
    unsigned cont = 0;

private:
    Noh *raiz;
};

ABB::~ABB()
{

    destruirRec(raiz);
}

void ABB::destruirRec(Noh *noh)
{

    if (noh)
    {
        destruirRec(noh->esq);
        destruirRec(noh->dir);
        delete noh;
    }
}

ABB::ABB()
{

    raiz = NULL;
}

void ABB::Inserir(Dado d)
{

    Noh *novo = new Noh(d);

    if (raiz == NULL)
    {
        raiz = novo;
    }

    else
    {
        Noh *atual = raiz;
        Noh *ant = NULL;

        while (atual != NULL)
        {
            ant = atual;

            if (atual->valor > d)
            {
                atual = atual->esq;
            }

            else
            {
                atual = atual->dir;
            }
        }
        novo->pai = ant;

        if (ant->valor > novo->valor)
        {
            ant->esq = novo;
        }

        else
        {
            ant->dir = novo;
        }
    }
}

unsigned ABB::NroDeFolhas()
{

    return NroDeFolhasAux(raiz);
}

unsigned ABB::NroDeFolhasAux(Noh *noh)
{

    if (noh == NULL)
    {

        return 0;
    }

    else if ((noh->dir == NULL) && (noh->esq == NULL))
    {

        return 1;
    }

    return (NroDeFolhasAux(noh->dir) + NroDeFolhasAux(noh->esq));
}

Dado ABB::busca(Dado valor)
{

    Noh *resultado = buscaAux(valor);
    cout << "Numero de nós acessados: " << " " << cont << endl;
    cont = 0;
    if (resultado != NULL)
    {
        return resultado->valor;
    }
    else
    {
        return 0;
    }
}

Noh *ABB::buscaAux(Dado chave)
{
    //Faz a busca na estrutura e retorna
    Noh *atual = raiz;

    while (atual != NULL)
    {
        if (atual->valor == chave)
        {
            return atual;
            cont++;
        }
        else if (atual->valor > chave)
        {
            atual = atual->esq;
            cont++;
        }
        else
        {
            atual = atual->dir;
            cont++;
        }
    }

    return atual;
}

int main()
{
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i)
    {
        cin >> valor;
        arvore.Inserir(valor);
    }
    //cout << arvore.NroDeFolhas() << endl;
    char option;
    cin >> option;

    do {
        switch (option)
        {
        case 'b':
            Dado chave;
            cout << "Insira uma chave: " << endl;
            cin >> chave;
            arvore.busca(chave);
            break;
        default:
            break;
        }
        cin >> option;
    }while(option != 's');
    return 0;
}