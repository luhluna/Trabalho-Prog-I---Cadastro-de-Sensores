#include "../include/menus.h"
#include <stdio.h>

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