//  =============================================================
//  <                       Conjuntos.h                         >
//  =============================================================

//  Blibliotecas Utilizadas:
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>

//  Definições de resultados:
    #define FALHA 0;
    #define FALSE 0;
    #define DECRESCENTE 0;
    #define SUCESSO 1;
    #define TRUE 1;
    #define CRESCENTE 1;

//  Estrutura de um conjunto:
    typedef struct {
        long int tamanho;
        unsigned long int *elementos;
    } Conjunto;

//  Protótipos das funções:
    int criaConjunto(Conjunto *);
    int conjuntoVazio(Conjunto *);
    int insereElementoConjunto(unsigned long int, Conjunto *);
    int excluirElementoConjunto (unsigned long int, Conjunto *);
    long int tamanhoConjunto(Conjunto *);
    long int maior(unsigned long int, Conjunto *);
    long int menor(unsigned long int, Conjunto *);
    int pertenceConjunto(unsigned long int, Conjunto *);
    int conjuntosIdenticos(Conjunto *, Conjunto *);
    int subconjunto(Conjunto *, Conjunto *);
    Conjunto *complemento(Conjunto *, Conjunto *);
    Conjunto *uniao(Conjunto *, Conjunto *);
    Conjunto *diferenca(Conjunto *, Conjunto *);
    void mostrarConjuntos(Conjunto *, int);
    void bubbleSort(Conjunto *, int);
    int copiarConjunto(Conjunto *, Conjunto *);
    int destruirConjunto(Conjunto *);




//    =============================================================
//    <                       Conjuntos.c                         >
//    =============================================================

//Cria um conjunto
int criaConjunto(Conjunto *C){
    if (C == NULL){
        //FALSE
        return FALHA;
    } else {
        //TRUE
        C->tamanho = 0;
        return SUCESSO;
    } 
}

//Verifica se um conjunto é vazio.
int conjuntoVazio(Conjunto *C) {
    return (C->tamanho == 0) ? 1 : 0;
}

//insere um elemento no conjunto.
int insereElementoConjunto(unsigned long int x, Conjunto *C){
    if (x > LONG_MAX){
        return FALHA;
    } 
    //percorre os elementos verificando se x ja pertence aos elementos.
    for (long int i = 0; i <= C->tamanho; i++){
        if(C->elementos[i] == x)
            //FALHA;
            return FALHA;
    }
    
    //faz uma alocação para aumentar de e somente se necessario o tamanho do vetor "elementos".
    C->tamanho++;
    C->elementos = (unsigned long int *)realloc(C->elementos, C->tamanho * sizeof(unsigned long int));
    C->elementos[C->tamanho-1] = x;
    //Verifica se existe espaço para a realocação.
    if(C->elementos == NULL){
        //FALSE
        return FALHA;
    } else {
        //TRUE
        return SUCESSO;
    }
}

//Exclui um elemento de um conjunto.
int excluirElementoConjunto (unsigned long int x, Conjunto *C){
    
    //percorre o vetor "elementos" para verificar se x pode ser excluído.
    for(long int i = 0; i < C->tamanho; i++){
        if (C->elementos[i] == x){

            //Faz uma realocação dos elementos para diminuir o tamanho do vetor (andando uma casa para trás).
            for (int j = i; j < C->tamanho; j++){
               C->elementos[j] = C->elementos[j+1];
                if(j == (C->tamanho-1)){

                    //Realocação dinamica para diminuir o tamanho do vetor.
                    C->tamanho--;
                    C->elementos = (unsigned long int *)realloc(C->elementos, C->tamanho * (sizeof(unsigned long int)));

                    //TRUE
                    return TRUE;
                }
            }
        } 
    }
    return FALSE;
}

//Mostra o tamanho do conjunto.
long int tamanhoConjunto(Conjunto *C){
    return (C != NULL) ? C->tamanho : 0; 
}

//Mostra a quantidade de elementos tem valor maior que um x qualquer.
long int maior(unsigned long int x, Conjunto *C){
    if (C != NULL){
        int maiores = 0;
        for(int i = 0; i < C->tamanho; i++){
            if (C->elementos[i] > x){
                maiores++;
            }
        }
        //TRUE
        return maiores;
    } else {
        //FALSE
        return FALSE;
    }
}

