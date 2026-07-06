#ifndef _UTILS_H
#define _UTILS_H

#include "types.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

sensores_cadastrados_t *anterior(sensores_cadastrados_t *lista, sensores_cadastrados_t *no);
void retirar_enter(string str);
void formatar_maiuscula(string str);
int gerar_leitura(int numero_max, int numero_min);
void limpar_tela(void);
void voltar_menu(void);
void salvar_dados_bin(sensor_t *lista_sen, setor_t *lista_set);
void carregar_dados_bin(sensor_t **lista_sen, setor_t **lista_set);
void exportar_html(sensor_t *lista_sen, setor_t *lista_set);
int opcao_arquivo(void);
void nome_arquivo(char *nome_arq);

#endif
