#ifndef _CADASTROS_H
#define _CADASTROS_H

#include "types.h"
#include <stdio.h>

sensor_t *novo_sensor(void);
setor_t *novo_setor(void);
void inserir_sensor_na_lista(sensor_t **lista, sensor_t *novo);
void inserir_setor_na_lista(setor_t **lista, setor_t *novo);
void excluir_sensor(sensor_t *lista_sen, setor_t *lista_set);

#endif