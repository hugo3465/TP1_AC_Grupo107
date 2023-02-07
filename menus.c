#include "menus.h"
#include "input.h"
#include "clientes.h"
#include "produtos.h"
#include "materiais.h"
#include "files.h"

int loginCliente(Clientes *clientes) {
    system("clear || cls");

    char codUtilizador[INDICE_COD_CLIENTE], password[INDICE_PASSWORD_CLIENTE];
    int indiceUtilizador;

    obterString(codUtilizador, INDICE_COD_CLIENTE, MSG_INSERIR_COD_UTILIZADOR);
    obterString(password, INDICE_PASSWORD_CLIENTE, MSG_INSERIR_PASSWORD);

    if ((indiceUtilizador = procurarCliente(clientes, codUtilizador)) != -1) { // ver se user existe
        if (strcmp(clientes->cliente[indiceUtilizador].password, password) == 0) { // Ver se a password esta certa
            return indiceUtilizador;
        }

    }

    mensagem(ERRO_LOGIN);

    return -1;
}

int loginAdministrador(Administradores *administradores) {
    system("clear || cls");

    char codAdministrador[INDICE_COD_ADMINISTRADOR], password[INDICE_PASSWORD_ADMINISTRADOR];
    int indiceAdministrador;

    obterString(codAdministrador, INDICE_COD_ADMINISTRADOR, MSG_INSERIR_COD_UTILIZADOR);
    obterString(password, INDICE_PASSWORD_ADMINISTRADOR, MSG_INSERIR_PASSWORD);

    if ((indiceAdministrador = procurarAdministrador(administradores, codAdministrador)) != -1) { // ver se user existe
        if (strcmp(administradores->administrador[indiceAdministrador].password, password) == 0) { // Ver se a password esta certa
            return indiceAdministrador;
        }

    }

    mensagem(ERRO_LOGIN);

    return -1;
}

int menuPrincipal() {
    system("clear || cls");

    int opcao;

    printf(CABECALHO);

    printf("\n\t\t1. Administrador");
    printf("\n\t\t2. Cliente");
    printf("\n\t\t0. Sair");

    printf("\n\nQuer entrar como: ");
    scanf("%d", &opcao);

    limparBuffer();

    return opcao;

}

