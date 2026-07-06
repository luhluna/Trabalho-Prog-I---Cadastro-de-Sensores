#include "../include/relatorios.h"
#include "../include/utils.h"
#include <stdio.h>

void listar_sensores(sensor_t *lista)
{
    printf("LISTA DE SENSORES CADASTRADOS:\n\n");

    for (lista; lista != NULL; lista = lista->proximo) {
        printf("Sensor de %s (medido em %s)-->[ID:%i]\n", lista->tipo, lista->unidade_medida, lista->id);
    }
}

void listar_setores(setor_t *lista)
{
    printf("LISTA DE SETORES CADASTRADOS:\n\n");

    for (lista; lista != NULL; lista = lista->proximo) {
        printf("%s -->[ID:%i]\n", lista->nome, lista->id);
    }
}

void relatorio_setores(setor_t *lista)
{
    int opcao;
    string nome_arq;
    FILE *fp = NULL;

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("LISTA DE SETORES CADASTRADOS:\n\n");

        for (lista; lista != NULL; lista = lista->proximo) {
            printf("%s -->[ID:%i] (%s)\n", lista->nome, lista->id, lista->descricao);
        }
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "NOME;ID;DESCRIÇÃO\n");

        for (lista; lista != NULL; lista = lista->proximo) {
            fprintf(fp, "%s;%i;%s\n", lista->nome, lista->id, lista->descricao);
        }

        fclose(fp);
    }
}

void relatorio_sensores_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    int opcao;
    string nome_arq;
    FILE *fp = NULL;

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("RELATÓRIO DE SENSORES:\n\n");

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
                for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                    if (sensor->id == cadastrados->id) {
                    printf("Sensor de %s (medido em %s)-->[ID:%i] no setor: %s\n", sensor->tipo, sensor->unidade_medida, sensor->id, setor->nome);
                    }
                }
            }
        }    
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "TIPO;UNIDADE DE MEDIDA;ID;SETOR\n");

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
                for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                    if (sensor->id == cadastrados->id) {
                    fprintf(fp, "%s;%s;%i;%s\n", sensor->tipo, sensor->unidade_medida, sensor->id, setor->nome);
                    }
                }
            }
        } 
        
        fclose(fp);
    } 
}

void relatorio_sensores_tipo(sensor_t *lista_sen, setor_t *lista_set)
{   
    int id_tipo, opcao;
    sensor_t *aux = NULL;
    FILE *fp = NULL;
    string nome_arq;

    printf("Digite o ID do sensor o qual você quer emitir o relatório:\n\n"); 
    listar_sensores(lista_sen);
    printf("::::");
    scanf("%i", &id_tipo);

    for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
        if (id_tipo == sensor->id) {
            aux = sensor;
            break;
        }
    }

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("O SENSOR DE %s ESTA CADASTRADO NOS SEGUINTES AMBIENTES:\n\n", aux->tipo);

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    printf("--> %s\n", setor->nome);
                }
            }
        }
    } 
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SENSOR;NOME\n");

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    fprintf(fp, "%s;%s\n", aux->tipo, setor->nome);
                }
            }
        }

        fclose(fp);
    } 
}

void relatorio_leituras_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    int primeira_leitura, segunda_leitura, opcao;
    FILE *fp = NULL;
    string nome_arq;

    opcao = opcao_arquivo();

    if (opcao == 1) {
    printf("RELATÓRIO DE LEITURAS GERAL:\n\n");

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
                for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                    if (sensor->id == cadastrados->id) {
                    printf("Sensor de %s (medido em %s)-->[ID:%i] no setor: %s:\n", sensor->tipo, sensor->unidade_medida, sensor->id, setor->nome);
                    
                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);

                    printf("Horário da primeira leitura: %i:%i:%i\n", sensor->primeiro_horario[0], sensor->primeiro_horario[1], sensor->primeiro_horario[2]);
                    printf("Primeira leitura: %i %s\n",  primeira_leitura, sensor->unidade_medida);
                    printf("Horário da segunda leitura: %i:%i:%i\n", sensor->segundo_horario[0], sensor->segundo_horario[1], sensor->segundo_horario[2]);
                    printf("Segunda leitura: %i %s\n\n",  segunda_leitura, sensor->unidade_medida);
                    }
                }
            }
        } 
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SENSOR;SETOR;HORA PRIMEIRA LEITURA;PRIMEIRA LEITURA;HORA SEGUNDA LEITURA;SEGUNDA LEITURA\n");

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
                for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                    if (sensor->id == cadastrados->id) {
                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);

                    fprintf(fp, "%s;%s;%i:%i:%i;%i %s;%i:%i:%i;%i %s\n", sensor->tipo, setor->nome, sensor->primeiro_horario[0], sensor->primeiro_horario[1], sensor->primeiro_horario[2], primeira_leitura, sensor->unidade_medida, sensor->segundo_horario[0], sensor->segundo_horario[1], sensor->segundo_horario[2], segunda_leitura, sensor->unidade_medida);
                    }
                }
            }
        }

        fclose(fp); 
    }   
}

