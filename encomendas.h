/** 
 * @file:   encomendas.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:48
 */

#ifndef ENCOMENDAS_H
#define ENCOMENDAS_H

#include <time.h>

#include "input.h"
#include "produtos.h"
#include "clientes.h"

#define INDICE_COD_ENCOMENDA 8
#define INDICE_COD_CLIENTE 8

#define MIN_DIA 1
#define MIN_MES 1
#define MAX_DIA 31
#define MAX_MES 12
#define MIN_QUANTIDADE_PRODUTOS 1
#define MAX_QUANTIDADE_PRODUTOS 999


#define TIPO_CODIGO_ENCOMENDA 'E' ///< caracter inicial do codigo de encomenda

#define MSG_INSERIR_DIA "Insira o dia da entrega da encomenda: " 
#define MSG_INSERIR_MES "Insira o mes da entrega da encomenda: "
#define MSG_INSERIR_ANO "Insira o ano da entrega da encomenda: "
//#define MSG_INSERIR_COD_CLIENTE "Insira o codigo do cliente que efetua a encomenda: "
#define MSG_INSERIR_CODIGO_PRODUTO "Insira o codigo do produto que pretende inserir na encomenda (escreva \"fim\" para acabar): "
#define MSG_INSERIR_QUANTIDADE_PRODUTO "Inira a quantidade que quer desse produto: "
#define MSG_INSERIR_COD_ENCOMENDA "Inira o codigo da encomenda: "
#define ERRO_ENCOMENDA_NAO_EXISTE "A encomenda que introduziu nao existe!"

/** @struct Produto_Quantidade
 *  @brief Estrutura que guarda quantidade que o cliente quer do produto que inseriu na encomenda.
 */
typedef struct {
    char codProduto[INDICE_COD_PRODUTO];
    int quantidade;
} Produto_Quantidade;

/** @struct Encomenda
 *  @brief Estrutura que guarda a informação de uma Encomenda.
 */
typedef struct {
    char codEncomenda[INDICE_COD_ENCOMENDA];
    char codCliente[INDICE_COD_CLIENTE];
    int quantidadeProdutos;
    Produto_Quantidade *produtos;
    Data dataRequerimento; ///< Indica o dia em que foi requesiada a encomenda
    Data dataEntrega;
    Estado estado; ///< Se ja passou o prazo de entrega ou nao
    float preco;
} Encomenda;

/** @struct Encomendas
 *  @brief Estrutra que guarda a informação de todos as encomendas.
 */
typedef struct {
    int contador;
    Encomenda *encomenda;
    int tamanhoArray;
} Encomendas;


/**
 * Funcao Procurar Encomenda
 * 
 * Vai procurar uma encomenda a apartir do codigo da encomenda introduzido, e vai retornar o seu indice, caso não exista, retorna -1.
 * 
 * @param encomendas
 * @param codEncomenda
 * @return retorna o indice da encomenda se ele  existir, caso contrário, retorna -1
 */
int procurarEncomenda(const Encomendas *encomendas, char *codEncomenda);

/**
 * Funcao Procurar Cliente Encomenda
 * 
 * Procura um cliente nas encomendas.
 * 
 * @param encomendas
 * @param codCliente
 * @return retorna o indice do cliente que realizou a encomenda se ele  existir, caso contrário, retorna -1
 */
int procurarClienteEncomenda(const Encomendas *encomendas, char *codCliente);


/**
 * Funcao apagar dados encomenda
 * 
 * Na funcao apagar encomenda, antes de ele ser apagado, vai chamar esta função que vai apagar os dados do mesmo.
 * 
 * @param encomenda
 */
void apagarDadosEncomenda(Encomenda *encomenda);

/**
 * Funcao aumentar array encomendas
 * 
 * Quando o array é criado no malloc que esta no lerEncomendas, ele e criado com 20 espaços a mais, e no adicionarEncomenda,
 *  e preciso chamar esta funcao, ela ve se o contador esta igual ao tamanho do array, caso esteja, vai realocar o array com mais 20 casas.
 * O array e realocado de 20 em 20, pois caso fosse realocado de 1 em 1, iria demorar muito tempo, isto, 
 *  caso houvesse muitas encomendas ja guardadas.
 * 
 * @param encomendas
 */
void aumentarArrayEncomendas(Encomendas *encomendas);

/**
 * Funcao calular preco encomenda
 * 
 * Calcula o preco da encomenda, ao somar o preco dos produtos dela
 * 
 * @param encomenda
 * @return retorna o preco final da encomenda
 */
float calcularPrecoEncomenda(const Encomenda *encomenda, const Produtos *produtos);


/**
 * Funcao adicionar encomenda
 * 
 * Esta funcao vai comecar por criar um codigo para a nova encomenda, caso esse codigo nao exista,
 *  vai chamar-se a si mesma ate que seja criado um codigo que nao exista. Caso o codigo nao exista,
 *  vai pedir ao utilizador para inserir os dados da encomenda.
 * Quando chegar a parte de inserir produtos, vai fazer um do while que vai pedir o codigo do produto, caso exista,
 *  vai fazer relloc do array produtos desse produto, para que o array tenha mais um espaço.
 * 
 * @param encomendas
 * @param cliente
 * @param produtos
 */
