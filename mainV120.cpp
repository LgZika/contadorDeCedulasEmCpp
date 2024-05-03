#include <iostream>
#include <fstream>
//#include <string>
//#include <cctype>

using namespace std;

string menu(string input){	// Função que exibe o menu
	cout << "==================================" << endl;
	cout << "       Contador de Cedulas!       " << endl;
	cout << "          Menu Principal          " << endl;
	cout << "==================================" << endl;
	cout << " - Sacar" << endl;
	cout << " - Cadastrar" << endl;
	cout << " - Ajuda" << endl;
	cout << " - Sair" << endl;
	cout << "==================================" << endl;
	cout << "   Opcao: ";
	cin >> input;

	for(int i = 0; i < input.size(); i++){ // Sempre transforma os comandos para lowercase
		tolower(input[i]);
	}
	return input;
}

int registerNotes(int *valueBanknotes, int typeBanknotes, string currencySymbol){ // Função para registrar e salvar as notas em um arquivo .txt
	ofstream arquivo("dados.txt");
	try{
		if(arquivo.is_open()){
			cout << "==================================" << endl;
			cout << "Quantas notas gostaria de cadastrar: ";
			cin >> typeBanknotes;

			cout << "Simbolo monetario da sua moeda: ";
			cin >> currencySymbol;
			arquivo << currencySymbol;

			cout << "Cadastro dos " + to_string(typeBanknotes) + " valores de cedulas" << endl;

			cout << "==================================" << endl;
			for(int i = 0; i < typeBanknotes; i++){
				cout << "Digite o valor da cedula " + to_string(i+1) + ": ";
				cin >> valueBanknotes[i];
				arquivo << endl << valueBanknotes[i];
			}
			arquivo.close();
		}else{
			throw 404;
		}
	}catch(int erro){
		cout << "Falha ao abrir o arquivo!" << endl;
		cout << "codigo: " << erro << endl;
	}
	return typeBanknotes;
}

void countNotes(int money, int *numberBanknotes, int *valueBanknotes, int typeBanknotes){	// Função de separação das notas por valor
    for(int i = 0; i < typeBanknotes; i++){
        numberBanknotes[i] = money / valueBanknotes[i];
     	money = money % valueBanknotes[i];

        if(money == 1 || money == 3){
            numberBanknotes[i]--;
        money += valueBanknotes[i];
        }
    }
}

void withdraw(string input, string currencySymbol, int *numberBanknotes, int *valueBanknotes, int typeBanknotes){
	int valid = 0;
	cout << "==================================" << endl;
	while(valid == 0){
		int check;
		cout << "Digite o valor a ser sacado: " + currencySymbol + " ";	//Le valor a ser sacado do Caixa Eletronico
		cin >> input;
		for (int i = 0; i < input.size(); i++){
			check = isdigit(input[i]);
			if(check){
				valid = 1;
			}else{
				valid = 0;
				break;
			}	
		}
	}
	int money = stoi(input);
	countNotes(money, numberBanknotes, valueBanknotes, typeBanknotes);	//chama a funcao para contar as cedulas

	cout << "==================================" << endl;
	for(int i = 0; i < typeBanknotes; i++){
		cout << "Qtd. Cedulas de " + currencySymbol + " " + to_string(valueBanknotes[i]) + ",00: " + to_string(numberBanknotes[i]) << endl;
	}
}

int main(){
	ifstream arquivo;
    string input, currencySymbol;
    int typeBanknotes;
    int *numberBanknotes = new int[typeBanknotes];	// Alocação variável de memória para 2 vetores unidimensionais               
    int *valueBanknotes = new int[typeBanknotes];

	valueBanknotes[0] = 0; 

	try{
		arquivo.open("dados.txt");
		if(arquivo.is_open()){
			typeBanknotes = 0;
			arquivo >> currencySymbol;
			while(!arquivo.eof()){
				arquivo >> valueBanknotes[typeBanknotes]; 
				typeBanknotes++;
			}
			arquivo.close();
		}else{
			throw 404;
		}
	}catch(int aviso){
		cout << "!!!Arquivo de dados nao pode ser carregado!!!" << endl;
		cout << "                 code." << aviso << endl;
		cout << "Cadastre as cedulas antes de iniciar;" << endl;
		typeBanknotes = registerNotes(valueBanknotes, typeBanknotes, currencySymbol);
	}
	
	while(input != "sair"){
    	input = menu(input);
		
		if(input == "sacar"){
			if(valueBanknotes[0] == 0){
				cout << "==================================" << endl;
				cout << "!!!Arquivo de dados Vazio!!!" << endl;
				cout << "Cadastre as cedulas antes de iniciar;" << endl;
				typeBanknotes = registerNotes(valueBanknotes, typeBanknotes, currencySymbol);
			}else{
				withdraw(input, currencySymbol, numberBanknotes, valueBanknotes, typeBanknotes);
			}

		}else if(input == "sair"){
			cout << "==================================" << endl;
			cout << " Sistema Finalizado - codigo.sair " << endl;
			cout << "==================================" << endl; 

		}else if(input == "cadastrar"){		
			typeBanknotes = registerNotes(valueBanknotes, typeBanknotes, currencySymbol);  //Cadastra valores de N notas diferentes
			try{
				arquivo.open("dados.txt"); // lê o arquivo depois de salvar
				if(arquivo.is_open()){
					typeBanknotes = 0;
					arquivo >> currencySymbol;
					while(!arquivo.eof()){
						arquivo >> valueBanknotes[typeBanknotes]; 
						typeBanknotes++;
					}
					arquivo.close();
				}else{
					throw 404;
				}
			}catch(int aviso){
				cout << "!!!Arquivo de dados nao pode ser carregado!!!" << endl;
				cout << "                 code." << aviso << endl;
				cout << "Cadastre as cedulas antes de iniciar;" << endl;
				typeBanknotes = registerNotes(valueBanknotes, typeBanknotes, currencySymbol);
			}

		}else if(input == "ajuda"){	// Seção de ajuda ao usuario final
			
			cout << "==================================" << endl;
			cout << "          Secao de ajuda          " << endl;
			cout << "==================================" << endl;
			cout << " - Sacar:                         " << endl;
			cout << "para sacar digite no terminal     " << endl;
			cout << "\"sacar\" e entre com o valor     " << endl;
			cout << "desejado;                         " << endl;
			cout << endl;
			cout << " - Cadastrar:                     " << endl;
			cout << "para cadastrar digite no terminal " << endl;
			cout << "\"cadastrar\", insira quantas     " << endl;
			cout << "cedulas ira cadastrar, insira o   " << endl;
			cout << "simbolo monetario da sua moeda e  " << endl;
			cout << "insira o valor de cada cedula em  " << endl;
			cout << "ordem decrescente;                " << endl;
			cout << endl;
			cout << " - Sair:                          " << endl;
			cout << "para sair digite no terminal      " << endl;
			cout << "\"sair\" e o sistema encerrar-se-a" << endl;
			cout << endl;
			cout << " - Oservacoes:                    " << endl;
			cout << "* Nosso sistema nao trabalha com  " << endl;
			cout << "moedas, ou seja, os centavos. Se  " << endl;
			cout << "inseridos, serao ignorados pelo   " << endl;
			cout << "programa;                         " << endl;
			cout << "* O sistema salva as ultimas      " << endl;
			cout << "cedulas cadastradas e as carrega  " << endl;
			cout << "sempre que iniciar                " << endl;

		}else{
			cout << "Opcao Invalida" << endl;
		}
	}	

    delete[] numberBanknotes;
    delete[] valueBanknotes;

    return 0;
}