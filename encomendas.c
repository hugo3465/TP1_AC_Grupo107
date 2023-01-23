#include "encomendas.h"

int procurarEncomenda(const Encomendas *encomendas, char *codEncomenda) {
    for (int i = 0; i < encomendas->contador; i++) {
        if (strcmp(encomendas->encomenda[i].codEncomenda, codEncomenda) == 0) {
            return i;
        }
    }
    return -1;
}

int procurarClienteEncomenda(const Encomendas *encomendas, char *codCliente) { ///< Procurar encomenda a partir do codCiente
    for (int i = 0; i < encomendas->contador; i++) {
        if (strcmp(encomendas->encomenda[i].codCliente, codCliente) == 0) {
            return i;
        }
    }
    return -1;
}

void apagarDadosEncomenda(Encomenda *encomenda) {
    free(encomenda->produtos);
    encomenda->produtos = NULL;

    free(encomenda);
    encomenda = NULL;
}

void aumentarArrayEncomendas(Encomendas *encomendas) {
    if (encomendas->contador >= encomendas->tamanhoArray) {
        encomendas->tamanhoArray = encomendas->contador + MALLOC_MARGEM;
        encomendas->encomenda = (Encomenda *) realloc(encomendas->encomenda, encomendas->tamanhoArray * sizeof (Encomenda));
    }
}

float calcularPrecoEncomenda(const Encomenda *encomenda, const Produtos *produtos) {
    float somaPreco = 0.0;
    int indiceProduto;

    for (int i = 0; i < encomenda->quantidadeProdutos; i++) {
        indiceProduto = procurarProduto(produtos, encomenda->produtos[i].codProduto);
        somaPreco += (float) produtos->produto[indiceProduto].preco * encomenda->produtos[i].quantidade;
    }

    return somaPreco;
}

void adicionarEncomenda(Encomendas *encomendas, Cliente *cliente, Produtos *produtos) {
    system("clear || cls");

    int i, indiceProduto;
    char codEncomenda[INDICE_COD_ENCOMENDA];
    char codProduto[INDICE_COD_PRODUTO];


    // Cod Encomenda, funcao para crair código
    criarCodigo(TIPO_CODIGO_ENCOMENDA, codEncomenda, INDICE_COD_ENCOMENDA);

    if (procurarEncomenda(encomendas, codEncomenda) == -1) {

        // Aumentar o array produtos, caso o contador dos encomendas seja igual ao array produtos
        aumentarArrayEncomendas(encomendas);

        // Alocar memoria 
        encomendas->encomenda[encomendas->contador].produtos = (Produto_Quantidade *) malloc(sizeof (Produto_Quantidade));

        // Codigo Encomenda
        strcpy(encomendas->encomenda[encomendas->contador].codEncomenda, codEncomenda);

        // Cliente e estado do cliente
        strcpy(encomendas->encomenda[encomendas->contador].codCliente, cliente->codCliente);
        cliente->estado = ATIVO;

        // Produto
        i = 0;
        do {
            obterString(codProduto, INDICE_COD_PRODUTO, MSG_INSERIR_CODIGO_PRODUTO);
            // ver se codProduto existe, e se o produto nao esta removido
            if ((indiceProduto = procurarProduto(produtos, codProduto)) != -1 && produtos->produto[indiceProduto].estaRemovido == false) {
                encomendas->encomenda[encomendas->contador].produtos = (Produto_Quantidade *)
                        realloc(encomendas->encomenda[encomendas->contador].produtos, (i + 2) * sizeof (Produto_Quantidade)); // aumentar tamanho array

                // Colocar o codigo do produto nas encomendas
                strcpy(encomendas->encomenda[encomendas->contador].produtos[i].codProduto, codProduto);

                // Quantidade do produto
                encomendas->encomenda[encomendas->contador].produtos[i].quantidade =
                        obterInt(MIN_QUANTIDADE_PRODUTOS, MAX_QUANTIDADE_PRODUTOS, MSG_INSERIR_QUANTIDADE_PRODUTO);

                // ativar o produto
                produtos->produto[indiceProduto].estado = ATIVO;

                // incrementar a quantidade de vezes que o produto foi requerido pela sua quantidade
                produtos->produto[indiceProduto].vezesUsadas += encomendas->encomenda[encomendas->contador].produtos[i].quantidade;

                i++;
            }
        } while (strcmp(codProduto, "fim") != 0);

        // Quantidade de produtos
        encomendas->encomenda[encomendas->contador].quantidadeProdutos = i;

        // variaveis usadas para a data de requerimento, elas vao buscar a data e hora do computador
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
        
        // Data Requerimento
        encomendas->encomenda[encomendas->contador].dataRequerimento.dia = local->tm_mday;
        encomendas->encomenda[encomendas->contador].dataRequerimento.mes = local->tm_mon + 1;
        encomendas->encomenda[encomendas->contador].dataRequerimento.ano = local->tm_year + 1900;

        // Data Entrega 
        encomendas->encomenda[encomendas->contador].dataEntrega.dia = obterInt(MIN_DIA, MAX_DIA, MSG_INSERIR_DIA);
        encomendas->encomenda[encomendas->contador].dataEntrega.mes = obterInt(MIN_MES, MAX_MES, MSG_INSERIR_MES);
        encomendas->encomenda[encomendas->contador].dataEntrega.ano = obterInt(local->tm_year + 1900, local->tm_year + 1905, MSG_INSERIR_ANO); // so da para fazer encomendas ate 5 anos, e por isso que esta 1905

        // Preco
        encomendas->encomenda[encomendas->contador].preco = calcularPrecoEncomenda(&(encomendas->encomenda[encomendas->contador]), produtos);
        
        // Estado da encomenda
        encomendas->encomenda[encomendas->contador].estado = ATIVO;

        // Quantidade de encomendas do cliente que a requeriu
        cliente->quantidadeEncomendas++;

        encomendas->contador++;

        mensagem(OPERACAO_BEM_SUCEDIDA);

    } else {
        adicionarEncomenda(encomendas, cliente, produtos); // Caso tenha inserido um codigo que ja existe, vai chamar-se a si mesma
    }
}

