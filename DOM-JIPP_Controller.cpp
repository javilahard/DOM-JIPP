
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
		
	    if(resp==1)
	       inicia_jogo();
		
		else if(resp==2)
		   break;
	}
	while(1);
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
			   (peca[i].lado2 > peca[prim].lado1 && peca[i].lado2 > peca[prim].lado2))          //verifica qual a maior soma e se a maior tiver iguais qual a peca com maior lado
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
		
		switch (op)
	   {
	    case 's':
	    case 'S':
		    exit(0);
		case 'C':
		case 'c':
	        {
			comprar(jogador);
	        continue;
	        }
	        break;
	    case 'J':
	    case 'j':
	    	{
		    escolha = escolher_peca(jogador);
			while((b != escolha) && (i < 28))             //verifica qual a peca escolhida a partir de sua indexacao no array de pecas e seu status
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
				else
				  {
				  apresenta_mensagem("Peca invalida! Tente novamente ou compre uma peca\n");
				  system("pause");
				  system("cls");
				  continue;
			      }
			   }
		    else if(lado == 'D' || lado == 'd')
			   {
			    if(mesa[qtmesa-1].ladoD == peca[i].lado1 || mesa[qtmesa-1].ladoD == peca[i].lado2)            //verifica pelo lado direito da peca que ja esta' na peca de indice qtmesa-1
				  {
				  carregaMesaD(i);
			      }
			    else
			      {
				  apresenta_mensagem("Peca invalida! Tente novamente ou compre uma peca\n");
			      system("pause");
			      system("cls");
			      continue;
			      }
			   }
		    
		    
	        }break;
	    
		default:
	    	{
			system("cls");
	    	apresenta_mensagem("Opcao Invalida!\n");
			system("pause");
			system("cls");
			continue;
		    }
		}
		
		if(jogador=='1')      //mudar o jogador para o da proxima rodada
		   	jogador='2';
		else
		   	jogador='1';
   }
	while(1);
}

void comprar(char jogador)
{

   int i = 14;          //as 14 primeiras pecas ja nao estao mais livres
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
    system("cls");
}


void carregaMesaE(int i)
{
//deslocamento de toda a mesa para abrir a primeira posicao 0
    for(int j = qtmesa; j > 0; j--)
	    mesa[j] = mesa[j-1];
//verifica se sera necessario inverter a peca a ser jogada e
//joga na posicao 0 da mesa
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
	//atualiza a variavel global mesaE com o ladoE agora atualizado
	mesaE = mesa[0].ladoE;
	
	qtmesa++; //incrementa a qtde de pecas na mesa
	peca[i].status = 'M'; //atualiza o status da peca jogada
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







