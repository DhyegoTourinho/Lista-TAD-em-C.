//  =============================================================
//  <                       Pilha.h                         >
//  =============================================================

// Blibliotecas
    #include <stdio.h>
    #include <stdlib.h>

//  Definições de resultados:
    #define FALHA 0;
    #define FALSE 0;
    #define SUCESSO 1;
    #define TRUE 1;

// Estrutura da pilha
    typedef struct {
        long int topo;
        long int* elementos;
        long int tamanho;
    } Pilha;

//  Protótipos das funções:
    int create(Pilha *);
    int isEmpty(Pilha *);
    int push(Pilha *, long int);
    unsigned long int pop(Pilha *);
    long int size(Pilha *);
    void show(Pilha *, int);
    int copy(Pilha *, Pilha *);

// Função para inicializar a pilha
int create(Pilha *P) {
    P->topo = 0;
    P->tamanho = 0;
    P->elementos = (long int*)malloc(P->tamanho * sizeof(long int));
    if (P->elementos == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        return 0;
    } else {
        return 1;
    }
}

// Função para verificar se a pilha está vazia
int isEmpty(Pilha *P) {
    return (P->tamanho == 0) ? 1 : 0;
}

// Função para incluir um elemento x na pilha
int push(Pilha *P, long int x) {
    if (P == NULL) {
        printf("Erro: Pilha cheia\n");
        return 0; // Falha ao adicionar, pilha cheia
    } else {
        P->tamanho++;
        P->topo++;
        P->elementos = (long int *)realloc(P->elementos, P->tamanho * sizeof(long int));
        P->elementos[P->topo-1] = x;
        return 1; // Sucesso ao adicionar
    }
}

// Função para remover o elemento do topo da pilha
unsigned long int pop(Pilha *P) {
    if (isEmpty(P) == 1) {
        printf("Erro: Pilha vazia\n");
        return 0; // Falha ao remover, pilha vazia
    } else {
        P->tamanho--;
        P->topo--;
        P->elementos = (long int *)realloc(P->elementos, P->tamanho * sizeof(long int));
        return 1;
    }
}

// Função para calcular a cardinalidade da pilha
long int size(Pilha *P) {
    return P->topo;
}

// Função para verificar se duas pilhas são idênticas
int isEqual(Pilha *P1, Pilha *P2) {
    if (size(P1) != size(P2)) {
        return 0; // Pilhas têm tamanhos diferentes, não são idênticas
    }

    for (int i = 0; i <= P1->topo; i++) {
        if (P1->elementos[i] != P2->elementos[i]) {
            return 0; // Elementos diferentes encontrados, pilhas não são idênticas
        }
    }

    return 1; // Pilhas são idênticas
}

// Função para mostrar os elementos presentes na pilha, em ordem
void show(Pilha *P, int ordem) {
    if (isEmpty(P) == 1) {
        printf("Pilha vazia\n");
        return;
    }

        if (ordem == 1) {
            printf("{ ");
        for(int i = 0; i < P->topo; i++){
            printf("%ld", P->elementos[i]);
            if(i < P->tamanho-1){
                printf(", ");
            }
        }
        printf(" }\n");
        } else {
            printf("{ ");
            for(int i = P->topo-1; i >= 0; i--){
            printf("%ld", P->elementos[i]);
            if(i >= 1){
                printf(", ");
            }
        }
        printf(" }\n");
    }
}

// Função para copiar uma pilha para outra pilha
int copy(Pilha *P1, Pilha *P2) {
    for (int i = 0; i < P1->topo; i++) {
        push(P2, P1->elementos[i]);
    }
    return 1;
}

int menu(){
    int escolha;
    printf("|================================================================================================================|\n");
    printf("|                                             PILHA 1 EM EXECUCAO                                                |\n");
    printf("|================================================================================================================|\n");
    printf("| | 1| > Criar uma Pilha.                               |    | 6| > Comparar se as Pilhas sao identicas.         |\n");
    printf("| | 2| > Verificar se a Pilha eh vazia.                 |    | 7| > Mostrar a Pilha.                             |\n");
    printf("| | 3| > Inserir um elemento na Pilha.                  |    | 8| > Copiar uma Pilha para outra.                 |\n");
    printf("| | 4| > Excluir um elemento da Pilha.                  |    | 9| > Configurar a segunda Pilha. (indisponivel)   |\n");
    printf("| | 5| > Calcular a cardinalidade da Pilha.             |    |10| > Encerrar programa.                           |\n");
    printf("|================================================================================================================|\n");
    printf("Escolha uma das opcoes: ");
    scanf("%d", &escolha);
    return escolha;    
}