int removerEncomenda(Encomendas *encomendas, Cliente *cliente, char *codEncomenda) {
    system("clear || cls");

    int indiceEncomenda, i;

    indiceEncomenda = procurarEncomenda(encomendas, codEncomenda);

    if (indiceEncomenda != -1 && encomendas->encomenda[indiceEncomenda].estado == DESATIVO) {

        for (i = indiceEncomenda; i < encomendas->contador - 1; i++) {
            encomendas->encomenda[i] = encomendas->encomenda[i + 1];
        }

        apagarDadosEncomenda(&encomendas->encomenda[i]);

        cliente->quantidadeEncomendas--;

        encomendas->contador--;

        return 1; // removeu com sucesso

    }

    return -1; // codigo de encomenda nao existe
}

int alterarEncomenda(Encomendas *encomendas, Produtos *produtos, char *codEncomenda) {
    system("clear || cls");

    int indiceEncomenda, indiceProduto, i;
    char codProduto[INDICE_COD_PRODUTO];


    indiceEncomenda = procurarEncomenda(encomendas, codEncomenda);

    if (indiceEncomenda != -1) {

        // Produtos 
        i = 0;
        do {
            obterString(codProduto, INDICE_COD_PRODUTO, MSG_INSERIR_CODIGO_PRODUTO);

            if ((indiceProduto = procurarProduto(produtos, codProduto)) != -1 && produtos->produto[indiceProduto].estaRemovido == false) { // ver se codProduto existe, e se o produto nao esta removido
                encomendas->encomenda[encomendas->contador].produtos = (Produto_Quantidade *)
                        realloc(encomendas->encomenda[encomendas->contador].produtos, (i + 2) * sizeof (Produto_Quantidade)); // aumentar tamanho array

                // Colocar o codigo do produto nas encomendas
                strcpy(encomendas->encomenda[encomendas->contador].produtos[i].codProduto, codProduto);

                // Quantidade do produto
                encomendas->encomenda[encomendas->contador].produtos[i].quantidade =
                        obterInt(MIN_QUANTIDADE_PRODUTOS, MAX_QUANTIDADE_PRODUTOS, MSG_INSERIR_QUANTIDADE_PRODUTO);

                // ativar o produto
                produtos->produto[indiceProduto].estado = ATIVO;

                // incrementar a quantidade de vezes que o produto foi requerido
                produtos->produto[indiceProduto].vezesUsadas++;

                i++;
            }
        } while (strcmp(codProduto, "fim") != 0);

        // Quantidade de produtos
        encomendas->encomenda[encomendas->contador].quantidadeProdutos = i;


        // Data Entrega
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
        encomendas->encomenda[indiceEncomenda].dataEntrega.dia = obterInt(MIN_DIA, MAX_DIA, MSG_INSERIR_DIA);
        encomendas->encomenda[indiceEncomenda].dataEntrega.mes = obterInt(MIN_MES, MAX_MES, MSG_INSERIR_MES);
        encomendas->encomenda[indiceEncomenda].dataEntrega.ano = obterInt(local->tm_year + 1900, local->tm_year + 1905, MSG_INSERIR_ANO); /// so da para fazer encomendas ate 5 anos, e por isso que esta 1905

        //Preco
        encomendas->encomenda[encomendas->contador].preco = calcularPrecoEncomenda(&(encomendas->encomenda[encomendas->contador]), produtos);   
        
        // Estado da encomenda
        encomendas->encomenda[encomendas->contador].estado = ATIVO;

        return 1; // alterou com sucesso
    }

    return -1; // codigo de encomenda nao existe
}

