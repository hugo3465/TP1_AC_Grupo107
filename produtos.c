#include "input.h"
#include "produtos.h"

int procurarProduto(const Produtos *produtos, char *codProduto) {
    for (int i = 0; i < produtos->contador; i++) {
        if (strcmp(produtos->produto[i].codProduto, codProduto) == 0) {
            return i;
        }
    }
    return -1;
}

void procurarNomeProduto(const Produtos *produtos, const Materiais *materiais, char *nome) {
    system("clear || cls");

    int verificacao = 0;

    for (int i = 0; i < produtos->contador; i++) {
        if (strcmp(produtos->produto[i].nome, nome) == 0) {
            imprimirProduto(&produtos->produto[i], materiais);
            verificacao++;
        }
    }

    if (verificacao == 0) {
        printf(ERRO_PRODUTO_INEXISTENTE);
    }
    pause();
}

void apagarDadosProduto(Produto *produto) {
    free(produto->materiais);
    produto->materiais = NULL;

    free(produto);
    produto = NULL;
}

void aumentarArrayProdutos(Produtos *produtos) {
    if (produtos->contador >= produtos->tamanhoArray) {
        produtos->tamanhoArray = produtos->contador + MALLOC_MARGEM;
        produtos->produto = (Produto *) realloc(produtos->produto, produtos->tamanhoArray * sizeof (Produto));
    }
}

float calcularPrecoProduto(float precoBruto) {
    float maoObra, margemLucro;

    maoObra = (CUSTO_MAO_OBRA * precoBruto) / 100;
    margemLucro = (MARGEM_LUCRO * precoBruto) / 100;

    return precoBruto + maoObra + margemLucro;
}

void adicionarProduto(Produtos *produtos, Materiais *materiais) {
    system("clear || cls");

    int i, indiceMaterial;
    float precoBrutoProduto;
    char codProduto[INDICE_COD_PRODUTO];
    char codMaterial[INDICE_COD_MATERIAL];

    // Criar Codigo do Produto
    criarCodigo(TIPO_CODIGO_PRODUTO, codProduto, INDICE_COD_PRODUTO);

    if (procurarProduto(produtos, codProduto) == -1) {

        // Aumentar o array produtos, caso o contador dos clientes seja igual ao array produtos
        aumentarArrayProdutos(produtos);

        // Alocar memoria 
        produtos->produto[produtos->contador].materiais = (Material_Quantidade *) malloc(sizeof (Material_Quantidade));

        // Codigo produto
        strcpy(produtos->produto[produtos->contador].codProduto, codProduto);

        // Nome Produto
        obterString(produtos->produto[produtos->contador].nome, INDICE_NOME_PRODUTO, MSG_INSERIR_NOME_PRODUTO);

        // Materiais
        i = 0;
        do {
            obterString(codMaterial, INDICE_COD_MATERIAL, MSG_INSERIR_COD_MATERIAL);
            if ((indiceMaterial = procurarMaterial(materiais, codMaterial)) != -1) { // verificar se material existe
                produtos->produto[produtos->contador].materiais = (Material_Quantidade *)
                        realloc(produtos->produto[produtos->contador].materiais, (i + 2) * sizeof (Material_Quantidade)); // aumentar tamanho array

                strcpy(produtos->produto[produtos->contador].materiais[i].codMatrial, codMaterial); // Passar nome material para a estrutura

                // obter a  quantidade do material
                produtos->produto[produtos->contador].materiais[i].quantidade = obterInt(MIN_QUANTIDADE, MAX_QUANTIDADE, MSG_INSERIR_QUANTIDADE_MATERIAL);

                //incrementar a quantidade de vezes que o material foi usado pela sua quantidade
                materiais->material[indiceMaterial].vezesUsadas += produtos->produto[produtos->contador].materiais[i].quantidade;

                i++;
            }
        } while (strcmp(codMaterial, "fim") != 0);

        // Quantidade de materiais
        produtos->produto[produtos->contador].quantidadeMateriais = i;

        // Dimensoes 
        produtos->produto[produtos->contador].dimensoes.altura = obterInt(MIN_ALTURA, MAX_ALTURA, MSG_INSERIR_ALTURA_PRODUTO);
        produtos->produto[produtos->contador].dimensoes.comprimento = obterInt(MIN_COMPRIMENTO, MAX_COMPRIMENTO, MSG_INSERIR_COMPRIMENTO_PRODUTO);
        produtos->produto[produtos->contador].dimensoes.largura = obterInt(MIN_LARGURA, MAX_LARGURA, MSG_INSERIR_LARGURA_PRODUTO);

        // Preco
        precoBrutoProduto = obterFloat(MIN_PRECO, MAX_PRECO, MSG_INSERIR_PRECO_PRODUTO);
        produtos->produto[produtos->contador].preco = calcularPrecoProduto(precoBrutoProduto);

        // Estado
        produtos->produto[produtos->contador].estado = DESATIVO;

        // estaRemovido
        produtos->produto[produtos->contador].estaRemovido = false;

        //Vezes usadas
        produtos->produto[produtos->contador].vezesUsadas = 0;

        produtos->contador++;


    } else {
        adicionarProduto(produtos, materiais);
    }

}

