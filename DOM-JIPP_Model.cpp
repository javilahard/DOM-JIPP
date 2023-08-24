/*DOM-JIPP_Model.cpp - Etapa 3
24/08/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/


#include "DOM-JIPP_Model.h"


typedef struct Peca
	{
		int lado1;
		int lado2;
		char status;
	} tipo_peca;
	
struct Mesa
	{
		int ladoE;
		int ladoD;
	} mesa[28];

tipo_peca peca[28];
tipo_peca aux;

	

