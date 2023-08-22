
/*DOM-JIPP_Controller.cpp - Etapa 2
16/08/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

#include "DOM-JIPP_View.cpp"
#include "DOM-JIPP_Controller.h"
#include <time.h>

void cria_peca(tipo_peca peca[28])	//preenchimento de cada peca com os lados em ordem crescente
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

void embaralha(tipo_peca peca[28])	//embaralhamento das pecas do jogo
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


/*void finicia()
{
	do
	{
		resp = fmenu();
		
		switch(resp)
		{
			case 1:
				fembaralha(peca);
				break;
			case 2:
				fcria_peca(peca);
				break;
			case 3:
				fmostra(peca);
			case 4:
				break;
			
			
		}
	}while(resp != 4);
}
*/

void inicia_jogo()
{
	int pi;
	char vez;
	char mens[];
	
	embaralha(peca);
	
	for(int i = 0; i < 7; i++)
	{
		peca[i].status = '1';
	}
	
	for(i = 7; i < 14; i++)
	{
		peca[i].status = '2';
	}
	
	for(i = 14; i < 28; i++)
	{
		peca[i].status = '0';	
	}
	
	pi = peca_inicial();
	peca[pi].status = 'M';
	mesa[0].ladoD = peca[pi].lado1;
	mesa[0].ladoE = peca[pi].lado2;
	njogadas++;
	
	if(peca[pi].status == '1')
	{
		mens[] = "O primeiro lance foi do jogador 1\n";
		apresenta_mensagem(mens);
		vez = '2';
	}
	else
	{
		mens[] = "O primeiro lance foi do jogador 2\n";
		apresenta_mensagem(mens);
		vez = '1';
	}
	
	jogar(vez);
}

int peca_inicial()
{
	int prim = 100;
	
	for(int i = 0; i < 14; i++)
	{
		if(peca[i].lado1 == peca[i].lado2)
		{
			if(prim == 100)
				prim = i;
			else
			{
				if(peca[i].lado1 > peca[prim].lado1)
				{
					prim = i;
				}	
			}
		}
	}
	
	if(prim != 100)
	{
		return prim;
	}
	
	prim = 0;
	
	for(int i = 1; i < 14; i++)
	{
		if(peca[i].lado1 + peca[i].lado2 > peca[prim].lado1 + peca[prim].lado2)
		{
			prim = i;
		else if(peca[i].lado1 + peca[i].lado2 == peca[prim].lado1 + peca[prim].lado2)
		{
			if((peca[i].lado1 > peca[prim].lado1 && peca[i].lado1 > peca[prim].lado2) ||
			   (peca[i].lado2 > peca[prim].lado1 && peca[i].lado2 > peca[prim].lado2))
			{
					prim = i;
			}
		}
	}
	return prim;
}

void jogar(char jogador)
{
	char op;
	
	mostra_mesa();
	apresenta_peca(jogador);
	op = menu_jogada();
	if(op == 'j' || op == 'J')
	{
		escolher_peca(jogador);
	}
}







