/*DOM-JIPP_Model.h 
23/09/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

typedef int booleano;             //para o "C", 0=False e qualquer outro inteiro = True.
#define FALSE 0
#define TRUE 1

int qtd_passar;               //qtd vezes que os jogadores passaram a vez. Atribui zero todas vez que alguem jogar e soma 1 quando alguem passar. Se for igual a 2 e' porque os jogadores passaram em seguida.
int mesaE, mesaD;            //extremidades da mesa.
int qtmesa;                 //quantidade de pecas totais no vetor mesa[28]
char jogador;              //varia entre '1' e '2', representa de qual jogador é a rodada.
int p;                    //qtd de pecas na mao do jogador, variavel usada na funcao de bater.
int resp;                //variavel usada para opcao do menu principal do usuario
int sent;               //sentinela para caso o jogador 2 seja o computador.