int removerProduto(Produtos *produtos, char *codProduto) {
    system("clear || cls");

    int indiceProduto, i;

    indiceProduto = procurarProduto(produtos, codProduto);

    if (indiceProduto != -1) {

        if (produtos->produto[indiceProduto].estado == DESATIVO) {

            for (i = indiceProduto; i < produtos->contador - 1; i++) {
                produtos->produto[i] = produtos->produto[i + 1];
            }

            apagarDadosMaterial(&produtos->produto[i]);

            produtos->contador--;

            return 1; // removido com sucesso
        }

        if (produtos->produto[indiceProduto].estado == ATIVO) {
            produtos->produto[indiceProduto].estaRemovido = true;
            return 2; // colocado como removido, pois ele ja foi requesitado em uma encomenda
        }
    }

    return -1; // caso o codigo introduzido nao exista
}

int alterarProduto(Produtos *produtos, Materiais *materiais, char *codProduto) {
    system("clear || cls");

    int indiceProduto, indiceMaterial, i;
    char codMaterial[INDICE_COD_MATERIAL];
    float precoBrutoProduto;

    indiceProduto = procurarProduto(produtos, codProduto);

    if (indiceProduto != -1) {

        // Alocar memoria 
        produtos->produto[indiceProduto].materiais = (Material_Quantidade *) malloc(sizeof (Material_Quantidade));

        // Codigo produto
        strcpy(produtos->produto[indiceProduto].codProduto, codProduto);

        // Nome Produto
        obterString(produtos->produto[indiceProduto].nome, INDICE_NOME_PRODUTO, MSG_INSERIR_NOME_PRODUTO);

        // Materiais 
        i = 0;
        do {
            obterString(codMaterial, INDICE_COD_MATERIAL, MSG_INSERIR_COD_MATERIAL);
            if ((indiceMaterial = procurarMaterial(materiais, codMaterial)) != -1) { /// verificar se material existe
                produtos->produto[indiceProduto].materiais = (Material_Quantidade *)
                        realloc(produtos->produto[indiceProduto].materiais, (i + 2) * sizeof (Material_Quantidade)); // aumentar tamanho array

                strcpy(produtos->produto[indiceProduto].materiais[i].codMatrial, codMaterial); // Passar nome material para a estrutura

                // obter a  quantidade do material
                produtos->produto[produtos->contador].materiais[i].quantidade = obterInt(MIN_QUANTIDADE, MAX_QUANTIDADE, MSG_INSERIR_QUANTIDADE_MATERIAL);

                //incrementar a quantidade de vezes que o material foi usado
                materiais->material[indiceMaterial].vezesUsadas++;

                i++;
            }
        } while (strcmp(codMaterial, "fim") != 0);

        // Quantidade de materiais
        produtos->produto[indiceProduto].quantidadeMateriais = i;

        // Dimensoes 
        produtos->produto[indiceProduto].dimensoes.altura = obterInt(MIN_ALTURA, MAX_ALTURA, MSG_INSERIR_ALTURA_PRODUTO);
        produtos->produto[indiceProduto].dimensoes.comprimento = obterInt(MIN_COMPRIMENTO, MAX_COMPRIMENTO, MSG_INSERIR_COMPRIMENTO_PRODUTO);
        produtos->produto[indiceProduto].dimensoes.largura = obterInt(MIN_LARGURA, MAX_LARGURA, MSG_INSERIR_LARGURA_PRODUTO);

        // Preco
        precoBrutoProduto = obterFloat(MIN_PRECO, MAX_PRECO, MSG_INSERIR_PRECO_PRODUTO);
        produtos->produto[indiceProduto].preco = calcularPrecoProduto(precoBrutoProduto);

        return 1; // alterado com sucesso

    }

    return -1; // caso o codigo introduzido nao exista
}

