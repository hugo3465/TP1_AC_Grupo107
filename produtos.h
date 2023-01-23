/** 
 * @file:   produtos.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:48
 */

#ifndef PRODUTOS_H
#define PRODUTOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "materiais.h"
#include "input.h"
#include "constantes.h"


#define TIPO_CODIGO_PRODUTO 'P' ///< caracter inicial do codigo do produto

#define MIN_ALTURA 0
#define MAX_ALTURA 50
#define MIN_COMPRIMENTO 0
#define MAX_COMPRIMENTO 50
#define MIN_LARGURA 0
#define MAX_LARGURA 50
#define MIN_PRECO 0.01
#define MAX_PRECO 10000
#define MIN_QUANTIDADE 1
#define MAX_QUANTIDADE 10000

#define INDICE_COD_PRODUTO 8
#define INDICE_NOME_PRODUTO 50

#define MSG_INSERIR_COD_PRODUTO "Insira o codigo do produto: "
#define MSG_INSERIR_NOME_PRODUTO "Insira o nome do produto: "
#define MSG_INSERIR_ALTURA_PRODUTO "Insira a altura do produto: "
#define MSG_INSERIR_COMPRIMENTO_PRODUTO "Insira a comprimento do produto: "
#define MSG_INSERIR_LARGURA_PRODUTO "Insira a largura do produto: "
#define MSG_INSERIR_PRECO_PRODUTO "Insira o preco bruto do produto: "
#define MSG_INSERIR_COD_MATERIAL "Insira o codigo do material que este produto e constituido (escreva \"fim\" para acabar): "
#define MSG_INSERIR_QUANTIDADE_MATERIAL "Insira a quantidade do respetivo material: "