//Mostra a quantidade de elementos tem valor menor que um x qualquer.
long int menor(unsigned long int x, Conjunto *C){
    if (C != NULL){
        int menores = 0;
        for(int i = 0; i < C->tamanho; i++){
            if (C->elementos[i] < x){
                menores++;
            }
        }
        //TRUE
        return menores;
    } else {
        //FALSE
        return FALSE;
    }
}

//Verifica se um elemento pertence ao conjunto.
int pertenceConjunto(unsigned long int x, Conjunto *C){
    for(int i = 0; i <= C->tamanho; i++){
        if (C->elementos[i] == x){
            //TRUE
            return TRUE;
        }
    }
    //FALSE
    return FALSE;
}

//Verifica se os conjuntos possuem os mesmos elementos.
int conjuntosIdenticos(Conjunto *C1, Conjunto *C2){
    int quantNumIguais = 0;
    for(int i = 0; i < C1->tamanho; i++){
        for(int j = 0; j < C2->tamanho; j++){
            if (C1->elementos[i] == C2->elementos[j]){
                quantNumIguais++;
            }
        }
    }
    return (quantNumIguais == C1->tamanho && quantNumIguais == C2->tamanho) ? 1 : 0;
}

//Verifica se o 1º conjunto é subconjunto do 2º conjunto.
int subconjunto(Conjunto *C1, Conjunto *C2){
    int quantNumIguais = 0;
    for(int i = 0; i <= C1->tamanho; i++){
        for(int j = 0; j <= C2->tamanho; j++){
         if (C1->elementos[i] == C2->elementos[j]){
                quantNumIguais++;
            }
        }
    }
    return (quantNumIguais == C1->tamanho) ? 1 : 0;
}

//Mostra os elementos que estão no 2º conjunto mas não estão no 1º conjunto. 
Conjunto *complemento(Conjunto *C1, Conjunto *C2){
    Conjunto *complemento = (Conjunto *)malloc(sizeof(Conjunto));
    complemento->elementos = (unsigned long int *)malloc(sizeof(unsigned long int));
    criaConjunto(complemento);

    for(int i = 0; i < C2->tamanho; i++){
         if (pertenceConjunto(C2->elementos[i], C1) == 0) {
                insereElementoConjunto(C2->elementos[i], complemento);
            }
        }
    return complemento;
}

//Mostra os elementos que estão presentes nos dois conjuntos.
Conjunto *uniao(Conjunto *C1, Conjunto *C2){
    Conjunto *uniao = (Conjunto *)malloc(sizeof(Conjunto));
    uniao->elementos = (unsigned long int *)malloc(sizeof(unsigned long int));
    criaConjunto(uniao);
    if(C1->tamanho > 0){
        for(long int i = 0; i < C1->tamanho; i++){
            insereElementoConjunto(C1->elementos[i], uniao);
        }
    } else {

    }

    if(C2->tamanho > 0){
        for(int i = 0; i < C2->tamanho; i++){
            insereElementoConjunto(C2->elementos[i], uniao);
        }
    } else {

    }    
    return uniao;
}

//Função para mostrar a os elementos que estão simultaneamente no conjunto 1 e conjunto 2.
Conjunto *interceccao(Conjunto *C1, Conjunto *C2){
    Conjunto *interceccao = (Conjunto *)malloc(sizeof(Conjunto));
    interceccao->elementos = (unsigned long int *)malloc(sizeof(unsigned long int));
    criaConjunto(interceccao);
    for(int i = 0; i < C1->tamanho; i++){
         if (pertenceConjunto(C1->elementos[i], C2) == 1){
                insereElementoConjunto(C1->elementos[i], interceccao);
            }
        }
    return interceccao;
}

