/*DOM-JIPP_Controller.cpp 
14/09/2023
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

void inicia()
{
	qtmesa=0;                                //e' preciso inicializar as variaveis globais por conta de situacoes apos finalizar um jogo ou reperar/gravar.
	qtd_passar=0;
	p=1;
	do
	{
		resp = menu();
		if(resp<1 || resp>6)
		{
		   apresenta_mensagem("Opcao invalida\n");
		   system("pause");
	       continue;
		}
	    if(resp==1 || resp==2)
	    {
	       sent=1;
	       qtd_passar=0;
	      
		   if(resp==2)
		      sent=2;
		   inicia_jogo();
		}
		else if(resp==3)
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
		else if(resp==4)
		   gravaCadastro();
		else if(resp==5)
		   recuperaCadastro();
	}
	while(resp!=6);
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
		jogador = '2';                                  //indica de qual jogador e' o proximo lance
	}
	else
	{
		apresenta_mensagem("O primeiro lance foi do jogador 2\n");
		jogador = '1';
	}
	
	peca[pi].status = 'M';	                         //atribui status mesa para a primeira peca depois de descoberta
	jogar(jogador);
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
				    prim = i;
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
		    prim = i;
		
		else if(peca[i].lado1 + peca[i].lado2 == peca[prim].lado1 + peca[prim].lado2)
		{
			if((peca[i].lado1 > peca[prim].lado1 && peca[i].lado1 > peca[prim].lado2) ||
			   (peca[i].lado2 > peca[prim].lado1 && peca[i].lado2 > peca[prim].lado2))          //verifica qual a maior soma e se a maior tiver iguais qual a peca com maior lado
			        
					prim = i;
		}
	}
	qtmesa = 1;
	return prim;
}

void jogar(char jogadorr)
{
	
	
	char op, lado;
	int soma_lados1, soma_lados2, qtdpecas1, qtdpecas2, escolha;
	int k, j, i, b, h;
	
	
	soma_lados1 = 0;                               //soma dos lados de todas as pecas pertencentes a cada jogador quando os 2 passarem a vez
	soma_lados2 = 0;
	qtdpecas1 = 0;                               //quantida de pecas de determinado jogador quando os 2 passarem a vez
	qtdpecas2 = 0;
    p = 1;                
	
	do
	{
		jogador=jogadorr;
		venc_batida(jogadorr);              /*funcao de batida precisa estar no comeco para o caso de um jogador jogar sua ultima peca e o deposito ainda nao esta vazio, 
		                                    entao quando a vez for dele novamente e o deposito estiver vazio ele conseguir bater*/
		if(p==0)                         //se alguem bater sai do jogo imediatamente e mostra o menu principal.
		   break;
		
		mostra_mesa();
		if(sent==2 && jogadorr=='2')
		     system("pause");
		apresenta_peca(jogadorr);
		
		if(sent==2 && jogadorr=='2')
	    {
	    	for(k=0; k<28; k++)
			{
			   if(peca[k].status=='2')
			   {
			   	    if((mesaD == peca[k].lado1) || (mesaD == peca[k].lado2) || (mesaE == peca[k].lado1) || (mesaE == peca[k].lado2))
			   	    {
					    op = 'J'; 
					    break;
				    }
			   }
		    }
		    
			if(k==28)
		    {
		       if(depositoVazio() == TRUE)
		            op = 'P';
		       else
		            op = 'C';
			}
		}
		else
		    op = menu_jogada();
		
		
		switch (op)
	    {
	        case 'S':
		        break;
		    case 'C':
		    {
		        comprar(jogadorr);
	            continue;
	        }
	        case 'P':
	        {
	    	    if(passar(jogadorr) == TRUE)
	    	    {
	    	       if(qtd_passar != 2)
	    	       {
			            if(jogadorr == '1')
			               jogadorr = '2';
                        else
                           jogadorr = '1';
                   }
               
			       else
			       {
				        apresenta_mensagem("Os dois jogadores passaram a vez em seguida!\n===Resultado da partida===\n\n");
				        for(j=0; j<28; j++)                                                  //percorre todas as pecas e verifica as pecas que tem status jogador
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
			            {
					        if(sent==2)
					            apresenta_mensagem("\n=== O Computador venceu!===\n");
					        else
					            apresenta_mensagem("\n===Jogador 2 venceu!===\n");
			            }
			            else
			            {
			   	            print_pontos(soma_lados1, soma_lados2);
			   	    
			   	            if(soma_lados1 < soma_lados2)
					            apresenta_mensagem("\n===Jogador 1 venceu!===\n"); 
					        else if(soma_lados1 > soma_lados2)
					        {
					            if(sent==2)
					                apresenta_mensagem("\n=== O Computador venceu!===\n"); 
					            else
					                apresenta_mensagem("\n===Jogador 2 venceu!===\n");
				            }
			            }
			            system("pause");
			            system("cls");
			            break;
			       }
			    }
	    	    continue;
		    }
	        
			case 'J':
	        {
	    	    if(sent==2 && jogadorr=='2')
	    	    {
	    		    qtd_passar = 0;
	    	        
					if((mesaD == peca[k].lado1) || (mesaD == peca[k].lado2))                      // se nao precisar escolher o lado verifica em qual lado a peca sera jogada automaticamente apos a escolha
			            carregaMesaD(k);
				    else
			            carregaMesaE(k);
			    
			        system("cls");  
			        print_jogadacomp(peca[k].lado1, peca[k].lado2);
			        system("pause");
			        system("cls");
			        venc_batida(jogadorr);
		        }
			    
		        else
			    {
				    for(h=0; h<28; h++)
				    {
					    if(peca[h].status==jogadorr)
					       break;
				    }
				    if(h==28)
				    {
					    system("cls");
					    apresenta_mensagem("\n\nVoce nao possui pecas para jogar, compre ou passe a vez.\n");
					    system("pause");
					    system("cls");
					    continue;
				    }
			        
					escolha = escolher_peca(jogadorr);
			        i=0;
			        b=0;
			        while((b != escolha) && (i < 28))             //verifica qual a peca escolhida a partir de sua indexacao no array de pecas e seu status
			        {
				        if(peca[i].status == jogadorr)
				            b++;
				        i++;
			        }
			        i--;
			
			        if(b != escolha && i == 27)
			        {
				        system("cls");
				        apresenta_mensagem("\n\nPeca invalida! Voce nao possui essa peca. Tente novamente \n");                                                    //caso o usuario digite uma peca diferente de suas opcoes na mao
				        system("pause");
			            system("cls");
			            continue;
		            }
			
		 	        if((mesaD == peca[i].lado1) || (mesaD == peca[i].lado2) || (mesaE == peca[i].lado1) || (mesaE == peca[i].lado2))                            // verifica se a peca escolhida e' possivel de ser jogada
			        {
				
			  	        qtd_passar = 0;
				
				
				        if((mesaE == mesaD) || (peca[i].lado1 == mesaE && peca[i].lado2 == mesaD) || (peca[i].lado1 == mesaD && peca[i].lado2 == mesaE))     //verifica a necessidade de deixar o usuario escolher o lado da mesa para jogar
			            {
			   	            lado = escolher_lado();                                                                                                                  
			   	            if(lado == 'E')
			   	                carregaMesaE(i);
			   	  
			   	            else if(lado == 'D')
			   	                carregaMesaD(i);
			   	  
				            else
				            {
				                apresenta_mensagem("Opcao invalida! Tente novamente\n");                       
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
			   
			            venc_batida(jogadorr);                                                       //depois de verificar que a peca pode ser jogada.
			        }
			        
					else
			        {
				        system("cls");
			            apresenta_mensagem("\n\nPeca incompativel! Tente novamente ou compre uma peca\n");                             
			            system("pause");
			            system("cls");
			            continue;
			        }  
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
		
		
	    if(jogadorr=='1')                          //muda o jogador para o da proxima rodada
		   jogadorr='2';
	    else
		   jogadorr='1';
	}
	while(qtd_passar != 2 && p!= 0 && op!= 'S');
	
}

void comprar(char jogador_)
{
   system("cls");
   int i = 14;                          //as 14 primeiras pecas ja nao estao mais livres
   while(i < 28)
   {
        if (peca[i].status == '0')
        {
           peca[i].status = jogador_;
           break;
        }
        i++;
   }
   if(i >= 28)
   {
        apresenta_mensagem("Nada a comprar\n");
        system("pause");
   }
   if(sent==2 && jogador_=='2')
   {
	    apresenta_mensagem("O Computador comprou!\n");
	    system("pause");
   }
   system("cls");
}

booleano passar(char jogador4)
{
  system("cls");
  if(sent==2 && jogador4=='2')
  {
  	 apresenta_mensagem("\n\nO Computador passou a vez\n");
  	 system("pause");
  	 system("cls");
	 qtd_passar++;
     return TRUE;  	
  }
  else
  {
      if (depositoVazio() == FALSE)
      {
          apresenta_mensagem("\n\nPassagem bloqueada. O deposito nao esta vazio. Voce deve jogar e/ou comprar\n");
          system("pause");
          system("cls");
          return FALSE;
      }
      else
      {
          for(int j=0; j<28; j++)                            //percorre todas as pecas e verifica as pecas que tem status do jogador do momento e se existe alguma que pode ser jogada.
          {
  		      if(peca[j].status == jogador4)
  		      {
  		          if((mesaD == peca[j].lado1) || (mesaD == peca[j].lado2) || (mesaE == peca[j].lado1) || (mesaE == peca[j].lado2))
			      {
			           apresenta_mensagem("\n\nPassagem bloqueada. Faca sua jogada!\n");
			           system("pause");
			           system("cls");
			           return FALSE;                     //dessa forma qtd_passar so' sera igual a 2 quando um jogador passar em seguida do outro
				  }
	          }
          }
	      qtd_passar++;
          return TRUE;
      }
   }
			
}

booleano depositoVazio()
{
  for(int i = 0; i < 28; i++)
  {
     if(peca[i].status == '0') 
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

void venc_batida(char jogador5)
{
	if(depositoVazio() == TRUE)
	{
	   int k;
	   k = 0;                             //qtd de pecas total 
	   p = 0;             
               
	   while(k<28)
	   {
          if(peca[k].status == jogador5)
		  {
			   p++;
			   break;
	      }
		  k++;
	   }
	   
	   if(p == 0)                   //se o jogador em questao tiver nenhuma peca na mao depois de verificado que ela pode ser jogada e o deposito esta vazio o jogador bate.
	   {
	   	   mostra_mesa();
		   apresenta_peca(jogador5);
	   	   print_bateu(jogador5);
	       system("pause");
	       system("cls");
	   }
	}
    
}

void gravaCadastro()
{

	if(p == 0 || qtd_passar == 2)
	{
		apresenta_mensagem("\n\nJogo terminado nao pode ser gravado.\n");
		system("pause");
		return;
	}
	
	if(qtmesa==0)
	{
		apresenta_mensagem("\n\nNenhum jogo foi iniciado para ser gravado.\n");
		system("pause");
		return;
	}
	int i;
    FILE *fp;
    FILE *fpm;
    FILE *fps;
    
     //dados do Jogo a ser salvo
   sitJogo.qtmesaJogo = qtmesa;
   sitJogo.jogadorJogo = jogador;
   sitJogo.mesaDJogo = mesaD;
   sitJogo.mesaEJogo = mesaE;
   sitJogo.qtd_passarJogo = qtd_passar;
   sitJogo.sent_Jogo = sent;
   
   if((fp = fopen("CAD_DOMINO", "w")) == NULL)
   {
        apresenta_mensagem("O arquivo CAD_DOMINO nao pode ser aberto para cadastrar");
        system("pause");
        return;
   }
   if((fpm = fopen("CAD_MESA", "w")) == NULL)
   {
        apresenta_mensagem("O arquivo CAD_MESA nao pode ser aberto para cadastrar");
        system("pause");
        return;
   }
   if((fps = fopen("CAD_JOGO", "w")) == NULL)
   {
        apresenta_mensagem("O arquivo CAD_JOGO nao pode ser aberto para cadastrar");
        system("pause");
        return;
   }
   
   if(fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
        apresenta_mensagem("Erro na gravacao do arquivo CAD_JOGO");
       
   for(i = 0; i < 28; i++)
   {
       if(fwrite(&peca[i], sizeof(struct Peca), 1, fp) != 1)
       {
          apresenta_mensagem("Erro na gravacao do arquivo CAD_DOMINO");
          break;
       }
   }   
   
   for(i = 0; i < sitJogo.qtmesaJogo; i++)
   {
       if(fwrite(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
       {
	      apresenta_mensagem("Erro na gravacao do arquivo CAD_MESA");
	      break;
       }
   }
   
   fclose(fps);
   fclose(fpm);
   fclose(fp);
   apresenta_mensagem("Gravados os arquivos CAD_DOMINO, CAD_MESA e CAD_JOGO");
   system("pause");
}

void recuperaCadastro()
{
   int i;
   FILE *fp;
   FILE *fpm;
   FILE *fps;
 
   if((fp = fopen("CAD_DOMINO", "r")) == NULL)
   {
      apresenta_mensagem("O arquivo CAD_DOMINO nao pode ser aberto");
      system("pause");
      return;
   }
   if((fpm = fopen("CAD_MESA", "r")) == NULL)
   {
       apresenta_mensagem("O arquivo CAD_MESA nao pode ser aberto");
       system("pause");
       return;
   }
   if((fps = fopen("CAD_JOGO", "r")) == NULL)
   {
       apresenta_mensagem("O arquivo CAD_JOGO nao pode ser aberto");
       system("pause");
       return;
   }
   
   if(fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
        apresenta_mensagem("Erro na leitura do arquivo CAD_JOGO");
   
   for(i = 0; i < 28; i++)
   {
      if (fread(&peca[i], sizeof(struct Peca), 1, fp) != 1)
      {
          apresenta_mensagem("Erro na leitura do arquivo CAD_DOMINO");
          break;
      }
   }
   
   for(i = 0; i < sitJogo.qtmesaJogo; i++)
   {
       if (fread(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
       {
           apresenta_mensagem("Erro na leitura do arquivo CAD_MESA");
           break;
       }
   }
   

   fclose(fps);
   fclose(fpm);
   fclose(fp);

   //recupera dados do Jogo salvo
   qtmesa = sitJogo.qtmesaJogo;
   jogador = sitJogo.jogadorJogo;
   mesaD = sitJogo.mesaDJogo;
   mesaE = sitJogo.mesaEJogo;
   qtd_passar = sitJogo.qtd_passarJogo;
   sent = sitJogo.sent_Jogo;
   
   apresenta_mensagem("retornando ao jogo recuperado");
   system("pause");
   jogar(jogador);
}
 








