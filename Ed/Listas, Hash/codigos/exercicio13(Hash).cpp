#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

//Funcao que calcula hash a partir de uma chave

//Classe noh que armazena chave e valor na tabela hash
class Noh
{
    friend class TabelaHash;

private:
    int chave;
    string valor;
    Noh *prox;

public:
    Noh(int c, string v)
    {
        chave = c;
        valor = v;
        prox = NULL;
    }
};

//Classe da tabela hash
class TabelaHash
{
private:
    Noh **elementos; //Vetor de ponteiros
    int cap;
    int mTamanho;
public:
    TabelaHash(int tam = 100);
    ~TabelaHash();
    void insere(int c, string v);
    string recuperarValor(int c);
    void removerValor(int c);
    void percorrer();
    void redimensiona(int novaCapacidade);
    int funcaoHash(int c);
};

//Construtor da tabela hash
TabelaHash::TabelaHash(int tam)
{
    elementos = new Noh *[tam];
    cap = tam;
    mTamanho = 0;
    for (int i = 0; i < tam; i++)
    {
        elementos[i] = NULL;
    }
}

//Destrutor da tabela hash
TabelaHash::~TabelaHash()
{
    for (int i = 0; i < cap; i++)
    {
        Noh *atual = elementos[i];

        while (atual != NULL)
        {
            Noh *aux = atual;
            atual = atual->prox;
            delete aux;
        }
    }
    delete[] elementos;
}
int TabelaHash::funcaoHash(int c)
{
    return c % cap;
    cout << "cap e:" << cap << endl;
}

//Inserir um valor v com uma chave c
void TabelaHash::insere(int c, string v)
{
    int h,opa;
    opa = floor(cap*0.7);
    h = funcaoHash(c);
    Noh *atual = new Noh(c, v);
    if (mTamanho == opa-1) {

        cout << "entrei" << endl;
        redimensiona(cap*2);
        cout << "sai" << endl;

        if (elementos[h] == NULL)
        {
            atual->prox = NULL;
            elementos[h] = atual;
        }
        else
        {
            Noh *atual = elementos[h];
            if (atual->prox == NULL)
            {
                Noh *novo = new Noh(c, v);
                atual->prox = novo;
            }
            else
            {
                while (atual->prox != NULL)
                {
                    atual = atual->prox;
                }
                Noh *novo = new Noh(c, v);
                atual->prox = novo;
            }
            mTamanho++;
        }
    } 

    else {

        if (elementos[h] == NULL)
        {
            atual->prox = NULL;
            elementos[h] = atual;
        }
        else
        {
            Noh *atual = elementos[h];
            if (atual->prox == NULL)
            {
                Noh *novo = new Noh(c, v);
                atual->prox = novo;
            }
            else
            {
                while (atual->prox != NULL)
                {
                    atual = atual->prox;
                }
                Noh *novo = new Noh(c, v);
                atual->prox = novo;
            }
        }
        mTamanho++;
    }
}

void TabelaHash::redimensiona(int novaCapacidade){
    
    int capOld = cap;
    TabelaHash *tabelaAux;
    tabelaAux = new TabelaHash [capOld];

    for (int i = 0; i < capOld; i++)
    {
        tabelaAux[i].insere(elementos[i]->chave, elementos[i]->valor);
    }
    
    for (int i = 0; i < capOld; i++)
    {
        cout << tabelaAux[i] << endl;
    }
    
}
//Recuperar um valor associado a uma chave
string TabelaHash::recuperarValor(int c)
{
    int j = funcaoHash(c);

    if ((elementos[j] != NULL) and (elementos[j]->chave == c))
    {
        return elementos[j]->valor;
    }
    else
    {
        Noh *atual = elementos[j];

        while ((atual != NULL) and (atual->chave != c))
        {
            atual = atual->prox;
        }

        if ((atual != NULL) and (atual->chave == c))
        {
            return atual->valor;
        }
        else
        {
            return "NAO ENCONTRADO";
        }
    }
}

//Remover um valor associado a uma chave
void TabelaHash::removerValor(int c)
{
    if (recuperarValor(c) == "NAO ENCONTRADO")
    {
        cout << "Erro na remocao...\n";
    }
    else
    {
        int j = funcaoHash(c);
        if ((elementos[j] != NULL) and (elementos[j]->chave == c))
        {
            Noh *removido = elementos[j];
            elementos[j] = elementos[j]->prox;
            delete removido;
        }
        else
        {
            Noh *atual = elementos[j];
            Noh *ant;

            while ((atual != NULL) and (atual->chave != c))
            {
                ant = atual;
                atual = atual->prox;
            }

            if ((atual != NULL) and (atual->chave == c))
            {
                Noh *removido = atual;
                ant->prox = atual->prox;
                delete removido;
            }
        }
        mTamanho--;
    }
}

//Percorrer a tabela hash
void TabelaHash::percorrer()
{
    Noh *atual;

    for (int i = 0; i < cap; i++)
    {
        cout << "Posicao: " << i << "->" << " ";
        atual = elementos[i];

        if (atual == NULL) {

            cout << "-1" << endl;
            cout << "lista de colisao:" << endl;
        }

        while (atual != NULL)
        {

            cout << atual->chave << " " << atual->valor << endl;
            atual = atual->prox;
            cout << "lista de colisao:" << endl;
        }
    }
}

int main()
{
    unsigned capacidade;
    cin >> capacidade;
    TabelaHash tabela(capacidade);
    char operacao;
    int chave;
    string valor;
    do
    {
        cin >> operacao;
        switch (operacao)
        {
        case 'I':
            cin >> chave >> valor;
            tabela.insere(chave, valor);
            break;
        case 'R':
            cin >> chave;
            tabela.removerValor(chave);
            break;
        case 'B':
            cin >> chave;
            valor = tabela.recuperarValor(chave);
            cout << valor << endl;
            break;
        case 'P':
            tabela.percorrer();
            break;
        case 'S':
            break;
        default:
            cerr << "operação inválida\n";
        }

    } while (operacao != 'S');
    return 0;
}