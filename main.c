/* 
 * @file:   main.c
 * @author: Cesar Castelo
 *          Hugo Guimaraes
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "menus.h"
#include "files.h"
#include "administradores.h"
#include "materiais.h"
#include "clientes.h"
#include "producao.h"
#include "produtos.h"
#include "encomendas.h"

/**
 * @main TP1_AC_Grupo107
 * Main do programa
 */
int main(int argc, char** argv) {

    Administradores administradores = {.contador = 0};
    Clientes clientes = {.contador = 0};
    Materiais materiais = {.contador = 0};
    Produtos produtos = {.contador = 0};
    Encomendas encomendas = {.contador = 0};

    int opcao, opcao2, indiceCliente, indiceAdministrador;
    Data data;
    time_t now;
    time(&now);
    struct tm * local = localtime(&now);
    int year = local->tm_year + 1900;

    lerClientes(&clientes, CLIENTES_DB_FILE);
    lerAdministradores(&administradores, ADMINISTRADORES_DB_FILE);
    lerMateriais(&materiais, MATERIAIS_DB_FILE);
    lerProdutos(&produtos, PRODUTOS_DB_FILE);
    lerEncomendas(&encomendas, ENCOMENDAS_DB_FILE);

    do {
        switch (opcao = menuPrincipal()) {
            case 1:
                if ((indiceAdministrador = loginAdministrador(&administradores)) != -1) {
                    do {
                        switch (opcao2 = menuAdministrador()) {
                            case 1:
                                menuAdminMateriais(&materiais);
                                break;
                            case 2:
                                menuAdminProdutos(&produtos, &materiais);
                                break;
                            case 3:
                                menuAdminClientes(&clientes, &encomendas);
                                break;
                            case 4:
                                menuAdminEncomendas(&encomendas, &clientes, &produtos);
                                break;
                            case 5:
                                data.dia = obterInt(MIN_DIA, MAX_DIA, MSG_DIA);
                                data.mes = obterInt(MIN_MES, MAX_MES, MSG_MES);
                                data.ano = obterInt(local->tm_year + 1900, local->tm_year + 1905, MSG_ANO);

                                printEncomendasPorSemana(&encomendas, &produtos, &clientes, &data);
                                
                                pause();
                                break;
                            case 6:
                                menuAdminAdministradores(&administradores);
                                break;
                            case 0:
                                break;
                            default:
                                printf(ERRO_OPCAO_INVALIDA);
                                pause();
                        }
                    } while (opcao2 != 0);
                }
                break;
            case 2:
                if ((indiceCliente = loginCliente(&clientes)) != -1) {
                    menuCliente(&encomendas, &clientes.cliente[indiceCliente], &clientes, &produtos, &materiais, clientes.cliente[indiceCliente].nome);
                }
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }
    } while (opcao != 0);

    //free(&clientes.cliente);
    //free(&clientes);


    return 0;
}