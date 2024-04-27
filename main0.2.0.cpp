#include <iostream>
#include <string>

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

void registerNotes(int *valueBanknotes, int typeBanknotes){

	cout << "==================================" << endl;
	cout << "Registro dos " + to_string(typeBanknotes) + " valores de notas" << endl;
	cout << "==================================" << endl;
	for(int i = 0; i < typeBanknotes; i++){
    	cout << "Digite o valor da cedula " + to_string(i+1) + ": ";
    	cin >> valueBanknotes[i];
	}
	cout << "==================================" << endl;
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

int terminalOutput(string input, int withdraw, int *numberBanknotes, int *valueBanknotes, int typeBanknotes){	// Administra os prints no terminal

	if(input == "sacar"){
		cout << endl;
		cout << "==================================" << endl;
		cout << "Digite o valor a ser sacado: ";                //Le valor a ser sacado do Caixa Eletronico
		cin >> input;

		withdraw = stoi(input);
		countNotes(numberBanknotes, valueBanknotes, withdraw, typeBanknotes); //chama a função para contar as notas

		cout << "==================================" << endl;
		for(int i = 0; i < typeBanknotes; i++){
			cout << "Qtd. Cedulas de $ " + to_string(valueBanknotes[i]) + ",00: " + to_string(numberBanknotes[i]) << endl;
		}
		cout << "==================================" << endl;
	}
	if(input == "exit"){
        cout << "==================================" << endl;
        cout << "  SISTEMA FINALIZADO - COD.exit  " << endl;
        cout << "==================================" << endl;
		return 1;   
    }

	if(input == "cadastrar"){
		registerNotes(valueBanknotes, typeBanknotes);                            //Cadastra valores de N notas diferentes
	}

	if(input == "ajuda"){
		cout << "Seção de ajuda" << endl;
	}
	return 0;
}

int main(){
    string input;	//Declara variaveis
    int withdraw;
    int typeBanknotes(6);
    int *numberBanknotes = new int[typeBanknotes];	// Alocação variável de memória                
    int *valueBanknotes = new int[typeBanknotes];

    while(input != "exit"){
    	input = menu(input);
		terminalOutput(input, withdraw, numberBanknotes, valueBanknotes, typeBanknotes); // chama a funçao de outputs no terminal
    }
    
    delete[] numberBanknotes;
    delete[] valueBanknotes;

    return 0;
}