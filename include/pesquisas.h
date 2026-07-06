#ifndef _PESQUISAS_H
#define _PESQUISAS_H

#include "types.h"

void pesquisa_setor(sensor_t *lista_sen, setor_t *lista_set);
sensor_t *pesquisa_sensor(string str, sensor_t *lista_sen); //Função Recursiva

#endif