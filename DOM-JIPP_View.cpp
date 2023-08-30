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
	printf("1.Iniciar o jogo\n");
    printf("2.Sair\n\n");
    printf("Opcao: ");
	scanf("%d", &resp);
	system("cls");
	if(resp!=1 && resp!=2)
		{
		printf("Opcao invalida!\n");
		system("pause");
	    system("cls");
		return resp;
	    }
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
	
	printf("JOGADOR %c: ", jogador);
	
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
	for(int i = 0; i < qtmesa; i++)
	{
		printf("[%d|%d]", mesa[i].ladoE, mesa[i].ladoD);	
	}
	printf("\n");
	printf("=============\n");
}

char menu_jogada()
{
	char op;
	printf("J - Jogar (possiveis: %d ou %d)\n", mesa[0].ladoE, mesa[qtmesa-1].ladoD);
	printf("C - Comprar\n");
	printf("P - Passar\n");
	printf("S - Sair do jogo\n");
	printf("Opcao: ");
	flush_in();
	scanf(" %c", &op);
	return op;
}

int escolher_peca(char jogador)
{
	int es;
	printf("Jogador %c: Escolha a peca para jogar: ", jogador);
    scanf("%d", &es);
	return es;
}

char escolher_lado()
{
	char lado;
	printf("Escolha o lado da mesa (E/D): ");
	flush_in();
	scanf("%c", &lado);
	system("cls");
	return lado;
}

void flush_in() //ou void fclear()
{
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n');
}

void venc_batida(char jogador)
{
	int k, p;
	p=0;
	k=0;
	while(k<28)
	{
        if(peca[k].status == jogador)
			p++;
		k++;
	}
		
	if(p==1)
	{
	   printf("Jogador %c bateu!\n", jogador);
	   exit(0);
    }
}





