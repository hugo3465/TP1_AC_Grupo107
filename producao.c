#include "input.h"
#include "producao.h"
#include "produtos.h"
#include "encomendas.h"


int getWeekOfYear(Data *data) {
    int year = data->ano;
    int month = data->mes;
    int day = data->dia;

    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    int jd = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    int d4 = jd + 31741 - (jd % 7);
    int L = d4 / 7;

    return L;
}

void printEncomendasPorSemana(Encomendas *encomendas, Produtos * produtos, Clientes *clientes, Data *data) {
    system("clear || cls");
    
    int i, indiceCliente;
    
    int weekOfYear = getWeekOfYear(data);
    
    for (i = 0; i < encomendas->contador; i++) {
        if (getWeekOfYear(&encomendas->encomenda[i].dataEntrega) == weekOfYear) {
            indiceCliente = procurarCliente(clientes, encomendas->encomenda[i].codCliente);
            imprimirEncomenda(&encomendas->encomenda[i], &clientes->cliente[indiceCliente], produtos);
        }
    }
}