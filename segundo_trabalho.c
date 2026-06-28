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
    struct sensor *proximo;
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
void listar_setores_mais_descricao(setor_t *lista);
void relatorio_sensores_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_sensores_tipo(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_leituras_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_leituras_setor(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_variacao_geral(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_variacao_setor(sensor_t *lista_sen, setor_t *lista_set);
void relatorio_media(sensor_t *lista_sen, setor_t *lista_set);
//ate aq ok!!!
void pesquisa_setor(void);
void pesquisa_sensor(void);
//daq pra frente td certo
void retirar_enter(string str);
void formatar_maiuscula(string str);
int gerar_leitura(int numero_max, int numero_min);
void limpar_tela(void);
void voltar_menu(void);

int main()
{
    int opcao, opcao_1, opcao_2, opcao_3, opcao_4, opcao_5, opcao_6, opcao_7, opcao_8, aux;
    sensor_t *lista_sensores = NULL, *sensor_novo = NULL, *sensor = NULL;
    setor_t *lista_setores = NULL, *setor_novo = NULL, *setor = NULL;

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
                                    sensores[qtd_sensores] = novo_sensor();
                                    qtd_sensores++;
                                    break;

                            case 2: limpar_tela();
                                    setores[qtd_setores] = novo_setor();
                                    qtd_setores++;
                                    break;    
                        }

                    } while (opcao_1 != 0); 
                    break;

            case 2: limpar_tela();
                    printf("Digite o ID do setor onde você gostaria de adicionar sensores?\n");
                    printf("(É permitido adicionar até 3 sensores por setor)\n\n");
                    listar_setores();
                    printf("::::");
                    scanf("%i", &opcao_2);
                    
                    for (int i = 0; i < qtd_setores; i++) {
                        if (setores[i].id == opcao_2) {
                            aux = i;
                        } 
                    }

                    if (setores[aux].qtd_sensores_cadastrados == MAX_S) {
                        printf("Este setor ja tem a quantidade máxima de sensores!\n\n");
                        voltar_menu();
                        break;
                    }

                    limpar_tela();
                        
                    do {
                        printf("Informe o ID:\n");
                        printf("(Digite '0' caso queira finalizar)\n\n");
                        listar_sensores();
                        printf("::::");
                        scanf("%i", &opcao_3);

                        if (opcao_3 == 0) {
                            break;
                        }

                        setores[aux].sensor[setores[aux].qtd_sensores_cadastrados] = opcao_3;
                        setores[aux].qtd_sensores_cadastrados++;  

                    } while (opcao_3 != 0 && setores[aux].qtd_sensores_cadastrados < MAX_S);
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
                                                    relatorio_sensores_geral();
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_sensores_tipo();
                                                    voltar_menu();
                                                    break;
                                        }
                                    } while (opcao_5 != 0);
                                    break;

                            case 2: limpar_tela();
                                    listar_setores_mais_descricao();
                                    voltar_menu();
                                    break;

                            case 3: do {
                                        limpar_tela();
                                        opcao_6 = menu_relatorios_leituras();

                                        switch (opcao_6) {

                                            case 1: limpar_tela();
                                                    relatorio_leituras_geral();
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_leituras_setor();
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
                                                    relatorio_variacao_geral();
                                                    voltar_menu();
                                                    break;

                                            case 2: limpar_tela();
                                                    relatorio_variacao_setor();
                                                    voltar_menu();
                                                    break;
                                        }
                                    } while (opcao_7 != 0);
                                    break;

                            case 5: limpar_tela();
                                    relatorio_media();
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
                                    pesquisa_setor();
                                    voltar_menu();
                                    break;

                            case 2: limpar_tela();
                                    pesquisa_sensor();
                                    voltar_menu();
                                    break;
                        }
                    } while (opcao_8 != 0);
                    break;
        }
    } while (opcao != 0); 

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
    
    sensor.id = qtd_sensores+1;

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

    novo->id = qtd_setores+1;
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
    novo->proximo = *lista;
    *lista = novo;
}

void inserir_setor_na_lista(setor_t **lista, setor_t *novo)
{
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

void listar_setores_mais_descricao(setor_t *lista)
{
    printf("LISTA DE SETORES CADASTRADOS:\n\n");

    for (int i = 0; i < qtd_setores; i++) {
        printf("%s -->[ID:%i] (%s)\n", lista->nome, lista->id, lista->descricao);
    }
}

void relatorio_sensores_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    printf("RELATÓRIO DE SENSORES:\n\n");

    for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
        for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
            for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor, cadastrados != NULL; cadastrados = cadastrados->proximo) {
                if (sensor->id == cadastrados->id) {
                printf("Sensor de %s (medido em %s)-->[ID:%i] no setor: %s\n", sensor->tipo, sensor->unidade_medida, sensor->id, setor->nome);
                }
            }
        }
    }    
}

