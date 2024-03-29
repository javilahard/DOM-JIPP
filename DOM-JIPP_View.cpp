/*DOM-JIPP_View.cpp 
23/09/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "DOM-JIPP_View.h"

int menu()
{ 
    system("cls");
    printf("===== DOMINO JIPP =====\n\n");
	printf("1.Iniciar o jogo(2 jogadores)\n");
	printf("2.Iniciar o jogo(contra o computador)\n");
	printf("3.Regras gerais do jogo\n");
	printf("4.Gravar partida\n");
	printf("5.Recuperar partida gravada\n");
    printf("6.Sair\n\n");
    printf("Opcao: ");
    scanf("%d", &resp);
    system("cls");
    
    if(resp==2)
	{
	    printf("\n\nO jogador 2 e' o computador.\n\n");
	    system("pause");
	    system("cls");
    }
	return resp;
}

void apresenta_peca(char jogadorrr)
{
	int a = 1;
	
	printf("JOGADOR %c: ", jogadorrr);
	
	for(int i = 0; i < 28; i++)
	{
		if(peca[i].status == jogadorrr)                     //caracter que vem do controller, respectivamente das funcoes iniciar e jogar.
		{
			printf(" %d.[%d|%d]   ", a, peca[i].lado1, peca[i].lado2);
			a++;
		}
	}
	printf("\n");
}

void apresenta_mensagem(char m[500])
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
	printf("\n=============\n\n");
}

char menu_jogada()
{
	char op;
	printf("J - Jogar (possiveis: %d ou %d)\n", mesa[0].ladoE, mesa[qtmesa-1].ladoD);
	printf("C - Comprar\n");
	printf("P - Passar\n");
	printf("S - Sair da partida\n");
	printf("Opcao: ");
	flush_in();
	scanf(" %c", &op);
	op = toupper(op);
	return op;
    
}

int escolher_peca(char jogador7)
{
	int es;
	printf("Jogador %c: Escolha a peca para jogar: ", jogador7);
	scanf("%d", &es);
	return es;
}

char escolher_lado()
{
	char lado;
	printf("Escolha o lado da mesa (E/D): ");
	flush_in();
	scanf("%c", &lado);
	lado = toupper(lado);
	system("cls");
	return lado;
}

void flush_in() //ou void fclear()
{
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n');
}

void print_bateu(char jogador6)
{
	if(sent==2 && jogador=='2')
	{
		printf("\n===Resultado da partida===\n\nO Computador jogou sua ultima peca na mesa e o monte esta' vazio!\n\n===O Computador bateu!===\n");
	}
	else
	    printf("\n===Resultado da partida===\n\nO Jogador %c jogou sua ultima peca na mesa e o monte esta' vazio!\n\n===Jogador %c bateu!===\n", jogador6, jogador6);
}

void print_qtd_pecas(int qtd_pecas1, int qtd_pecas2)
{
	if(sent==2)
	{
	   printf(" Qtd de pecas Jogador 1: %d\n\n Qtd de pecas Computador: %d\n", qtd_pecas1, qtd_pecas2);
    }
    else
       printf(" Qtd de pecas Jogador 1: %d\n\n Qtd de pecas Jogador 2: %d\n", qtd_pecas1, qtd_pecas2);
}


void print_pontos(int pontos1, int pontos2)
{
	if(sent==2)
	{
	   printf("\n Pontos Jogador 1: %d\n\n Pontos Computador: %d\n", pontos1, pontos2);
    }
    else
       printf("\n Pontos Jogador 1: %d\n\n Pontos Jogador 2: %d\n", pontos1, pontos2);
}

void print_jogadacomp(int lado_1, int lado_2)
{
	printf("\n\nO computador jogou a peca [%d|%d].\n\n", lado_1, lado_2);
}






