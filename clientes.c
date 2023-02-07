#include "clientes.h"

int procurarCliente(const Clientes *clientes, char *codCliente) {
    for (int i = 0; i < clientes->contador; i++) {
        if (strcmp(clientes->cliente[i].codCliente, codCliente) == 0) {
            return i;
        }
    }
    return -1;
}

void procurarNomeCliente(const Clientes *clientes, char *nome) {
    system("clear || cls");

    int verificacao = 0;

    for (int i = 0; i < clientes->contador; i++) {
        if (strcmp(clientes->cliente[i].nome, nome) == 0) {
            imprimirCliente(&clientes->cliente[i]);
            verificacao++;
        }
    }

    if (verificacao == 0) {
        printf(ERRO_CLIENTE_INEXISTENTE);
    }
}

void apagarDadosCliente(Cliente *cliente) {
    free(cliente);
    cliente = NULL;

}

void aumentarArrayClientes(Clientes *clientes) {
    if (clientes->contador >= clientes->tamanhoArray) {
        clientes->tamanhoArray = clientes->contador + MALLOC_MARGEM;
        clientes->cliente = (Cliente *) realloc(clientes->cliente, clientes->tamanhoArray * sizeof (Cliente));
    }
}

void adicionarCliente(Clientes *clientes) {
    system("clear || cls");

    char codCliente[INDICE_COD_CLIENTE];

    // Criar Codigo de cliente
    criarCodigo(TIPO_CODIGO_CLIENTE, codCliente, INDICE_COD_CLIENTE);

    if (procurarCliente(clientes, codCliente) == -1) {

        // Aumentar o array clientes, caso o contador dos clientes seja igual ao array clientes
        aumentarArrayClientes(clientes);

        // Codigo Cliente
        strcpy(clientes->cliente[clientes->contador].codCliente, codCliente);

        // Nome Cliente
        obterString(clientes->cliente[clientes->contador].nome, INDICE_NOME_CLIENTE, MSG_INSERIR_NOME_CLIENTE);

        // Morada
        obterString(clientes->cliente[clientes->contador].morada, INDICE_MORADA_CLIENTE, MSG_INSERIR_MORADA);

        // NIF
        clientes->cliente[clientes->contador].nif = obterInt(INDICE_MIN_NIF, INDICE_MAX_NIF, MSG_INSERIR_NIF);

        // Origem
        obterString(clientes->cliente[clientes->contador].origem, INDICE_ORIGEM_CLIENTE, MSG_INSERIR_PAIS_ORIGEM);

        // Password
        obterString(clientes->cliente[clientes->contador].password, INDICE_PASSWORD_CLIENTE, MSG_INSERIR_PASSWORD);

        // Estado
        clientes->cliente[clientes->contador].estado = DESATIVO; /// O estado vem desativo por padrao, e so fica aitvo quando o ciente fazer uma encomenda

        // Quantidade de encomendas que o cliente realizou
        clientes->cliente[clientes->contador].quantidadeEncomendas = 0;

        clientes->contador++;

    } else {
        adicionarCliente(clientes);
    }
}

int removerCliente(Clientes *clientes, char *codCliente) { // Só devera ser possivel remover clientes que não tenham encomendas realizadas
    system("clear || cls");

    int indiceCliente, i;

    indiceCliente = procurarCliente(clientes, codCliente);

    if (indiceCliente != -1) {
        if (clientes->cliente[indiceCliente].quantidadeEncomendas == 0) { // Só deve dar para remover clientes que nao tenham realizado encomendas
            for (i = indiceCliente; i < clientes->contador - 1; i++) {
                clientes->cliente[i] = clientes->cliente[i + 1];
            }

            apagarDadosCliente(&clientes->cliente[i]);

            clientes->contador--;

            return 1; // removeu com sucesso

        }

        return 0; // nao removeu pois o cliente ja tinha encomendas
    }

    return -1; // codigo de cliente nao existe

}

