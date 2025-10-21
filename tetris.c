// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.



    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PECAS 5

// Representação de uma peça do Tetris Stack
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// Fila circular
Peca fila[MAX_PECAS];
int head = 0;   // índice da frente (dequeue)
int tail = 0;   // índice onde será inserido o próximo (enqueue)
int count = 0;  // número de elementos na fila

// Contador global para gerar ids únicos
int proximoId = 1;

// Gera automaticamente uma nova peça
Peca gerarPeca() {
    Peca p;
    const char tipos[] = { 'I', 'O', 'T', 'L' }; // tipos usados conforme especificação
    int idx = rand() % (sizeof(tipos) / sizeof(tipos[0]));
    p.nome = tipos[idx];
    p.id = proximoId++;
    return p;
}

// Verifica se a fila está cheia
int estaCheia() {
    return count == MAX_PECAS;
}

// Verifica se a fila está vazia
int estaVazia() {
    return count == 0;
}

// Insere (enqueue) uma peça no final da fila. Retorna 1 se sucesso, 0 se cheia.
int enqueue(Peca p) {
    if (estaCheia()) return 0;
    fila[tail] = p;
    tail = (tail + 1) % MAX_PECAS;
    count++;
    return 1;
}

// Remove (dequeue) a peça da frente da fila. Retorna a peça removida.
// Se vazia, retorna uma peça com id == -1 para indicar erro.
Peca dequeue() {
    Peca vazio;
    vazio.id = -1;
    if (estaVazia()) return vazio;
    Peca p = fila[head];
    head = (head + 1) % MAX_PECAS;
    count--;
    return p;
}

// Exibe o estado atual da fila
void visualizarFila() {
    printf("\nEstado atual da fila (capacidade %d):\n", MAX_PECAS);
    if (estaVazia()) {
        printf("  <vazia>\n");
        return;
    }
    int idx = head;
    for (int i = 0; i < count; i++) {
        Peca p = fila[idx];
        printf("  Pos %d: Tipo '%c' | id=%d\n", i + 1, p.nome, p.id);
        idx = (idx + 1) % MAX_PECAS;
    }
}

// Inicializa a fila com 5 peças geradas automaticamente
void inicializarFila() {
    head = tail = count = 0;
    for (int i = 0; i < MAX_PECAS; i++) {
        Peca p = gerarPeca();
        enqueue(p); // deve sempre ter espaço nesse momento
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    srand((unsigned int) time(NULL));
    inicializarFila();

    printf("=== Tetris Stack ===\n");
    int opcao = 0;
    do {
        printf("\nMenu:\n");
        printf("  1 - Visualizar fila atual\n");
        printf("  2 - Jogar peça da frente (dequeue) [insere automaticamente nova peça no final]\n");
        printf("  3 - Inserir manualmente nova peça no final (enqueue)\n");
        printf("  4 - Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }

        switch (opcao) {
            case 1:
                visualizarFila();
                break;
            case 2: {
                // Jogar peça: remove da frente e insere automaticamente nova peça no final
                Peca removida = dequeue();
                if (removida.id == -1) {
                    printf("\nNão há peças para jogar; a fila está vazia.\n");
                } else {
                    printf("\nPeça jogada: Tipo '%c' | id=%d\n", removida.nome, removida.id);
                    Peca nova = gerarPeca();
                    if (enqueue(nova)) {
                        printf("Nova peça gerada automaticamente inserida no final: Tipo '%c' | id=%d\n", nova.nome, nova.id);
                    } else {
                        // Se a fila estiver cheia (situação improvável aqui), avisamos.
                        printf("Falha ao inserir nova peça: fila cheia.\n");
                    }
                }
                visualizarFila();
                break;
            }
            case 3: {
                // Inserir manualmente uma nova peça no final
                if (estaCheia()) {
                    printf("\nImpossível inserir: a fila está cheia.\n");
                } else {
                    Peca manual = gerarPeca();
                    if (enqueue(manual)) {
                        printf("\nPeça inserida manualmente no final: Tipo '%c' | id=%d\n", manual.nome, manual.id);
                    } else {
                        printf("\nFalha ao inserir peça.\n");
                    }
                }
                visualizarFila();
                break;
            }
            case 4:
                printf("\nSaindo. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Escolha 1-4.\n");
        }
    } while (opcao != 4);

    return 0;
}