void menuCliente(Encomendas *encomendas, Cliente *cliente, Clientes *clientes, Produtos *produtos, Materiais *materiais, char *nome) {
    int opcao;
    char codEncomenda[INDICE_COD_ENCOMENDA];

    do {
        system("clear || cls");

        printf("\t---- Bem-vindo %s ----", nome);
        printf("\n\t    1. Listar Produtos");
        printf("\n\t    2. Fazer Encomenda");
        printf("\n\t    3. Alterar Encomenda");
        printf("\n\t    4. Remover Encomenda");
        printf("\n\t    5. Listagens");
        printf("\n\t    6. Alterar Password");
        printf("\n\t    7. Exportar Produtos");
        printf("\n\t    8. Gravar");
        printf("\n\t    0. Sair");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();


        switch (opcao) {
            case 1:
                listarProdutosSemMateriais(produtos);
                pause();
                break;
            case 2:
                adicionarEncomenda(encomendas, cliente, produtos);
                break;
            case 3:
                obterString(codEncomenda, INDICE_COD_ENCOMENDA, MSG_INSERIR_COD_ENCOMENDA);

                (alterarEncomenda(encomendas, produtos, codEncomenda) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_ENCOMENDA_NAO_EXISTE);

                mensagem(OPERACAO_BEM_SUCEDIDA);

                break;
            case 4:
                obterString(codEncomenda, INDICE_COD_ENCOMENDA, MSG_INSERIR_COD_ENCOMENDA);

                (removerEncomenda(encomendas, produtos, codEncomenda) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_ENCOMENDA_NAO_EXISTE);

                break;
            case 5:
                menuListagensEncomendas(encomendas, cliente, produtos);
                break;
            case 6:
                alterarPasswordCliente(cliente);
                break;
            case 7:
                exportarProdutosparaCsv(produtos, materiais, PRODUTOS_CSV_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 8:
                guardarEncomendas(encomendas, ENCOMENDAS_DB_FILE);
                guardarClientes(clientes, CLIENTES_DB_FILE); // como as encomendas tb alteram as infomrações do cliente que as pediu, entao precisa de guardar os clientes tambem
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
        }
    } while (opcao != 0);
}

void menuListagensEncomendas(Encomendas *encomendas, Cliente *cliente, Produtos *produtos) {
    int opcao;

    do {
        system("clear || cls");

        printf("\t---- Listagens ----");
        printf("\n\t1. Listar as suas encomendas");
        printf("\n\t2. Procurar Encomenda");
        printf("\n\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();


        switch (opcao) {
            case 1:
                listarEncomendasCliente(encomendas, cliente, produtos);
                pause();
                break;
            case 2:
                // FALTA ESTE
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
        }
    } while (opcao != 0);
}

int menuAdministrador() {
    system("clear || cls");

    int opcao;

    printf("\t---- Administrador ----");
    printf("\n\t     1. Materiais");
    printf("\n\t     2. Produtos");
    printf("\n\t     3. Clientes");
    printf("\n\t     4. Encomendas");
    printf("\n\t     5. Producao para determinada semana");
    printf("\n\t     6. Administradores");
    printf("\n\t     0. Voltar");

    printf(MSG_ESCOLHER_OPCAO);
    scanf("%d", &opcao);
    limparBuffer();

    return opcao;
}

void menuAdminMateriais(Materiais *materiais) {
    int opcao;
    char codMaterial[INDICE_COD_MATERIAL], descricaoMaterial[INDICE_DESCRICAO_MATERIAL];

    do {
        system("clear || cls");

        printf("\t---- Administrador / Materiais ----");
        printf("\n\t\t1. Adicionar Material");
        printf("\n\t\t2. Alterar Material");
        printf("\n\t\t3. Remover Material");
        printf("\n\t\t4. Listar Materiais");
        printf("\n\t\t5. Listar Materiais mais usados");
        printf("\n\t\t6. Procurar Material");
        printf("\n\t\t7. Exportar Materiais");
        printf("\n\t\t8. Gravar");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarMaterial(materiais);
                break;
            case 2:
                obterString(codMaterial, INDICE_COD_MATERIAL, MSG_INSERIR_CODIGO_MATERIAL);

                (alterarMaterial(materiais, codMaterial) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_MATERIAL_NAO_EXISTE);

                break;
            case 3:
                obterString(codMaterial, INDICE_COD_MATERIAL, MSG_INSERIR_CODIGO_MATERIAL);

                (removerMaterial(materiais, codMaterial) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_MATERIAL_NAO_EXISTE);

                break;
            case 4:
                listarMateriais(materiais);
                pause();
                break;
            case 5:
                materiaisMaisUsados(materiais);
                pause();
                break;
            case 6:
                obterString(descricaoMaterial, INDICE_DESCRICAO_MATERIAL, MSG_INSERIR_DESCRICAO_MATERIAL);
                procurarDescricaoMaterial(materiais, descricaoMaterial);
                break;
            case 7:
                exportarMateiaisparaCsv(materiais, MATERIAIS_CSV_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 8:
                guardarMateriais(materiais, MATERIAIS_DB_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}

void menuAdminProdutos(Produtos *produtos, Materiais *materiais) {
    int opcao, verificacao;
    char codProduto[INDICE_COD_PRODUTO], path[500];

    do {
        system("clear || cls");

        printf("\t---- Administrador / Produtos ----");
        printf("\n\t\t1. Adicionar Produto");
        printf("\n\t\t2. Alterar Produto");
        printf("\n\t\t3. Remover Produto");
        printf("\n\t\t4. Restaurar Produto");
        printf("\n\t\t5. Listagens");
        printf("\n\t\t6. Importar Produtos");
        printf("\n\t\t7. Exportar Produtos");
        printf("\n\t\t8. Gravar");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarProduto(produtos, materiais);
                break;
            case 2:
                obterString(codProduto, INDICE_COD_PRODUTO, MSG_INSERIR_COD_PRODUTO);

                (alterarProduto(produtos, materiais, codProduto) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_PRODUTO_NAO_EXISTE);

                break;
            case 3:
                obterString(codProduto, INDICE_COD_PRODUTO, MSG_INSERIR_COD_PRODUTO);

                verificacao = removerProduto(produtos, codProduto);

                if (verificacao == -1) {
                    mensagem(ERRO_PRODUTO_NAO_EXISTE);
                } else if (verificacao == 2) {
                    mensagem(PRODUTO_COM_ENCOMENDAS);
                } else {
                    mensagem(OPERACAO_BEM_SUCEDIDA);
                }

                break;
            case 4:
                obterString(codProduto, INDICE_COD_PRODUTO, MSG_INSERIR_COD_PRODUTO);

                (restaurarProduto(produtos, codProduto) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_PRODUTO_NAO_EXISTE);

                break;
            case 5:
                menuAdminListagensProdutos(produtos, materiais);
                break;
            case 6:
                obterString(path, 500, MSG_INSERIR_CAMINHO_IMPORT);

                if (importarProdutos(produtos, materiais, path) == 1) {
                    mensagem(OPERACAO_BEM_SUCEDIDA);
                }

                break;
            case 7:
                exportarProdutosparaCsv(produtos, materiais, PRODUTOS_CSV_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 8:
                guardarProdutos(produtos, PRODUTOS_DB_FILE);
                guardarMateriais(materiais, MATERIAIS_DB_FILE); // este save e preciso por causa da importacao, que tambem salva os materiais
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}

void menuAdminListagensProdutos(Produtos *produtos, Materiais *materiais) {
    int opcao;
    char nomePoduto[INDICE_NOME_PRODUTO];

    do {
        system("clear || cls");

        printf("\t---- Administrador/Produtos/Listagens ----");
        printf("\n\t\t1. Listar Produtos");
        printf("\n\t\t2. Listar Produtos Ativos");
        printf("\n\t\t3. Listar Produtos Desativos");
        printf("\n\t\t4. Listar Produtos Apagados");
        printf("\n\t\t5. Listar Produtos mais vendidos");
        printf("\n\t\t6. Procurar Produto");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                listarProdutos(produtos, materiais);
                pause();
                break;
            case 2:
                listarProdutosPorEstado(produtos, materiais, ATIVO);
                pause();
                break;
            case 3:
                listarProdutosPorEstado(produtos, materiais, DESATIVO);
                pause();
                break;
            case 4:
                listarProdutosApagados(produtos, materiais);
                pause();
                break;
            case 5:
                produtosMaisVendidos(produtos);
                pause();
                break;
            case 6:
                obterString(nomePoduto, INDICE_NOME_PRODUTO, MSG_INSERIR_NOME_PRODUTO);
                procurarNomeProduto(produtos, materiais, nomePoduto);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}

void menuAdminClientes(Clientes *clientes, Encomendas *encomendas) {
    int opcao, verificacao;
    char codCliente[INDICE_COD_CLIENTE];

    do {
        system("clear || cls");

        printf("\t---- Administrador / Clientes ----");
        printf("\n\t\t1. Adicionar Cliente");
        printf("\n\t\t2. Alterar Cliente");
        printf("\n\t\t3. Remover Cliente");
        printf("\n\t\t4. Exportar Clientes");
        printf("\n\t\t5. Listagens");
        printf("\n\t\t6. Gravar");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarCliente(clientes);
                break;
            case 2:
                obterString(codCliente, INDICE_COD_CLIENTE, MSG_INSERIR_COD_CLIENTE);

                (alterarCliente(clientes, codCliente) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_CLIENTE_NAO_EXISTE);

                break;
            case 3:
                obterString(codCliente, INDICE_COD_CLIENTE, MSG_INSERIR_COD_CLIENTE);

                verificacao = removerCliente(clientes, codCliente);

                if (verificacao == -1) {
                    mensagem(ERRO_CLIENTE_NAO_EXISTE);
                } else if (verificacao == 0) {
                    mensagem(ERRO_CLIENTE_COM_ENCOMENDAS);
                } else {
                    mensagem(OPERACAO_BEM_SUCEDIDA);
                }

                break;
            case 4:
                exportarClientesparaCsv(clientes, CLIENTES_CSV_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 5:
                menuAdminListagensClientes(clientes);
                break;
            case 6:
                guardarClientes(clientes, CLIENTES_DB_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}

void menuAdminListagensClientes(Clientes *clientes) {
    int opcao;
    char nomeCliente[INDICE_NOME_CLIENTE];

    do {
        system("clear || cls");

        printf("\t---- Administrador/Clientes/Listagens ----");
        printf("\n\t\t1. Listar todos os clientes");
        printf("\n\t\t2. Listar Clientes ativos");
        printf("\n\t\t3. Listar Clientes desativos");
        printf("\n\t\t4. Listar Clientes com mais encomendas");
        printf("\n\t\t5. Paises de origem mais frequentes");
        printf("\n\t\t6. Paises de origem dos clientes com mais encomendas");
        printf("\n\t\t7. Procurar Cliente");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();


        switch (opcao) {
            case 1:
                listarClientes(clientes);
                pause();
                break;
            case 2:
                listarClientesPorEstado(clientes, ATIVO);
                pause();
                break;
            case 3:
                listarClientesPorEstado(clientes, DESATIVO);
                pause();
                break;
            case 4:
                clientesComMaisEncomendas(clientes);
                pause();
                break;
            case 5:
                listagemTopPaisesMaisClientes(clientes);
                pause();
                break;
            case 6:
                listarPaisesMaisEncomendas(clientes);
                pause();
                break;
            case 7:
                obterString(nomeCliente, INDICE_NOME_CLIENTE, MSG_INSERIR_NOME_CLIENTE);

                procurarNomeCliente(clientes, nomeCliente);

                pause();
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
        }
    } while (opcao != 0);
}

void menuAdminEncomendas(Encomendas *encomendas, Clientes *clientes, Produtos *produtos) {
    int opcao;

    do {
        system("clear || cls");

        printf("\t---- Administrador / Encomendas ----");
        printf("\n\t\t1. Listar Encomendas");
        printf("\n\t\t2. Listar Encomendas ativas");
        printf("\n\t\t3. Listar Encomendas desativas");
        printf("\n\t\t4. Exportar Encomendas");

        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                listarEncomendas(encomendas, clientes, produtos);
                pause();
                break;
            case 2:
                listarEncomendasPorEstado(encomendas, clientes, produtos, ATIVO);
                pause();
                break;
            case 3:
                listarEncomendasPorEstado(encomendas, clientes, produtos, DESATIVO);
                pause();
                break;
            case 4:
                exportarEncomendasparaCsv(encomendas, produtos, ENCOMENDAS_CSV_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}

void menuAdminAdministradores(Administradores *administradores) {
    int opcao;
    char codAdministrador[INDICE_COD_ADMINISTRADOR], nomeAdministrador[INDICE_NOME_ADMINISTRADOR];

    do {
        system("clear || cls");

        printf("\t---- Administrador / Administradores ----");
        printf("\n\t\t1. Adicionar administrador");
        printf("\n\t\t2. Alterar administrador");
        printf("\n\t\t3. Remover administrador");
        printf("\n\t\t4. Listar administradores");
        printf("\n\t\t5. Procurar administrador");
        printf("\n\t\t6. Gravar");
        printf("\n\t\t0. Voltar");

        printf(MSG_ESCOLHER_OPCAO);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarAdministrador(administradores);
                break;
            case 2:
                obterString(codAdministrador, INDICE_COD_ADMINISTRADOR, MSG_INSERIR_COD_ADMINISTRADOR);

                (alterarAdministrador(administradores, codAdministrador) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_ADMINISTRADOR_NAO_EXISTE);

                break;
            case 3:
                obterString(codAdministrador, INDICE_COD_ADMINISTRADOR, MSG_INSERIR_COD_ADMINISTRADOR);

                (removerAdministrador(administradores, codAdministrador) == 1) ? mensagem(OPERACAO_BEM_SUCEDIDA) : mensagem(ERRO_ADMINISTRADOR_NAO_EXISTE);

                break;
            case 4:
                listarAdministradores(administradores);
                pause();
                break;
            case 5:
                obterString(nomeAdministrador, INDICE_NOME_ADMINISTRADOR, MSG_INSERIR_NOME_ADMINISTRADOR);
                procurarNomeAdministrador(administradores, nomeAdministrador);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 6:
                guardarAdministradores(administradores, ADMINISTRADORES_DB_FILE);
                mensagem(OPERACAO_BEM_SUCEDIDA);
                break;
            case 0:
                break;
            default:
                printf(ERRO_OPCAO_INVALIDA);
                pause();
        }

    } while (opcao != 0);
}