void adicionarEncomenda(Encomendas *encomendas, Cliente *cliente, Produtos *produtos);


/**
 * Funcao remover encomenda
 * 
 * Esta funcao vai pedir para que seja inserido um codigo de uma encomeda que o cliente deseja remover,
 *  caso esse codigo nao exista, vai saltar fora. Caso exista, e o seu estado esteja como 'desativo',
 *  vai fazer com que todas as encomendas à frente passem 1 espaço no array para tras,
 *  e vai apagar os dados do produto que se quer remover, para que fique com valores a 0 em memoria.
 * 
 * @param encomendas
 * @param cliente
 * @param codEncomenda
 * @return retorna 1 se removeu a encomenda, caso contrario, retorna -1.
 */
int removerEncomenda(Encomendas *encomendas, Cliente *cliente, char *codEncomenda);


/**
 * Funcao alterar encomenda
 * 
 * Esta funcao e muito parecida com o adicionar, mas  nesta, vai pedir um codigo de encomenda, caso nao exista,
 *  vai saltar fora. Caso exista, vai pedir para serem inseridos novos valores.
 * O codigo da encomenda nao pode ser alterado.
 * 
 * @param encomendas
 * @param produtos
 * @param codEncomenda
 * @return retorna 1 se alterou a encomenda, caso contrario, retorna -1.
 */
int alterarEncomenda(Encomendas *encomendas, Produtos *produtos, char *codEncomenda);


/**
 * Funcao listar encomendas
 * 
 * Esta funcao vai listar todas as encomendas que existem.
 * Somente um administrador pode visualizar esta listagem.
 * 
 * @param encomendas
 * @param clientes
 * @param produtos
 */
void listarEncomendas(const Encomendas *encomendas, const Clientes *clientes, const Produtos *produtos);

/**
 * Funcao listar encomendas cliente
 * 
 * Esta funcao vai listar todas as encomendas que o cliente que esta logado ja realizou.
 * 
 * @param encomendas
 * @param cliente
 * @param produtos
 */
void listarEncomendasCliente(const Encomendas *encomendas, const Cliente *cliente, const Produtos *produtos);

/**
 * Funcao imprimir encomenda
 * 
 * Esta funcao e chamada pela funcao listar encomendas por estado, ela mostra uma versao muito mais simplificada de uma encomenda
 * 
 * @param encomenda
 */
void imprimirEncomenda(const Encomenda *encomenda, const Cliente *cliente, const Produtos *produtos);

/**
 * Funcao listar encomendas por estado
 * 
 * Esta funcao recebe o estado como parametro, se receber como estado 'ATIVO', entao mostra as encomendas ativas. Se receber 'DESATIVO',
 * entao mostra as encomendas desativas.
 * 
 * @param encomendas
 * @param estado
 */
void listarEncomendasPorEstado(const Encomendas *encomendas, const Clientes *clientes, Produtos *produtos, const Estado estado);

/**
 * Funcao ler encomendas
 * 
 * Vai ler as encomendas que ficam no ficheiro encomendas.bin que fica na pasta files, caso esse ficheiro não exista,
 *  vai criar um. Caso exita, vai ler o contador das encomendas e vai fazer malloc nesse contador + 20 casas, que e a MALLOC_MARGEM.
 * No caso das encomendas, para alem de fazer malloc na propria variavel encomendas, tambem vai ter de fazer outro malloc quando ler os produtos, para isso,
 *  quando ele ler a quantidade de produtos, que e um campo da estrutura encomenda, vai fazer malloc no array materiais dessa mesma quantidade,
 * depois le os produtos dessa encomenda, e guarda-se no array encomendas.
 * 
 * @param encomendas
 * @param ficheiro
 */
void lerEncomendas(Encomendas *encomendas, const char *ficheiro);

/**
 * Funcao guardar encomendas
 * 
 * Vai guardar o array encomendas dentro do ficheiro encomendas.bin.
 * 
 * @param encomendas
 * @param ficheiro
 */
void guardarEncomendas(Encomendas *encomendas, const char *ficheiro);


/**
 * Funcao exportar encomendas para csv
 * 
 * Quando chamada pela funcao exportarEncomendasparaCsv, vai colocar no ficheiro .csv a encomenda que lhe mandaram.
 * 
 * @param encomenda
 * @param fp
 */
void exportarEncomendaparaCsv(const Encomenda *encomenda, const Produtos *produtos, const FILE *fp);

/**
 * Funcao exportar encomendas para csv
 * 
 * Vai exportar o array encomendas para um csv chamado encomendas.csv,
 *  para que depois seja possivel visualizar os dados em tabelas no excel. Esta funcao funciona em conjunto com a funcao exportarProdutoparaCsv.
 * Os ficheiros .csv ficam guardados dentro da pasta tabelas.
 * 
 * @param encomendas
 * @param ficheiro
 */
void exportarEncomendasparaCsv(const Encomendas *encomendas, const Produtos *produtos, const char *ficheiro);

#endif /* ENCOMENDAS_H */