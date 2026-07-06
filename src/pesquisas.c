#include "../include/pesquisas.h"
#include "../include/utils.h"

void pesquisa_setor( sensor_t *lista_sen, setor_t *lista_set)
{
    int aux = 0;
    string pesquisa;

    printf("Informe o nome do setor procurado: ");
    fgets(pesquisa, T_STR, stdin);
    retirar_enter(pesquisa);
    formatar_maiuscula(pesquisa);
    printf("\n");

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (strcmp(pesquisa, setor->nome) == 0) {
            aux = 1;

            printf("INFORMAÇÕES DO SETOR %s:\n\n", setor->nome);
            printf("ID: %i\n", setor->id);
            printf("Descrição: %s\n", setor->descricao);
            printf("Sensores cadastrados:\n"); 

            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
                    if (sensor->id == cadastrados->id) {
                        printf("- Sensor de %s\n", sensor->tipo);
                    }
                }
            }
        } 
    }  

    if (aux == 0) printf("O setor informado não existe!");
}

sensor_t *pesquisa_sensor(string str, sensor_t *lista_sen)
{
    if(!lista_sen) return NULL;
    if(strcmp(lista_sen->tipo, str) == 0) return lista_sen;
    return pesquisa_sensor(str, lista_sen->proximo);
}