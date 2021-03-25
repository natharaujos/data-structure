// as mudanças feitas em relação a etapa manual, estão comentadas!

// OS VETORES "PARTICIPATE" E "PARCEIRO" FORAM ALOCADOS COM 100 POSIÇÕES.

// struct's "parceriaLoja" e "parceriaOficina" foram adicionados, e o struct "parceria" foi removido

#include <iostream>
using namespace std;

struct participantes {
	
	string nome;
	string marca;
	string modelo;
	string ano;
	string telefone;
};

struct parceriaLoja {
	
	string loja;
	string nomeMarca;
	string beneficio;
	string servico; // variaveis "servico" e "preco" foram adicionadas
	string preco;
};

struct	parceriaOficina {
	
	string oficina; 
	string nomeMarca;
	string beneficio;
	string servico; // variaveis "servico" e "preco" foram adicionadas
	string preco;
};

class associacao {
	
	public:
		int totalOficinas; // variavel adicionada para facilitar a busca
		int totalLojas;
		participantes *participate; // variavel adicionada 
		parceriaLoja *parceiroLoja; // variavel adicionada
		parceriaOficina *parceiroOficina; // variavel adicionada
		void registrarAcordos();
		void consultarNome(string);
		~associacao(); // destrutor adicionado
		associacao(); // construtor adicionado
};

associacao::associacao() {
		
		participate = new participantes[100];
		parceiroLoja = new parceriaLoja[100];
		parceiroOficina = new parceriaOficina[100];
		totalOficinas=0;
		totalLojas = 0;
}

void associacao::registrarAcordos() {
	
		cout << "Escolha: " << endl;
		cout << "[1] - Loja" << endl;
		cout << "[2] - Oficina" << endl;
		
		int option;
		cin >> option;
		
		cin.ignore();
		
		if (option==1)
		{
			cout << "Nome Loja: ";
			getline(cin, parceiroLoja[totalLojas].loja);
			
			cout << "Marca Especializada: ";
			getline(cin, parceiroLoja[totalLojas].nomeMarca);
			
			cout << "Nome do Cliente: ";
			getline(cin, participate[totalLojas].nome);
			
			cout << "Tipo de Servico: ";
			getline(cin, parceiroLoja[totalLojas].servico);
			
			cout << "Preco: ";
			getline(cin, parceiroLoja[totalLojas].preco);
			
			cout << "--Escolha um Beneficio--" << endl;
			cout << "[1] - Desconto por servico" << endl;
			cout << "[2] - Brinde" << endl;
			cout << "[3] - Revisao gratuita apos 5 sevicos" << endl;
		
			int opcao1;
			cin >> opcao1;
		
			cin.ignore();
		
			switch (opcao1)
			{
				case 1:
					cout << "Voce recebeu um DESCONTO POR SERVICO de " << parceiroLoja[totalLojas].loja << endl;
					break;

				case 2:
					cout << "Voce recebeu um BRINDE de " << parceiroLoja[totalLojas].loja << endl;
					break;
			
				case 3:
					cout << "Voce recebeu uma REVISAO GRATUITA APOS 5 SERVICOS de " << parceiroLoja[totalLojas].loja << endl;
					break;
				default:
					cout << "Digite um numero valido";
			}
			
			cout << "Loja Cadastrada com Sucesso!" << endl;
			
			totalLojas++;
		}
		
		else if (option==2)
		{
			cout << "Nome Oficina: ";
			getline(cin, parceiroOficina[totalOficinas].oficina);
			
			cout << "Marca Especializada: ";
			getline(cin, parceiroOficina[totalOficinas].nomeMarca);
			
			cout << "Nome do Cliente: ";
			getline(cin, participate[totalOficinas].nome);
			
			cout << "Tipo de Servico: ";
			getline(cin, parceiroOficina[totalOficinas].servico);
		
			cout << "--Escolha um Beneficio--" << endl;
			cout << "[1] - Desconto" << endl;
			cout << "[2] - Brinde" << endl;
			cout << "[3] - Revisao gratuita apos 5 sevicos" << endl;
		
			int opcao2;
			cin >> opcao2;
		
			cin.ignore();
		
			switch (opcao2)
			{
				case 1:
					cout << "Voce recebeu um DESCONTO POR SERVICO de " << parceiroOficina[totalOficinas].oficina << endl;
					break;

				case 2:
					cout << "Voce recebeu um BRINDE de " << parceiroOficina[totalOficinas].oficina << endl;
					break;
			
				case 3:
					cout << "Voce recebeu uma REVISAO GRATUITA APOS 5 SERVICOS de " << parceiroOficina[totalOficinas].oficina << endl;
					break;
				default:
					cout << "Digite um numero valido";
			}
			
			cout << "Oficina Cadastrada com Sucesso!" << endl;
		
			totalOficinas++;
		}
}

void associacao::consultarNome(string marca) {
		
		for (int i = 0; i < totalLojas; i++)
		{
			if (marca==parceiroLoja[i].nomeMarca)
			{
				cout << parceiroLoja[i].loja << endl;
			}
		}
		
		for (int i = 0; i < totalOficinas; i++)
		{	
			if (marca==parceiroOficina[i].nomeMarca)
			{
				cout << parceiroOficina[i].oficina  << endl;
			}
		}
}

associacao::~associacao() {
	
	cout << endl;
	cout << "morrendo..." << endl;
	delete[] participate;
	delete[] parceiroLoja;
	delete[] parceiroOficina;
	totalOficinas = 0;
	cout << "MORRI" << endl;
}

int main () {

	int numParticipantes;
	
	cout << "Insira o numero de Participantes da Associacao: ";
	cin >> numParticipantes;
	
	associacao *associate=new associacao;
	
	for (int i = 0; i < numParticipantes; i++)
	{
		cout << endl;
			
		cout << "Nome: ";
		cin >> associate->participate[i].nome;
		
		cout << "Marca da Moto: ";
		cin >> associate->participate[i].marca;
		
		cout << "Modelo: ";
		cin >> associate->participate[i].modelo;
			
		cout << "Ano: ";
		cin >> associate->participate[i].ano;
			
		cout << "Telefone para contato: ";
		cin >> associate->participate[i].telefone;
			
		cout << endl;		
	}
	
	int numAcordos;
	
	cout << endl;
	
	cout << "----Registrar Acordos----" << endl;
	
	cout << "Insira o numero de Acordos: ";
	cin >> numAcordos;
	
	cin.ignore();
	
	for (int i = 0; i < numAcordos; i++)
	{
		
		cout << endl;
		
		associate->registrarAcordos();
		
		cout << endl;
	}
	
	cout << "----Digite o nome da Marca de sua moto para consultar oficinas/lojas especializadas----: ";
	
	string marca;
	
	cin >> marca;

	associate->consultarNome(marca);
	
	delete associate;
	
	return 0;
}
