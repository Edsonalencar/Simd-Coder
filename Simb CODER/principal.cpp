#include <iostream>
#include "simd.h"
#include "cripto.h"
using namespace std;

int main(void) {
	int fistInput = 0, secondValue = 0, thirdValue = 0, fourthValue = 0;
	unsigned int dataStorageOne = 0, dataStorageTwo = 0, sumStorage = 0, multStorage = 0;
	unsigned long long sumStorageCripto = 0, multStorageCripto = 0;
	char separator;

	// Pegando valores passados pelo usuario e armazenando em uma variavel de 32 bits
	cin >> separator >> fistInput >> separator >> secondValue >> separator >> thirdValue >> separator >> fourthValue >> separator;
	dataStorageOne = Armazena(fistInput, secondValue, thirdValue, fourthValue);

	cin >> separator >> fistInput >> separator >> secondValue >> separator >> thirdValue >> separator >> fourthValue >> separator;
	dataStorageTwo = Armazena(fistInput, secondValue, thirdValue, fourthValue);

	cout << endl;

	cout << "Operandos em 32 bits = " << dataStorageOne << endl;
	cout << "Operandos em 32 bits = " << dataStorageTwo << endl;

	cout << endl;

	// Realizando o processo de soma simultanea dos valores.
	sumStorage = Soma(dataStorageOne, dataStorageTwo);
	// Realizando o processo de multiplicação simultanea dos valores.
	multStorage = Mult(dataStorageOne, dataStorageTwo);

	cout << "Soma em 32 bits = " << sumStorage << endl;
	cout << "Mult em 32 bits = " << multStorage << endl;

	cout << endl;

	// mostrando valores em tela de maneira formatada.
	cout << "[";
	cout.width(3); cout.fill('0');
	cout << int(Primeiro(sumStorage)) << ",";
	cout.width(3); cout.fill('0');
	cout << int(Segundo(sumStorage)) << ",";
	cout.width(3);
	cout.fill('0');
	cout << int(Terceiro(sumStorage)) << ",";
	cout.width(3);
	cout.fill('0');
	cout << int(Quarto(sumStorage)) << "] = Somas\n";

	cout << "[";
	cout.width(3);
	cout.fill('0');
	cout << int(Primeiro(multStorage)) << ",";
	cout.width(3);
	cout.fill('0');
	cout << int(Segundo(multStorage)) << ",";
	cout.width(3);
	cout.fill('0');
	cout << int(Terceiro(multStorage)) << ",";
	cout.width(3);
	cout.fill('0');
	cout << int(Quarto(multStorage)) << "] = Multiplicações\n";

	cout << endl;
	// codificando valores resultados de soma e multiplicação.
	sumStorageCripto = Codificar(sumStorage);
	multStorageCripto = Codificar(multStorage);

	cout << "Soma Cripto 64 bits = " << sumStorageCripto << endl;
	cout << "Mult Cripto 64 bits = " << multStorageCripto << endl;
	 
	cout << endl;

	// pegando as posições da codificação da soma que sofreram auteração.
	unsigned char keyCriptoSum[6] = { 0 };
	unsigned int keysCriptoSoma = sumStorageCripto;

	keyCriptoSum[0] = (keysCriptoSoma >> 27);
	keysCriptoSoma = keysCriptoSoma & ~(keyCriptoSum[0] << 27);

	keyCriptoSum[1] = (keysCriptoSoma >> 22);
	keysCriptoSoma = keysCriptoSoma & ~(keyCriptoSum[1] << 22);

	keyCriptoSum[2] = (keysCriptoSoma >> 17);
	keysCriptoSoma = keysCriptoSoma & ~(keyCriptoSum[2] << 17);

	keyCriptoSum[3] = (keysCriptoSoma >> 12);
	keysCriptoSoma = keysCriptoSoma & ~(keyCriptoSum[3] << 12);

	keyCriptoSum[4] = (keysCriptoSoma >> 7);
	keysCriptoSoma = keysCriptoSoma & ~(keyCriptoSum[4] << 7);

	keyCriptoSum[5] = (keysCriptoSoma >> 2);

	cout << "Valor Codificado = " << (sumStorageCripto >> 32) << " (";
	cout << int(keyCriptoSum[0]) << " " << int(keyCriptoSum[1]) << " ";
	cout << int(keyCriptoSum[2]) << " " << int(keyCriptoSum[3]) << " ";
	cout << int(keyCriptoSum[4]) << " " << int(keyCriptoSum[5]) << ")" << endl;

	cout << "Soma Decodificada = " << Decodificar(sumStorageCripto) << endl;

	cout << endl;

	// pegando as posições da codificação da Multiplicação que sofreram auteração.
	unsigned char keyCriptoMult[6] = { 0 };
	unsigned int keysCriptoMult = multStorageCripto;

	keyCriptoMult[0] = (keysCriptoMult >> 27);
	keysCriptoMult = keysCriptoMult & ~(keyCriptoMult[0] << 27);

	keyCriptoMult[1] = (keysCriptoMult >> 22);
	keysCriptoMult = keysCriptoMult & ~(keyCriptoMult[1] << 22);

	keyCriptoMult[2] = (keysCriptoMult >> 17);
	keysCriptoMult = keysCriptoMult & ~(keyCriptoMult[2] << 17);

	keyCriptoMult[3] = (keysCriptoMult >> 12);
	keysCriptoMult = keysCriptoMult & ~(keyCriptoMult[3] << 12);

	keyCriptoMult[4] = (keysCriptoMult >> 7);
	keysCriptoMult = keysCriptoMult & ~(keyCriptoMult[4] << 7);

	keyCriptoMult[5] = (keysCriptoMult >> 2);

	cout << "Valor Codificado = " << (multStorageCripto >> 32) << " (";
	cout << int(keyCriptoMult[0]) << " " << int(keyCriptoMult[1]) << " ";
	cout << int(keyCriptoMult[2]) << " " << int(keyCriptoMult[3]) << " ";
	cout << int(keyCriptoMult[4]) << " " << int(keyCriptoMult[5]) << ")" << endl;

	cout << "Mult Decodificada = " << Decodificar(multStorageCripto) << endl;
}