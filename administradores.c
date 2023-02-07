#include "administradores.h"


int procurarAdministrador(const Administradores *administradores, char *codAdministrador) {
    for (int i = 0; i < administradores->contador; i++) {
        if (strcmp(administradores->administrador[i].codAdministrador, codAdministrador) == 0) {
            return i;
        }
    }
    return -1;
}


void procurarNomeAdministrador(const Administradores *administradores, char *nome) {
    system("clear || cls");

    int verificacao = 0;

    for (int i = 0; i < administradores->contador; i++) {
        if (strcmp(administradores->administrador[i].nome, nome) == 0) {

            printf("CodAdministrador: %s\n", administradores->administrador[i].codAdministrador);
            printf("Nome: %s\n", administradores->administrador[i].nome);

            printf("\n\n");

            verificacao++;
        }
    }

    if (verificacao == 0) {
        printf(ERRO_ADMINISTRADOR_INEXISTENTE);
    }

    pause();
}


void apagarDadosAdministrador(Administrador *administrador) {
    free(administrador);
    administrador = NULL;
}


void aumentarArrayAdministradores(Administradores *administradores) {
    if (administradores->contador >= administradores->tamanhoArray) {
        administradores->tamanhoArray = administradores->contador + MALLOC_MARGEM;
        administradores->administrador = (Administrador *) realloc(administradores->administrador, administradores->tamanhoArray * sizeof(Produto));
    }
}


void adicionarAdministrador(Administradores *administradores) {
    system("clear || cls");

    char codAdministrador[INDICE_COD_ADMINISTRADOR];

    // Criar Codigo de Administrador
    criarCodigo(TIPO_CODIGO_ADMINISTRADOR, codAdministrador, INDICE_COD_ADMINISTRADOR);

    if (procurarAdministrador(administradores, codAdministrador) == -1) {

        // Aumentar o array administradores, caso o contador dos clientes seja igual ao array administradores
        aumentarArrayAdministradores(administradores);

        // Codigo Administrador
        strcpy(administradores->administrador[administradores->contador].codAdministrador, codAdministrador);

        // Nome Administrador
        obterString(administradores->administrador[administradores->contador].nome, INDICE_NOME_ADMINISTRADOR, MSG_INSERIR_NOME_ADMINISTRADOR);

        // Password
        obterString(administradores->administrador[administradores->contador].password, INDICE_PASSWORD_ADMINISTRADOR, MSG_INSERIR_PASSWORD);

        administradores->contador++;

    } else {
        adicionarAdministrador(administradores);
    }
}


int removerAdministrador(Administradores *administradores, char *codAdministrador) {
    system("clear || cls");

    int indiceAdministrador, i;

    indiceAdministrador = procurarAdministrador(administradores, codAdministrador);

    if (indiceAdministrador != -1) {
        for (i = indiceAdministrador; i < administradores->contador - 1; i++) {
            administradores->administrador[i] = administradores->administrador[i + 1];
        }

        apagarDadosAdministrador(&administradores->administrador[i]);

        administradores->contador--;
        
        return 1; // removeu com sucesso

    }
    
    return -1; // codigo de cliente nao existe
}


int alterarAdministrador(Administradores *administradores, char *codAdministrador) {
    system("clear || cls");

    int indiceAdministrador;

    indiceAdministrador = procurarAdministrador(administradores, codAdministrador);

    if (indiceAdministrador != -1) {

        // Nome Administrador
        obterString(administradores->administrador[indiceAdministrador].nome, INDICE_NOME_ADMINISTRADOR, MSG_INSERIR_NOME_ADMINISTRADOR);

        // Password
        obterString(administradores->administrador[indiceAdministrador].password, INDICE_PASSWORD_ADMINISTRADOR, MSG_INSERIR_PASSWORD);
        
        return 1; // removeu com sucesso

    } 
    
    return -1; // codigo de cliente nao existe
}


void listarAdministradores(const Administradores *administradores) {
    system("clear || cls");

    printf("=================================\n"); // separador
    
    for (int i = 0; i < administradores->contador; i++) {
        printf("CodAdministrador: %s\n", administradores->administrador[i].codAdministrador);
        printf("Nome: %s\n", administradores->administrador[i].nome);

        printf("\n\n");
    }
    
    printf("================================="); // separador
}


void lerAdministradores(Administradores *administradores, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb"); // b - binary

    if (fp == NULL) {
        fp = fopen(ficheiro, "wb"); // Caso o ficheiro ainda não tenha sido criado, vai criar um novo
        return NULL;
    }

    // Ler numero de administradores do ficheiro
    fread(&administradores->contador, sizeof (int), 1, fp);


    // Calcular indice para o array que sera criado
    administradores->tamanhoArray = administradores->contador + MALLOC_MARGEM;

    administradores->administrador = (Administrador*) malloc(administradores->tamanhoArray * sizeof (Administrador));
    if (administradores->administrador == NULL) {
        perror("\n\nErro ao alocar memoria ");
        pause();
        return NULL;
    }

    for (int i = 0; i < administradores->contador; i++) {
        fread(&administradores->administrador[i], sizeof (Administrador), 1, fp);
    }


    fclose(fp);
}


void guardarAdministradores(Administradores *administradores, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");

    if (fp == NULL) {
        perror("\n\nNao foi possivel guardar os administradores!");
        pause();
        return;
    }

    fwrite(&administradores->contador, sizeof (int), 1, fp);

    for (int i = 0; i < administradores->contador; i++) {
        fwrite(&administradores->administrador[i], sizeof (Administrador), 1, fp);
    }

    fclose(fp);
}