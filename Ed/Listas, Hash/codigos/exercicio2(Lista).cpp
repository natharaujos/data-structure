#include <iostream>
#include <cstdlib>

using namespace std;

typedef string Dado; 

class noh {
    friend class listadup;
    private:
        Dado dado;
        noh* proximo;
        noh* anterior;
    public:
        noh(Dado d  = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
    anterior = NULL;
}

class listadup {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
        void removeTodos();
    public:
        listadup();
        listadup(const listadup& umaLista);
        ~listadup();
        listadup& operator=(const listadup& umaLista);
        inline void insere(Dado dado);
        void insereNoFim(Dado dado);
        void imprime();
        void imprimeInverso();
        inline bool vazia();
        void inverte();
};

listadup::listadup() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}
listadup::listadup(const listadup& umaLista){
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    noh* aux = umaLista.primeiro;
    while (aux != NULL)
    {
        insereNoFim(aux->dado);
        aux = aux ->proximo;
    }
    
}

listadup::~listadup( ) {
    removeTodos();
}

void listadup::removeTodos(){
    noh* aux = primeiro;
    noh* temp;
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

listadup& listadup::operator=(const listadup& umaLista){
    removeTodos();
    noh* aux = umaLista.primeiro;
    while (aux != NULL)
    {
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
    
}
void listadup::insere(Dado dado){
    insereNoFim(dado);
}

void listadup::insereNoFim(Dado dado){
    noh* novo = new noh(dado);
    
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }else
    {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
}

void listadup::imprime(){
    noh* aux = primeiro;
    while (aux != NULL)
    {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

void listadup::imprimeInverso() {
    noh* aux = ultimo;
    while (aux != NULL)
    {
        cout << aux->dado << " ";
        aux = aux->anterior;
    }
    cout << endl;
    
}

inline bool listadup::vazia(){

    return(tamanho == 0);
}

void listadup::inverte() {

    noh *aux = NULL;
    noh *pos = primeiro;

    while (pos != NULL) { 
        aux = pos->proximo;
        pos->proximo = pos->anterior;
        pos->anterior = aux;
        pos = aux;
    }
    
    noh *att = primeiro;
    primeiro = ultimo;
    ultimo = att;
}

int main() {

    listadup lista1;

    string variavel, valor;

    cin >> variavel; 

    while (variavel != "Q") {

        if (variavel == "I") {

            cin >> valor;
            lista1.insereNoFim(valor);
        }

        if (variavel == "P") {

            lista1.imprime();
        }

        if (variavel == "X") {

            lista1.inverte();
        }

        if (variavel == "R") {

            lista1.imprimeInverso();
        }

        cin >> variavel;
    }

    lista1.imprime();
    lista1.imprimeInverso();
    
    return 0;
}