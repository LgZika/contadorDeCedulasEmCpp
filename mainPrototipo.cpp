#include <iostream>
//#include <string>

using namespace std;

void registerNotes(int *valueBanknotes, int typeBanknotes) {
	cout << "=================================" << endl;
	cout << "Registro dos " + to_string(typeBanknotes) + " valores de notas" << endl;
	cout << "=================================" << endl;
	for(int i = 0; i < typeBanknotes; i++){
    	cout << "Digite o valor da cedula " + to_string(i+1) + ": ";
    	cin >> valueBanknotes[i];
	}
	cout << "=================================" << endl;
}

void countNotes(int *numberBanknotes, int *valueBanknotes, int withdraw, int typeBanknotes){       //Função de separação das notas por valor
    int backup;

    for(int i = 0; i < typeBanknotes; i++){
        numberBanknotes[i] = withdraw / valueBanknotes[i];
        withdraw = withdraw % valueBanknotes[i];

        if(withdraw == 1 || withdraw == 3){
            numberBanknotes[i]--;
            withdraw += valueBanknotes[i];
        }
    }
    
//     numberBanknotes[0] = (withdraw / valueBanknotes[0]);
//     numberBanknotes[1] = ((withdraw % valueBanknotes[0]) / valueBanknotes[1]);
//     numberBanknotes[2] = (((withdraw % valueBanknotes[0]) % valueBanknotes[1]) / valueBanknotes[2]);
//     numberBanknotes[3] = ((((withdraw % valueBanknotes[0]) % valueBanknotes[1]) % valueBanknotes[2]) / valueBanknotes[3]);
//     numberBanknotes[4] = (((((withdraw % valueBanknotes[0]) % valueBanknotes[1]) % valueBanknotes[2]) % valueBanknotes[3]) / valueBanknotes[4]);
//     numberBanknotes[5] = ((((((withdraw % valueBanknotes[0]) % valueBanknotes[1]) % valueBanknotes[2]) % valueBanknotes[3]) % valueBanknotes[4]) / valueBanknotes[5]);
}

void terminalOutput(int *numberBanknotes, int *valueBanknotes, int typeBanknotes) {
	cout << "=================================" << endl;
	for(int i = 0; i < typeBanknotes; i++){
    	cout << "Qtd. Cedulas de $ " + to_string(valueBanknotes[i]) + ",00: " + to_string(numberBanknotes[i]) << endl;
	}
	cout << "=================================" << endl;
}

int main(){
    string input;                      //Declara variaveis
    int withdraw;
    int exitSystem(0);
    int typeBanknotes(6);
    int *numberBanknotes = new int[typeBanknotes];                     //Declara ponteiros para arrays
    int *valueBanknotes = new int[typeBanknotes];
    
    registerNotes(valueBanknotes, typeBanknotes);                            //Cadastra valores de N notas diferentes

    while (exitSystem != 1){
    	
    	cout << endl << "=================================" << endl;
    	cout << "Digite o valor a ser sacado: ";                //Le valor a ser sacado do Caixa Eletronico
    	cin >> input;
    	if(input == "exit"){
        	exitSystem = 1;
        	cout << "=================================" << endl;
        	cout << "SISTEMA INTERROMPIDO - COD.exit" << endl;
        	cout << "=================================" << endl;
        	break;    
    	}
    	withdraw = stoi(input);
        cout << withdraw << endl; 
        
     	countNotes(numberBanknotes, valueBanknotes, withdraw, typeBanknotes); //Conta notas por valor
     	terminalOutput(numberBanknotes, valueBanknotes, typeBanknotes); // informações
    }
    
    delete[] numberBanknotes;
    delete[] valueBanknotes;

    return 0;
}
