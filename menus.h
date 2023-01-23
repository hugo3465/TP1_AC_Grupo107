/* 
 * @file:   materiais.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 21 de dezembro de 2022, 02:05
 */

#ifndef MENUS_H
#define MENUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "administradores.h"
#include "materiais.h"
#include "clientes.h"
#include "producao.h"
#include "produtos.h"
#include "encomendas.h"

#define CABECALHO "\
*****************************************************\n\
*****                                           *****\n\
*****             Moveis para Todos             *****\n\
*****                                           *****\n\
*****************************************************\n"


#define MSG_INSERIR_COD_UTILIZADOR "Introduza o codigo de utilizador: "
#define MSG_INSERIR_PASSWORD "Introduza a password: "
#define MSG_ESCOLHER_OPCAO "\n\nQual opcao vai escolher: "

#define ERRO_LOGIN "Password ou utilizador invalio!"

#define ERRO_OPCAO_INVALIDA "Opcao Invalida!"
    

    int loginCliente(Clientes *clientes);

    int loginAdministrador(Administradores *administradores);
    

    int menuPrincipal();
    

    void menuCliente(Encomendas *encomendas, Cliente *cliente, Clientes *clientes, Produtos *produtos, Materiais *materiais, char *nome);
    
    void menuListagensEncomendas(Encomendas *encomendas, Cliente *cliente, Produtos *produtos);
    

    int menuAdministrador();
    

    void menuAdminMateriais(Materiais *materiais);
    

    void menuAdminProdutos(Produtos *produtos, Materiais *materiais);
    
    void menuAdminListagensProdutos(Produtos *produtos, Materiais *materiais);
    

    void menuAdminClientes(Clientes *clientes, Encomendas *encomendas);
    
    void menuAdminListagensClientes(Clientes *clientes);
    

    void menuAdminEncomendas(Encomendas *encomendas, Clientes *clientes, Produtos *produtos);
    
    void menuAdminAdministradores(Administradores *administradores);


#ifdef __cplusplus
}
#endif

#endif /* MENUS_H */

