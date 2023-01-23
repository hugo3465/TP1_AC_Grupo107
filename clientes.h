/** 
 * @file:   cliente.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:48
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "input.h"


#define INDICE_COD_CLIENTE 8
#define INDICE_COD_ENCOMENDA 8
#define INDICE_NOME_CLIENTE 99
#define INDICE_MORADA_CLIENTE 155
#define INDICE_MIN_NIF 100000000 ///< obrigar o nif a ter 9 casas decimais
#define INDICE_MAX_NIF 999999999 ///< obrigar o nif a ter 9 casas decimais
#define INDICE_ORIGEM_CLIENTE 100
#define INDICE_PASSWORD_CLIENTE 15

#define TIPO_CODIGO_CLIENTE 'C' ///< caracter inicial do codigo de cliente

#define MSG_INSERIR_COD_CLIENTE "Insira o codigo de cliente: "
#define MSG_INSERIR_NOME_CLIENTE "Insira o nome: "
#define MSG_INSERIR_MORADA "Insira a morada: "
#define MSG_INSERIR_NIF "Insira o nif: "
#define MSG_INSERIR_PAIS_ORIGEM "Insira o pais de origem: "
#define MSG_INSERIR_PASSWORD "Insira a password: "

#define ERRO_CLIENTE_NAO_EXISTE "O cliente que introduziu nao existe!"
#define ERRO_CLIENTE_INEXISTENTE "Não existe nenhum cliente com esse nome!\n"
#define ERRO_CLIENTE_COM_ENCOMENDAS "Nao e possivel remover um cliente que ja tenha realizado encomendas!"
#define ERRO_PASSWORD_REPETIDA "As passwords nao podem ser repetidas"

    /** @struct Cliente
     *  @brief @brief Estrutura que guarda a informação de um cliente.
     */
    typedef struct {
        char codCliente[INDICE_COD_CLIENTE];
        char nome[INDICE_NOME_CLIENTE];
        char morada[INDICE_MORADA_CLIENTE];
        int nif;
        char origem[INDICE_ORIGEM_CLIENTE];
        char password[INDICE_PASSWORD_CLIENTE];
        int quantidadeEncomendas;
        Estado estado;
    } Cliente;

    /** @struct Clientes
     *  @brief Estrutra que guarda a informação de todos os clientes.
     */
    typedef struct {
        int contador;
        Cliente *cliente;
        int tamanhoArray;
    } Clientes;


    /**
     * Funcao procurar cliente
     * 
     * Vai procurar um cliente a apartir do codigo do cliente introduzido, e vai retornar o seu indice, caso não exista, retorna -1.
     * 
     * @param clientes
     * @param codCliente
     * @return retorna o indice do cliente se ele  existir, caso contrário, retorna -1
     */
    int procurarCliente(const Clientes *clientes, char *codCliente);

    /**
     * Funcao procurar nome cliente
     * 
     * Procura um cliente pelo nome.
     * 
     * @param clientes
     * @param nome
     */
    void procurarNomeCliente(const Clientes *clientes, char *nome);


    /**
     * Funcao apagar dados cliente
     * 
     * Na funcao apagar cliente, antes de ele ser apagado, vai chamar esta funcao que vai apagar os dados do mesmo.
     * 
     * @param cliente
     */
    void apagarDadosCliente(Cliente *cliente);

    /**
     * Funcao aumentar array clientes
     * 
     * Quando o array e criado no malloc que esta no lerClientes, ele e criado com 20 espacos a mais, e no adicionarCliente,
     *  e preciso chamar esta funcao, ela ve se o contador esta igual ao tamanho do array, caso esteja, vai realocar o array com mais 20 casas.
     * O array e realocado de 20 em 20, pois caso fosse realocado de 1 em 1, iria demorar muito tempo, isto, 
     *  caso houvesse muitos clientes ja guardados.
     * 
     * @param clientes
     */
    void aumentarArrayClientes(Clientes *clientes);


    /**
     * Funcao adicionar cliente
     * 
     * Esta funcao vai comecar por criar um codigo para o novo cliente, caso esse codigo nao exista,
     *  vai chamar-se a si mesma ate que seja criado um codigo que nao exista. Caso o codigo nao exista,
     *  vai pedir ao utilizador para inserir os dados do cliente.
     * 
     * @param clientes
     */
    void adicionarCliente(Clientes *clientes);


    /**
     * Funcao remover cliente
     * 
     * Esta funcao vai pedir para que seja inserido o codigo de algum cliente que o administrador deseja remover,
     *  caso esse codigo nao exista, vai saltar fora. Caso exista, vai fazer com que todos os clientes qie esteja, a frente passem 1 espaco no array para tras,
     *  e vai apagar os dados do cliente que se quer remover, para que fique com valores a 0 em memoria.
     * 
     * @param clientes
     * @param codCliente
     * @return retorna 1 caso tenha removido, -1 caso nao tenha removido pois o cliente nao exista, ou -1 caso o cliente ja tenha feito encomendas.
     */
    int removerCliente(Clientes *clientes, char *codCliente);


    /**
     * Funcao alterar cliente
     * 
     * Esta funcao e muito parecida com o adicionar, mas nesta, vai pedir um codigo de cliente, caso nao exista,
     *  vai saltar fora. Caso exista, vai pedir para serem inseridos novos valores.
     * O codigo do cliente nao pode ser alterado.
     * 
     * @param clientes
     * @param codCliente
     * @return retorna 1 caso tenha alterado com sucesso, caso contrario, retorna -1 caso o codCliente nao exista
     */
    int alterarCliente(Clientes *clientes, char *codCliente);

    /**
     * Funcoa alterar password cliente
     * 
     * Esta funcao permite que o cliente que esta logado possa alterar a sua palavra passe.
     * 
     * @param cliente
     */
    void alterarPasswordCliente(Cliente *cliente);


    /**
     * Funcao imprimir cliente
     * 
     * Vai imprimir as informacoes de um unico cliente.
     * 
     * @param cliente
     */
    void imprimirCliente(const Cliente *cliente);

    /**
     * Funcao listar clientes
     * 
     * Esta funcao funciona juntamente com a funcao imprimirCliente, ela vai listar os clientes que existem.
     * 
     * @param clientes
     */
    void listarClientes(const Clientes *clientes);

    /**
     * Funcao listar Clientes por Estado
     * 
     * Esta funcao recebe o estado como parametro, se receber como estado 'ATIVO', entao mostra os clientes ativos. Se receber 'DESATIVO',
     * entao mostra os clientes desativos.
     * 
     * @param clientes
     * @param estado
     */
    void listarClientesPorEstado(const Clientes *clientes, const Estado estado);

    /**
     * Funcao ordenar cliente por encomendas
     * 
     * Esta funcao vai ordenar todos os clientes pela quantidade de encomendas, e vai guarda-los por ordem decrescente.
     * Esta funcao vai guardar um cliente na variavel swap, e vai percorrer todo o array, até encontrar um cliente com mais encomendas, caso haja, vai trocar com o cliente
     * que tinha guardado. Quando acabar de percorrer o array, vai guardar o proximo cliente e voltar a percorrer todo o array. Assim sucessivamente
     * até verificar todos os clientes.
     * 
     * @param clientes
     */
    void ordenarClientesPorQntEncomenda(Clientes * clientes);

    /**
     * Funcao clientes com mais encomendas
     * 
     * Esta funcao funciona em conjunto com a funcao 'ordenarClientesPorQntEncomendas', ela vai chamar essa funcao, para que ela ordene
     * os clientes por ordem decrescente por quantidade de encomendas, e depois vai pedir para serem listados todos os clientes.
     * 
     * @param clientes
     */
    void clientesComMaisEncomendas(Clientes *clientes);


    /**
     * Funcoa listagem Top Paises Mais Clientes
     * 
     * Esta funcao cria e preenche uma lista com os paises de origem dos clientes e a quantidade de clientes registrados de cada pais.
     *  Ela aloca memoria para a estrutura de dados "Listagens" e, a seguir, percorre a lista de clientes para
     *  contar quantos clientes de cada pais existem. Se um pais ja estiver na lista, o contador correspondente e incrementado.
     *  Caso nao exista, o pais e adicionado a lista e o contador e definido como 1.
     * A funcao também usa uma funcao chamada "ordenarListagens" para classificar a lista de paises por ordem decrescente em quantidade
     *  de clientes, e uma funcao chamada "printArrayListagens" para imprimir os resultados.
     * Por fim, liberta a memoria alocada.
     * 
     * @param clientes
     */
    void listagemTopPaisesMaisClientes(Clientes *clientes);

    /**
     * Funcao listar paises com mais encomendas
     * 
     * Comeca por alocar memoria para um novo array dinamico de estruturas chamado "listarPaisesMaisEncomendas" do tamanho do numero de clientes existentes na estrutura "Clientes".
     * Depois itera atraves dos clientes e adiciona informacoes sobre o pais de origem e a quantidade de encomendas do pais no array
     *  "listarPaisesMaisEncomendas", sem repetir paises ja existentes no array. A função "ordenarListagens" e entao chamada para ordenar
     *  o array "listarPaisesMaisEncomendas" e a funcao "printArrayListagens" e chamada para imprimir o array.
     * No final, liberta a memoria alocada para o array criado previamente
     * 
     * @param clientes
     */
    void listarPaisesMaisEncomendas(Clientes *clientes);


    /**
     * Funcao ler clientes
     * 
     * Cai ler os clientes que ficam no ficheiro clientes.bin que fica na pasta files, caso esse ficheiro nao exista,
     *  vai criar um. Caso exita, vai ler o contador dos clientes e vai fazer malloc nesse contador + 20 casas, que e a MALLOC_MARGEM.
     * 
     * @param clientes
     * @param ficheiro
     */
    void lerClientes(Clientes *clientes, const char *ficheiro);

    /**
     * Funcao guardar clientes
     * 
     * Vai guardar o array clientes dentro do ficheiro clientes.bin.
     * 
     * @param clientes
     * @param ficheiro
     */
    void guardarClientes(Clientes *clientes, const char *ficheiro);


    /**
     * Funcao exportar cliente para Csv
     * 
     * Quando chamada pela funcao exportarClientesparaCsv, vai colocar no ficheiro .csv o cliente que lhe mandaram.
     * 
     * @param cliente
     * @param fp
     */
    void exportarClienteparaCsv(const Cliente *cliente, const FILE *fp);

    /**
     * Funcao exportar clientes para Csv
     * 
     * Vai exportar o array clientes para um csv chamado clientes.csv,
     * para que depois seja possivel visualizar os dados em tabelas no excel. Esta funcao funciona em conjunto com a funcao exportarClienteparaCsv.
     * Os ficheiros .csv ficam guardados dentro da pasta tabelas.
     * 
     * @param clientes
     * @param ficheiro
     */
    void exportarClientesparaCsv(const Clientes *clientes, const char *ficheiro);


#ifdef __cplusplus
}
#endif

#endif /* CLIENTE_H */