#define ERRO_PRODUTO_NAO_EXISTE "O produto que introduziu nao existe!\n"
#define ERRO_PRODUTO_INEXISTENTE "Nao existe nenhum produto com esse nome!\n"
#define PRODUTO_COM_ENCOMENDAS "Como o produto ja foi requesitado numa encomenda, entao o status dele foi colocado como removido!\nPode depois ativa-lo no menu dos produtos."

    /** @struct Material_Quantidade
     *  @brief Estrutura que guarda quantidade de do material inserido para a confeccao do produto.
     */
    typedef struct {
        char codMatrial[INDICE_COD_MATERIAL];
        int quantidade;
    } Material_Quantidade;

    /** @struct Produto
     *  @brief Estrutura que guarda a informação de um Produto.
     */
    typedef struct {
        char codProduto[INDICE_COD_PRODUTO];
        char nome[50];
        Dimensao dimensoes;
        int quantidadeMateriais; ///< Quantidade de materiais diferentes sao necessarios para fabricar o produto
        Material_Quantidade *materiais; ///< Guarda o codigo do produto e a quantidade necessaria desse material
        Estado estado; ///< 0 - poduto desativado, 1 - produto ativo (que ja foi requesitado numa encomenda)
        float preco; ///< Sera pedido ao utilizador o preco bruto do produto, mas o que sera guardado sera o preco liquido.
        Bool estaRemovido; ///< indica se um produto que ja foi requesitado foi removido ou nao, 0 - false, 1 - true
        int vezesUsadas; ///< quantidade de vezes que um produto foi requesitado em encomendas
    } Produto;

    /** @struct Produtos
     *  @brief Estrutra que guarda a informação de todos os produtos.
     */
    typedef struct {
        int contador; ///< numero de produtos existentes no array
        Produto *produto;
        int tamanhoArray; ///< tamanho do array que sera criado para os produtos, que tem sempre mais do que aquilo que guarda
    } Produtos;


    /**
     * Funcao Procurar Produto
     * 
     * Vai procurar um produto a apartir do codigo do produto introduzido, e vai retornar o seu indice.
     * 
     * @param produtos
     * @param codProduto
     * @return retorna o indice do produto se ele  existir, caso contrário, retorna -1
     */
    int procurarProduto(const Produtos *produtos, char *codProduto);

    /**
     * Funcao procurar nome produto
     * 
     * Procura um produto pelo nome.
     * 
     * @param produtos
     * @param materiais
     * @param nome
     */
    void procurarNomeProduto(const Produtos *produtos, const Materiais *materiais, char *nome);

    /**
     * Funcao apagar dados de um prdoduto
     * 
     * Na funcao apagar produto, antes de ele ser apagado, vai chamar esta função que vai apagar os dados do mesmo.
     * 
     * @param produto
     */
    void apagarDadosProduto(Produto *produto);

    /**
     * Funcao Aumentar o array dos produtos
     * 
     * Quando o array é criado no malloc que esta no lerProdutos, ele e criado com 20 espaços a mais, e no adicionarProduto,
     *  e preciso chamar esta funcao, ela ve se o contador esta igual ao tamanho do array, caso esteja, vai realocar o array com mais 20 casas.
     * O array e realocado de 20 em 20, pois caso fosse realocado de 1 em 1, iria demorar muito tempo, isto, 
     *  caso houvesse muitos produtos ja guardados.
     * 
     * @param produtos
     */
    void aumentarArrayProdutos(Produtos *produtos);

    /**
     * Funcao calcular preco do produto
     * 
     * Retorna o preco final do produto, com o custo de mao de obra, a margem de lucro.
     * 
     * @param precoBruto do produto
     * @return preco total do preco mandado pela funcao (precoBruto + maoObra + margemLucro)
     */
    float calcularPrecoProduto(float precoBruto);


    /**
     * Funcao adicionar Produto
     * 
     * Esta funcao vai comecar por criar um codigo para o novo produto, caso esse codigo nao exista,
     *  vai chamar-se a si mesma ate que seja criado um codigo que nao exista. Caso o codigo nao exista,
     *  vai pedir ao utilizador para inserir os dados do produto.
     * Quando chegar a parte de inserir materiais, vai fazer um do while que vai pedir o codigo do material, caso exista,
     *  vai fazer relloc do array materiais desse produto, para que o array tenha mais um espaço.
     * 
     * @param produtos
     * @param materiais
     */
    void adicionarProduto(Produtos *produtos, Materiais *materiais);


    /**
     * Funcao remover Produto
     * 
     * Esta funcao vai pedir para que seja inserido um codigo de um produto que o administrador deseja remover,
     *  caso esse codigo nao exista, vai saltar fora. Caso exista, vai fazer com que todos os produtos à frente passem 1 espaço no array para tras,
     *  e vai apagar os dados do produto que se quer remover, para que fique com valores a 0 em memoria.
     * 
     * @param produtos
     * @param codProduto
     * @return retorna 1 se removeu. Retorna -1 se o produto introduzido nao existe. Caso o produto esteja ativo, e posto como removido e retorna 2
     */
    int removerProduto(Produtos *produtos, char *codProduto);

    /**
     * Funcao alterar Produto
     * 
     * Esta funcao e muito parecida com o adicionar, mas  nesta, vai pedir um codigo de produto, caso nao exista,
     *  vai saltar fora. Caso exista, vai pedir para serem inseridos novos valores.
     * O codigo do produto nao pode ser alterado.
     * 
     * @param produtos
     * @param materiais
     * @param codProduto
     * @return retorna 1 se alterou, e retorna -1 se o produto introduzido nao existe
     */
    int alterarProduto(Produtos *produtos, Materiais *materiais, char *codProduto);

    /**
     * Funcao restaurar produto
     * 
     * Esta duncao serve para restaurar um produto que tenha como status apagado.
     * 
     * @param produtos
     * @param codProduto
     * @return faz return -1 caso nao encontre o codigo de produto, caso contrario, coloca o produto como nao removido e faz return 1.
     */
    int restaurarProduto(Produtos *produtos, char *codProduto);

    /**
     * Funcao Imprimir Produto
     * 
     * Vai imprimir as informacoes de um unico produto.
     * 
     * @param produto
     * @param materiais
     */
    void imprimirProduto(const Produto *produto, const Materiais *materiais);

    /**
     * Funcao listar Produtos
     * 
     * Esta funcao funciona juntamente com a funcao imprimirProduto, como o nome diz, vai listar os produtos juntamente com os seus respetivos materiais.
     * 
     * @param produtos
     * @param materiais
     */
    void listarProdutos(const Produtos *produtos, const Materiais *materiais);

    /**
     * Funcao listar produtos apagados
     * 
     * Esta funcao funciona juntamente com a funcao imprimirProduto, como o nome diz, vai listar somente os produtos que estao como apagados.
     * 
     * @param produtos
     * @param materiais
     */
    void listarProdutosApagados(const Produtos *produtos, const Materiais *materiais);

    /**
     * Funcao Listar produtos sem materiais
     * 
     * Vai fazer a listagem de todos os produtos que foram salvos em memoria, mas sem exibir os materiais que sao feitos.
     * 
     * @param produtos
     */
    void listarProdutosSemMateriais(const Produtos *produtos);

    /**
     * Funcao listar Produtos por Estado
     * 
     * Esta funcao recebe o estado como parametro, se receber como estado 'ATIVO', entao mostra os produtos ativos. Se receber 'DESATIVO',
     * entao mostra os produtos desativos.
     * 
     * @param produtos
     * @param estado
     */
    void listarProdutosPorEstado(const Produtos *produtos, const Materiais *materiais, const Estado estado);

    /**
     * Funcao ordenar produtos por vendidos
     * 
     * Esta funcao vai ordenar todos os produtos pela quantidade de vezes que este e vendido numa encomenda, e vai guarda-los por ordem decrescente.
     * Esta funcao vai guardar um produto na variavel swap, e vai percorrer todo o array, até encontrar um produto que foi mais vendido, caso haja, vai trocar com o produto
     * que tinha guardado. Quando acabar de percorrer o array, vai guardar o proximo produto na variavel swap e voltar a percorrer todo o array. Assim sucessivamente
     * até verificar todos os produtos.
     * 
     * @param produtos
     */
    void ordenarProdutosPorVendidos(Produtos *produtos);

    /**
     * Funcao Produtos mais Vendidos
     * 
     * Esta funcao funciona em conjunto com a funcao 'ordenarProdutosPorVendidos', ela vai chamar essa funcao, para que ela ordene
     * os produtos por ordem decrescente pela variavel 'vezes usadas', e depois vai pedir para serem listados todos os materiais.
     * 
     * @param produtos
     * @param materiais
     */
    void produtosMaisVendidos(Produtos * produtos, Materiais * materiais);
    

    /**
     * Funcao ler proodutos
     * 
     * Vai ler os produtos que ficam no ficheiro produtos.bin que fica na pasta files, caso esse ficheiro não exista,
     *  vai criar um. Caso exita, vai ler o contador dos produtos e vai fazer malloc nesse contador + 20 casas, que e a MALLOC_MARGEM.
     * No caso dos produtos, para alem de fazer malloc na propria variavel produtos, tambem vai ter de fazer outro malloc quando ler os materiais,
     *  para isso,quando ele ler a quantidade de materiais, que e um campo da estrutura produto,
     * vai fazer malloc no array materiais dessa mesma quantidade,
     *  depois le os materiais desse produtos, e guarda-se no array produtos.
     * 
     * @param produtos
     * @param ficheiro
     */
    void lerProdutos(Produtos *produtos, const char *ficheiro);

    /**
     * Funcao guardar Produtos
     * 
     * vai guardar o array produtos dentro do ficheiro produtos.bin.
     * 
     * @param produtos
     * @param ficheiro
     */
    void guardarProdutos(Produtos *produtos, const char *ficheiro);


    /**
     * Funcao exportat Produto para csv
     * 
     * Quando chamada pela funcao exportarProdutosparaCsv, vai colocar no ficheiro .csv o produto que lhe mandaram.
     * 
     * @param produto
     * @param fp
     */
    void exportarProdutoparaCsv(const Produto *produto, const Materiais *materiais, const FILE *fp);

    /**
     * Funcao exportar  Produtos para csv
     * 
     * Vai exportar o array produtos para um csv chamado produtos.csv,
     *  para que deepois seja possivel visualizar os dados em tabelas no excel. Esta funcao funciona em conjunto com a funcao exportarProdutoparaCsv
     * Os ficheiros .csv ficam guardados dentro da pasta tabelas.
     *  
     * @param produto
     * @param fp
     */
    void exportarProdutosparaCsv(const Produtos *produtos, const Materiais *materiais, const char *ficheiro);


    /**
     * Funcao importar produtos
     * 
     * Esta funcao comeca por declarar as variaveis ​​para armazenar informacoes lidas no ficheiro que e passado na funcao.
     *  A seguir, usa a funcao "fscanf" para ler essas informacoes do ficheiro e armazena-las nas variaveis ​​declaradas.
     *  Com a funcao "procurarProduto" verifica se o produto ja existe no array produtos e, caso nao exista, adiciona-o.
     *  Tambem usa a funcao "aumentarArrayProdutos" para aumentar o tamanho do array de produtos se necessario. Tambem
     *  faz uso da funcao "realloc" para alocar mais memoria para a estrutura "Material_Quantidade" e armazena as
     *  informacoes sobre os materiais utilizados no produto, registando quantas vezes esse produto foi usado.
     * 
     * @param produtos
     * @param materiais
     * @param ficheiro
     * @return retorna -1 se nao conseguiu abrir o ficheiro. Caso tenha lido o ficheiro, vai returnar como valor 1.
     */
    int importarProdutos(Produtos *produtos, Materiais *materiais, const char *ficheiro);


#ifdef __cplusplus
}
#endif

#endif /* PRODUTOS_H */

