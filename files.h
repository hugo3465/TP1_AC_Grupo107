/* 
 * File:   files.h
 * Author: Cesar Castelo
 *         Hugo Guimaraes
 *         Pedro Pinho
 *
 * Created on 2 de janeiro de 2023, 15:44
 */

/// @file files.h
#ifndef FILES_H
#define FILES_H

#ifdef __cplusplus
extern "C" {
#endif


#define CLIENTES_DB_FILE "files//clientes.bin"
#define ADMINISTRADORES_DB_FILE "files//administradores.bin"
#define MATERIAIS_DB_FILE "files//materiais.bin"
#define PRODUTOS_DB_FILE "files//produtos.bin"
#define ENCOMENDAS_DB_FILE "files//encomendas.bin"

#define CLIENTES_CSV_FILE "tabelas//clientes.csv"
#define PRODUTOS_CSV_FILE "tabelas//produtos.csv"
#define MATERIAIS_CSV_FILE "tabelas//materiais.csv"
#define ENCOMENDAS_CSV_FILE "tabelas//encomendas.csv"



#ifdef __cplusplus
}
#endif

#endif /* FILES_H */