//Função para mostrar os elementos que estão em 1º conjunto, mas não estão no 2º conjunto.
Conjunto *diferenca(Conjunto *C1, Conjunto *C2){
    Conjunto *diferenca = (Conjunto *)malloc(sizeof(Conjunto));
    diferenca->elementos = (unsigned long int *)malloc(sizeof(unsigned long int));
    criaConjunto(diferenca);

    for(long int i = 0; i < C1->tamanho; i++){
         if (pertenceConjunto(C1->elementos[i], C2) == 0) {
                insereElementoConjunto(C1->elementos[i], diferenca);
            }
        }
    return diferenca;
}

//Mostra os conjuntos passados por parametro.
void mostrarConjuntos(Conjunto *C, int ordem){
    bubbleSort(C, ordem);
    printf("\nTamanho: %ld\n", C->tamanho);
    printf("Elementos: { ");


    for(int i = 0; i < C->tamanho; i++){
        printf("%ld", C->elementos[i]);
        if(i < C->tamanho-1){
            printf(", ");
        }
    }
    printf(" }\n");
}

// Função para ordenar um vetor de forma crescente ou decrescente
void bubbleSort(Conjunto *C, int ordem) {
    long int i, j;

    for (i = 0; i < C->tamanho-1; i++) {
        for (j = 0; j < C->tamanho - i - 1; j++) {
            // Verifica se é para ordenar de forma crescente ou decrescente e troca os elementos se necessário
            if (ordem == 1) {
                if (C->elementos[j] > C->elementos[j + 1]) {
                    unsigned long int aux = C->elementos[j];
                    C->elementos[j] = C->elementos[j + 1];
                    C->elementos[j + 1] = aux;
                }
            } else {
                if (C->elementos[j] < C->elementos[j + 1]) {
                    unsigned long int aux = C->elementos[j];
                    C->elementos[j] = C->elementos[j + 1];
                    C->elementos[j + 1] = aux;
                }
            }
        }
    }
}

//Função para Copiar um conjunto A para um Conjunto B.
int copiarConjunto(Conjunto *C1, Conjunto *C2){
    //Verifica se o somatorio dos tamanhos vai ultrapassar o limite do conjunto.
    if ((C2->tamanho + C1->tamanho) < 999999){
        long int C2tamanhoAntigo = C2->tamanho;
        //Copia os elementos do C1 para o C2.
        for (long int i = 0; i < C1->tamanho; i++){
            insereElementoConjunto(C1->elementos[i], C2);
        }
        if (C2->tamanho == C2tamanhoAntigo + C1->tamanho){
        } else {
            return FALHA;
        }
    }
    return SUCESSO;
}

//Exclui um conjunto da memoria.
int destruirConjunto(Conjunto *C){
    free(C);
    return SUCESSO;
}

void menuAux(){
    printf("|================================================================================================================|\n");
    printf("|                                             CONJUNTO 1 EM EXECUCAO                                             |\n");
    printf("|================================================================================================================|\n");
    printf("| | 1| > Criar um conjunto C.                           |    |11| > Gerar complemento de um conjunto             |\n");
    printf("| | 2| > Verificar se o conjunto C e vazio.             |    |12| > Gerar uniao de dois conjuntos.               |\n");
    printf("| | 3| > Inserir um elemento no conjunto C.             |    |13| > Gerar intersecao entre dois conjuntos.       |\n");
    printf("| | 4| > Excluir um elemento do conjunto C.             |    |14| > Gerar diferenca entre dois conjuntos.        |\n");
    printf("| | 5| > Calcular a cardinalidade do conjunto C.        |    |15| > Gerar o conjunto das partes.                 |\n");
    printf("| | 6| > Verificar elementos maiores que um numero.     |    |16| > Mostrar um conjunto.                         |\n");
    printf("| | 7| > Verificar elementos menores que um numero.     |    |17| > Copiar conjunto para outro.                  |\n");
    printf("| | 8| > Verificar pertinencia de um elemento.          |    |18| > Destruir conjunto.                           |\n");
    printf("| | 9| > Comparar conjuntos identicos.                  |    |19| > Configurar um segundo conjunto.              |\n");
    printf("| |10| > Verificar contigencia.                         |    |20| > Encerrar programa.                           |\n");
    printf("|================================================================================================================|\n");
}