//CRIAR AS FUNÇÕES DENTRO DO MAIN E PRONTO LINDO

int main() {
    Pilha *P = (Pilha *)malloc(sizeof(Pilha));
    P->elementos = (long int *)malloc(sizeof(long int));
    Pilha *P2 = (Pilha *)malloc(sizeof(Pilha));
    P2->elementos = (long int *)malloc(sizeof(long int));

    int escolha, ordem, opcao;
    long int x;
    int quantDePilhas = 0;
    
    escolha = menu();
    
    while (escolha != 10){
        switch (escolha){

            case 1:
            if(quantDePilhas < 1){
                quantDePilhas++;
                if (create(P) == 1){
                    create(P);
                    printf("Pilha Criada com Sucesso!\n");
                    break;
                }
            } else {
                printf("A pilha ja foi criada.\n");
            }
            
            case 2:
            if(isEmpty(P) == 1){
                printf("A pilha esta vazia.\n");
                break;
            } else {
                printf("A pilha nao esta vazia.\n");
                break;
            }

            case 3:
            if (P != NULL){
                do {
                    printf("Digite o elemento que deseja inserir: ");
                    scanf("%ld", &x);
                    if (push(P, x) == 1){
                        printf("Elemento inserido com SUCESSO!\n");
                        printf("deseja inserir mais um elemento na pilha?\n|0| > Nao\n|1| > Sim\n");
                        scanf("%d", &opcao);
                    } else {
                        printf("Nao foi possivel inserir o numero na Pilha. ;(\n");
                        printf("deseja inserir mais um elemento ao conjunto?\n|0| > Nao\n|1| > Sim\n");
                        scanf("%d", &opcao);
                    }
                } while (opcao == 1); break;
            } else {
                printf("Crie uma Pilha antes de executar esta operacao.\n");
                break;
            }  

            case 4:
            if(P != NULL){
                if (pop(P) == 1){
                    printf("Elemento excluido com SUCESSO\n");
                    break;
                } else {
                    printf("Nao foi possivel excluir o elemento da Pilha. ;(\n");
                    break;
                }
            }
            
            case 5:
            if (P != NULL){
                printf("A cardinalidade da pilha é: %ld\n", size(P));
                break;
            } else {
                printf("Nao foi possivel realizar a operacao.\n");
                break;
            }
            

            case 6:
            if(P != NULL && P2 != NULL){
                if (isEqual(P, P2) == 1){
                    printf("As Pilhas sao identicas.\n");
                    break;
                } else {
                    printf("As Pilhas sao diferentes.\n");
                    break;
                }
            } else {
                printf("Nao foi possivel realizar a operacao.\n");
                break;
            }

            case 7:
            if (P != NULL){
                printf("Escolha a ordem:\n|1| > TOPO\n|2| > BASE\n");
                scanf("%d", &ordem);
                show(P, ordem);
                break;
            } else {
                printf("Nao foi possivel realizar a operacao.\n");
                break;
            }
            
            case 8:
            if (P != NULL){
                    if(copy(P, P2) == 1){
                    printf("Copia realizada com sucesso!\n");
                    break;
                } else {
                    printf("Nao foi possivel realizar a operacao.\n");
                    break;
                }
            } else {
                printf("Nao foi possivel realizar a operacao.\n");
                break;
            }
            
            case 10:
            break;
            }

        if (escolha == 10){
            printf("Tem certeza que deseja encerrar o programa?\n|10| > Confirmar.\n|0| > Cancelar.\n>");
            scanf("%d", &opcao);
            if (opcao == 10){
                printf("Obrigado por utilizar o programa.\n");
                free(P->elementos);
                free(P);
                free(P2);
                free(P2->elementos);
                return 0;
            } else {
                printf("Operacao cancelada!\n");
                break;
            }
        }
        printf("Escolha uma das opcoes: ");
        scanf("%d", &escolha);    
    }
    
    free(P);
    free(P2);

    return 0;
}
