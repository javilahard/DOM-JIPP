/*DOM-JIPP_Model.cpp 
14/09/2023
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
	
struct Jogo
{
 int qtmesaJogo; //qtd.de pecas na mesa
 int jogadorJogo; //jogador atual
 int mesaDJogo; //extremidade direita da mesa
 int mesaEJogo; //extremidade esquerda da mesa
 int qtd_passarJogo; //qtd_passar atual
 int sent_Jogo;  //opcao do menu principal
} sitJogo; //situacao do jogo

tipo_peca peca[28];
tipo_peca aux;


	

