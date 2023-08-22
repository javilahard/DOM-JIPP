/*DOM-JIPP - Projeto Domino - Etapa 1
09/08/2023
Grupo: JIPP
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//biblioteca para a geracao de numeros aleatorios

typedef struct peca
	{
		int lado1;
		int lado2;
		char status;
	} tipo_peca;	//definicao de cada peca com os dois lados e o status
	
tipo_peca peca[28];	//vetor correspondente as 28 pecas do jogo
tipo_peca aux;	//peca auxiliar para embaralhar as pecas posteriormente

void fcria_peca(tipo_peca peca[28]);
void fembaralha(tipo_peca peca[28]);
void fmostra(tipo_peca peca[28]);
void fmenu();


main()
{
	
	fcria_peca(peca);
	fmenu();
	
	
}

void fcria_peca(tipo_peca peca[28])	//preenchimento de cada peca com os lados em ordem crescente
{
	int p = 0;
	
	for(int i = 0; i <= 6; i++)
	{
		for(int j = i; j <= 6; j++)
		{
			peca[p].lado1 = i;
			peca[p].lado2 = j;
			peca[p].status = '0';
			p++;
		}
	}
}

void fembaralha(tipo_peca peca[28])	//embaralhamento das pecas do jogo
{
	srand(time(NULL));
	
	for(int i = 0; i <= 27; i++)
	{
		int a = rand()%28;
		
		aux = peca[i];
		peca[i] = peca[a];
		peca[a] = aux;
		
	}
}

void fmostra(tipo_peca peca[28])	//mostra a configuracao atual das pecas no jogo
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
}

void fmenu()
{   
    float num;
	
	printf("========== Bem-vindo(a) ao Jogo de Domino JIPP! ==============\n\n");
	printf("========== Para iniciar digite um numero qualquer(0 para sair): ");
	scanf("%f", &num);
	if(num==0)
	   exit(0);
	system("cls");
    
	int resp;
	printf("===== DOMINO JIPP =====\n\n");	
	
    do
	{
		printf("1. Embaralhar pecas\n");
		printf("2. Reorganizar pecas\n");
		printf("3. Mostrar pecas na tela\n");
		printf("4. Sair\n");
		scanf("%d", &resp);
		system("cls");
		switch(resp)
		{
			case 1:
				fembaralha(peca);
				printf("Pecas embaralhadas com sucesso :)\n");
				break;
			case 2:
				fcria_peca(peca);
				printf("Pecas reorganizadas com sucesso :)\n");
				break;
			case 3:
				fmostra(peca);
				break;
			case 4:
				printf("MENU encerrado\n");
				break;
			default:
				printf("Opcao invalida!\n");
		}
		system("pause");
		system("cls");
	
	}while(resp != 4);
}


