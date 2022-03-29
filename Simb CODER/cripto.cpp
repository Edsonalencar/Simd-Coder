#include <random>
#include <iostream>
#include "cripto.h"
using namespace std;

// Popula um vetor de 6 posições com valores aleatorios depois percorre uma variavel de 32 bits invertendo o valor dos bits
// das posições geradas anteriormente, por fim, junta o valor modificado com as posições que foram auteradas em uma variavel de 
// 64 bits e a retorna.
unsigned long long Codificar(unsigned int input) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, 31);

	unsigned char random[6] = {0};
	unsigned int result = input;
	
	// Populando vetor com valores aleatorios
	for (int i = 0; i < 6; i++) {
		random[i] = dist(mt);
	}

	// auterando o bit das posições selecionadas
	for (int i = 0; i < 6; i++) {
		if(TestarBit(result, random[i])) {
			result = DesligarBit(result, random[i]);
		}
		else {
			result = LigarBit(result, random[i]);
		}
	}

	// Juntando tudo em uma variavel de 64 bits
	unsigned long long resultCodex = 0;

	resultCodex = (unsigned long long (result) << 32);
	resultCodex = resultCodex | (unsigned long long (random[0]) << 27);
	resultCodex = resultCodex | (unsigned long long (random[1]) << 22);
	resultCodex = resultCodex | (unsigned long long (random[2]) << 17);
	resultCodex = resultCodex | (unsigned long long (random[3]) << 12);
	resultCodex = resultCodex | (unsigned long long (random[4]) << 7);
	resultCodex = resultCodex | (unsigned long long (random[5]) << 2);

	return resultCodex;
}

// Percorre a variavel de 64 bits pegando o valor codificado (valor de 32 bits) e as posições que foram auteradas neste valor,
// depois retorna os valores destas posições ao seu estado original
unsigned int Decodificar(unsigned long long input) {

	unsigned int keys = input;
	unsigned char keyCripto[6];

	// pegando as posições que foram auteradas
	keyCripto[0] = (keys >> 27);
	keys = keys & ~(keyCripto[0] << 27);

	keyCripto[1] = (keys >> 22);
	keys = keys & ~(keyCripto[1] << 22);

	keyCripto[2] = (keys >> 17);
	keys = keys & ~(keyCripto[2] << 17);

	keyCripto[3] = (keys >> 12);
	keys = keys & ~(keyCripto[3] << 12);

	keyCripto[4] = (keys >> 7);
	keys = keys & ~(keyCripto[4] << 7);

	keyCripto[5] = (keys >> 2);
	
	// pegando valor codificado
	unsigned int result = (input >> 32);

	// retornando as posições auteradas do valor codificado ao seu estado original
	for (int i = 0; i < 6; i++) {
		if (TestarBit(result, keyCripto[i])) {
			result = DesligarBit(result, keyCripto[i]);
		}
		else {
			result = LigarBit(result, keyCripto[i]);
		}
	}

	return result;
}

// Aplica uma mascara fazendo um "Or" de modo a mudar um bit de determinada posição de 0 para 1 (ativar bit)
unsigned int LigarBit(unsigned int input, unsigned char random) {
	unsigned int mesk = 1 << random;
	unsigned int result = input;
	result = result | mesk;

	return result;
}

// Aplica uma mascara fazendo um "End" de modo a mudar um bit de determinada posição de 1 para 0 (desativar bit)
unsigned int DesligarBit(unsigned int input, unsigned char random) {
	unsigned int mesk = ~(1 << random);
	unsigned int result = input;
	result = result & mesk;

	return result;
}

// Aplica uma mascara fazendo um "End" de modo a verificar se um bit de determinada posição esta ativo ou não
bool TestarBit(unsigned int input, unsigned char random) {
	unsigned int mesk = 1 << random;
	unsigned int result = input;
	
	if (result & mesk) { return true; }
	else { return false; }
}