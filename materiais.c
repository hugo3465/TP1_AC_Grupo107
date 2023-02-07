#include <stdio.h>
#include "input.h"
#include "materiais.h"
#include "encomendas.h"

int procurarMaterial(const Materiais *materiais, char *codMatrial) {
    for (int i = 0; i < materiais->contador; i++) {
        if (strcmp(materiais->material[i].codMatrial, codMatrial) == 0) {
            return i;
        }
    }
    return -1;
}

void procurarDescricaoMaterial(const Materiais *materiais, char *nome) {
    system("clear || cls");

    int verificacao;

    for (int i = 0; i < materiais->contador; i++) {
        if (strcmp(materiais->material[i].descricao, nome) == 0) {
            imprimirMaterial(&materiais->material[i]);
            verificacao++;
        }
    }

    if (verificacao == 0) {
        printf(ERRO_MATERIAL_INEXISTENTE);
    }

    pause();
}

void apagarDadosMaterial(Material *material) {
    free(material);
    material = NULL;
}

void aumentarArrayMateriais(Materiais *materiais) {
    if (materiais->contador >= materiais->tamanhoArray) {
        materiais->tamanhoArray = materiais->contador + MALLOC_MARGEM;
        materiais->material = (Material *) realloc(materiais->material, materiais->tamanhoArray * sizeof (Material));
    }
}

void adicionarMaterial(Materiais *materiais) {
    system("clear || cls");

    char codMaterial[INDICE_COD_MATERIAL];

    // Funcao para crair código material
    criarCodigo(TIPO_COD_MATERIAL, codMaterial, INDICE_COD_MATERIAL);


    if (procurarMaterial(materiais, codMaterial) == -1) {

        // Aumentar o array materiais, caso o contador dos clientes seja igual ao array materiais
        aumentarArrayMateriais(materiais);

        // Codigo Material
        strcpy(materiais->material[materiais->contador].codMatrial, codMaterial);

        // decricao
        obterString(materiais->material[materiais->contador].descricao, INDICE_DESCRICAO_MATERIAL, MSG_INSERIR_DESCRICAO_MATERIAL);

        // unidade
        obterString(materiais->material[materiais->contador].unidade, INDICE_UNIDADE_MATERIAL, MSG_INSERIR_UNIDADE_MATERIAL);

        // vezes usadas
        materiais->material[materiais->contador].vezesUsadas = 0;

        materiais->contador++;
    } else {
        adicionarMaterial(materiais); // Caso tenha inserido um codigo que ja exista
    }
}

int removerMaterial(Materiais *materiais, char *codMaterial) {
    system("clear || cls");

    int indiceMaterial, i;

    indiceMaterial = procurarMaterial(materiais, codMaterial);

    if (indiceMaterial != -1) {
        for (i = indiceMaterial; i < materiais->contador - 1; i++) {
            materiais->material[i] = materiais->material[i + 1];
        }

        apagarDadosMaterial(&materiais->material[i]);

        materiais->contador--;

        return 1; // removeu com sucesso

    }

    return -1; // codigo de material nao existe
}

int alterarMaterial(Materiais *materiais, char *codMaterial) {
    system("clear || cls");

    int indiceMaterial;

    indiceMaterial = procurarMaterial(materiais, codMaterial);

    if (indiceMaterial != -1) {

        // decricao
        obterString(materiais->material[indiceMaterial].descricao, INDICE_DESCRICAO_MATERIAL, MSG_INSERIR_DESCRICAO_MATERIAL);

        // unidade
        obterString(materiais->material[indiceMaterial].unidade, INDICE_UNIDADE_MATERIAL, MSG_INSERIR_UNIDADE_MATERIAL);

        return 1; // alterou com sucesso

    }

    return -1; // codigo de material nao existe
}

void imprimirMaterial(const Material *material) {
    printf("\tcodMaterial: %s\n", material->codMatrial);
    printf("\tDescricao: %s\n", material->descricao);
    printf("\tUnidade: %s\n", material->unidade);

    printf("\n\n");
}

void listarMateriais(const Materiais *materiais) {
    system("clear || cls");

    printf("=================================\n"); // separador
    
    for (int i = 0; i < materiais->contador; i++) {
        printf("Material %d:\n", i + 1);
        imprimirMaterial(&materiais->material[i]);
    }
    
    printf("================================="); // separador
}

void ordenarMateriaisPorUsados(Materiais * materiais) {
    int i, j, position;
    Material swap;

    for (i = 0; i < (materiais->contador - 1); i++) {
        position = i;
        for (j = i + 1; j < materiais->contador; j++) {
            if (materiais->material[position].vezesUsadas < materiais->material[j].vezesUsadas) {
                position = j;
            }
        }
        if (position != i) {
            swap = materiais->material[i];
            materiais->material[i] = materiais->material[position];
            materiais->material[position] = swap;
        }
    }
}

void materiaisMaisUsados(Materiais * materiais) {
    system("clear || cls");
    
    ordenarMateriaisPorUsados(materiais);
    listarMateriais(materiais);
}

void lerMateriais(Materiais *materiais, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb"); // b - binary

    if (fp == NULL) {
        fp = fopen(ficheiro, "wb"); // Caso o ficheiro ainda não tenha sido criado, vai criar um novo
        return NULL;
    }

    // Ler numero de Materiais do ficheiro
    fread(&materiais->contador, sizeof (int), 1, fp);

    // Calcular indice para o array que sera criado
    materiais->tamanhoArray = materiais->contador + MALLOC_MARGEM;

    materiais->material = (Material *) malloc(materiais->tamanhoArray * sizeof (Material));
    if (materiais->material == NULL) {
        perror("\n\nErro ao alocar memoria ");
        pause();
        return;
    }

    for (int i = 0; i < materiais->contador; i++) {
        fread(&materiais->material[i], sizeof (Material), 1, fp);
    }


    fclose(fp);
}

void guardarMateriais(Materiais *materiais, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");

    if (fp == NULL) {
        perror("\n\nNao foi possivel guardar os materiais!");
        pause();
        return;
    }

    fwrite(&materiais->contador, sizeof (int), 1, fp);

    for (int i = 0; i < materiais->contador; i++) {
        fwrite(&materiais->material[i], sizeof (Material), 1, fp);
    }

    fclose(fp);
}

void exportarMaterialparaCsv(const Material *material, const FILE *fp) {
    fprintf(fp, "%s;", material->codMatrial);
    fprintf(fp, "%s;", material->descricao);
    fprintf(fp, "%s\n", material->unidade);
}

void exportarMateiaisparaCsv(const Materiais *materiais, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "w");

    if (fp == NULL) {
        perror("Erro ao abrir ficheiro!");
        return;
    }

    fprintf(fp, "CodMaterial;Descricao;Unidade\n");
    for (int i = 0; i < materiais->contador; i++) {
        exportarMaterialparaCsv(&materiais->material[i], fp);
    }

    fclose(fp);
}