void relatorio_sensores_tipo(sensor_t *lista_sen, setor_t *lista_set)
{   
    int id_tipo;
    sensor_t *aux = NULL;

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

    printf("O SENSOR DE %s ESTA CADASTRADO NOS SEGUINTES AMBIENTES:\n\n", aux->tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
            if (aux->id == cadastrados->id) {
                printf("--> %s\n", setor->nome);
            }
        }
    } 
}

void relatorio_leituras_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    int primeira_leitura, segunda_leitura;

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

void relatorio_leituras_setor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura;
    setor_t *aux = NULL;

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

void relatorio_variacao_geral(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, variacao;
    sensor_t *aux = NULL;

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

    printf("RELATÓRIO DE VARIAÇÃO DE LEITURAS DO SENSOR DE %s\n\n", aux->tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        for (sensores_cadastrados_t *cadastrados = setor->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
            if (aux->id == cadastrados->id) {
                printf("Sensor de %s no setor: %s\n", sensor->tipo, setor->nome);

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

void relatorio_variacao_setor(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, variacao;
    setor_t *aux;

    printf("Digite o ID do setor o qual você quer emitir o relatório de variação de leituras:\n\n"); 
    listar_setores();
    printf("::::");
    scanf("%i", &id_tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        if (id_tipo == setor->id) {
            aux = setor;
            break;
        }
    }

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

void relatorio_media(sensor_t *lista_sen, setor_t *lista_set)
{
    int id_tipo, primeira_leitura, segunda_leitura, soma, soma_1 = 0, soma_2 = 0, qtd = 0;
    float media;
    sensor_t *aux = NULL;

    printf("Digite o ID do sensor o qual você quer emitir o relatório de média de leituras:\n\n"); 
    listar_sensores();
    printf("::::");
    scanf("%i", &id_tipo);

    for (sensor_t *sensor = lista_sen; sensor != NULL; sensor = sensor->proximo) {
        if (id_tipo == sensor->id) {
            aux = sensor;
            break;
        }
    }

    printf("LEITURAS DO SENSOR DE %s:\n\n", aux->tipo);

    for (setor_t *setor = lista_set; setor != NULL; setor = setor->proximo) {
        for (sensores_cadastrados_t *cadastrados = aux->sensores_nesse_setor; cadastrados != NULL; cadastrados = cadastrados->proximo) {
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

void pesquisa_setor(void)
{
    int aux = 0;
    string pesquisa;

    printf("Informe o nome do setor procurado: ");
    fgets(pesquisa, T_STR, stdin);
    retirar_enter(pesquisa);
    formatar_maiuscula(pesquisa);
    printf("\n");

    for (int i = 0; i < qtd_setores; i++) {
        if (strcmp(pesquisa, setores[i].nome) == 0) {
            aux = 1;

            printf("INFORMAÇÕES DO SETOR %s:\n\n", setores[i].nome);
            printf("ID: %i\n", setores[i].id);
            printf("Descrição: %s\n", setores[i].descricao);
            printf("Sensores cadastrados:\n"); 

            for (int j = 0; j < setores[i].qtd_sensores_cadastrados; j++) {
                for (int k = 0; k < qtd_sensores; k++) {
                    if (sensores[k].id == setores[i].sensor[j]) {
                        printf("- Sensor de %s\n", sensores[k].tipo);
                    }
                }
            }
        } 
    }  

    if (aux == 0) printf("O setor informado não existe!");
}

void pesquisa_sensor(void)
{
    int aux = 0;
    string pesquisa;

    printf("Informe o nome do sensor procurado: ");
    fgets(pesquisa, T_STR, stdin);
    retirar_enter(pesquisa);
    formatar_maiuscula(pesquisa);
    printf("\n");

    for (int i = 0; i < qtd_sensores; i++) {
        if (strcmp(pesquisa, sensores[i].tipo) == 0) {
            aux = 1;

            printf("INFORMAÇÕES DO SENSOR %s:\n\n", sensores[i].tipo);
            printf("ID: %i\n", sensores[i].id);
            printf("Unidade de medida: %s\n", sensores[i].unidade_medida);
            printf("Valor máximo da faixa de leitura: %i\n", sensores[i].maximo_faixa_de_leitura); 
            printf("Horário da primeira leitura: %i:%i:%i\n", sensores[i].primeiro_horario[0], sensores[i].primeiro_horario[1], sensores[i].primeiro_horario[2]);
            printf("Horário da segunda leitura: %i:%i:%i\n", sensores[i].segundo_horario[0], sensores[i].segundo_horario[1], sensores[i].segundo_horario[2]);
        } 
    }  

    if (aux == 0) printf("O sensor informado não existe!");
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