int menu(){
    int escolha;
    printf("|================================================================================================================|\n");
    printf("|                                             CONJUNTO 1 EM EXECUCAO                                             |\n");
    printf("|================================================================================================================|\n");
    printf("| | 1| > Criar um conjunto C.                           |    |11| > Gerar complemento de um conjunto             |\n");
    printf("| | 2| > Verificar se o conjunto C e vazio.             |    |12| > Gerar uniao de dois conjuntos.               |\n");
    printf("| | 3| > Inserir um elemento no conjunto C.             |    |13| > Gerar intersecao entre dois conjuntos.       |\n");
    printf("| | 4| > Excluir um elemento do conjunto C.             |    |14| > Gerar diferenca entre dois conjuntos.        |\n");
    printf("| | 5| > Calcular a cardinalidade do conjunto C.        |    |15| > Gerar o conjunto das partes.                 |\n");
    printf("| | 6| > Verificar elementos maiores que um numero.     |    |16| > Mostrar um conjunto.                         |\n");
    printf("| | 7| > Verificar elementos menores que um numero.     |    |17| > Copiar conjunto para outro.                  |\n");
    printf("| | 8| > Verificar pertinencia de um elemento.          |    |18| > Destruir conjunto.                           |\n");
    printf("| | 9| > Comparar conjuntos identicos.                  |    |19| > Configurar um segundo conjunto.              |\n");
    printf("| |10| > Verificar contigencia.                         |    |20| > Encerrar programa.                           |\n");
    printf("|================================================================================================================|\n");
    printf("Escolha uma das opcoes: ");
    scanf("%d", &escolha);
    return escolha;
}

int menuSegundoConjunto(){
    int escolha;
    //system("cls");
    printf("|================================================================================================================|\n");
    printf("|                                             CONJUNTO 2 EM EXECUCAO                                             |\n");
    printf("|================================================================================================================|\n");
    printf("| | 1| > Criar um conjunto C.                           |    |11| > Gerar complemento de um conjunto             |\n");
    printf("| | 2| > Verificar se o conjunto C e vazio.             |    |12| > Gerar uniao de dois conjuntos.               |\n");
    printf("| | 3| > Inserir um elemento no conjunto C.             |    |13| > Gerar intersecao entre dois conjuntos.       |\n");
    printf("| | 4| > Excluir um elemento do conjunto C.             |    |14| > Gerar diferenca entre dois conjuntos.        |\n");
    printf("| | 5| > Calcular a cardinalidade do conjunto C.        |    |15| > Gerar o conjunto das partes.                 |\n");
    printf("| | 6| > Verificar elementos maiores que um numero.     |    |16| > Mostrar um conjunto.                         |\n");
    printf("| | 7| > Verificar elementos menores que um numero.     |    |17| > Copiar conjunto para outro.                  |\n");
    printf("| | 8| > Verificar pertinencia de um elemento.          |    |18| > Destruir conjunto.                           |\n");
    printf("| | 9| > Comparar conjuntos identicos.                  |    |19| > Configurar o primeiro conjunto.              |\n");
    printf("| |10| > Verificar contigencia.                         |    |20| > Encerrar programa.                           |\n");
    printf("|================================================================================================================|\n");
    printf("Escolha uma das opcoes: ");
    scanf("%d", &escolha);
    return escolha;
}
//    =============================================================
//    <                    Corpo Principal                        >
//    =============================================================