int restaurarProduto(Produtos *produtos, char *codProduto) {
    system("clear || cls");

    int indiceProduto;

    if (indiceProduto = procurarProduto(produtos, codProduto) != -1) {
        produtos->produto[indiceProduto].estaRemovido = false;
        return 1;
    }

    return -1;
}

void imprimirProduto(const Produto *produto, const Materiais *materiais) {
    int indiceMaterial;

    printf("CodProduto: %s\n", produto->codProduto);
    printf("Nome: %s\n", produto->nome);
    printf("Dimensoes: %dx%dx%d\n", produto->dimensoes.comprimento, produto->dimensoes.largura, produto->dimensoes.altura);
    printf("Vezes Usadas: %d\n", produto->vezesUsadas);

    printf("Materiais:\n");
    for (int i = 0; i < produto->quantidadeMateriais; i++) {
        indiceMaterial = procurarMaterial(materiais, produto->materiais[i].codMatrial);

        printf("\tCodMaterial: %s\n", produto->materiais[i].codMatrial);
        printf("\tNome: %s\n", materiais->material[indiceMaterial].descricao);
        printf("\tQuantidade: %d\n\n", produto->materiais[i].quantidade);
    }

    printf("Preco: %.2f\n", produto->preco);

    printf("\n\n");
}

void listarProdutos(const Produtos *produtos, const Materiais *materiais) {
    system("clear || cls");

    for (int i = 0; i < produtos->contador; i++) {
        if (produtos->produto[i].estaRemovido == false) { // listar apenas os produtos que nao estao como removidos
            imprimirProduto(&produtos->produto[i], materiais);
        }
    }
}

void listarProdutosApagados(const Produtos *produtos, const Materiais *materiais) {
    system("clear || cls");

    for (int i = 0; i < produtos->contador; i++) {
        if (produtos->produto[i].estaRemovido == true) { // listar apenas os produtos que estao como removidos
            imprimirProduto(&produtos->produto[i], materiais);
        }
    }
}

void listarProdutosSemMateriais(const Produtos *produtos) {
    system("clear || cls");

    for (int i = 0; i < produtos->contador; i++) {
        if (produtos->produto[i].estaRemovido == false) { // listar apenas os produtos que nao estao como removidos
            printf("CodProduto: %s\n", produtos->produto[i].codProduto);
            printf("Nome: %s\n", produtos->produto[i].nome);
            printf("Preco: %.2f\n", produtos->produto[i].preco);
            printf("Dimensoes: %dx%dx%d\n", produtos->produto[i].dimensoes.comprimento,
                    produtos->produto[i].dimensoes.largura, produtos->produto[i].dimensoes.altura);

            printf("\n\n");
        }
    }
}

void listarProdutosPorEstado(const Produtos *produtos, const Materiais *materiais, const Estado estado) {
    for (int i = 0; i < produtos->contador; i++) {
        if (produtos->produto[i].estado == DESATIVO && estado == DESATIVO) {
            imprimirProduto(&produtos->produto[i], materiais);
        } else if (produtos->produto[i].estado == ATIVO && estado == ATIVO) {
            imprimirProduto(&produtos->produto[i], materiais);
        }
    }
}

void ordenarProdutosPorVendidos(Produtos *produtos) {
    int i, j, position;
    Produto swap;
    
    for (i = 0; i < (produtos->contador - 1); i++) {
        position = i;
        for (j = i + 1; j < produtos->contador; j++) {
            if (produtos->produto[position].vezesUsadas < produtos->produto[j].vezesUsadas) {
                position = j;
            }
        }
        if (position != i) {
            swap = produtos->produto[i];
            produtos->produto[i] = produtos->produto[position];
            produtos->produto[position] = swap;
        }
    }
}

void produtosMaisVendidos(Produtos * produtos, Materiais * materiais) {
    system("clear || cls");
    
    ordenarProdutosPorVendidos(produtos);
    listarProdutos(produtos, materiais);
}

