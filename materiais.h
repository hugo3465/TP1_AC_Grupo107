/**
 * @file:   materiais.h
 * @author:  Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 11 de dezembro de 2022, 15:37
 */

#ifndef MATERIAIS_H
#define MATERIAIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
    
#define INDICE_COD_MATERIAL 8
#define INDICE_DESCRICAO_MATERIAL 100
#define INDICE_UNIDADE_MATERIAL 4

#define TIPO_COD_MATERIAL 'M' ///< caracter inicial do codigo de material

#define MSG_INSERIR_DESCRICAO_MATERIAL "Insira a descricao do material: "
#define MSG_INSERIR_UNIDADE_MATERIAL "Insira a unidade do material (max. 3 caracteres): "
#define MSG_INSERIR_CODIGO_MATERIAL "Insira o codigo do material: "

#define ERRO_MATERIAL_NAO_EXISTE "O mateiral que introduziu nao existe!"
#define ERRO_MATERIAL_INEXISTENTE "Não existe nenhum material com essa descricao!\n"

    /** @struct Material
     *  @brief Estrutura que guarda a informação de um Material.
     */
    typedef struct {
        char codMatrial[INDICE_COD_MATERIAL];
        char descricao[INDICE_DESCRICAO_MATERIAL];
        char unidade[INDICE_UNIDADE_MATERIAL];
        int vezesUsadas; ///< quantidade de vezes que um material foi preciso para fazer os produtos
    } Material;

    /** @struct Materiais
     *  @brief Estrutra que guarda a informação de todos as Materiais.
     */
    typedef struct {
        int contador;
        Material *material;
        int tamanhoArray;
    } Materiais;


    /**
     * Funcao procurar material
     * 
     * Vai procurar um material a apartir do codigo do material introduzido, e vai retornar o seu indice, caso nao exista, retorna -1.
     * 
     * @param materiais
     * @param codMatrial
     * @return retorna o indice do material se ele  existir, caso contrário, retorna -1
     */
    int procurarMaterial(const Materiais *materiais, char *codMatrial);

    /**
     * Funcao procurar descricao material
     * 
     * Procura um material pelo nome.
     * 
     * @param materiais
     * @param nome
     */
    void procurarDescricaoMaterial(const Materiais *materiais, char *nome);


    /**
     * Funcao apagar dados material
     * 
     * Na funcao apagar material, antes de ele ser apagado, vai chamar esta funcao que vai apagar os dados do mesmo.
     * 
     * @param material
     */
    void apagarDadosMaterial(Material *material);

    /**
     * Funcao aumentar array materiais
     * 
     * Quando o array e criado no malloc que esta no lerMateriais, ele e criado com 20 espacos a mais, e no adicionarMaterial,
     *  e preciso chamar esta funcao, ela ve se o contador esta igual ao tamanho do array, caso esteja, vai realocar o array com mais 20 casas.
     * O array e realocado de 20 em 20, pois caso fosse realocado de 1 em 1, iria demorar muito tempo, isto, 
     *  caso houvesse muitos materiais ja guardados.
     * 
     * @param materiais
     */
    void aumentarArrayMateriais(Materiais *materiais);


    /**
     * Funcao adicionar material
     * 
     * Esta funcao vai comecar por criar um codigo para o novo material, caso esse codigo nao exista,
     *  vai chamar-se a si mesma ate que seja criado um codigo que nao exista. Caso o codigo nao exista,
     *  vai pedir ao utilizador para inserir os dados do material.
     * 
     * @param materiais
     */
    void adicionarMaterial(Materiais *materiais);


    /**
     * Funcao remover material
     * 
     * Esta funcao vai pedir para que seja inserido o codigo de algum material que o administrador deseja remover,
     *  caso esse codigo nao exista, vai saltar fora. Caso exista, vai fazer com que todos os materiais que estejam a frente passem 1 espaco no array para tras,
     *  e vai apagar os dados do material que se quer remover, para que fique com valores a 0 em memoria.
     * @param materiais
     * @param codMaterial
     * @return retorna 1 caso tenha removido com sucesso, se nao, retorna -1.
     */
    int removerMaterial(Materiais *materiais, char *codMaterial);

    /**
     * Funcao alterar material
     * 
     * Esta funcao e muito parecida com o adicionar, mas nesta, vai pedir um codigo de material, caso nao exista,
     *  vai saltar fora. Caso exista, vai pedir para serem inseridos novos valores.
     * O codigo do material nao pode ser alterado.
     * 
     * @param materiais
     * @param codMaterial
     * @return retorna 1 caso tenha alterado o material com sucesso, caso contrario, retorna -1.
     */
    int alterarMaterial(Materiais *materiais, char *codMaterial);


    /**
     * Funcao imprimir material
     * 
     * Vai imprimir as informacoes de um unico material.
     * 
     * @param material
     */
    void imprimirMaterial(const Material *material);

    /**
     * Funcao listar materiais
     * 
     * Esta funcao funciona juntamente com a funcao imprimirMateriais, ela vai listar os materiais que existem.
     * 
     * @param materiais
     */
    void listarMateriais(const Materiais *materiais);
    
    /**
     * Funcao ordenar Materiais por usados
     * 
     * Esta funcao vai ordenar todos os materiais pela quantidade de vezes que este e usado na confesao dos produtos, e vai guarda-los por ordem decrescente.
     * Esta funcao vai guardar um material na variavel swap, e vai percorrer todo o array, até encontrar um material que foi mais usado, caso haja, vai trocar com o material
     * que tinha guardado. Quando acabar de percorrer o array, vai guardar o proximo material na variavel swap e voltar a percorrer todo o array. Assim sucessivamente
     * até verificar todos os materiais.
     * 
     * @param materiais
     */
    void ordenarMateriaisPorUsados(Materiais * materiais);
    
    /**
     * Funcao materiais mais usados
     * 
     * Esta funcao funciona em conjunto com a funcao 'ordenarMateriaisPorUsados', ela vai chamar essa funcao, para que ela ordene
     *  os materiais de acordo com o numero de vezes que eles foram usados. Ela faz isso ao comparar cada elemento com todos os outros
     *  elementos e trocando-os de posição se necessário.
     * 
     * @param materiais
     */
    void materiaisMaisUsados(Materiais * materiais);

    /**
     * Funcao ler materiais
     * 
     * Cai ler os materiais que ficam no ficheiro materiais.bin que fica na pasta files, caso esse ficheiro nao exista,
     *  vai criar um. Caso exita, vai ler o contador dos materiais e vai fazer malloc nesse contador + 20 casas, que e a MALLOC_MARGEM.
     * 
     * @param materiais
     * @param ficheiro
     */
    void lerMateriais(Materiais *materiais, const char *ficheiro);

    /**
     * Funcao guardar materiais
     * 
     * Vai guardar o array materiais dentro do ficheiro materiais.bin.
     * 
     * @param materiais
     * @param ficheiro
     */
    void guardarMateriais(Materiais *materiais, const char *ficheiro);


    /**
     * Funcao exportar encomendas para csv
     * 
     * Quando chamada pela funcao exportarMateiaisparaCsv, vai colocar no ficheiro .csv o material que lhe mandaram.
     * Para conseguir exportar, vai usar a funcao "fwrite", que vai inserir os dados individualmente separados por ";", 
     * e no final de cada registo, vai fazer um "\n".
     * 
     * @param encomenda
     * @param fp
     */
    void exportarMaterialparaCsv(const Material *material, const FILE *fp);

    /**
     * Funcao exportar encomendas para csv
     * 
     * Vai exportar o array materiais para um csv chamado materiais.csv,
     *  para que depois seja possivel visualizar os dados em tabelas no excel. Esta funcao funciona em conjunto com a funcao exportarMaterialparaCsv.
     * Os ficheiros .csv ficam guardados dentro da pasta tabelas.
     * 
     * @param encomendas
     * @param ficheiro
     */
    void exportarMateiaisparaCsv(const Materiais *materiais, const char *ficheiro);

    /**
     * Funcao Importar Materiais
     * 
     * Faz import dos materiais de um ficheiro csv.
     * 
     * @param materiais
     * @param ficheiro
     * @return retorna se fez import de algo, se não, retorna -1
     */
    int importMaterias(Materiais *materiais, const char *ficheiro);

#ifdef __cplusplus
}
#endif

#endif /* MATERIAIS_H */

