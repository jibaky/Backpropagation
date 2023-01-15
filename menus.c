//
// Created by Cpides on 15/01/2023.
//

#include <stdio.h>
#include "menus.h"

void MenuApresentacao(){
// Apresentação do programa
    printf(" ***************************************************        \n");
    printf("        ** RNA Backpropagation **                           \n");
    printf("                     2022                                   \n");
    printf("  - Trabalho Pratico - Inteligencia Artificial              \n");
    printf("  - Aluno: Felipe Sousa Canuto dos Santos, RA 171257375     \n");
    printf("  - Aluno: Heitor Daniel Vani Gomes, RA 181255261           \n");
    printf(" ***************************************************        \n");
}

void MenuEscolhaFuncao(){
    printf("\nQual funcao de transferencia deseja utilizar? \n");
    printf("\t 1 - Logistica \n");
    printf("\t 2 - Tangente Hiperbolica \n");
    printf("Opcao: ");
}

void MenuEscolhaParada(){
    printf("\nQual condicao de parada deseja utilizar? \n");
    printf("\t 1 - Erro Maximo \n");
    printf("\t 2 - Numero de Iteracoes \n");
    printf("Opcao: ");
}

void ExibeFimTreinamento(int i){
    printf("O treinamento finalizado! \n\n");
    printf("Num. de iteracoes realizadas: %d \n\n", i);
    printf("Pesos finais obtidos: \n");
}

void ExibeInfoNeuronios(int i, int in, int saida, int oculta){
    printf("\nInformacoes encontradas no conjunto de amostras: \n");
    printf("Quantidade de amostras no arquivo : %d \n", i);
    printf("Numero de Neuronios na Camada de Entrada: %i \n", in);
    printf("Numero de Neuronios na Camada de Saida: %i \n", saida);
    printf("Numero de Neurunios na Camada Oculta: %i \n\n", oculta);
}