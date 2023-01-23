/** 
 * @file   input.h
 * @author:  Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:45
 */

#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#define MALLOC_MARGEM 20 ///< para ter sempre mais x espacos, para melhor performance
#define INDICE_NOME 100

    /** @enum Estado
     *  @brief Como algumas estruturas usam o mesmo enum, entao para evitar repeticao, criou-se este enum global, que indica o estado do produto, encomenda ou cliente.
     */
    typedef enum {
        DESATIVO = 0, ATIVO = 1
    } Estado;

    /** @enum Bool
     *  @brief Cria um tipo de dados booleano, onde e possivel criar variaveis do tipo booleano
     */
    typedef enum {
        false = 0, true = 1
    } Bool;

    /** @struct Data
     *  @brief um dipo de dados que permite guardar uma data.
     */
    typedef struct {
        int dia;
        int mes;
        int ano;
    } Data;

    /** @struct Dimensao
     *  @brief Um tipo de dados que foi criado  para que seja possivel a insercao de dimensoes de um objeto.
     */
    typedef struct {
        int altura;
        int largura;
        int comprimento;
    } Dimensao;

    /**
     * @structListagens
     * @brief Uma maneira de fazer listagens distintas. Organizar os dados em uma estrutura generica, e organiza-los depois. E usada somente nos clientes
     */
    typedef struct {
        char nome[INDICE_NOME];
        int contador;
    } Listagens;

    /**
     * Funcao pause
     */
    void pause();

    /**
     * Funcao limpar buffer
     */
    void limparBuffer();

    /**
     * Funcao mensagem
     * 
     * Faz print da mensagem da mensagem passada pela funcao, e faz um pause depois
     * 
     * @param msg
     */
    void mensagem(char *msg);

    /**
     * Funcao obter int
     *
     * @param minVal
     * @param maxVal
     * @param msg
     * @return retorna o inteiro que foi introduzido
     */
    int obterInt(int minVal, int maxVal, char *msg);

    /**
     * Funcao obter float
     * 
     * @param minVal
     * @param maxVal
     * @param msg
     * @return retorna o float que foi introduzido
     */
    float obterFloat(float maxVal, float minVal, char *msg);

    /**
     * Funcao obter double
     * 
     * @param minVal
     * @param maxVal
     * @param msg
     * @return retorna o double que foi introduzido
     */
    double obterDouble(double maxVal, double minVal, char *msg);

    /**
     * Funcao obter char
     * 
     * @param msg
     * @return retorna o char que foi introduzido
     */
    char obterChar(char *msg);

    /**
     * Funcao obter string
     * 
     * @param string
     * @param tamanho
     * @param msg
     */
    void obterString(char *string, int tamanho, char *msg);


    /**
     * Funcao criar codigo
     * 
     * Esta funcao gera um codigo aleatório com letras e numeros. Usa a variavel "tipoCod" como
     *  o primeiro caractere do codigo gerado, e usa uma string chamada "array" para armazenar o codigo gerado.
     *  Ela tambem usa a variavel "numCaracteres" para determinar o comprimento do codigo gerado.
     *  A funcao usa duas strings, "alfabeto" e "numeros", para armazenar as letras e os numeros que serao usados
     *  ​​para gerar o codigo.
     * A funcao usa a função rand() para gerar numeros aleatorios para selecionar letras e numeros a serem adicionados ao codigo.
     * 
     * @param tipoCod
     * @param array
     * @param numCaracteres
     */
    void criarCodigo(char tipoCod, char *array, int numCaracteres);


    /**
     * Funcao Print Array Listagens
     * 
     * Apresenta na consola do array do tipo 'Listagens' que lhe e mandado.
     * 
     * @param listagens
     * @param size
     */
    void printArrayListagens(Listagens *listagens, int size);
    
    /**
     * Funcoa Ordenar Listagens
     * 
     * A funcao comeca por iterar o array "listagens" coma utilizacao de dois ciclos. O ciclo externo "i" e o ciclo interno "j".
     * O ciclo interno "j" verifica se o valor "contador" na posicao atual "j" e maior do que o valor "contador" na posicao
     *  "position" e, se for, atualiza a posicao "position" para o valor atual "j". No fim do ciclo interno "j", a posição
     *  "position" tem o indice do maior valor "contador" da parte que resta do array.
     * 
     * Se a posicao "position" for diferente da posicao atual "i" do ciclo externo, significa que o maior valor "contador"
     *  nao esta na posicao atual "i" e as estruturas em "listagens[i]" e "listagens[position]" sao trocadas a partir de uma
     *  estrutura temporaria "swap" e assim continuamente ate o array estar completamente ordenado.
     * 
     * @param listagens
     * @param size
     */
    void ordenarListagens(Listagens *listagens, int size);

#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */

