// Arquivo Principal

// Biblioteca com as função para treino e teste da RNA
#include <locale.h>
#include "funcs.c"
#include "menus.c"


int main(int argc, char *argv[]) {

    // Configurando ambiente

    setlocale(LC_ALL, "Portuguese");

    MenuApresentacao();

    // Declaração das variáveis
    char trainingFileName[30];
    char testFileName[30];
    FILE* trainingFile;
    FILE* testFile;
    int neurCamEntrada;
    int neurCamSaida;
    int neurCamOculta;
    int i = 0;
    char n[4];
    char val[3];
    char line[150];
    char *valor;
    char *valueAnt;
    char resp;
    int qtdAmostras = -1;
    int colum = 0;
    int row = 0;
    int **matrizAmostras;
    int **matrizAmostrasTeste;
    double erLimiar;
    int numIteracoes;
    char op;


    // Abrindo o arquivos de teste e de treino
    if(argc == 1) { // Necessita do nome do arquivo
        printf("Voce tambem pode entrar com o nome do arquivo direto nos argumentos. \nEx: ./Backpropagation treinamento.csv teste.csv\n\n");
        printf("Nome do arquivo de treino: ");
        setbuf(stdin, NULL); scanf("%s", trainingFileName);
        printf("Abrindo arquivo: %s \n", trainingFileName);

        printf("Nome do arquivo de teste: ");
        setbuf(stdin, NULL); scanf("%s", testFileName);
        printf("Abrindo arquivo: %s \n", testFileName);

    } else if(argc > 1) { // Abre arquivo por parâmetro

        strcpy(trainingFileName, argv[1]);
        printf("Abrindo arquivo treino: %s \n", trainingFileName);

        strcpy(testFileName, argv[2]);
        printf("Abrindo arquivo teste: %s \n", testFileName);

    } else return printf("Argumentos inválidos :( \n");

    if(!(trainingFile = fopen(trainingFileName, "r")))
        return printf("Arquivo treino não encontrado! :( \n");
    if(!(testFile = fopen(testFileName, "r")))
        return printf("Arquivo teste não encontrado! :( \n");
    printf("Arquivo aberto. \n");


    // Verificando a quantidade de neuronios na camada de entrada
    while (fgets(val, 4, trainingFile) != NULL) {
        i++;
        if (val[2] != ',') {
            neurCamEntrada = i - 1;
            fgets(val, 4, trainingFile);
            break;
        }
    }

    //Verificando a quantidade de neuronios na camada de saida
    while (fgets(line, sizeof(line), trainingFile)) {
        valor = strtok(line, ",");
        while (valor != NULL) {
            valueAnt = valor;
            valor = strtok(NULL, ",");
        }
        qtdAmostras++;
    }
    neurCamSaida = valueAnt[0] - '0';

    // Verificando a quantidade de neuronios na camada oculta de maneira automatica
    neurCamOculta = abs(sqrt(neurCamEntrada * neurCamSaida));

    // Criando a matriz com as amostras de treinamento

    matriz_amostras = (int **) malloc(qtdAmostras * sizeof(sizeof(int *)));
    rewind(trainingFile);
    fgets(line, sizeof(line), trainingFile);
    while (fgets(line, sizeof(line), trainingFile)) {

        valor = strtok(line, ",");
        matrizAmostras[row] = (int *) malloc((neurCamEntrada + 1) * sizeof(int));
        while (valor != NULL && colum <= neurCamEntrada) {
            matrizAmostras[row][colum] = atoi(valor);
            valor = strtok(NULL, ",");
            colum++;
        }
        colum = 0;
        row++;
        if(row == qtdAmostras) break;
    }

    EmbaralharLinhas(matriz_amostras, qtdAmostras); // Embaralhar linhas para desagrupar as classes


    // Criando a matriz com as amostras de teste
    qtdAmostras = -1;

    while (fgets(line, sizeof(line), testFile)) qtdAmostras++;
    matriz_amostras_teste = (int **) malloc(qtdAmostras * sizeof(sizeof(int *)));
    rewind(testFile); row = colum = 0;
    fgets(line, sizeof(line), testFile);


    while (fgets(line, sizeof(line), testFile)) {
        valor = strtok(line, ",");
        matrizAmostrasTeste[row] = (int *) malloc((neurCamEntrada + 1) * sizeof(int));
        while (valor != NULL && colum < neurCamEntrada + 1) {
            matrizAmostrasTeste[row][colum] = atoi(valor);
            valor = strtok(NULL, ",");
            colum++;
        }
        colum = 0;
        row++;
        if(row == qtdAmostras) break;
    }

    //Criando a matriz de confusão
    int **matriz_confusao = (int **) malloc(neurCamSaida * sizeof(sizeof(int *)));
    for (i=0; i < neurCamSaida; i++) {
        matriz_confusao[i] = (int *) malloc(neurCamSaida * sizeof(int));
        for (int j=0; j < neurCamSaida; j++) matriz_confusao[i][j] = 0;
    }

    do {
        // Exibindo algumas informacoes
        ExibeInfoNeuronios(qtdAmostras, neurCamEntrada, neurCamSaida, neurCamOculta);

        // Configuração manual do numero de neuronios na camada oculta
        printf("Deseja alterar o numero de neuronios na camada oculta? [S,n]: ");
        setbuf(stdin, NULL); scanf("%c", &resp);
        resp = toupper(resp);

        if (resp == 'S') {
            printf("Entre com o novo numero de neuronios na camada oculta: ");
            setbuf(stdin, NULL); scanf("%i", &neurCamOculta);
        } else if (resp != 'N') return printf("Opcao invalida :( \n");
        printf("Numero de Neuronios na Camada Oculta: %i \n", neurCamOculta);


        // Verificando a função de transferência desejada
        do {
            MenuEscolhaFuncao();
            setbuf(stdin, NULL); scanf("%i", &opcoes[0]);
        } while (opcoes[0] != 1 && opcoes[0] != 2);

        // Verificando a condição de parada do treinamento
        MenuEscolhaParada();
        setbuf(stdin, NULL); scanf("%i", &opcoes[1]);

        if (opcoes[1] == 1) { // Erro max.
            printf("Entre com o valor do erro maximo: ");

            setbuf(stdin, NULL); scanf("%lf", &erLimiar);
        } else if (opcoes[1] != 2) return printf("Opcao invalida :( \n");
        else {  // Quant iteracoes
            printf("Entre com o valor maximo de iterações: ");
            setbuf(stdin, NULL); scanf("%d", &numIteracoes);
        }

        // Setando tx de aprendizado (n)                ;
        printf("Entre com uma taxa de aprendizado [ex.: 0,01]: ");
        setbuf(stdin, NULL); scanf("%f", &tx_aprendizado);


        // Criando as matrizes com os pesos (linhas: cada nó, colum: valor respectivo da camada anterior)
        double **pesos_o;
        pesos_o = (double **) malloc(neurCamOculta * sizeof(sizeof(double *)));
        double **pesos_s;
        pesos_s = (double **) malloc(neurCamSaida * sizeof(sizeof(double *)));
        // Gerando pesos aleatórios [-0.5, +0.5]
        srand(time(NULL));
        for (int i=0; i < neurCamOculta; i++) {
            pesos_o[i] = (double *) malloc(neurCamEntrada * sizeof(double));
            for (int j=0; j < neurCamEntrada; j++)
                pesos_o[i][j] = (double)(rand())/(double)(RAND_MAX)*0.5 - (double)(rand())/(double)(RAND_MAX)*0.5;
        }
        for (int i=0; i < neurCamSaida; i++) {
            pesos_s[i] = (double *) malloc(neurCamOculta * sizeof(double));
            for (int j=0; j < neurCamOculta; j++)
                pesos_s[i][j] = (double)(rand())/(double)(RAND_MAX)*0.5 - (double)(rand())/(double)(RAND_MAX)*0.5;
        }

        // Exibindo as matrizes com seus pesos
        puts("\n");
        printf("Pesos iniciais gerados: \n");
        printf("Camada Oculta: \n");
        ExibeMatrizDouble(pesos_o, neurCamOculta, neurCamEntrada);
        puts("\n");
        printf("Camada de Saida: \n");
        ExibeMatrizDouble(pesos_s, neurCamSaida, neurCamOculta);

        // Loop com o treinamento  =====================================================================================
        int contador = 0;
        double erro; // Erro da rede
        int classe_posicao = neurCamEntrada;
        printf("\nTreinando...");
        do {    // Treina o conjunto de amostras até o limite estabelecido
            for (row=0; row < qtdAmostras; row++) // Passa toda a amostra no Backpropagation
                erro = Treinar(matrizAmostras[row], classe_posicao, pesos_o, pesos_s, neurCamEntrada, neurCamOculta, neurCamSaida);
            contador++;

            if (opcoes[1] == 1) { // erro max
                if(erro <= erLimiar)
                {
                    printf("\nErro maximo atingido\n");
                    printf("Erro da rede: %f\n", erro);
                    break;
                }
            } else { // num iter
                if (contador == numIteracoes) {
                    printf("\nNumero maximo de iteracoes alcancado\n");
                    printf("Erro da rede: %f\n", erro);
                    break;
                }
            }
        } while (1);

        // Exibe os pesos encontrados no treinamento
        ExibeFimTreinamento(contador);
        printf("Camada Oculta: \n");
        ExibeMatrizDouble(pesos_o, neurCamOculta, neurCamEntrada);
        puts("\n");
        printf("Camada de Saida: \n");
        ExibeMatrizDouble(pesos_s, neurCamSaida, neurCamOculta);
        puts("\n");

        // Teste da rede
        printf("\nProsseguindo com os testes da RNA Backpropagation\n");
        printf("Quantidade de amostras para o teste: %d \n", qtdAmostras);

        for (row=0; row < qtdAmostras; row++) // Testando a rede para cada amostra do conjunto de teste
            Testar(matriz_confusao, matrizAmostrasTeste[row], pesos_o, pesos_s, neurCamEntrada, neurCamOculta, neurCamSaida);

        // Exibindo matriz de confusão
        printf("\nMatriz de confusao obtida: \n");
        ExibeMatrizInt(matriz_confusao, neurCamSaida, neurCamSaida);

        // Pergunta se o usuario deseja realizar um novo teste
        printf("\n\nDeseja realizar o treinamento novamente? [S/n]:");
        setbuf(stdin, NULL); scanf("%c", &op); op =  toupper(op);

        // Limpa as matrizes com os pesos e zera a matriz de confusao
        for(row=0; row < neurCamOculta; row++) free(pesos_o[row]);
        for(row=0; row < neurCamSaida; row++) {
            free(pesos_s[row]);
            for(colum=0; colum < neurCamSaida; colum++) matriz_confusao[row][colum]=0;
        }
    } while(op == 'S');

    // Finalizando o programa
    printf("\nPrograma finalizdo;;; \n");
    fclose(trainingFile);
    fclose(testFile);

    system("PAUSE");
    return 0;
};
