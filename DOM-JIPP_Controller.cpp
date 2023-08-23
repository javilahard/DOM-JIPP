
/*DOM-JIPP_Controller.cpp - Etapa 3
24/08/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

#include "DOM-JIPP_View.cpp"
#include "DOM-JIPP_Controller.h"
#include <time.h>

void cria_peca(tipo_peca peca[28])	               //preenchimento de cada peca com os lados em ordem crescente
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

void embaralha(tipo_peca peca[28])	               //embaralhamento das pecas do jogo
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
	int pi;                                  //primeira peca
	char vez;
	
	embaralha(peca);
	
	for(int i = 0; i < 7; i++)
	{
		peca[i].status = '1';
	}
	
	for(int i = 7; i < 14; i++)
	{
		peca[i].status = '2';
	}
	
	for(int i = 14; i < 28; i++)
	{
		peca[i].status = '0';	          //status '0' sao as pecas do monte
	}
	
	pi = peca_inicial();
	peca[pi].status = 'M';                    //atribui status mesa para a primeira peca depois de descoberta
	mesa[0].ladoE = peca[pi].lado1;
	mesa[0].ladoD = peca[pi].lado2;
	MesaE=mesa[0].ladoE;
	MesaD=mesa[0].ladoD;
	
	if(peca[pi].status == '1')
	{
		apresenta_mensagem("O primeiro lance foi do jogador 1\n");
		vez = '2';                       //indica de qual jogador e' o proximo lance
	}
	else
	{
		apresenta_mensagem("O primeiro lance foi do jogador 2\n");
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
		qtmesa = 1;        //quantidade de pecas na mesa
		return prim;
	}
	
	prim = 0;
	
	for(int i = 1; i < 14; i++)
	{
		if(peca[i].lado1 + peca[i].lado2 > peca[prim].lado1 + peca[prim].lado2)
		{
			prim = i;
		}
		else if(peca[i].lado1 + peca[i].lado2 == peca[prim].lado1 + peca[prim].lado2)
		{
			if((peca[i].lado1 > peca[prim].lado1 && peca[i].lado1 > peca[prim].lado2) ||
			   (peca[i].lado2 > peca[prim].lado1 && peca[i].lado2 > peca[prim].lado2))
			{
					prim = i;
			}
		}
	}
	qtmesa = 1;
	return prim;
}

void jogar(char jogador)
{
	char op, lado;
	int escolha, a = 0, i = 0;
	
	mostra_mesa();
	apresenta_peca(jogador);
	op = menu_jogada();
	if(op == 'j' || op == 'J')
	{
		escolha = escolher_peca(jogador);
		while(i < 28 || a+1 != escolha)
		{
			if(peca[i].status == jogador)
			{
				a++;
			}
			i++;
		}
		lado = escolher_lado();
		if(lado == 'E' || lado == 'e')
		{
			if(mesa[0].ladoE == peca[a].lado1 || mesa[0].ladoE == peca[a].lado2)
			{
			  carregaMesaE(a); 	
			}
		}
	}
}

void carregaMesaE(int a)
{
//deslocamento de toda a mesa para abrir a primeira posição 0
	for(int i = qtmesa; i > 0; i--)
	mesa[i] = mesa[i-1];
//verifica se será necessário inverter a peça a ser jogada e
//joga na posição 0 da mesa
	if (peca[a].lado2 == mesaE)
	{
		mesa[0].ladoE = peca[a].lado1;
		mesa[0].ladoD = peca[a].lado2;
	}
	else
	{
		mesa[0].ladoE = peca[a].lado2;
		mesa[0].ladoD = peca[a].lado1;
	}
	//atualiza a variável global mesaE com o ladoE agora atualizado
	mesaE = mesa[0].ladoE;
	
	qtmesa++; //incrementa a qtde de peças na mesa
	peca[a].status = 'M'; //atualiza o status da peça jogada
}
void carregaMesaD(int a)
{
	if (peca[a].lado2 == mesaD)
	{
		mesa[qtmesa].ladoE = peca[a].lado1;
		mesa[qtmesa].ladoD = peca[a].lado2;
	}
	else
	{
		mesa[qtmesa].ladoE = peca[a].lado2;
		mesa[qtmesa].ladoD = peca[a].lado1;
	}
	
	mesaD = mesa[qtmesa].ladoD;
	peca[a].status = 'M'; 
}






