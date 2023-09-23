/*DOM-JIPP_Controller.h 
23/09/2023
Igor Costa
Joao Avila Harduin
Pedro Evaristo de Oliveira
Priscilla de Souza Jardim
*/

/* A funcao abaixo recebe um tipo_peca vetor peca[28] e
 * atribui valores ao vetor peca. */
void cria_peca(tipo_peca peca[28]);

/* A funcao abaixo recebe um tipo_peca vetor peca[28] e
 * embaralha os elementos do vetor peca. */
void embaralha(tipo_peca peca[28]);

/* A funcao abaixo recebe a opcao do usuario no menu principal e 
 * executa a funcao relacionada a opcao. */
void inicia();

/* A funcao abaixo atribui valores ao vetor peca[28] e 
 * define a primeira peca na mesa, depois executa a funcao jogar. */
void inicia_jogo();

/* A funcao abaixo devolve a primera peca que sera jogada automaticamente na mesa. */
int peca_inicial();

/* A funcao abaixo recebe um caracter jogadorr igual a '1' ou a '2' e
 * executa todas as funcao determinadas pela opcao do usuario no menu secundario(menu de uma partida),
 * mudando jogadorr de acordo com a rodada. */
void jogar(char jogadorr);

/* A funcao abaixo recebe um caracter jogador_ igual a '1' ou a '2' e 
 * se possivel altera o status '0'(deposito de pecas) para status jogador_ . */
void comprar(char jogador_);

/* A funcao abaixo recebe um caracter jogador4 igual a '1' ou a '2' e
 * devolve TRUE se for possivel alterar jogador4 ou devolve FALSE se nao for possivel. */
booleano passar(char jogador4);

/* A funcao abaixo verifica se no vetor peca[28] ainda existe algum elemento com status '0',
 * se existir devolve FALSE senao devolve TRUE. */
booleano depositoVazio();

/* A funcao abaixo recebe um inteiro i <= 27 e
 * atribui ao vetor mesa[0] o vetor peca[i]. */
 void carregaMesaE(int i);
 
/* A funcao abaixo recebe um inteiro i <= 27 e
 * atribui ao vetor mesa[qtmesa] o vetor peca[i]. */ 
void carregaMesaD(int i);

/* A funcao abaixo atribui 'a estrura Jogo cada um dos valores de suas respectivas variaveis globais e 
 * posteriormente escreve em arquivos separados as estruturas Jogo, Peca e Mesa. */
void gravaCadastro();

/* A funcao abaixo le os arquivos das estruturas Jogo, Peca e Mesa e 
 * posteriormente atribui os valores da estrutura Jogo a cada uma de suas respectivas variaveis globais, e finalmente executa a funcao jogar. */
void recuperaCadastro();

/* A funcao abaixo recebe um caracter jogador5 igual a '1' ou a '2' e
 * determina o valor da variavel p, indicando se jogador5 bateu ou nao. */
void venc_batida(char jogador5);