void imprimirEncomenda(const Encomenda *encomenda, const Cliente *cliente, const Produtos *produtos) {
    int indiceProduto;

    printf("codEncomenda: %s\n", encomenda->codEncomenda);
    printf("Cliente: %s\n", cliente->nome);

    printf("Produtos: \n");
    for (int j = 0; j < encomenda->quantidadeProdutos; j++) {
        indiceProduto = procurarProduto(produtos, encomenda->produtos[j].codProduto);

        printf("\tCodProduto: %s\n", encomenda->produtos[j].codProduto);
        printf("\tProduto: %s \n", produtos->produto[indiceProduto].nome);
        printf("\tQuantidade: %d \n\n", encomenda->produtos[j].quantidade);
    }

    printf("Data de Entrega: %d/%d/%d \n", encomenda->dataEntrega.dia, encomenda->dataEntrega.mes, encomenda->dataEntrega.ano);
    printf("Preco: %.2f\n", encomenda->preco);

    printf("\n\n");
}

void listarEncomendas(const Encomendas *encomendas, const Clientes *clientes, const Produtos *produtos) {
    system("clear || cls");

    int indiceCliente;

    for (int i = 0; i < encomendas->contador; i++) {
        indiceCliente = procurarCliente(clientes, encomendas->encomenda[i].codCliente);
        imprimirEncomenda(&encomendas->encomenda[i], &clientes->cliente[indiceCliente], produtos);
    }
}

void listarEncomendasCliente(const Encomendas *encomendas, const Cliente *cliente, const Produtos *produtos) {
    system("clear || cls");

    for (int i = 0; i < encomendas->contador; i++) {
        if(strcmp(encomendas->encomenda[i].codCliente, cliente->codCliente) == 0) {
            imprimirEncomenda(&encomendas->encomenda[i], cliente, produtos);
        }
    }
}

void listarEncomendasPorEstado(const Encomendas *encomendas, const Clientes *clientes, Produtos *produtos, const Estado estado) {
    system("clear || cls");
    
    int indiceCliente;
    
    for (int i = 0; i < encomendas->contador; i++) {
        indiceCliente = procurarCliente(clientes, encomendas->encomenda[i].codCliente); // Procurar cliente para madar para o imprimir
        
        if (encomendas->encomenda[i].estado == DESATIVO && estado == DESATIVO) {
            imprimirEncomenda(&encomendas->encomenda[i], &clientes->cliente[indiceCliente], produtos);
        } else if (encomendas->encomenda[i].estado == ATIVO && estado == ATIVO) {
            imprimirEncomenda(&encomendas->encomenda[i], &clientes->cliente[indiceCliente], produtos);
        }
    }
}