int alterarCliente(Clientes *clientes, char *codCliente) {
    system("clear || cls");

    int indiceCliente;

    indiceCliente = procurarCliente(clientes, codCliente);

    if (indiceCliente != -1) {

        // Nome Cliente
        obterString(clientes->cliente[indiceCliente].nome, INDICE_NOME_CLIENTE, MSG_INSERIR_NOME_CLIENTE);

        // Morada
        obterString(clientes->cliente[indiceCliente].morada, INDICE_MORADA_CLIENTE, MSG_INSERIR_MORADA);

        // NIF
        clientes->cliente[indiceCliente].nif = obterInt(INDICE_MIN_NIF, INDICE_MAX_NIF, MSG_INSERIR_NIF);

        /// O administrador não pode alterar a password do cliente, so o proprio cliente pode fazer isso

        // Origem
        obterString(clientes->cliente[indiceCliente].origem, INDICE_ORIGEM_CLIENTE, MSG_INSERIR_PAIS_ORIGEM);

        return 1; // alterou com sucesso

    }

    return -1; // nao conseguiu alterar pois o cliente nao existe
}

void alterarPasswordCliente(Cliente *cliente) {
    system("clear || cls");

    char password[INDICE_PASSWORD_CLIENTE];

    obterString(password, INDICE_PASSWORD_CLIENTE, MSG_INSERIR_PASSWORD);

    if (strcmp(password, cliente->password) != 0) { // as passwords nao podem ser as mesmas
        obterString(cliente->password, INDICE_PASSWORD_CLIENTE, MSG_INSERIR_PASSWORD);
    } else {
        printf(ERRO_PASSWORD_REPETIDA);
        pause();
    }
}

void imprimirCliente(const Cliente *cliente) {
    printf("\tCodCliente: %s\n", cliente->codCliente);
    printf("\tNome: %s\n", cliente->nome);
    printf("\tMorada: %s\n", cliente->morada);
    printf("\tNif: %d\n", cliente->nif);
    printf("\tPais de Origem: %s\n", cliente->origem);
    (cliente->estado == ATIVO) ? printf("\tEstado: Ativo") : printf("\tEstado: Desativo");

    printf("\n\n");
}

void listarClientes(const Clientes *clientes) {
    system("clear || cls");

    printf("=================================\n"); // separador
    
    for (int i = 0; i < clientes->contador; i++) {
        printf("Cliente %d:\n", i + 1);
        imprimirCliente(&clientes->cliente[i]);
    }
    
    printf("================================="); // separador
    
}

void listarClientesPorEstado(const Clientes *clientes, const Estado estado) {
    system("clear || cls");
    
    printf("=================================\n"); // separador
    
    for (int i = 0; i < clientes->contador; i++) {
        if (clientes->cliente[i].estado == DESATIVO && estado == DESATIVO) {
            imprimirCliente(&clientes->cliente[i]);
        } else if (clientes->cliente[i].estado == ATIVO && estado == ATIVO) {
            imprimirCliente(&clientes->cliente[i]);
        }
    }
    
    printf("================================="); // separador
    
}

void ordenarClientesPorQntEncomenda(Clientes * clientes) {
    int i, j, position;

    Cliente swap;

    for (i = 0; i < (clientes->contador - 1); i++) {
        position = i;
        for (j = i + 1; j < clientes->contador; j++) {
            if (clientes->cliente[position].quantidadeEncomendas < clientes->cliente[j].quantidadeEncomendas) {
                position = j;
            }
        }
        if (position != i) {
            swap = clientes->cliente[i];
            clientes->cliente[i] = clientes->cliente[position];
            clientes->cliente[position] = swap;
        }
    }
}

void clientesComMaisEncomendas(Clientes * clientes) {
    system("clear || cls");

    ordenarClientesPorQntEncomenda(clientes);

    listarClientes(clientes);
}

void listagemTopPaisesMaisClientes(Clientes *clientes) {
    system("clear || cls");

    Listagens *listagemTopPaisesMaisClientes;
    
    int contador = 0;
    
    // criar um array do tamanho dos clientes, para nao ter que fazer realloc depois
    listagemTopPaisesMaisClientes = (Listagens*) malloc(sizeof (Listagens) * clientes->contador); 

    // Guardar a informação sem repetir
    for (int i = 0; i < clientes->contador; i++) {
        int existe = 0; // alerta se a variavel existe no array listagemTopPaisesMaisClientes
        
        for (int j = 0; j < contador; j++) {
            if (strcmp(clientes->cliente[i].origem, listagemTopPaisesMaisClientes[j].nome) == 0) { // caso exista
                listagemTopPaisesMaisClientes[j].contador++;
                existe = 1;
                break;
            }
        }
        
        if (!existe) { // caso nao exista
            strcpy(listagemTopPaisesMaisClientes[contador].nome, clientes->cliente[i].origem); // copia o nome do pais para a variavel nome do array
            listagemTopPaisesMaisClientes[contador].contador = 1; // como encontrou um pais novo, entao coloca o contador a 1
            contador++; // vai incrementar o contador que serve de inidce do array listagemTopPaisesMaisClientes
        }
    } //Cria e preenche os paises e a quantidade que os mesmos se repetem

    ordenarListagens(listagemTopPaisesMaisClientes, contador);

    printf("Paises com mais clientes registados: \n");
    printArrayListagens(listagemTopPaisesMaisClientes, contador);
    
    free(listagemTopPaisesMaisClientes);
    listagemTopPaisesMaisClientes = NULL;

}

