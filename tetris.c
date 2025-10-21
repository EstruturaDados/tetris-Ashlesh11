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

#define MAX_FILA 5
#define MAX_PILHA 3

// Representação de uma peça do Tetris Stack
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// --- Fila circular ---
Peca fila[MAX_FILA];
int head = 0;   // índice da frente (dequeue)
int tail = 0;   // índice onde será inserido o próximo (enqueue)
int count = 0;  // número de elementos na fila

// --- Pilha de reserva ---
Peca pilha[MAX_PILHA];
int topo = 0; // número de elementos na pilha (topo indica próxima posição livre)

// Contador global para gerar ids únicos
int proximoId = 1;

// Gera automaticamente uma nova peça
Peca gerarPeca() {
    Peca p;
    const char tipos[] = { 'I', 'O', 'T', 'L' };
    int idx = rand() % (sizeof(tipos) / sizeof(tipos[0]));
    p.nome = tipos[idx];
    p.id = proximoId++;
    return p;
}

// --- Operações da fila ---
int estaCheiaFila() {
    return count == MAX_FILA;
}

int estaVaziaFila() {
    return count == 0;
}

// Insere (enqueue) uma peça no final da fila. Retorna 1 se sucesso, 0 se cheia.
int enqueue(Peca p) {
    if (estaCheiaFila()) return 0;
    fila[tail] = p;
    tail = (tail + 1) % MAX_FILA;
    count++;
    return 1;
}

// Remove (dequeue) a peça da frente da fila. Retorna a peça removida.
// Se vazia, retorna peça com id == -1.
Peca dequeue() {
    Peca vazio;
    vazio.id = -1;
    if (estaVaziaFila()) return vazio;
    Peca p = fila[head];
    head = (head + 1) % MAX_FILA;
    count--;
    return p;
}

// --- Operações da pilha ---
int estaCheiaPilha() {
    return topo == MAX_PILHA;
}

int estaVaziaPilha() {
    return topo == 0;
}

// Push: empilha uma peça. Retorna 1 se sucesso, 0 se cheia.
int pushPilha(Peca p) {
    if (estaCheiaPilha()) return 0;
    pilha[topo++] = p;
    return 1;
}

// Pop: desempilha a peça do topo. Se vazia, retorna peça com id == -1.
Peca popPilha() {
    Peca vazio;
    vazio.id = -1;
    if (estaVaziaPilha()) return vazio;
    topo--;
    return pilha[topo];
}

// --- Visualização ---
void visualizarFila() {
    printf("\nFila (capacidade %d):\n", MAX_FILA);
    if (estaVaziaFila()) {
        printf("  <vazia>\n");
        return;
    }
    int idx = head;
    for (int i = 0; i < count; i++) {
        Peca p = fila[idx];
        printf("  Pos %d: Tipo '%c' | id=%d\n", i + 1, p.nome, p.id);
        idx = (idx + 1) % MAX_FILA;
    }
}

void visualizarPilha() {
    printf("\nPilha de reserva (capacidade %d):\n", MAX_PILHA);
    if (estaVaziaPilha()) {
        printf("  <vazia>\n");
        return;
    }
    // mostrar do topo para base para ficar claro qual será usada ao pop
    for (int i = topo - 1; i >= 0; i--) {
        Peca p = pilha[i];
        printf("  Nivel %d: Tipo '%c' | id=%d\n", i + 1, p.nome, p.id);
    }
}

// Inicializa a fila com MAX_FILA peças geradas automaticamente e pilha vazia
void inicializarSistema() {
    head = tail = count = 0;
    topo = 0;
    proximoId = 1;
    for (int i = 0; i < MAX_FILA; i++) {
        Peca p = gerarPeca();
        enqueue(p);
    }
}

// Limpa buffer de entrada após leitura inválida
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    srand((unsigned int) time(NULL));
    inicializarSistema();

    printf("=== Tetris Stack ===\n");
    printf("Fila fixa de %d peças + Pilha de reserva (max %d)\n", MAX_FILA, MAX_PILHA);

    int opcao = -1;
    do {
        printf("\nMenu:\n");
        printf("  1 - Jogar peça (usar frente da fila)\n");
        printf("  2 - Reservar peça (mover frente da fila para a pilha)\n");
        printf("  3 - Usar peça reservada (pop)\n");
        printf("  0 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }

        switch (opcao) {
            case 1: { // Jogar peça: remove frente e insere automaticamente nova peça no final
                Peca removida = dequeue();
                if (removida.id == -1) {
                    printf("\nNão há peças na fila para jogar.\n");
                } else {
                    printf("\nVocê jogou a peça: Tipo '%c' | id=%d\n", removida.nome, removida.id);
                    Peca nova = gerarPeca();
                    if (enqueue(nova)) {
                        printf("Peça nova gerada automaticamente inserida no final: Tipo '%c' | id=%d\n", nova.nome, nova.id);
                    } else {
                        // Situação improvável pois sempre enfileiramos quando há espaço, mas guardamos mensagem
                        printf("Falha ao inserir nova peça na fila (fila cheia).\n");
                    }
                }
                visualizarFila();
                visualizarPilha();
                break;
            }
            case 2: { // Reservar: mover a peça da frente para a pilha (se houver espaço)
                if (estaCheiaPilha()) {
                    printf("\nNão é possível reservar: pilha de reserva cheia (max %d).\n", MAX_PILHA);
                } else {
                    Peca removida = dequeue();
                    if (removida.id == -1) {
                        printf("\nNão há peças na fila para reservar.\n");
                    } else {
                        if (pushPilha(removida)) {
                            printf("\nPeça reservada: Tipo '%c' | id=%d (empilhada)\n", removida.nome, removida.id);
                            Peca nova = gerarPeca();
                            if (enqueue(nova)) {
                                printf("Peça nova gerada automaticamente inserida no final: Tipo '%c' | id=%d\n", nova.nome, nova.id);
                            } else {
                                printf("Falha ao inserir nova peça na fila (fila cheia).\n");
                            }
                        } else {
                            // Se push falhar (pilha cheia) — devolvemos a peça à frente: para manter consistência,
                            // mas conforme lógica acima, checamos cheia antes de dequeue, então não deve ocorrer.
                            printf("Erro ao empilhar peça (pilha cheia). A peça não foi removida da fila.\n");
                            // Para segurança, reenfileirar a peça removida no início (ajuste índices)
                            // Simples solução: inserir no final e rotacionar até ficar na frente seria complexa.
                            // Porém, pois essa situação não ocorre, omitimos a restauração.
                        }
                    }
                }
                visualizarFila();
                visualizarPilha();
                break;
            }
            case 3: { // Usar peça reservada: pop da pilha e usar (não altera a fila)
                if (estaVaziaPilha()) {
                    printf("\nPilha de reserva vazia: não há peças reservadas para usar.\n");
                } else {
                    Peca usada = popPilha();
                    printf("\nVocê usou a peça reservada: Tipo '%c' | id=%d\n", usada.nome, usada.id);
                    // Observação: Usar peça reservada não altera a fila, conforme especificação.
                }
                visualizarFila();
                visualizarPilha();
                break;
            }
            case 0:
                printf("\nSaindo. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Escolha 0-3.\n");
        }

    } while (opcao != 0);

    return 0;
}