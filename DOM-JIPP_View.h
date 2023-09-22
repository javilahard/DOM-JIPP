/*DOM-JIPP_View.h 
14/09/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

/* A funcao abaixo devolve a variavel global resp,
 * que varia de 1 a 6 dependendo da escolha do usuario. */
int menu();

/* A funcao abaixo recebe um caracter jogadorrr igual a '1' ou a '2' e 
 * mostra na tela todas as pecas com status jogadorrr. */
void apresenta_peca(char jogadorrr);

/* A funcao abaixo recebe um vetor de caracteres m[500] e
 * o mostra na tela. */
void apresenta_mensagem(char m[500]);

/* A funcao abaixo mostra na tela todas as pecas do vetor mesa ate mesa[qtmesa-1],
 * ou seja, as pecas que foram jogadas na mesa. */
void mostra_mesa();

/* A funcao abaixo devolve a opcao escolhida pelo usuario no menu secundario. */
char menu_jogada();

/* A funcao abaixo recebe um caracter jogador7 igual a '1' ou a '2' e
 * devolve um inteiro que representa a opcao escolhida dentre as pecas que jogador7 possui. */
int escolher_peca(char jogador7);

/* A funcao abaixo devolve o caracter "e" ou "d",
 * que representa em qual extremo da mesa o jogador deseja jogar sua peca, mesaE ou mesaD. */
char escolher_lado();

/* A funcao abaixo limpa o buffer do teclado, evitando erros com o scanf. */
void flush_in();

/*As quatro funcoes abaixo apenas recebem um ou mais valores e os mostram na tela com uma mensagem especifica. */
void print_bateu(char jogador6);
void print_qtd_pecas(int qtd_pecas1, int qtd_pecas2);
void print_pontos(int pontos1, int pontos2);
void print_jogadacomp(int lado_1, int lado_2);