void lerProdutos(Produtos *produtos, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb"); // b - binary

    if (fp == NULL) {
        fp = fopen(ficheiro, "wb"); // Caso o ficheiro ainda não tenha sido criado, vai criar um novo
        return;
    }

    // Ler numero de Produtos do ficheiro
    fread(&produtos->contador, sizeof (int), 1, fp);

    // Calcular indice para o array que sera criado
    produtos->tamanhoArray = produtos->contador + MALLOC_MARGEM;

    produtos->produto = (Produto *) malloc(produtos->tamanhoArray * sizeof (Produto));
    if (produtos->produto == NULL) {
        perror("\n\nErro ao alocar memoria ");
        pause();
        return;
    }

    // Ler produtos
    for (int i = 0; i < produtos->contador; i++) {
        fread(produtos->produto[i].nome, sizeof (char), INDICE_NOME_PRODUTO, fp);
        fread(produtos->produto[i].codProduto, sizeof (char), INDICE_COD_PRODUTO, fp);
        fread(&produtos->produto[i].dimensoes, sizeof (Dimensao), 1, fp);
        fread(&produtos->produto[i].quantidadeMateriais, sizeof (int), 1, fp);

        produtos->produto[i].materiais = malloc(produtos->produto[i].quantidadeMateriais * sizeof (Material_Quantidade));
        fread(produtos->produto[i].materiais, sizeof (Material_Quantidade), produtos->produto[i].quantidadeMateriais, fp);

        fread(&produtos->produto[i].estado, sizeof (Estado), 1, fp);
        fread(&produtos->produto[i].preco, sizeof (float), 1, fp);
        fread(&produtos->produto[i].estaRemovido, sizeof (Bool), 1, fp);
    }

    fclose(fp);
}

void guardarProdutos(Produtos *produtos, const char *ficheiro) {

    FILE *fp = fopen(ficheiro, "wb");

    if (fp == NULL) {
        perror("\n\nNao foi possivel guardar os clientes!");
        pause();
        return;
    }

    fwrite(&produtos->contador, sizeof (int), 1, fp);

    for (int i = 0; i < produtos->contador; i++) {
        fwrite(produtos->produto[i].nome, sizeof (char), INDICE_NOME_PRODUTO, fp);
        fwrite(produtos->produto[i].codProduto, sizeof (char), INDICE_COD_PRODUTO, fp);
        fwrite(&produtos->produto[i].dimensoes, sizeof (Dimensao), 1, fp);

        fwrite(&produtos->produto[i].quantidadeMateriais, sizeof (int), 1, fp);
        fwrite(produtos->produto[i].materiais, sizeof (Material_Quantidade), produtos->produto[i].quantidadeMateriais, fp);

        fwrite(&produtos->produto[i].estado, sizeof (Estado), 1, fp);
        fwrite(&produtos->produto[i].preco, sizeof (float), 1.0, fp);
        fwrite(&produtos->produto[i].estaRemovido, sizeof (Bool), 1, fp);
    }

    fclose(fp);
}

void exportarProdutoparaCsv(const Produto *produto, const Materiais *materiais, const FILE *fp) {
    int indiceMaterial;

    fprintf(fp, "%s;%s;", produto->codProduto, produto->nome);
    fprintf(fp, "%dx%dx%d;", produto->dimensoes.comprimento, produto->dimensoes.largura, produto->dimensoes.altura);
    fprintf(fp, "%.2f;", produto->preco);

    for (int i = 0; i < produto->quantidadeMateriais; i++) {
        indiceMaterial = procurarMaterial(materiais, produto->materiais[i].codMatrial);

        fprintf(fp, "%s;", produto->materiais[i].codMatrial);
        fprintf(fp, "%s;", materiais->material[indiceMaterial].descricao);
        fprintf(fp, "%d;", produto->materiais[i].quantidade);
        fprintf(fp, "%s\n", materiais->material[indiceMaterial].unidade);

        if (i < produto->quantidadeMateriais - 1) {
            fprintf(fp, ";;;;");
        }
    }
}

