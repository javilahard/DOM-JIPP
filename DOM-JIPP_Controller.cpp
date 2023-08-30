
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
	int soma_lados1, soma_lados2, qtdpecas1, qtdpecas2;
	
	qtd_passar = 0;
	soma_lados1 = 0;                  //soma dos lados de todas as pecas pertencentes a cada jogador quando os 2 passarem a vez
	soma_lados2 = 0;
	qtdpecas1 = 0;                  //quantida de pecas de determinado jogador quando os 2 passarem a vez
	qtdpecas2 = 0;
	
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
	    case 'P':
	    case 'p':
	    {
	    	if(passar(jogador) == TRUE)
	    	{
			   if(jogador == '1')
			      jogador = '2';
               else
                  jogador = '1';
		    }
	    	
			if(qtd_passar==2)                              // se os 2 jogadores passarem a vez o jogo acabou
			{
				for(int j=0; j<28; j++)                //percorre todas as pecas e verifica as pecas que tem status jogador
	    	   {
	    	   	    if(peca[j].status=='1' || peca[j].status=='2')
	    	   	    {
	    	   	    	if(peca[j].status=='1')
	    	   	        {
							qtdpecas1++;
						    soma_lados1 = soma_lados1 + peca[j].lado1 + peca[j].lado2;
					    }
	    	   	    	else
	    	   	        {
							qtdpecas2++;
							soma_lados2 = soma_lados2 + peca[j].lado1 + peca[j].lado2;
					    }
	    	   	    }
	    		}
			   if(qtdpecas1 < qtdpecas2)
			        apresenta_mensagem("Jogador 1 venceu! \n"); 
			   
			   else if(qtdpecas1 > qtdpecas2)
			        apresenta_mensagem("Jogador 2 venceu! \n");
			   else
			   {
			   	    if(soma_lados1 < soma_lados2)
					   apresenta_mensagem("Jogador 1 venceu! \n"); 
					else
					   apresenta_mensagem("Jogador 2 venceu! \n");     
			   }
			   break;
			}
			continue;
			
		}
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
			
			if((b != escolha) && (i == 27))
			{
				system("cls");
				apresenta_mensagem("Peca invalida! Voce nao possui essa peca. Tente novamente \n");        //caso o usuario digite uma peca diferente de suas opcoes na mao
				system("pause");
			    system("cls");
			    continue;
		    }
			
			if((mesaD == peca[i].lado1) || (mesaD == peca[i].lado2) || (mesaE == peca[i].lado1) || (mesaE == peca[i].lado2))                            // verifica se a peca escolhida e' possivel de ser jogada
			{
			   venc_batida(jogador);               //depois de verificar que a peca pode ser jogada, verifica-se se e' a ultima peca do jogador da vez.
			   
			   if((mesaE == mesaD) || (peca[i].lado1 == mesaE && peca[i].lado2 == mesaD) || (peca[i].lado1 == mesaD && peca[i].lado2 == mesaE))             //verifica a necessidade de deixar o usuario escolher o lado da mesa para jogar
			   {
			   	    lado = escolher_lado();                                                                                                                  
			   	    if(lado == 'E' || lado == 'e')
			   	        carregaMesaE(i);
			   	  
			   	    else if(lado == 'D' || lado == 'd')
			   	        carregaMesaD(i);
			   	  
				    else
				    {
				       apresenta_mensagem("Opcao invalida! Tente novamente\n");                                    //consistencia do lado escolhido
				       system("pause");
				       system("cls");
				       continue;
			        }
			   }
			   else if((mesaD == peca[i].lado1) || (mesaD == peca[i].lado2))                      // se nao precisar escolher o lado verifica em qual lado a peca sera jogada automaticamente apos a escolha
			   {
					carregaMesaD(i);
					system("cls");  
			   }                 
			                         
			   else
			   {
			        carregaMesaE(i);
			        system("cls");  
			   }
		    }
			
			else
			{
				system("cls");
			    apresenta_mensagem("Peca invalida! Tente novamente ou compre uma peca\n");                              //caso a peca escolhida nao seja compativel com nenhuma das extremidades da mesa
			    system("pause");
			    system("cls");
			    continue;
			}
			
			
			
			break;
		    
	    }
	    
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
	while(qtd_passar < 2);
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
       {
       system("cls");
	   apresenta_mensagem("Nada a comprar\n");
       system("pause");
       }
    system("cls");
}

booleano passar(char jogador)
{
  
  system("cls");
  if (depositoVazio() == FALSE)
  {
    apresenta_mensagem("Passagem bloqueada. O deposito nao esta vazio. Voce deve jogar e/ou comprar");
    system("pause");
    system("cls");
    return FALSE;
  }
  else
  {
    for(int j=0; j<28; j++)                       //percorre todas as pecas e verifica as pecas que tem status do jogador do momento e se existe alguma que pode ser jogada.
   {
  		if(peca[j].status == jogador)
  		{
  		    if((mesaD == peca[j].lado1) || (mesaD == peca[j].lado2) || (mesaE == peca[j].lado1) || (mesaE == peca[j].lado2))
			    {
			      system("cls");
			      apresenta_mensagem("Passagem bloqueada. Faca sua jogada!\n");
			      system("pause");
			      system("cls");
			      qtd_passar--;                     //dessa forma qtd_passar so' sera igual a 2 quando um jogador passar em seguida do outro
				  return FALSE;
			    }
	    }
    }
	system("cls");
    apresenta_mensagem("Passagem concedida!\n");
	system("pause");
	system("cls");
	qtd_passar++;
    return TRUE;
  }
			
}
//verifica se o deposito está vazio
booleano depositoVazio()
{
  for(int i = 0; i < 28; i++)
  {
    if (peca[i].status == '0') 
    return FALSE;
  }
return TRUE;
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







