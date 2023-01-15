#include <stdio.h>
#include "menus.h"

void MenuApresentacao(){
// Apresentação do programa
    printf("\n - Rede Neural Backpropagation\n");
    printf("\n - Trabalho Pratico - Inteligencia Artificial 2022");
    printf("\n - Aluno: Felipe Canuto, RA 171257375");
    printf("\n - Aluno: Heitor Gomes, RA 181255261");
    printf("\n - Professor: Almir O. Artero \n\n");
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

void ExibeFimTreinamento(int contador){
    printf("O treinamento finalizado! :D \n\n");
    printf("Num. de iteracoes realizadas: %d \n\n", contador);
    printf("Pesos finais obtidos: \n");
}