void relatorio_leituras_setor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, opcao;
    setor_t *aux = NULL;
    FILE *fp = NULL;
    string nome_arq;

    printf("Digite o ID do setor o qual você quer emitir o relatório de leituras:\n\n"); 
    listar_setores(lista_set);
    printf("::::");
    scanf("%i", &id_tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (id_tipo == setor->id) {
            aux = setor;
            break;
        }
    }
    
    opcao = opcao_arquivo();
    if (opcao == 1) {
        printf("RELATÓRIO DE LEITURAS DO SETOR %s:\n\n", aux->nome);

        for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
            for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
                if (cadastrados->id == sensor->id) {
                    printf("Sensor de %s:\n", sensor->tipo);

                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);

                    printf("Horário da primeira leitura: %i:%i:%i\n", sensor->primeiro_horario[0], sensor->primeiro_horario[1], sensor->primeiro_horario[2]);
                    printf("Primeira leitura: %i %s\n",  primeira_leitura, sensor->unidade_medida);
                    printf("Horário da segunda leitura: %i:%i:%i\n", sensor->segundo_horario[0], sensor->segundo_horario[1], sensor->segundo_horario[2]);
                    printf("Segunda leitura: %i %s\n\n",  segunda_leitura, sensor->unidade_medida);
                }
            }
        }
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SENSOR;HORA PRIMEIRA LEITURA;PRIMEIRA LEITURA;HORA SEGUNDA LEITURA;SEGUNDA LEITURA\n");

        for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
            for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
                if (cadastrados->id == sensor->id) {
                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);

                    fprintf(fp, "%s;%i:%i:%i;%i %s;%i:%i:%i;%i %s\n", sensor->tipo, sensor->primeiro_horario[0], sensor->primeiro_horario[1], sensor->primeiro_horario[2], primeira_leitura, sensor->unidade_medida, sensor->segundo_horario[0], sensor->segundo_horario[1], sensor->segundo_horario[2], segunda_leitura, sensor->unidade_medida);
                }
            }
        }

        fclose(fp);
    } 
}

void relatorio_variacao_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, variacao, opcao;
    sensor_t *aux = NULL;
    FILE *fp = NULL;
    string nome_arq;

    printf("Digite o ID do sensor o qual você quer emitir o relatório de variação de leituras:\n\n"); 
    listar_sensores(lista_sen);
    printf("::::");
    scanf("%i", &id_tipo);

    for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
        if (id_tipo == sensor->id) {
            aux = sensor;
            break;
        }
    }

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("RELATÓRIO DE VARIAÇÃO DE LEITURAS DO SENSOR DE %s\n\n", aux->tipo);

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    printf("Sensor de %s no setor: %s\n", aux->tipo, setor->nome);

                    primeira_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);

                    printf("Primeira Leitura: %i\n", primeira_leitura);
                    printf("Segunda Leitura: %i\n", segunda_leitura);

                    variacao = (primeira_leitura - segunda_leitura);

                    printf("Variação entre a primeira e a segunda leitura: %i\n\n", variacao);
                }
            }
        } 
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SENSOR;SETOR;PRIMEIRA LEITURA;SEGUNDA LEITURA;VARIAÇÃO\n");

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    primeira_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    variacao = (primeira_leitura - segunda_leitura);

                    fprintf(fp, "%s;%s;%i %s;%i %s;%i\n", aux->tipo, setor->nome, primeira_leitura, aux->unidade_medida, segunda_leitura, aux->unidade_medida, variacao);
                }
            }
        } 

        fclose(fp);
    }
}

