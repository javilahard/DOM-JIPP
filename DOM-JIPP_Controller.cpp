/*DOM-JIPP_Controller.cpp - Etapa 4
31/08/2023
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
	int k = 0;
	int j, i;
	
	for(i = 0; i <= 6; i++)
	{
		for(j = i; j <= 6; j++)
		{
			peca[k].lado1 = i;
			peca[k].lado2 = j;
			k++;
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
	    {
	       apresenta_mensagem("===REGRAS DO DOMINO JIPP===\n\nRegra1: Cada jogador comeca com 7 pecas aleatorias, podendo comprar quantas pecas quiser no seu turno.\n");
		   apresenta_mensagem("Regra2: O jogo inicia com o jogador que tiver a peca [6|6]. Caso ninguem tenha a [6|6] entao calcula-se outra primeira peca que e' jogada e o primeiro turno sera do jogador que nao tinha a primeira peca.\n");
	       apresenta_mensagem("Regra3: Na sua vez cada jogador deve colocar uma das pecas em uma das extremidades da mesa, de forma que os lados coincidam.\n\nRegra4: Quando o jogador coloca sua peca sobre a mesa, seu turno acaba e passa para o proximo.\n");
		   apresenta_mensagem("Regra5: Caso um jogador nao possua uma peca compativel para jogar, deve comprar do monte ate encontrar uma peca ou ate as pecas do monte acabarem. So quando atendidas essas condicoes o jogador pode passar a vez(passar o turno sem jogar uma peca).\n");
	       apresenta_mensagem("Regra6: O jogo pode acabar de duas maneiras, porem nos dois casos o deposito de pecas deve estar vazio. A primeira e' se um jogador colocar sua ultima peca na mesa, essa acao e' chamada de bater e ele vence o jogo.");
		   apresenta_mensagem("A segunda sao casos onde nenhum dos jogadores pode continuar a partida, acontece quando ninguem tem uma peca possivel de ser lancada na mesa, nesse momento a partida esta fechada. Vence aquele que tiver menos pecas e caso empatem, vence aquele com menos pontos(soma dos lados das pecas).\n");
	       system("pause");
	       system("cls");
		}
	
	}
	while(resp != 3);
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
	p = 1;                     //inicializa "p" com um valor aleatorio
	
	do
	{
		int escolha, b = 0, i = 0;
		                 
		venc_batida(jogador);                /*funcao de batida precisa estar no comeco para o caso de um jogador jogar sua ultima peca e o deposito ainda nao esta vazio, 
		                                       entao quando a vez for dele novamente e o deposito estiver vazio ele conseguir bater*/
		if(p==0)                         //se alguem bater sai do jogo imediatamente e mostra o menu de opcoes da partida.
		   break;
		mostra_mesa();
		apresenta_peca(jogador);
		op = menu_jogada();
		
		switch (op)
	   {
	    case 'S':
		    break;
		case 'C':
		{
		    comprar(jogador);
	        continue;
	    }
	    case 'P':
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
				apresenta_mensagem("Os dois jogadores passaram a vez em seguida!\n===Resultado da partida===\n\n");
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
	    	   print_qtd_pecas(qtdpecas1, qtdpecas2);
			   
			   if(qtdpecas1 < qtdpecas2)
			        apresenta_mensagem("\n===Jogador 1 venceu!===\n"); 
			   
			   else if(qtdpecas1 > qtdpecas2)
			        apresenta_mensagem("\n===Jogador 2 venceu!===\n");
			   else
			   {
			   	    print_pontos(soma_lados1, soma_lados2);
			   	    
			   	    if(soma_lados1 < soma_lados2)
					   apresenta_mensagem("\n===Jogador 1 venceu!===\n"); 
					else if(soma_lados1 > soma_lados2)
					   apresenta_mensagem("\n===Jogador 2 venceu!===\n"); 
			   }
			   system("pause");
			   system("cls");
			   break;
			}
			continue;
			
		}
	    case 'J':
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
				
				qtd_passar = 0;
				
				
				if((mesaE == mesaD) || (peca[i].lado1 == mesaE && peca[i].lado2 == mesaD) || (peca[i].lado1 == mesaD && peca[i].lado2 == mesaE))             //verifica a necessidade de deixar o usuario escolher o lado da mesa para jogar
			   {
			   	    lado = escolher_lado();                                                                                                                  
			   	    if(lado == 'E')
			   	        carregaMesaE(i);
			   	  
			   	    else if(lado == 'D')
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
			   
			   venc_batida(jogador);                 //depois de verificar que a peca pode ser jogada.
			   
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
	while(qtd_passar != 2 && p!= 0 && op!= 'S');
	
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
			      return FALSE;                     //dessa forma qtd_passar so' sera igual a 2 quando um jogador passar em seguida do outro
				}
	    }
    }
	system("cls");
	qtd_passar++;
    return TRUE;
  }
			
}
//verifica se o deposito esta vazio
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

void venc_batida(char jogador)
{
	if(depositoVazio() == TRUE)
	{
	   int k;
	   k = 0;        //qtd de pecas total 
	   p = 0;             
               
	   while(k<28)
	   {
          if(peca[k].status == jogador)
			 p++;                    
		  k++;
	   }
	   
	   if(p == 0)                   //se o jogador em questao tiver nenhuma peca na mao depois de verificado que ela pode ser jogada e o deposito esta vazio o jogador bate.
	   {
	   	   mostra_mesa();
		   apresenta_peca(jogador);
	   	   print_bateu(jogador);
	       system("pause");
	       system("cls");
	   }
    }
    
}







