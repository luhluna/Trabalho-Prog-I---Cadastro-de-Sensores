#include "./include/menus.h"
#include "./include/cadastros.h"
#include "./include/relatorios.h"
#include "./include/utils.h"
#include "./include/pesquisas.h"
#include <stdio.h>

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