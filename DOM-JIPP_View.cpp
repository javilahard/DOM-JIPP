/*DOM-JIPP_View.cpp - Etapa 3
24/08/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

#include <stdio.h>
#include <stdlib.h>
#include "DOM-JIPP_View.h"

int menu()
{ 
    
    printf("===== DOMINO JIPP =====\n\n");
	
	
		printf("1. Embaralhar pecas\n");
		printf("2. Reorganizar pecas\n");
		printf("3. Mostrar pecas na tela\n");
	        printf("4. Iniciar o jogo\n");
		printf("5. Sair\n");
		scanf("%d", &resp);
		system("cls");
		switch(resp)
		{
			case 1:
				
				printf("Pecas embaralhadas com sucesso :)\n");
				break;
			case 2:
				printf("Pecas reorganizadas com  sucesso :)\n");
				break;
			case 3:
				return resp;
				break;
			case 4:
			        return resp;
			        break;
			case 5:
				printf("MENU encerrado\n");
				break;
			default:
				printf("Opcao invalida!\n");
		}
		system("pause");
		system("cls");
		return resp;
}

void mostra(tipo_peca peca[28])	
{
	int p = 0;
	
	for(int i = 0; i <= 6; i++)
	{
		for(int j = i; j <= 6; j++)
		{
			printf("%d|%d\t", peca[p].lado1, peca[p].lado2);
			p++;
		}
		printf("\n");
		
	}
	system("pause");
	system("cls");
}

void apresenta_peca(char jogador)
{
	int a = 1;
	
	for(int i = 0; i < 28; i++)
	{
		if(peca[i].status == jogador)                     //caracter que vem do controller, respectivamente das funcoes iniciar e jogar.
		{
			printf("%d.[%d|%d]   ", a, peca[i].lado1, peca[i].lado2);
			a++;
		}
	}
	printf("\n");
}

void apresenta_mensagem(char m[100])
{
	printf("%s\n", m);
}

void mostra_mesa()
{
	printf("=============\n");
	printf("MESA: ");
	for(int i = 0; i <= qtmesa; i++)
	{
		printf("[%d|%d]", mesa[i].ladoE, mesa[i].ladoD);	
	}
	printf("=============\n");
}

char menu_jogada()
{
	char op;
	printf("J - Jogar (possiveis: %d ou %d)\n", mesa[0].ladoE, mesa[njogadas-1].ladoD);
	printf("C - Comprar\n");
	printf("S - Sair (interromper o jogo)\n");
	printf("Opcao: ");
	scanf(" %c", &op);
	return op;
}

int escolher_peca(char jogador)
{
	int es;
	printf("Jogador %c: Escolha a peca para jogar (0 para desistir): ", jogador);
	scanf("%d", &es);
	return es;
}

char escolher_lado()
{
	char lado;
	printf("Escolha o lado da mesa (E/D): ");
	scanf(" %c");
	return lado;
}