void listarPaisesMaisEncomendas(Clientes *clientes) {
    system("clear || cls");

    Listagens *listarPaisesMaisEncomendas;

    int contador = 0;

    // é criado um array do tamanho dos clietens, para nao ter que fazer realloc depois
    listarPaisesMaisEncomendas = (Listagens*) malloc(sizeof(Listagens) * clientes->contador); 

    // Guardar infomormação sem repetir
    for (int i = 0; i < clientes->contador; i++) {
        int existe = 0; // alerta se a variavel existe no array recorrente
        
        for (int j = 0; j < contador; j++) { // caso exista
            if (strcmp(clientes->cliente[i].origem, listarPaisesMaisEncomendas[j].nome) == 0) {
                listarPaisesMaisEncomendas[j].contador += clientes->cliente[i].quantidadeEncomendas;
                existe = 1;
                break;
            }
        }
        if (!existe) { // caso nao exista
            strcpy(listarPaisesMaisEncomendas[contador].nome, clientes->cliente[i].origem); // copia o nome do pais para a variavel nome do array
            listarPaisesMaisEncomendas[contador].contador = clientes->cliente[i].quantidadeEncomendas;
            contador++;
        }
    } //Cria e preenche os paises e a quantidade de encomendas de encomendas soamadas do respetivos clientes

    ordenarListagens(listarPaisesMaisEncomendas, contador);

    printf("Lista dos Paises com mais encomendas: \n");
    printArrayListagens(listarPaisesMaisEncomendas, contador);
    
    free(listarPaisesMaisEncomendas);
    listarPaisesMaisEncomendas = NULL;
}

void lerClientes(Clientes *clientes, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb"); // b - binary

    if (fp == NULL) {
        fp = fopen(ficheiro, "wb"); // Caso o ficheiro ainda não tenha sido criado, vai criar um novo
        return NULL;
    }

    // Ler numero de Clientes do ficheiro
    fread(&clientes->contador, sizeof (int), 1, fp);

    // Calcular indice para o array que sera criado
    clientes->tamanhoArray = clientes->contador + MALLOC_MARGEM;

    clientes->cliente = (Cliente*) malloc(clientes->tamanhoArray * sizeof (Cliente));
    if (clientes->cliente == NULL) {
        perror("\n\nErro ao alocar memoria ");
        pause();
        return NULL;
    }

    for (int i = 0; i < clientes->contador; i++) {
        fread(&clientes->cliente[i], sizeof (Cliente), 1, fp);
    }


    fclose(fp);
}

void guardarClientes(Clientes *clientes, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");

    if (fp == NULL) {
        perror("\n\nNao foi possivel guardar os clientes!");
        pause();
        return;
    }

    fwrite(&clientes->contador, sizeof (int), 1, fp);

    for (int i = 0; i < clientes->contador; i++) {
        fwrite(&clientes->cliente[i], sizeof (Cliente), 1, fp);
    }

    fclose(fp);
}

void exportarClienteparaCsv(const Cliente *cliente, const FILE * fp) {
    fprintf(fp, "%s;", cliente->codCliente);
    fprintf(fp, "%s;", cliente->nome);
    fprintf(fp, "%s;", cliente->morada);
    fprintf(fp, "%d;", cliente->nif);
    fprintf(fp, "%s\n", cliente->origem);
}

void exportarClientesparaCsv(const Clientes *clientes, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "w");

    if (fp == NULL) {
        perror("Erro ao abrir ficheiro!");
        return;
    }

    fprintf(fp, "CodCliente;Nome;Morada;Nif;Origem\n");
    for (int i = 0; i < clientes->contador; i++) {
        exportarClienteparaCsv(&clientes->cliente[i], fp);
    }

    fclose(fp);
}