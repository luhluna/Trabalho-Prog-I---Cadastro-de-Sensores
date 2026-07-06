#ifndef _TYPES_H
#define _TYPES_H

#define T_STR 200
#define T 100
#define MAX_S 3

typedef char string[T_STR];

typedef struct sensores_cadastrados {
    int id;
    struct sensores_cadastrados *proximo;
}sensores_cadastrados_t;

typedef struct sensor {
    int id;
    int maximo_faixa_de_leitura;
    int minimo_faixa_de_leitura;
    int primeiro_horario[3];
    int segundo_horario[3];
    string tipo;
    string unidade_medida; 
    struct sensor *proximo;
}sensor_t;

typedef struct setor {
    int id;
    int qtd_sensores_cadastrados;
    sensores_cadastrados_t *sensores_nesse_setor;
    string nome;
    string descricao;
    struct setor *proximo;
}setor_t;

#endif