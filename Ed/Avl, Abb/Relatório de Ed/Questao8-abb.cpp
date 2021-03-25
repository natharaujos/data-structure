#include <iostream>
#include <queue>
#include <stdexcept>
#include <chrono>

using namespace std;

using namespace std::chrono;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
        //~Noh();
        //unsigned NroDeFolhas() const;
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

Noh::Noh(Dado d) {
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

class ABB {
    public:
        ABB();
        ~ABB();
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        // Pode ser Ãºtil para depurar o programa.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        // Retorna o nro de folhas na Ã¡rvore.
        unsigned NroDeFolhas();
        unsigned NroDeFolhasAux(Noh*);
        void destruirRec(Noh*);
        void Inserir(Dado d);
        void Imprimir();
        Dado busca(Dado valor);
        Noh* buscaAux(Dado chave);
        Noh* minimoAux(Noh* atual);
        void transplanta(Noh* antigo, Noh* novo);
        void remove(Dado d);
        void imprimirRemove();
    private:
        Noh* raiz;
        int cont = 0;
        int cont2 = 0;
        int cont3 = 0;
};

ABB::~ABB(){
    
    destruirRec(raiz);
}

void ABB::destruirRec(Noh* noh) {

    if(noh) {
        destruirRec(noh->esq);
        destruirRec(noh->dir);
        delete noh;
    }
}

ABB::ABB(){

    raiz = NULL;
}
void ABB::Imprimir(){

    cout << "numero de nohs" << " " << cont << endl;
    cont = 0;
}

void ABB::Inserir(Dado d) {
    
    Noh* novo = new Noh(d);
    
    if(raiz == NULL){
        raiz = novo;
    } 
    
    else {
        Noh* atual = raiz;
        Noh* ant = NULL;
        
        while(atual != NULL){
            ant = atual;
            
            if(atual -> valor > d){
                atual = atual -> esq;
                cont++;
            } 
            
            else {
                atual = atual -> dir;
                cont++;
            }
        }
        novo -> pai = ant;
        
        if(ant -> valor > novo -> valor){
            ant -> esq = novo;
            
        } 
        
        else {
            ant -> dir = novo;
            
        }
    }

    Imprimir();
}

unsigned ABB::NroDeFolhas() {
    
    return NroDeFolhasAux(raiz);
}

unsigned ABB::NroDeFolhasAux(Noh* noh) {

    if(noh == NULL) {
        
        return 0;
    }

    else if ((noh->dir == NULL) && (noh->esq == NULL)){
        
        return 1;
    }

    return (NroDeFolhasAux(noh->dir) + NroDeFolhasAux(noh->esq));
}
Dado ABB::busca(Dado valor){
    Noh* resultado = buscaAux(valor);
    cout << "numero de nohs acessados:" << " " << cont2 << endl;
    cont2 = 0;
    if (resultado != NULL){
        return resultado->valor;
    }else{
        return 0;
    }
}

Noh* ABB::buscaAux(Dado chave){
    //Faz a busca na estrutura e retorna
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual -> valor == chave){
            cont2++;
            return atual;
        } else if(atual -> valor > chave){
            cont2++;
            atual = atual->esq;
        } else {
            cont2++;
            atual = atual->dir;     
        }
    }
    return atual;
}

Noh* ABB::minimoAux(Noh* atual){
    //Retorna o minimo da arvore
    while(atual -> esq != NULL){
        atual = atual -> esq;
    }
    return atual;
}

void ABB::transplanta(Noh* antigo, Noh* novo){
    //Troca dois nos
    if(raiz == antigo){
        raiz = novo;
        cont3++;
    } else if(antigo == antigo->pai->esq){
        antigo ->pai->esq = novo;
        cont3++;
    } else {
        antigo->pai->dir = novo;
        cont3++;
    }
    if(novo != NULL){
        novo->pai = antigo->pai;
        cont3++;
    }
}
void ABB::imprimirRemove(){
    cout << "nohs acessados: " << " " << cont2 + cont3 << endl;
    cont2 = 0;
    cont3 = 0;
}

void ABB::remove(Dado d){
    //Remove um elemento (noh) da arvore
    //Noh* aux = new Noh(d);
    Noh* remover = buscaAux(d);
    
    if(remover == NULL){
        cout << "ERRO" << endl;
    } else {
        if(remover -> esq == NULL){
            transplanta(remover, remover -> dir);
            cont3+=2;

        } else if(remover -> dir == NULL){
            transplanta(remover, remover -> esq);
            cont3+=2;

        } else {
            Noh* sucessor = minimoAux(remover -> dir);
            
        
            if(sucessor -> pai != remover){
                transplanta(sucessor, sucessor -> dir);
                cont3+=2;
                sucessor -> dir = remover -> dir;
                cont3++;
                sucessor -> dir -> pai = sucessor;
                cont3++;
            }
            transplanta(remover, sucessor);
            cont3+=2;
            sucessor -> esq = remover -> esq;
            cont3++;
            sucessor -> esq -> pai = sucessor;
            cont3++;

        }
        imprimirRemove();
        delete remover;
    }
    
}

int main() {
 

    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;

    for (unsigned i = 0; i < qtde; ++i)
    {
        cin >> valor;
        arvore.Inserir(valor);
    }

    char option;
    cin >> option;

    auto start = high_resolution_clock::now();
    do {
        switch (option)
        {
        case 'b':
            Dado chave;
            cout << "Insira uma chave: " << endl;
            cin >> chave;
            arvore.busca(chave);
            break;
        case 'r':
            cout << "Insira uma chave para ser removida: " << endl;
            cin >> chave;
            arvore.remove(chave);
        default:
            break;
        }
        cin >> option;
    }while(option != 's');

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << duration.count() << endl;
    return 0;
    
}