#ifndef _RELATORIOS_H
#define _RELATORIOS_H

#include "types.h"
#include <stdio.h>

void listar_sensores(sensor_t *lista);
void listar_setores(setor_t *lista);
void relatorio_setores(setor_t *lista);
void relatorio_sensores_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_sensores_tipo(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_leituras_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_leituras_setor(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_variacao_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_variacao_setor(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_media(sensor_t *lista_sen, setor_t *lista_set);

#endif