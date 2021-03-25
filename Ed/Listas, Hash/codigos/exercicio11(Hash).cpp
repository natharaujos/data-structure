// Tabela Hash com tratamento de colisão por endereçamento aberto
#include <iostream>
#include <string>
#include <stdexcept>

typedef int TValor; // tipo do valor armazenado

class InfoHash
{
    friend class Hash; // essa classe só deve ser usada na classe Hash
    InfoHash();
    InfoHash(const std::string &chave, const TValor &valor);
    std::string mChave;
    TValor mValor;
};

class Hash
{
public:
    Hash(unsigned capacidade = 50);
    ~Hash();
    // Mostra todos as posições de armazenamento da hash.
    void EscreverEstrutura(std::ostream &saida) const;
    // Insere uma cópia do valor. Não permite inserção de chave repetida.
    void Inserir(const std::string &chave, const TValor &valor);
    // Remove um item da hash associado com a chave dada.
    void Remover(const std::string &chave);
    // Retorna o valor associado a uma chave.
    TValor Valor(const std::string &chave) const;

protected:
    // Retorna a posicao em que uma chave está armazenada na estrutura.
    unsigned Buscar(const std::string &chave) const;
    // Insere um InfoHash na estrutura. Auxiliar para Inserir(chave/valor) e Redimensionar.
    void Inserir(InfoHash *ptPar);
    // Retorna a posicao em que uma chave deveria ficar na estrutura.
    unsigned Posicao(const std::string &chave) const;
    // Altera a capacidade da estrutura.
    void Redimensionar(unsigned novaCapacidade);
    InfoHash **mVetPtDados;
    InfoHash *REMOVIDO; // ponteiro especial a ser usado para marcar posições de elemento removido
    unsigned mCapacidade;
    unsigned mTamanho;
};

using namespace std;

InfoHash::InfoHash()
    : mChave(), mValor()
{
}

InfoHash::InfoHash(const std::string &chave, const TValor &valor)
    : mChave(chave), mValor(valor)
{
}

Hash::Hash(unsigned capacidade) // capacidade tem valor default
    : mVetPtDados(new InfoHash *[capacidade]), REMOVIDO(new InfoHash()), mCapacidade(capacidade), mTamanho(0)
{
    for (unsigned i = 0; i < mCapacidade; i++)
    {
        mVetPtDados[i] = NULL;
    }
}

Hash::~Hash()
{

    for (unsigned i = 0; i < mCapacidade; ++i)
    {
        mVetPtDados[i] = NULL;
    }

    delete[] mVetPtDados;

    delete REMOVIDO;
}

unsigned Hash::Buscar(const std::string &chave) const
{

    int pos = Posicao(chave);
    int posFinal = pos;
    do
    {
        InfoHash *dado = mVetPtDados[pos];
        if (dado == nullptr)
        {
            return -1;
        }
        if (dado->mChave == chave)
        {
            return pos;
        }
        pos = (pos + 1) % mCapacidade;

    } while (pos != posFinal);
    return -1;
}

void Hash::EscreverEstrutura(std::ostream &saida) const
{
    // Mostra todos as posições de armazenamento da hash. Ajuda a debugar.
    for (unsigned i = 0; i < mCapacidade; ++i)
    {
        saida << '[' << i;
        if (mVetPtDados[i] != NULL)
        {
            if (mVetPtDados[i] == REMOVIDO)
                saida << "/removido";
            else
                saida << '/' << mVetPtDados[i]->mChave << '/' << mVetPtDados[i]->mValor;
        }
        saida << "] ";
    }
}

void Hash::Inserir(const string &chave, const TValor &valor)
{

    if (mTamanho < mCapacidade)
    {
        InfoHash *novo = new InfoHash(chave, valor);
        int pos = Posicao(chave);
        while (mVetPtDados[pos] != NULL and mVetPtDados[pos]->mChave != chave and mVetPtDados[pos] != REMOVIDO)
        {
            pos++;
            pos %= mCapacidade;
        }
        if (mVetPtDados[pos] == NULL or mVetPtDados[pos] == REMOVIDO)
        {
            mTamanho++;
            mVetPtDados[pos] = novo;
        }
        else
        {
            throw invalid_argument("chave repetida");
        }
    }
    else
    {
        Redimensionar(mCapacidade + 5);
        Inserir(chave, valor);
    }
}

void Hash::Inserir(InfoHash *ptPar)
{

    unsigned pos = Posicao(ptPar->mChave);
    unsigned i = 0;
    while (mVetPtDados[(pos + i) % mCapacidade] != NULL)
    {

        i++;
    }
    mVetPtDados[(pos + i) % mCapacidade] = ptPar;
}

unsigned Hash::Posicao(const string &chave) const
{
    // Retorna a posição de armazenamento de uma chave, 0 <= posicao < mCapacidade. Protegido.
    unsigned pos = 1;
    unsigned tamanho = unsigned(chave.length());
    for (unsigned i = 0; i < tamanho; ++i)
        pos = 7 * pos + chave[i];
    return pos % mCapacidade;
}

void Hash::Redimensionar(unsigned novaCapacidade)
{

    if (novaCapacidade < mTamanho)
    {
        throw invalid_argument("nova capacidade invalida");
    }
    else
    {
        InfoHash **auxVet = mVetPtDados;
        unsigned old = mCapacidade;
        mCapacidade = novaCapacidade;
        mVetPtDados = new InfoHash *[novaCapacidade];
        for (unsigned i = 0; i < novaCapacidade; i++)
        {
            mVetPtDados[i] = NULL;
        }
        InfoHash *aux;
        for (unsigned i = 0; i < old; i++)
        {
            aux = auxVet[i];
            if (aux != NULL)
            {
                Inserir(aux);
            }
            auxVet[i] = NULL;
        }
        delete[] auxVet;
    }
}

void Hash::Remover(const std::string &chave)
{

    if (mTamanho == 0)
    {
        throw invalid_argument("");
    }
    int pos = Buscar(chave);
    if (pos == -1)
    {
        throw invalid_argument("");
    }
    mVetPtDados[pos] = REMOVIDO;
    mTamanho--;
}

TValor Hash::Valor(const std::string &chave) const
{

    unsigned pos = Buscar(chave);
    return mVetPtDados[pos]->mValor;
}

int main()
{
    unsigned capacidade;
    cin >> capacidade;
    Hash tabela(capacidade);
    char operacao;
    string chave;
    TValor valor;
    do
    {
        try
        {
            cin >> operacao;
            switch (operacao)
            {
            case 'i': // inserir
                cin >> chave >> valor;
                tabela.Inserir(chave, valor);
                break;
            case 'r': // remover
                cin >> chave;
                tabela.Remover(chave);
                break;
            case 'c': // consultar
                cin >> chave;
                valor = tabela.Valor(chave);
                cout << valor << endl;
                break;
            case 'd': // debug (mostrar estrutura)
                tabela.EscreverEstrutura(cout);
                cout << endl;
                break;
            case 'f': // finalizar
                // vai testar depois
                break;
            default:
                cerr << "operação inválida\n";
                break;
            }
        }
        catch (exception &e)
        {
            // ignorar a mensagem que explica o erro e só escrever ERRO.
            cout << "ERRO" << endl;
        }
    } while (operacao != 'f');
    return 0;
}