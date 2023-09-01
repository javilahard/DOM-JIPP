/*DOM-JIPP_Model.h - Etapa 4
31/08/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

typedef int booleano; //para o "C", 0=False e qualquer outro inteiro = True.
#define FALSE 0
#define TRUE 1

int qtd_passar;           //qtd de pecas na mao do jogador. Atribui zero todas vez que alguem jogar e soma 1 quando alguem passar. Se for igual a 2 e' porque os jogadores passaram em seguida.
int mesaE, mesaD;    //extremidades da mesa.
int qtmesa;       
char jogador;   
int p;                   //qtd de pecas na mao do jogador, variavel usada na funcao de bater.