int main(){
    Conjunto *C = (Conjunto *)malloc(sizeof(Conjunto));
    C->elementos = (unsigned long int *)malloc(sizeof(long int));
    Conjunto *C2 = (Conjunto *)malloc(sizeof(Conjunto));
    C2->elementos = (unsigned long int *)malloc(sizeof(long int));


    unsigned long int x;
    int controladorDoConjunto1 = 0;
    int controladorDoConjunto2 = 0;
    int opcao;
    int ordem;
    int escolha = menu();

    while (escolha < 21 && escolha > 0) {
        
        switch(escolha){
            case 1 :
            if(controladorDoConjunto1 >= 1){
                printf("O Conjunto ja foi criado.\n");
                break;
            } else {
                if(criaConjunto(C) == 1){
                    printf("Conjunto criado com sucesso!\n");
                    controladorDoConjunto1++;
                    break;
                } else {
                    printf("Nao foi possivel criar o conjunto. ;(\n");
                    break;
                }
            }

            case 2 :
            if (conjuntoVazio(C) == 1){
                printf("O conjunto eh vazio!\n");
                break;
            } else {
                printf("O conjunto nao eh vazio\n");
                break;
            }

            case 3 :
            if (C != NULL){
                do {
                    printf("Digite o numero natural que deseja inserir: ");
                    scanf("%ld", &x);
                    if (insereElementoConjunto(x, C) == 1){
                        printf("Numero inserido com SUCESSO!\n");
                        printf("deseja inserir mais um numero ao conjunto?\n|0| > Nao\n|1| > Sim\n");
                        scanf("%d", &opcao);
                    } else {
                        printf("Nao foi possivel inserir o numero no conjunto. ;(\n");
                        printf("deseja inserir mais um numero ao conjunto?\n|0| > Nao\n|1| > Sim\n");
                        scanf("%d", &opcao);
                    }
                } while (opcao == 1); break;
            } else {
                printf("Crie um conjunto antes de executar esta operacao.\n");
                break;
            }  

            case 4 :
            printf("\nDigite o elemento que deseja excluir: ");
            scanf("%ld", &x);
            if (excluirElementoConjunto(x, C) == 1){
                printf("Elemento excluido com SUCESSO\n");
                break;
            } else {
                printf("Nao foi possivel excluir o elemento do conjunto. ;(\n");
                break;
            }

            case 5 :
            printf("A cardinalidade do conjunto é: %ld\n", tamanhoConjunto(C));
            break;

            case 6 :
            printf("insira um parametro: ");
            scanf("%ld", &x);
            printf("Quantidade de elementos maiores: %ld\n", maior(x, C));
            break;

            case 7 :
            printf("insira um parametro: ");
            scanf("%ld", &x);
            printf("Quantidade de elementos menores: %ld\n", menor(x, C));
            break;

            case 8 :
                if(C != NULL){
                printf("Insira o elemento que deseja verificar pertinencia:");
                scanf("%ld", &x);
                    if(pertenceConjunto(x, C) == 1){
                        printf("O elemento '%ld' pertence ao conjunto\n", x);
                        break;
                    } else {
                        printf("O elemento '%ld' nao pertence ao conjunto\n", x);
                        break;
                    }
                } else {
                    printf("O conjunto nao existe.\n");
                    break;
                }

            case 9 :
            if(C != NULL && C2 != NULL){
                if (conjuntosIdenticos(C, C2) == 1){
                    printf("Os conjunto sao identicos.\n");
                    break;
                } else {
                    printf("Os conjuntos sao diferentes.\n");
                    break;
                }
            } else {
                printf("Eh necessario criar os conjunto.\n");
                break;
            }
            
            case 10 :
            if(C != NULL && C2 != NULL){
                if (subconjunto(C, C2) == 1){
                    printf("Esta contido\n");
                    break;
            } else {
                printf("Nao esta contido\n");
                break;
            }
            } else {
                printf("Eh necessario criar os conjunto.\n");
                break;
            }

            case 11 :
            if(C != NULL && C2 != NULL){
                    printf("SUCESSO em gerar o complemento!\n");
                    mostrarConjuntos(complemento(C, C2), 1);
                    break;
            } else {
                printf("Eh necessario criar os conjunto.");
                break;
            }

            case 12 :
            if(C != NULL && C2 != NULL){
                    printf("SUCESSO em gerar a uniao!\n");
                    mostrarConjuntos(uniao(C, C2), 1);
                    break;
                } else {
                    printf("Eh necessario criar os conjunto.");
                    break;
                }
            
            
            case 13 :
            
            if(C != NULL && C2 != NULL){
                printf("SUCESSO em gerar a interseccao!\n");
                mostrarConjuntos(interceccao(C, C2), 1);
                break;
            } else {
                printf("Eh necessario criar os conjunto.");
                break;
            }

            case 14 :
            if(C != NULL && C2 != NULL){
                printf("SUCESSO em gerar a diferenca!\n");
                mostrarConjuntos(diferenca(C, C2), 1);
                break;
            } else {
                printf("Eh necessario criar os conjunto.");
                break;
            }

            case 15 :
            printf("Funcao ainda nao disponivel.\n");
            printf("Estara disponivel apenas na 1.2v do programa.\n");
            break;

            case 16 :
            printf("Selecione a ordem que sera mostrado\n|0| Crescente \n|1| Decrescente\n");
            scanf("%d", &ordem);
            mostrarConjuntos(C, ordem);
            break;

            case 17 :
            if (copiarConjunto(C, C2) == 1){
                printf("SUCESSO em copiar o conjunto!\n");
                break;
            } else {
                printf("Eh necessario criar os conjunto.");
                break;
            }

            case 18 :
            if (destruirConjunto(C) == 1){
                printf("Conjunto destruido com SUCESSO!\n");
                controladorDoConjunto1--;
                break;
            } else {
                printf("Não foi possivel destruir o conjunto\n");
                break;
            }

            case 19 :
            system("cls");
            escolha = menuSegundoConjunto();
            while (escolha < 21 && escolha > 0) {
                switch(escolha) {
                    case 1 :
                    if(controladorDoConjunto2 >= 1){
                        printf("O Conjunto ja foi criado.\n");
                        break;
                    } else {
                        if(criaConjunto(C2) == 1){
                            printf("Conjunto criado com sucesso!\n");
                            controladorDoConjunto2++;
                            break;
                        } else {
                            printf("Nao foi possivel criar o conjunto. ;(\n");
                            break;
                        }
                    }

                    case 2 :
                    if (conjuntoVazio(C2) == 1){
                        printf("O conjunto eh vazio!\n");
                        break;
                    } else {
                        printf("O conjunto nao eh vazio\n");
                        break;
                    }

                    case 3 :
                    if (C2 != NULL){
                        do {
                            printf("Digite o numero natural que deseja inserir: ");
                            scanf("%ld", &x);
                            if (insereElementoConjunto(x, C2) == 1){
                                printf("Numero inserido com SUCESSO!\n");
                                printf("deseja inserir mais um numero ao conjunto?\n|0| > Nao\n|1| > Sim\n");
                                scanf("%d", &opcao);
                                break;
                            } else {
                                printf("Nao foi possivel inserir o numero no conjunto. ;(\n");
                                printf("deseja inserir mais um numero ao conjunto?\n|0| > Nao\n|1| > Sim\n");
                                scanf("%d", &opcao);
                                break;
                            }
                        } while (opcao == 1); break;
                    } else {
                        printf("Crie um conjunto antes de executar esta operacao.\n");
                        break;
                    }

                    case 4 :
                    printf("\nDigite o elemento que deseja excluir: ");
                    scanf("%ld", &x);
                    if (excluirElementoConjunto(x, C2) == 1){
                        printf("Elemento excluido com SUCESSO\n");
                        break;
                    } else {
                        printf("Nao foi possivel excluir o elemento do conjunto. ;(\n");
                        break;
                    }

                    case 5 :
                    printf("A cardinalidade do conjunto é: %ld\n", tamanhoConjunto(C2));
                    break;

                    case 6 :
                    printf("insira um parametro: ");
                    scanf("%ld", &x);
                    printf("Quantidade de elementos maiores: %ld\n", maior(x, C2));
                    break;

                    case 7 :
                    printf("insira um parametro: ");
                    scanf("%ld", &x);
                    printf("Quantidade de elementos menores: %ld\n", menor(x, C2));
                    break;

                    case 8 :
                        if(C != NULL){
                        printf("Insira o elemento que deseja verificar pertinencia:");
                        scanf("%ld", &x);
                            if(pertenceConjunto(x, C2) == 1){
                                printf("O elemento '%ld' pertence ao conjunto\n", x);
                                break;
                            } else {
                                printf("O elemento '%ld' nao pertence ao conjunto\n", x);
                                break;
                            }
                        } else {
                            printf("O conjunto nao existe.\n");
                            break;
                        }

                    case 9 :
                    if(C != NULL && C2 != NULL){
                        if (conjuntosIdenticos(C2, C) == 1){
                            printf("Os conjunto sao identicos.\n");
                            break;
                        } else {
                            printf("Os conjuntos sao diferentes.\n");
                            break;
                        }
                    } else {
                        printf("Eh necessario criar os conjunto.\n");
                        break;
                    }
                    
                    case 10 :
                    if(C != NULL && C2 != NULL){
                        if (subconjunto(C2, C) == 1){
                            printf("Esta contido\n");
                            break;
                    } else {
                        printf("Nao esta contido\n");
                        break;
                    }
                    } else {
                        printf("Eh necessario criar os conjunto.\n");
                        break;
                    }
                
                    case 11 :
                    if(C != NULL && C2 != NULL){
                            printf("SUCESSO em gerar o complemento!\n");
                            mostrarConjuntos(complemento(C2, C), 1);
                            break;
                    } else {
                        printf("Eh necessario criar os conjunto.\n");
                        break;
                    }

                    case 12 :
                    if(C != NULL && C2 != NULL){
                            printf("SUCESSO em gerar a uniao!\n");
                            mostrarConjuntos(uniao(C2, C), 1);
                            break;
                    } else {
                        printf("Eh necessario criar os conjunto.\n");
                        break;
                    }
                    
                    case 13 :
                    
                    if(C != NULL && C2 != NULL){
                        printf("SUCESSO em gerar a interseccao!\n");
                        mostrarConjuntos(interceccao(C2, C), 1);
                        break;
                    } else {
                        printf("Eh necessario criar os conjunto.");
                        break;
                    }

                    case 14 :
                    if(C != NULL && C2 != NULL){
                        printf("SUCESSO em gerar a diferenca!\n");
                        mostrarConjuntos(diferenca(C2, C), 1);
                        break;
                    } else {
                        printf("Eh necessario criar os conjunto.");
                        break;
                    }

                    case 15 :
                    printf("Funcao ainda nao disponivel.\n");
                    printf("Estara disponivel apenas na 1.2v do programa.\n");
                    break;

                    case 16 :
                    printf("Selecione a ordem que sera mostrado\n|0| Crescente \n|1| Decrescente\n");
                    scanf("%d", &ordem);
                    mostrarConjuntos(C2, ordem);
                    break;

                    case 17 :
                    if (copiarConjunto(C2, C) == 1){
                        printf("SUCESSO em copiar o conjunto!\n");
                        break;
                    } else {
                        printf("Eh necessario criar os conjunto.");
                        break;
                    }

                    case 18 :
                    if (destruirConjunto(C2) == 1){
                        printf("Conjunto destruido com SUCESSO!\n");
                        controladorDoConjunto2--;
                        break;
                    } else {
                        printf("Não foi possivel destruir o conjunto.\n");
                        break;
                    }

                    case 19 :
                    system("cls");
                    break;
                    
                    case 20 :
                    printf("Tem certeza que deseja encerrar o programa?\n|20| > Confirmar.\n| 0| > Cancelar.\n");
                    scanf("%d", &opcao);
                    if (opcao == 20){
                    printf("Obrigado por utilizar o programa.\n\n");
                    free(C->elementos);
                    free(C2->elementos);
                    free(C2);
                    free(C);
                    return 0;
                    } else {
                        printf("Operacao cancelada!\n");
                        break;
                    }
                }
                    
                if(escolha == 19){
                    menuAux();
                    break;
                }
                printf("Escolha uma das opcoes: ");
                scanf("%d", &escolha);           
            }
            break;
            
            case 20 :
            printf("Tem certeza que deseja encerrar o programa?\n|20| > Confirmar.\n| 0| > Cancelar.\n>");
            scanf("%d", &opcao);
            if (opcao == 20){
            printf("Obrigado por utilizar o programa.\n");
            free(C->elementos);
            free(C2->elementos);
            free(C2);
            free(C);
            return 0;
            } else {
                printf("Operacao cancelada!\n");
                break;
            }
        }
        printf("Escolha uma das opcoes: ");
        scanf("%d", &escolha);

    }
    free(C->elementos);
    free(C2->elementos);
    free(C2);
    free(C);
    return 0;
        
}