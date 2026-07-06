#include "../include/cadastros.h"
#include "../include/types.h"
#include "../include/relatorios.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>

sensor_t *novo_sensor(void)
{
    int numero;
    sensor_t *novo = NULL;

    novo = (sensor_t*)malloc(sizeof(sensor_t));

    printf("Informe o tipo do sensor: ");
    fgets(novo->tipo, T_STR, stdin);
    retirar_enter(novo->tipo);
    formatar_maiuscula(novo->tipo);

    printf("Informe a unidade de medida utilizada: ");
    fgets(novo->unidade_medida, T_STR, stdin);
    retirar_enter(novo->unidade_medida);

    printf("Insira o número máximo da faixa de leitura de dados: ");
    scanf("%i", &novo->maximo_faixa_de_leitura);
    getchar();

    printf("Insira o número mínimo da faixa de leitura de dados: ");
    scanf("%i", &novo->minimo_faixa_de_leitura);
    getchar();

    printf("Informe o horário em que deve ser feita a primeira leitura (horas, minutos e segundos): ");
    for (int i = 0; i < 3; i++) {
        scanf("%i", &numero);
        novo->primeiro_horario[i] = numero;
    }
    getchar();

    printf("Informe o horário em que deve ser feita a segunda leitura (horas, minutos e segundos): ");
    for (int i = 0; i < 3; i++) {
        scanf("%i", &numero);
        novo->segundo_horario[i] = numero;
    }
    getchar();

    novo->proximo = NULL;

    return novo;
}

setor_t *novo_setor(void)
{
    setor_t *novo = NULL;

    novo = (setor_t*)malloc(sizeof(setor_t));

    novo->qtd_sensores_cadastrados = 0;

    printf("Informe o nome do setor: ");
    fgets(novo->nome, T_STR, stdin);
    retirar_enter(novo->nome);
    formatar_maiuscula(novo->nome);

    printf("Descrição do setor: ");
    fgets(novo->descricao, T_STR, stdin);
    retirar_enter(novo->descricao);
    formatar_maiuscula(novo->descricao);

    novo->proximo = NULL;

    return novo;
}

void inserir_sensor_na_lista(sensor_t **lista, sensor_t *novo)
{
    int id_do_sensor = 0;
    sensor_t *sensor = *lista;

    while(sensor != NULL) {
        id_do_sensor++;
        sensor = sensor->proximo;
    }

    novo->id = id_do_sensor + 1;

    novo->proximo = *lista;
    *lista = novo;
}

void inserir_setor_na_lista(setor_t **lista, setor_t *novo)
{
    int id_do_setor = 0;
    setor_t *setor = *lista;

    while(setor != NULL) {
        id_do_setor++;
        setor = setor->proximo;
    }

    novo->id = id_do_setor + 1;

    novo->proximo = *lista;
    *lista = novo;
}

void excluir_sensor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_setor, id_sensor;
    setor_t *aux = NULL;
    sensores_cadastrados_t *aux_2 = NULL, *sensor_anterior = NULL;

    listar_setores(lista_set);
    printf("Digite o ID do setor onde o sensor será removido:\n");
    printf(":::: ");
    scanf("%i", &id_setor);
    getchar();

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (setor->id == id_setor) {
            aux = setor;
            break;
        }
    }

    if (aux->sensores_nesse_setor == NULL) {
        printf("Este setor não possui sensores cadastrados.\n");
        return;
    }

    printf("SENSORES CADASTRADOS NESSE SETOR:\n\n");
    for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            if (sensor->id == cadastrados->id) {
                printf("Sensor de %s --> [ID:%i]\n", sensor->tipo, cadastrados->id);
            }
        }
    }

    printf("Digite o ID do sensor que será removido\n");
    printf(":::: ");
    scanf("%i", &id_sensor);
    getchar();

    for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
       if (cadastrados->id == id_sensor) {
           aux_2 = cadastrados;
           break;
       }
    }

    if (aux_2 == aux->sensores_nesse_setor) {
        aux->sensores_nesse_setor = aux_2->proximo;
    }
    else {
        sensor_anterior = anterior(aux->sensores_nesse_setor, aux_2);
        sensor_anterior->proximo = aux_2->proximo;
    }

    printf("O sensor foi removido.\n");
    free(aux_2);
    aux->qtd_sensores_cadastrados--;
}