/**
 * @file:   producao.h
 * @author: Cesar Castelo, 
 *          Hugo Guimaraes, 
 *          Pedro Pinho
 *
 * @date Created on 8 de dezembro de 2022, 14:48
 */

#ifndef PRODUCAO_H
#define PRODUCAO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "materiais.h"
#include "produtos.h"
#include "encomendas.h"

#define MIN_DIA 1
#define MIN_MES 1
#define MAX_DIA 31
#define MAX_MES 12
#define MSG_DIA "Insira o dia que pretende ver: "
#define MSG_MES "Insira o mes: "
#define MSG_ANO "Insira o ano: "

#define MSG_ERRO_DIA "Você inseriu um dia inválido"
#define MSG_ERRO_MES "Você inseriu um mês inválido"
#define MSG_ERRO_ANO "Você inseriu um ano inválido"
#define MSG_ERRO_SEMANA "Você inseriu um dia da semana sem ser Segunda-Feira"

    /**
     * Funcoa Get Week of Year
     * 
     * Esta funcao calcula a semana do ano de acordo com a data que e passada como parametro.
     *  A funcao usa os campos "ano", "mes" e "dia" da estrutura "Data" para calcular o numero da semana.
     *  Ele usa algumas formulas para calcular o dia juliano (jd), o dia da semana (d4) e o numero
     *  da semana (L) a partir da data fornecida.
     * 
     * @param data
     * @return retorna o número da semana calculado.
     */
    int getWeekOfYear(Data *data);

    /**
     * Funcao Print Encomendas por Semana
     * 
     * Esta funcao imprime as encomendas de uma determinada semana, especificada pela funcao "getWeekOfYear",
     *  comparando-a com a data de entrega das encomendas armazenadas,entao ela usa as funcoes "procurarCliente"
     *  e "imprimirEncomenda" para imprimir informações detalhadas sobre as encomendas.
     * 
     * @param encomendas
     * @param produtos
     * @param clientes
     * @param data
     */
    void printEncomendasPorSemana(Encomendas *encomendas, Produtos * produtos, Clientes *clientes, Data *data);


#ifdef __cplusplus
}
#endif

#endif /* PRODUCAO_H */

