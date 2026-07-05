#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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

int menu_principal(void);
int menu_cadastro(void);
int menu_relatorios(void);
int menu_relatorios_sensores(void);
int menu_relatorios_leituras(void);
int menu_relatorios_variacao(void);
int menu_pesquisas(void);
sensor_t *novo_sensor(void);
setor_t *novo_setor(void);
void inserir_sensor_na_lista(sensor_t **lista, sensor_t *novo);
void inserir_setor_na_lista(setor_t **lista, setor_t *novo);
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
void pesquisa_setor(sensor_t *lista_sen, setor_t *lista_set);
sensor_t *pesquisa_sensor(string str, sensor_t *lista_sen); //Função Recursiva
void excluir_sensor(sensor_t *lista_sen, setor_t *lista_set);
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

int main()
{
    int opcao, opcao_1, opcao_2, opcao_3, opcao_4, opcao_5, opcao_6, opcao_7, opcao_8;
    sensor_t *lista_sensores = NULL, *sensor_novo = NULL;
    setor_t *lista_setores = NULL, *setor_novo = NULL, *aux = NULL;
    sensores_cadastrados_t *novo_cadastro = NULL;

    carregar_dados_bin(&lista_sensores, &lista_setores);
    srand(time(NULL));

    do {
        limpar_tela();
        opcao = menu_principal();

        switch (opcao) {

            case 1: do {

                        limpar_tela();
                        opcao_1 = menu_cadastro();

                        switch (opcao_1) {

                            case 1: limpar_tela();
                                    sensor_novo = novo_sensor();
                                    inserir_sensor_na_lista(&lista_sensores, sensor_novo);
                                    break;

                            case 2: limpar_tela();
                                    setor_novo = novo_setor();
                                    inserir_setor_na_lista(&lista_setores, setor_novo);
                                    break;    
                        }

                    } while (opcao_1 != 0); 
                    break;

            case 2: limpar_tela();
                    printf("Digite o ID do setor onde você gostaria de adicionar sensores?\n");
                    printf("(É permitido adicionar até 3 sensores por setor)\n\n");
                    listar_setores(lista_setores);
                    printf("::::");
                    scanf("%i", &opcao_2);
                    
                    for (setor_t *setor = lista_setores; setor != NULL; setor = setor->proximo) {
                        if (setor->id == opcao_2) {
                            aux = setor;
                        } 
                    }

                    if (aux->qtd_sensores_cadastrados == MAX_S) {
                        printf("Este setor ja tem a quantidade máxima de sensores!\n\n");
                        voltar_menu();
                        break;
                    }

                    limpar_tela();
                        
                    do {
                        printf("Informe o ID:\n");
                        printf("(Digite '0' caso queira finalizar)\n\n");
                        listar_sensores(lista_sensores);
                        printf("::::");
                        scanf("%i", &opcao_3);

                        if (opcao_3 == 0) {
                            break;
                        }

                        novo_cadastro = (sensores_cadastrados_t*)malloc(sizeof(sensores_cadastrados_t));
                        novo_cadastro->id = opcao_3;
                        novo_cadastro->proximo = aux->sensores_nesse_setor;
                        aux->sensores_nesse_setor = novo_cadastro;
                        aux->qtd_sensores_cadastrados++;

                    } while (opcao_3 != 0 && aux->qtd_sensores_cadastrados < MAX_S);
                    break;

            case 3: do {
                        limpar_tela();
                        opcao_4 = menu_relatorios();

                        switch (opcao_4) {

                            case 1: do {
                                        limpar_tela();
                                        opcao_5 = menu_relatorios_sensores();

                                        switch (opcao_5) {

                                            case 1: limpar_tela();
                                                    relatorio_sensores_geral(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_sensores_tipo(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;
                                        }
                                    } while (opcao_5 != 0);
                                    break;

                            case 2: limpar_tela();
                                    relatorio_setores(lista_setores);
                                    voltar_menu();
                                    break;

                            case 3: do {
                                        limpar_tela();
                                        opcao_6 = menu_relatorios_leituras();

                                        switch (opcao_6) {

                                            case 1: limpar_tela();
                                                    relatorio_leituras_geral(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_leituras_setor(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;
                                        }
                                    } while (opcao_6 != 0);
                                    break;
                                
                            case 4: do {
                                        limpar_tela();
                                        opcao_7 = menu_relatorios_variacao();

                                        switch (opcao_7) {

                                            case 1: limpar_tela();
                                                    relatorio_variacao_geral(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_variacao_setor(lista_sensores, lista_setores);
                                                    voltar_menu();
                                                    break;
                                        }
                                    } while (opcao_7 != 0);
                                    break;

                            case 5: limpar_tela();
                                    relatorio_media(lista_sensores, lista_setores);
                                    voltar_menu();
                                    break;
                        }
                        
                    } while (opcao_4 != 0);
                    break;

            case 4: do {
                        limpar_tela();
                        opcao_8 = menu_pesquisas();

                        switch (opcao_8) {

                            case 1: limpar_tela();
                                    pesquisa_setor(lista_sensores, lista_setores);
                                    voltar_menu();
                                    break;

                            case 2: limpar_tela();
                                    string pesquisa;

                                    printf("Informe o nome do sensor procurado: ");
                                    fgets(pesquisa, T_STR, stdin);
                                    retirar_enter(pesquisa);
                                    formatar_maiuscula(pesquisa);

                                    sensor_t *sensor = pesquisa_sensor(pesquisa, lista_sensores);

                                    if (sensor) {
                                        printf("INFORMAÇÕES DO SENSOR %s:\n\n", sensor->tipo);
                                        printf("ID: %i\n", sensor->id);
                                        printf("Unidade de medida: %s\n", sensor->unidade_medida);
                                        printf("Valor máximo da faixa de leitura: %i\n", sensor->maximo_faixa_de_leitura); 
                                        printf("Valor mínimo da faixa de leitura: %i\n", sensor->minimo_faixa_de_leitura); 
                                        printf("Horário da primeira leitura: %i:%i:%i\n", sensor->primeiro_horario[0], sensor->primeiro_horario[1], sensor->primeiro_horario[2]);
                                        printf("Horário da segunda leitura: %i:%i:%i\n", sensor->segundo_horario[0], sensor->segundo_horario[1], sensor->segundo_horario[2]);
                                    }
                                    else {
                                        printf("O sensor informado não existe!");
                                    }

                                    voltar_menu();
                                    break;
                        }
                    } while (opcao_8 != 0);
                    break;

            case 5: limpar_tela();
                    excluir_sensor(lista_sensores, lista_setores);
                    voltar_menu();
                    break;
                    
            case 6: exportar_html(lista_sensores, lista_setores);
                    break;
        }
    } while (opcao != 0); 

    salvar_dados_bin(lista_sensores, lista_setores);
    return 0;
}

int menu_principal(void)
{
    int opcao;

    printf("|-----------------------------------|\n");
    printf("|    PROGRAMA PARA MONITORAMENTO    |\n");
    printf("|     DE AMBIENTES COM SENSORES     |\n");
    printf("|-----------------------------------|\n\n");
    printf("1.Adicionar novos sensores ou setores\n");
    printf("2.Cadastrar sensores em um setor\n");
    printf("3.Emitir relatórios\n");
    printf("4.Pesquisar setor ou sensor\n");
    printf("5.Excluir sensor cadastrado em um setor\n");
    printf("6.Exportar html sensores e setores\n");
    printf("0.Sair do programa\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_cadastro(void)
{
    int opcao;

    printf("ESCOLHA SUA OPÇÃO:\n\n");
    printf("1.Cadastrar novo sensor\n");
    printf("2.Cadastrar novo setor\n");
    printf("0.Voltar para o menu principal\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_relatorios(void)
{
    int opcao;

    printf("QUAL TIPO DE RELATÓRIO VOCÊ PROCURA?\n");
    printf("1.Relatório de sensores (geral ou por tipo)\n");
    printf("2.Relatório de setores\n");
    printf("3.Relatório de leituras (geral ou por setor)\n");
    printf("4.Relatório de variação de leituras (geral ou por setor)\n");
    printf("5.Relatório de médias de leitura por tipo de sensor\n");
    printf("0.Voltar para o menu principal\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_relatorios_sensores(void)
{
    int opcao;

    printf("ESCOLHA SUA OPÇÃO:\n\n");
    printf("1.Emitir relatório geral de sensores\n");
    printf("2.Emitir relatório de sensores por tipo\n");
    printf("0.Voltar para a seção de relatórios\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_relatorios_leituras(void)
{
    int opcao;

    printf("ESCOLHA SUA OPÇÃO:\n\n");
    printf("1.Emitir relatório de leituras geral\n");
    printf("2.Emitir relatório de leituras por setor\n");
    printf("0.Voltar para a seção de relatórios\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_relatorios_variacao(void)
{
    int opcao;

    printf("ESCOLHA SUA OPÇÃO:\n\n");
    printf("1.Emitir relatório de variação de leituras geral\n");
    printf("2.Emitir relatório de variação de leituras por setor\n");
    printf("0.Voltar para a seção de relatórios\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_pesquisas(void)
{
    int opcao;

    printf("ESCOLHA SUA OPÇÃO:\n\n");
    printf("1.Pesquisar setor por nome\n");
    printf("2.Pesquisar sensor por nome\n");
    printf("0.Voltar para a seção de relatórios\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

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

void excluir_sensor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_setor, id_sensor;
    setor_t *aux = NULL;
    sensores_cadastrados_t *aux_2 = NULL, *sensor_anterior = NULL;

    listar_setores(lista_set);
    printf("Digite o ID do setor onde o sensor será removido:\n");
    printf(":::: ");
    scanf("%i", &id_setor);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (setor->id == id_setor) {
            aux = setor;
            break;
        }
    }

    if (aux->sensores_nesse_setor == NULL) {
        printf("Este setor não possui sensores cadastrados.\n");
        voltar_menu();
        return;
    }

    listar_sensores(lista_sen);
    printf("Digite o ID do sensor que será removido\n");
    printf(":::: ");
    scanf("%i", &id_sensor);

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
    printf("2.Arquivo texto\n");
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