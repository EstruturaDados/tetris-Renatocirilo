#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM 5

typedef struct {
    char nome; // 'I', 'O', 'T', 'L', etc.
    int id;
} Peca;

typedef struct {
    Peca fila[TAM];
    int frente;
    int tras;
    int contador;
} FilaCircular;

// ------------------ GERA PEÇA AUTOMÁTICA ------------------
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    p.nome = tipos[rand() % 7];
    p.id = rand() % 1000;  // ID aleatório
    return p;
}

// ------------------ INICIALIZA FILA ------------------
void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->contador = 0;

    for(int i = 0; i < TAM; i++) {
        f->tras = (f->tras + 1) % TAM;
        f->fila[f->tras] = gerarPeca();
        f->contador++;
    }
}

// ------------------ ENQUEUE ------------------
void inserirPeca(FilaCircular *f) {
    if(f->contador == TAM) {
        printf("Fila cheia! (Mas neste desafio ela sempre se mantém cheia)\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM;
    f->fila[f->tras] = gerarPeca();
    f->contador++;
}

// ------------------ DEQUEUE ------------------
void jogarPeca(FilaCircular *f) {
    if(f->contador == 0) {
        printf("Fila vazia! Algo errado.\n");
        return;
    }

    Peca jogada = f->fila[f->frente];

    printf("\nPeça jogada: %c (ID %d)\n", jogada.nome, jogada.id);

    f->frente = (f->frente + 1) % TAM;
    f->contador--;

    // Inserir nova peça automaticamente
    inserirPeca(f);
}

// ------------------ EXIBIR FILA ------------------
void exibirFila(FilaCircular *f) {
    printf("\n--- Fila Atual de Peças ---\n");

    int idx = f->frente;
    for(int i = 0; i < f->contador; i++) {
        Peca p = f->fila[idx];
        printf("%d) Tipo: %c | ID: %d\n", i+1, p.nome, p.id);
        idx = (idx + 1) % TAM;
    }
}

// ------------------ PROGRAMA PRINCIPAL ------------------
int main() {
    srand(time(NULL));

    FilaCircular fila;
    inicializarFila(&fila);

    int opcao;

    do {
        printf("\n===== TETRIS STACK – NÍVEL NOVATO =====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila);
                printf("Nova peça inserida!\n");
                break;
            case 3:
                exibirFila(&fila);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
