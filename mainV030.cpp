#include <iostream>
#include <fstream>
//#include <string>

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

void registerNotes(int *valueBanknotes, int typeBanknotes, string currencySymbol){
	fstream arquivo("dados.txt", ios::out);
	string valor;
	try{
		if(arquivo.is_open()){
			cout << "Quantas notas gostaria de cadastrar: ";
			cin >> typeBanknotes;
			cout << "Simbolo monetario da sua moeda: ";
			cin >> currencySymbol;
			arquivo << currencySymbol;

			cout << "==================================" << endl;
			cout << "Registro dos " + to_string(typeBanknotes) + " valores de cedulas" << endl;
			cout << "==================================" << endl;
			for(int i = 0; i < typeBanknotes; i++){
				cout << "Digite o valor da cedula " + to_string(i+1) + ": ";
				cin >> valueBanknotes[i];
				cout << typeBanknotes << " " << valueBanknotes[i] << endl;
				arquivo << endl << valueBanknotes[i];
			}
			arquivo.close();
			cout << "==================================" << endl;
		}else{
			throw 404;
		}
	}catch(int erro){
		cout << "Falha ao abrir o arquivo. Erro: " << erro << endl;
	}
}

void countNotes(int *numberBanknotes, int *valueBanknotes, int withdraw, int typeBanknotes){	// Função de separação das notas por valor
    for(int i = 0; i < typeBanknotes; i++){
        numberBanknotes[i] = withdraw / valueBanknotes[i];
        withdraw = withdraw % valueBanknotes[i];

        if(withdraw == 1 || withdraw == 3){
            numberBanknotes[i]--;
            withdraw += valueBanknotes[i];
        }
    }
}

int main(){
	fstream arquivo("dados.txt", ios::in);
    string input, currencySymbol;
    int withdraw;
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
		}else{
			throw 404;
		}
	}catch(int aviso){
		cout << "Arquivo de dados nao encontrado. " << aviso << endl;
	}
	arquivo.close();
	
	while(input != "exit"){
    	input = menu(input);
		
		if(input == "sacar"){
			if(valueBanknotes[0] == 0){
			cout << "Arquivo vazio" << endl;
		}else{
			cout << endl;
			cout << "==================================" << endl;
			cout << "Digite o valor a ser sacado: ";                //Le valor a ser sacado do Caixa Eletronico
			cin >> input;

			withdraw = stoi(input);
			countNotes(numberBanknotes, valueBanknotes, withdraw, typeBanknotes); //chama a função para contar as notas

			cout << "==================================" << endl;
			for(int i = 0; i < typeBanknotes; i++){
				cout << "Qtd. Cedulas de " + currencySymbol + " " + to_string(valueBanknotes[i]) + ",00: " + to_string(numberBanknotes[i]) << endl;
			}
		}
		}else if(input == "exit"){
			cout << "==================================" << endl;
			cout << "  SISTEMA FINALIZADO - COD.exit  " << endl;
			cout << "==================================" << endl;   
		}else if(input == "cadastrar"){
			registerNotes(valueBanknotes, typeBanknotes, currencySymbol);  //Cadastra valores de N notas diferentes

		}else if(input == "ajuda"){
			cout << "Seção de ajuda" << endl;

		}else{
			cout << "Opcao Invalida" << endl;
		}
		cout << typeBanknotes << endl;
	}	
	
    delete[] numberBanknotes;
    delete[] valueBanknotes;
    return 0;
}