
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


void inicia()
{
	do
	{
	    resp = menu();
		
	     switch(resp)
	     {
		        case 1:
		           embaralha(peca);
		           break;
			case 2:
			   cria_peca(peca);
			   break;
			case 3:
			   mostra(peca);
		           break;
		     case 4:
		           inicia_jogo();
		           break;
			case 5:
			   break;
			
			
	      }
	  }while(resp != 4);
}


void inicia_jogo()
{
	int pi;                                  //peca inicial
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
	mesa[0].ladoE = peca[pi].lado1;
	mesa[0].ladoD = peca[pi].lado2;
	mesaE = mesa[0].ladoE;
	mesaD = mesa[0].ladoD;
	
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
	
	peca[pi].status = 'M';	//atribui status mesa para a primeira peca depois de descoberta
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
	do
	{
		
		int escolha, b = 0, i = 0;
		
	    mostra_mesa();
		apresenta_peca(jogador);
		op = menu_jogada();
		
		if(op == 'S' || op == 's')
		   break;
		
		if(op == 'c' || op == 'C')
	    {
		    comprar(jogador);
	        continue;
	    }
		
		if(op == 'j' || op == 'J')
		{
		
			escolha = escolher_peca(jogador);
			while((b != escolha) && (i < 28))             //verifica qual é a peca escolhida a partir de seu numero de apresentacao das pecas de um jogador e de sua indexacao no array de pecas
			{
				if(peca[i].status == jogador)
				{
					b++;
				}
				i++;
			}
			
			i--;
			
			lado = escolher_lado();
			
			if(lado == 'E' || lado == 'e')
			   {
				if(mesa[0].ladoE == peca[i].lado1 || mesa[0].ladoE == peca[i].lado2)            //verifica se e' possivel jogar a peca escolhida a partir do lado esquerdo da peca ja na mesa que e' sempre mesa[0]
				{
				  carregaMesaE(i); 	
				}
			   }
		    else if(lado == 'D' || lado == 'd')
			    {
			    if(mesa[qtmesa-1].ladoD == peca[i].lado1 || mesa[qtmesa-1].ladoD == peca[i].lado2)            //verifica pelo lado direito da peca que ja esta' na peca de indice qtmesa-1
				   {
				    carregaMesaD(i);
			       }
				
			    } 
		}
		if(jogador=='1')
		   	jogador='2';
		else
		   	jogador='1';
	}
	while(1);
}


void comprar(char jogador)
{

   int i = 14;          //as 14 primeiras peças já não estão mais livres
   while(i < 28)
   {
       if (peca[i].status == '0')
        {
         peca[i].status = jogador;
         break;
        }
        i++;
   }
   if (i >= 28)
       apresenta_mensagem("Nada a comprar\n");
}


void carregaMesaE(int i)
{
//deslocamento de toda a mesa para abrir a primeira posição 0
    for(int j = qtmesa; j > 0; j--)
	    mesa[j] = mesa[j-1];
//verifica se será necessário inverter a peça a ser jogada e
//joga na posição 0 da mesa
	if (peca[i].lado2 == mesaE)
	{
		mesa[0].ladoE = peca[i].lado1;
		mesa[0].ladoD = peca[i].lado2;
	}
	else
	{
		mesa[0].ladoE = peca[i].lado2;
		mesa[0].ladoD = peca[i].lado1;
	}
	//atualiza a variável global mesaE com o ladoE agora atualizado
	mesaE = mesa[0].ladoE;
	
	qtmesa++; //incrementa a qtde de peças na mesa
	peca[i].status = 'M'; //atualiza o status da peça jogada
}

void carregaMesaD(int i)
{
	if (peca[i].lado1 == mesaD)
	{
		mesa[qtmesa].ladoE = peca[i].lado1;                 //mesa[qtmesa] pois a peca vai ficar na posicao seguinte da anterior 
		mesa[qtmesa].ladoD = peca[i].lado2;
	}
	else
	{
		mesa[qtmesa].ladoE = peca[i].lado2;
		mesa[qtmesa].ladoD = peca[i].lado1;
	}
	
	mesaD = mesa[qtmesa].ladoD;
	qtmesa++;
	peca[i].status = 'M'; 
}







