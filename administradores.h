/** 
 * @file:   administradores.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 26 de dezembro de 2022, 15:15
 */

#ifndef ADMINISTRADORES_H
#define ADMINISTRADORES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "input.h"
#include "encomendas.h"
#include "clientes.h"

#define INDICE_COD_ADMINISTRADOR 8
#define INDICE_NOME_ADMINISTRADOR 99
#define INDICE_PASSWORD_ADMINISTRADOR 15

#define TIPO_CODIGO_ADMINISTRADOR 'A' ///< caracter inicial do codigo de administrador

#define MSG_INSERIR_COD_ADMINISTRADOR "Insira o codigo de administrador: "
#define MSG_INSERIR_NOME_ADMINISTRADOR "Insira o nome do administrador: "
#define MSG_INSERIR_PASSWORD "Insira a password: "

#define ERRO_ADMINISTRADOR_NAO_EXISTE "O administrador que introduziu nao existe!"
#define ERRO_ADMINISTRADOR_INEXISTENTE "Não existe nenhum administrador com esse nome!\n"

    /** @struct Administrador
     *  @brief Estrutura que guarda a informação de um administrador.
     */
    typedef struct {
        char codAdministrador[INDICE_COD_ADMINISTRADOR];
        char nome[INDICE_NOME_ADMINISTRADOR];
        char password[INDICE_PASSWORD_ADMINISTRADOR];
    } Administrador;

    /** @struct Administradores
     *  @brief Estrutra que guarda a informação de todos os administradores.
     */
    typedef struct {
        int contador; ///< Quantidade de administradores que existem
        Administrador *administrador;
        int tamanhoArray; ///< Tamnho do array administrador quando executar a funcao lerAdimnistradores, vai ser sempre maior do que o contador
    } Administradores;



    /**
     * Funcao procurar administrador
     * 
     * Vai procurar um administrador a apartir do codigo do produto introduzido, e vai retornar o seu indice, caso não exista, retorna -1.
     * 
     * @param administradores
     * @param codAdministrador
     * @return retorna o indice do administrador se ele  existir, caso contrário, retorna -1
     */
    int procurarAdministrador(const Administradores *administradores, char *codAdministrador);

    /**
     * Funcao procurar nome administrador
     * 
     * Vai procurar administrador pelo nome, e vai mostra-lo(s) no ecra.
     * 
     * @param administradores
     * @param nome
     */
    void procurarNomeAdministrador(const Administradores *administradores, char *nome);


    /**
     * Funcao apagar dados cliente
     * 
     * Na funcao apagar administrador, antes de ele ser apagado, vai chamar esta função que vai apagar os dados do mesmo.
     * 
     * @param administrador
     */
    void apagarDadosAdministrador(Administrador *administrador);

    /**
     * Funcao aumentar array administradores
     * 
     *  Quando o array é criado no malloc que esta no lerAdministrador, ele e criado com 20 espaços a mais, e no adicionarAdministrador,
     *  e preciso chamar esta funcao, ela ve se o contador esta igual ao tamanho do array, caso esteja, vai realocar o array com mais 20 casas.
     * O array e realocado de 20 em 20, pois caso fosse realocado de 1 em 1, iria demorar muito tempo,
     *  isto, caso houvesse muitos administradores ja guardados.
     * 
     * @param administradores
     */
    void aumentarArrayAdministradores(Administradores *administradores);


    /**
     * Funcao adicionar administrador
     * 
     * Esta funcao vai comecar por criar um codigo para o novo administrador, caso esse codigo nao exista,
     *  vai chamar-se a si mesma ate que seja criado um codigo que nao exista. Caso o codigo nao exista,
     *  vai pedir ao utilizador para inserir os dados do administrador.
     * 
     * @param administradores
     */
    void adicionarAdministrador(Administradores *administradores);


    /**
     * Funcao remover administradores
     * 
     * Esta funcao vai pedir para que seja inserido o codigo do administrador que se deseja remover,
     *  caso esse codigo nao exista, vai saltar fora. Caso exista, vai fazer com que todos os produtos à frente passem 1 espaço no array para tras,
     *  e vai apagar os dados do produto que se quer remover, para que fique com valores a 0 em memoria.
     * 
     * @param administradores
     * @param codAdministrador
     * @return retorna 1 caso tenha removido, caso contrario, retorna -1, se o codAdministrador introduzido nao existe
     */
    int removerAdministrador(Administradores *administradores, char *codAdministrador);


    /**
     * Funcao alterarAdministradores
     * 
     * Esta funcao e muito parecida com o adicionar, mas  nesta, vai pedir um codigo de administrador, caso nao exista,
     *  vai saltar fora. Caso exista, vai pedir para serem inseridos novos valores.
     * O codigo do administrador nao pode ser alterado.
     * 
     * @param administradores
     * @param codAdministrador
     * @return retorna 1 caso tenha alterado, caso contrario, retorna -1, se o codAdministrador introduzido nao existe
     */
    int alterarAdministrador(Administradores *administradores, char *codAdministrador);


    /**
     * 
     * Funcao listar administradores
     * 
     * Esta funcao vai listar todas os administradores que existem.
     * Somente um administrador pode visualizar esta listagem.
     * 
     * @param administradores
     */
    void listarAdministradores(const Administradores *administradores);
    

    /**
     * Funcao ler administradores
     * 
     * Vai ler os administradores que ficam no ficheiro administradores.bin que fica na pasta files, caso esse ficheiro nao exista,
     *  vai criar um. Caso exita, vai ler o contador dos administradores e vai fazer malloc nesse contador + 20 casas, que e a MALLOC_MARGEM.
     * 
     * @param administradores
     * @param ficheiro
     */
    void lerAdministradores(Administradores *administradores, const char *ficheiro);

    /**
     * Funcao guardar administradores
     * 
     * Vai guardar o array administradores dentro do ficheiro administradores.bin.
     * 
     * @param administradores
     * @param ficheiro
     */
    void guardarAdministradores(Administradores *administradores, const char *ficheiro);


#ifdef __cplusplus
}
#endif

#endif /* ADMINISTRADORES_H */

