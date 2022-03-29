#include "simd.h"

// Recebe 4 valores de 8 bits (0 a 255), armazena e retorna esses 4 valores em uma variavel de 32 bits
unsigned int Armazena(unsigned char input1, unsigned char input2, unsigned char input3, unsigned char input4) {
	unsigned int result = 0;

	result = result | (input1 << 24);
	result = result | (input2 << 16);
	result = result | (input3 << 8);
	result = result | input4;

	return result;
}

// percorre 24 bits da variavel de 32 para pegar os primeiros 8 bits e devolver seu valoir
unsigned char Primeiro(unsigned int input) {
	return (input >> 24);
}

// percorre 16 bits da variavel de 32 para pegar os proximos 8 bits e devolver seu valoir
unsigned char Segundo(unsigned int input) {
	return (input >> 16);
}

// percorre 8 bits da variavel de 32 para pegar os proximos 8 bits e devolver seu valoir
unsigned char Terceiro(unsigned int input) {
	return (input >> 8);
}

// pega os primeiros 8 bits da variavel de 32 que corresponde ao 4º valor atribuido a ela
unsigned char Quarto(unsigned int input) {
	return input;
}

// Recebe duas variaveis de 32 bits, pega seus respectivos valores, realiza sua soma e devolve os resultados
// em uma variavel de 32 bits
unsigned int Soma(unsigned int input1, unsigned int input2) {
	unsigned char firstValue = Primeiro(input1) + Primeiro(input2);
	unsigned char secondValue = Segundo(input1) + Segundo(input2);
	unsigned char thirdValue = Terceiro(input1) + Terceiro(input2);
	unsigned char fourthValue = Quarto(input1) + Quarto(input2);

	return Armazena(firstValue, secondValue, thirdValue, fourthValue);
}

// Recebe duas variaveis de 32 bits, pega seus respectivos valores, realiza sua multiplicãção e devolve os resultados
// em uma variavel de 32 bits
unsigned int Mult(unsigned int input1, unsigned int input2) {
	unsigned char firstValue = Primeiro(input1) * Primeiro(input2);
	unsigned char secondValue = Segundo(input1) * Segundo(input2);
	unsigned char thirdValue = Terceiro(input1) * Terceiro(input2);
	unsigned char fourthValue = Quarto(input1)  * Quarto(input2);

	return Armazena(firstValue, secondValue, thirdValue, fourthValue);
}