#include "../include/utils.h"
#include "../include/cadastros.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

sensores_cadastrados_t *anterior(sensores_cadastrados_t *lista, sensores_cadastrados_t *no)
{
    while (lista) {
        if (lista->proximo == no) return lista;
        lista = lista->proximo;
    }

    return NULL;
}

void retirar_enter(string str)
{
    str[strlen(str)-1] = '\0';
}

void formatar_maiuscula(string str)
{
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

int gerar_leitura(int numero_max, int numero_min)
{
    int leitura;

    leitura = (rand() % numero_max - numero_min +1) + numero_min;

    return leitura;
}

void limpar_tela(void)
{
    system("clear");
}

void voltar_menu(void)
{
    int voltar;

    printf("\n(Digite 0 seguido de ENTER para voltar ao menu anterior)\n");
    scanf("%i", &voltar);
}

void salvar_dados_bin(sensor_t *lista_sen, setor_t *lista_set)
{
    FILE *fp_sensores = NULL;
    FILE *fp_setores = NULL;


    fp_sensores = fopen("sensores.bin", "wb");

    while (lista_sen) {
        fwrite(lista_sen, sizeof(sensor_t), 1, fp_sensores);
        lista_sen = lista_sen->proximo; 
    }

    fclose(fp_sensores);

    fp_setores = fopen("setores.bin", "wb");

    while (lista_set) {
        fwrite(lista_set, sizeof(setor_t), 1, fp_setores);
        for(sensores_cadastrados_t *cadastrados = lista_set->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
            fwrite(cadastrados, sizeof(sensores_cadastrados_t), 1, fp_setores);
        }
        lista_set = lista_set->proximo;
    }

    fclose(fp_setores);
}

void carregar_dados_bin(sensor_t **lista_sen, setor_t **lista_set)
{
    FILE *fp_sensores = NULL;
    FILE *fp_setores = NULL;
    sensor_t *sensor_novo = NULL;
    setor_t *setor_novo = NULL;
    sensores_cadastrados_t *cadastro_novo = NULL;
    int qtd;

    fp_sensores = fopen("sensores.bin", "rb");

    if (fp_sensores != NULL) {
        while (!feof(fp_sensores)) {
            sensor_novo = (sensor_t*)malloc(sizeof(sensor_t));
            fread(sensor_novo, sizeof(sensor_t), 1, fp_sensores);
            sensor_novo->proximo = NULL;
            if (!feof(fp_sensores)) {
                inserir_sensor_na_lista(lista_sen, sensor_novo);
            }
            else {
                free(sensor_novo);
            }
        }

        fclose(fp_sensores);
    }

    fp_setores = fopen("setores.bin", "rb");

    if (fp_setores != NULL) {
        while (!feof(fp_setores)) {
            setor_novo = (setor_t*)malloc(sizeof(setor_t));
            fread(setor_novo, sizeof(setor_t), 1, fp_setores);
            setor_novo->sensores_nesse_setor = NULL;
            qtd = setor_novo->qtd_sensores_cadastrados;
            for (int i = 0; i < qtd; i++) {
                cadastro_novo = (sensores_cadastrados_t*)malloc(sizeof(sensores_cadastrados_t));
                fread(cadastro_novo, sizeof(sensores_cadastrados_t), 1, fp_setores);
                cadastro_novo->proximo = setor_novo->sensores_nesse_setor;
                setor_novo->sensores_nesse_setor = cadastro_novo;
            }
            setor_novo->proximo = NULL;
            if (!feof(fp_setores)) {
                inserir_setor_na_lista(lista_set, setor_novo);
            }
            else {
                free(setor_novo);
            }
        }

        fclose(fp_setores);
    }
}

void exportar_html(sensor_t *lista_sen, setor_t *lista_set)
{
    FILE *fp = NULL;

    fp = fopen("dados.html", "w");

    fprintf(fp, "<html><body>\n");
    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>ID do Sensor</th><th>Tipo do Sensor</th><th>Unidade de Medida</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    while (lista_sen) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%i</td>\n", lista_sen->id);
        fprintf(fp, "<td>%s</td>", lista_sen->tipo);
        fprintf(fp, "<td>%s</td>", lista_sen->unidade_medida);
        fprintf(fp, "</tr>\n");
        lista_sen = lista_sen->proximo;
    }

    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");

    fprintf(fp, "<table>\n");
    fprintf(fp, "<thead>\n");
    fprintf(fp, "<tr><th>ID do Setor</th><th>Nome do Setor</th><th>Descricao</th></tr>\n");
    fprintf(fp, "</thead>\n");
    fprintf(fp, "<tbody>\n");

    while (lista_set) {
        fprintf(fp, "<tr>\n");
        fprintf(fp, "<td>%i</td>\n", lista_set->id);
        fprintf(fp, "<td>%s</td>", lista_set->nome);
        fprintf(fp, "<td>%s</td>", lista_set->descricao);
        fprintf(fp, "</tr>\n");
        lista_set = lista_set->proximo;
    }
    
    fprintf(fp, "</tbody>\n");
    fprintf(fp, "</table>\n");
    fprintf(fp, "</body></html>\n");

    fclose(fp);
}

int opcao_arquivo(void)
{
    int opcao;

    printf("Emitir relatório na tela ou em arquivo .csv?\n");
    printf("1.Tela\n");
    printf("2.Arquivo .csv\n");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

void nome_arquivo(char *nome_arq)
{
    printf("Informe qual será o nome do arquivo: ");
    fgets(nome_arq, T_STR, stdin);
    retirar_enter(nome_arq);
    strcat(nome_arq, ".csv");
}