void exportarProdutosparaCsv(const Produtos *produtos, const Materiais *materiais, const char *ficheiro) {

    FILE *fp = fopen(ficheiro, "w");

    if (fp == NULL) {
        perror("Erro ao abrir ficheiro!");
        return;
    }

    fprintf(fp, "CodProduto;Nome;Dimensoes;preco;CodMaterial;Descricao;Quantidade;Unidade\n");
    for (int i = 0; i < produtos->contador; i++) {
        exportarProdutoparaCsv(&produtos->produto[i], materiais, fp);
    }

    fclose(fp);

}

int importarProdutos(Produtos *produtos, Materiais *materiais, const char *ficheiro) {

    FILE *fp = fopen(ficheiro, "r");

    if (fp == NULL) {
        perror("Erro ao abrir ficheiro!");
        pause();
        return -1;
    }

    int result, indiceProduto, indiceMaterial;

    char codProduto[INDICE_COD_PRODUTO];
    char nomeProduto[INDICE_NOME_PRODUTO];
    int comprimento;
    int largura;
    int altura;
    float preco;
    char codMaterial[INDICE_COD_MATERIAL];
    char descricao[INDICE_DESCRICAO_MATERIAL];
    int quantidade;
    char unidade[INDICE_UNIDADE_MATERIAL];
    int quantidadeMateriais;


    fscanf(fp, "%*[^\n]\n"); // Passar os titulos a frente

    while (!feof(fp)) {
        result = fscanf(fp, "%[^;];%[^;];%dx%dx%d;%f;%[^;];%[^;];%d;%s\n",
                codProduto,
                nomeProduto,
                &comprimento,
                &largura,
                &altura,
                &preco,
                codMaterial,
                descricao,
                &quantidade,
                unidade);

        if (result == 0) {
            fscanf(fp, ";;;;%[^;];%[^;];%d;%s\n",
                    codMaterial,
                    descricao,
                    &quantidade,
                    unidade);

            quantidadeMateriais++;
        }

        if ((indiceProduto = procurarProduto(produtos, codProduto)) == -1) {
            aumentarArrayProdutos(produtos); // verificar se e preciso aumentar o array ou nao

            strcpy(produtos->produto[produtos->contador].codProduto, codProduto);
            strcpy(produtos->produto[produtos->contador].nome, nomeProduto);

            produtos->produto[produtos->contador].dimensoes.comprimento = comprimento;
            produtos->produto[produtos->contador].dimensoes.largura = largura;
            produtos->produto[produtos->contador].dimensoes.altura = altura;

            produtos->produto[produtos->contador].preco = preco;

            produtos->produto[produtos->contador].estado = ATIVO;

            produtos->produto[produtos->contador].estaRemovido = false;

            quantidadeMateriais = 0;

            produtos->produto[produtos->contador].vezesUsadas = 0;

            produtos->contador++;
        } else { // se o produto já existir, vai incrementar a quantidade de vezes usadas
            produtos->produto[indiceProduto].vezesUsadas += quantidade;
        }

        produtos->produto[produtos->contador - 1].materiais = (Material_Quantidade *)
                realloc(produtos->produto[produtos->contador - 1].materiais, (quantidadeMateriais + 1) * sizeof (Material_Quantidade));

        strcpy(produtos->produto[produtos->contador - 1].materiais[quantidadeMateriais].codMatrial, codMaterial);
        produtos->produto[produtos->contador - 1].materiais[quantidadeMateriais].quantidade = quantidade;

        produtos->produto[produtos->contador - 1].quantidadeMateriais = quantidadeMateriais + 1;

        // Inserir material caso ele nao exista
        if ((indiceMaterial = procurarMaterial(materiais, codMaterial)) == -1) { //caso o material nao exista, vai adiciona-lo ao array dos materiais
            aumentarArrayMateriais(materiais); // Aumentar o array materiais, caso o contador dos clientes seja igual ao array materiais

            strcpy(materiais->material[materiais->contador].codMatrial, codMaterial);
            strcpy(materiais->material[materiais->contador].descricao, descricao);
            strcpy(materiais->material[materiais->contador].unidade, unidade);
            materiais->material[materiais->contador].vezesUsadas = 0;

            materiais->contador++;

        } else { // se o material já existir, vai incrementar a quantidade de vezes usadas
            materiais->material[indiceMaterial].vezesUsadas += quantidadeMateriais;
        }
    }

    return 1;

    fclose(fp);
}