void relatorio_variacao_setor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, variacao, opcao;
    setor_t *aux;
    FILE *fp = NULL;
    string nome_arq;

    printf("Digite o ID do setor o qual você quer emitir o relatório de variação de leituras:\n\n"); 
    listar_setores(lista_set);
    printf("::::");
    scanf("%i", &id_tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (id_tipo == setor->id) {
            aux = setor;
            break;
        }
    }

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("RELATÓRIO DE VARIAÇÃO DE LEITURAS DOS SENSORES DO SETOR %s\n\n", aux->nome);

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (sensor->id == cadastrados->id) {
                    printf("- Sensor de %s\n", sensor->tipo);

                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);

                    printf("Primeira Leitura: %i\n", primeira_leitura);
                    printf("Segunda Leitura: %i\n", segunda_leitura);

                    variacao = (primeira_leitura - segunda_leitura);

                    printf("Variação entre a primeira e a segunda leitura: %i\n\n", variacao);
                }
            }
        }
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SETOR;SENSOR;PRIMEIRA LEITURA;SEGUNDA LEITURA;VARIAÇÃO\n");

        for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
            for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (sensor->id == cadastrados->id) {
                    primeira_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(sensor->maximo_faixa_de_leitura, sensor->minimo_faixa_de_leitura);
                    variacao = (primeira_leitura - segunda_leitura);

                    fprintf(fp, "%s;%s;%i %s;%i %s;%i\n", aux->nome, sensor->tipo, primeira_leitura, sensor->unidade_medida, segunda_leitura, sensor->unidade_medida, variacao);
                }
            }
        }
        
        fclose(fp);
    }
}

void relatorio_media(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, soma, soma_1 = 0, soma_2 = 0, qtd = 0, opcao;
    float media;
    sensor_t *aux = NULL;
    FILE *fp = NULL;
    string nome_arq;

    printf("Digite o ID do sensor o qual você quer emitir o relatório de média de leituras:\n\n"); 
    listar_sensores(lista_sen);
    printf("::::");
    scanf("%i", &id_tipo);

    for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
        if (id_tipo == sensor->id) {
            aux = sensor;
            break;
        }
    }

    opcao = opcao_arquivo();

    if (opcao == 1) {
        printf("LEITURAS DO SENSOR DE %s:\n\n", aux->tipo);

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    qtd++;
                    primeira_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    soma_1 += primeira_leitura;
                    soma_2 += segunda_leitura;

                    printf("Sensor de %s no setor: %s\n", aux->tipo, setor->nome);
                    printf("Primeira Leitura: %i\n", primeira_leitura);
                    printf("Segunda Leitura: %i\n\n", segunda_leitura);
                }
            }
        } 

        soma = (soma_1 + soma_2);
        media = ((float)soma / (qtd * 2));

        printf("MÉDIA DE LEITURAS DO SENSOR DE %s: %.2f %s\n\n", aux->tipo, media, aux->unidade_medida);
    }
    else {
        nome_arquivo(nome_arq);
        fp = fopen(nome_arq, "w");

        fprintf(fp, "SENSOR;SETOR;PRIMEIRA LEITURA;SEGUNDA LEITURA\n");

        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (aux->id == cadastrados->id) {
                    qtd++;
                    primeira_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    segunda_leitura = gerar_leitura(aux->maximo_faixa_de_leitura, aux->minimo_faixa_de_leitura);
                    soma_1 += primeira_leitura;
                    soma_2 += segunda_leitura;

                    fprintf(fp, "%s;%s;%i;%i\n", aux->tipo, setor->nome, primeira_leitura, segunda_leitura);
                }
            }
        } 

        soma = (soma_1 + soma_2);
        media = ((float)soma / (qtd * 2));

        fprintf(fp, "\nMÉDIA DE LEITURAS DO SENSOR DE %s: %.2f %s\n", aux->tipo, media, aux->unidade_medida);

        fclose(fp);
    }
}