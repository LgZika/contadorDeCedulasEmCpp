#include <iostream>
#include <fstream>
//#include <string>
//#include <cctype>

using namespace std;

string menu(string input){
	cout << "==================================" << endl;
	cout << "          Menu Principal          " << endl;
	cout << "==================================" << endl;
	cout << " - Sacar" << endl;
	cout << " - Cadastrar Cedulas" << endl;
	cout << " - Ajuda" << endl;
	cout << "==================================" << endl;
	cout << "   Opcao: ";
	cin >> input;

	for(int i = 0; i < input.size(); i++){ // Sempre transforma os comandos para lowercase
		tolower(input[i]);
	}
	return input;
}

int registerNotes(int *valueBanknotes, int typeBanknotes, string currencySymbol){
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
	ifstream arquivo("dados.txt");
    string input, currencySymbol;
    int typeBanknotes;
    int *numberBanknotes = new int[typeBanknotes];	// Alocação variável de memória para 2 vetores unidimensionais               
    int *valueBanknotes = new int[typeBanknotes];

	valueBanknotes[0] = 0; 

	try{
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
	
	while(input != "exit"){
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

		}else if(input == "exit"){
			cout << "==================================" << endl;
			cout << "  Sistema Finalizado - code.exit  " << endl;
			cout << "==================================" << endl; 

		}else if(input == "cadastrar"){		
			typeBanknotes = registerNotes(valueBanknotes, typeBanknotes, currencySymbol);  //Cadastra valores de N notas diferentes

		}else if(input == "ajuda"){
			cout << "Seção de ajuda" << endl;

		}else{
			cout << "Opcao Invalida" << endl;
		}
	}	

    delete[] numberBanknotes;
    delete[] valueBanknotes;

    return 0;
}