void lerEncomendas(Encomendas *encomendas, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb"); // b - binary

    if (fp == NULL) {
        fp = fopen(ficheiro, "wb"); // Caso o ficheiro ainda não tenha sido criado, vai criar um novo
        return NULL;
    }

    // Ler numero de Clientes do ficheiro
    fread(&encomendas->contador, sizeof (int), 1, fp);

    // Calcular indice para o array que sera criado
    encomendas->tamanhoArray = encomendas->contador + MALLOC_MARGEM;

    encomendas->encomenda = (Encomenda *) malloc(encomendas->tamanhoArray * sizeof (Encomenda));
    if (encomendas->encomenda == NULL) {
        perror("\n\nErro ao alocar memoria ");
        pause();
        return NULL;
    }

    // Ler encomendas
    for (int i = 0; i < encomendas->contador; i++) {
        fread(encomendas->encomenda[i].codEncomenda, sizeof (char), INDICE_COD_ENCOMENDA, fp);
        fread(encomendas->encomenda[i].codCliente, sizeof (char), INDICE_COD_CLIENTE, fp);
        fread(&encomendas->encomenda[i].quantidadeProdutos, sizeof (int), 1, fp);

        // Alocar memoria para os produtos
        encomendas->encomenda[i].produtos = malloc(encomendas->encomenda[i].quantidadeProdutos * sizeof (Produto_Quantidade));
        fread(encomendas->encomenda[i].produtos, sizeof (Produto_Quantidade), encomendas->encomenda[i].quantidadeProdutos, fp);


        fread(&encomendas->encomenda[i].dataRequerimento, sizeof (Data), 1, fp);
        fread(&encomendas->encomenda[i].dataEntrega, sizeof (Data), 1, fp);
        fread(&encomendas->encomenda[i].estado, sizeof (Estado), 1, fp);
        fread(&encomendas->encomenda[i].preco, sizeof (float), 1.0, fp);
    }


    fclose(fp);
}

void guardarEncomendas(Encomendas *encomendas, const char *ficheiro) { // ERRO A GRAVAR
    FILE *fp = fopen(ficheiro, "wb");

    if (fp == NULL) {
        perror("\n\nNao foi possivel guardar as encomendas!");
        pause();
        return;
    }

    fwrite(&encomendas->contador, sizeof (int), 1, fp);

    for (int i = 0; i < encomendas->contador; i++) {
        fwrite(encomendas->encomenda[i].codEncomenda, sizeof (char), INDICE_COD_ENCOMENDA, fp);
        fwrite(encomendas->encomenda[i].codCliente, sizeof (char), INDICE_COD_CLIENTE, fp);

        fwrite(&encomendas->encomenda[i].quantidadeProdutos, sizeof (int), 1, fp);
        fwrite(encomendas->encomenda[i].produtos, sizeof (Produto_Quantidade), encomendas->encomenda[i].quantidadeProdutos, fp); //erro aqui

        fwrite(&encomendas->encomenda[i].dataRequerimento, sizeof (Data), 1, fp);
        fwrite(&encomendas->encomenda[i].dataEntrega, sizeof (Data), 1, fp);
        fwrite(&encomendas->encomenda[i].estado, sizeof (Estado), 1, fp);
        fwrite(&encomendas->encomenda[i].preco, sizeof (float), 1.0, fp);
    }

    fclose(fp);
}

void exportarEncomendaparaCsv(const Encomenda *encomenda, const Produtos *produtos, const FILE *fp) {
    int indiceProduto;

    fprintf(fp, "%s;%s;", encomenda->codEncomenda, encomenda->codCliente);
    fprintf(fp, "%d/%d/%d;", encomenda->dataEntrega.dia, encomenda->dataEntrega.mes, encomenda->dataEntrega.ano);

    for (int i = 0; i < encomenda->quantidadeProdutos; i++) {
        indiceProduto = procurarProduto(produtos, encomenda->produtos[i].codProduto);

        fprintf(fp, "%s;", encomenda->produtos[i].codProduto);

        fprintf(fp, "%dx%dx%d;", produtos->produto[indiceProduto].dimensoes.comprimento,
                produtos->produto[indiceProduto].dimensoes.largura,
                produtos->produto[indiceProduto].dimensoes.altura);

        fprintf(fp, "%.2f;", produtos->produto[indiceProduto].preco);
        fprintf(fp, "%d\n", encomenda->produtos[i].quantidade);

        if (i < encomenda->quantidadeProdutos - 1) {
            fprintf(fp, ";;;");
        }
    }
}

void exportarEncomendasparaCsv(const Encomendas *encomendas, const Produtos *produtos, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "w");

    if (fp == NULL) {
        perror("Erro ao abrir ficheiro!");
        pause();
        return;
    }

    fprintf(fp, "CodEncomenda;CodCliente;Data de Entrega;CodProduto;Dimensoes;Preco;Quantidade\n");
    for (int i = 0; i < encomendas->contador; i++) {
        exportarEncomendaparaCsv(&encomendas->encomenda[i], produtos, fp);
    }

    fclose(fp);

}