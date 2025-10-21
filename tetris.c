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
#include <string.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Representação de uma peça do Tetris Stack
typedef struct {
    char nome; // 'I', 'O', 'T', 'L' (podem ser ampliados)
    int id;    // identificador único
} Peca;

// --- Estruturas principais ---
Peca fila[MAX_FILA];
int head = 0;   // índice da frente (dequeue)
int tail = 0;   // índice onde será inserido o próximo (enqueue)
int count = 0;  // número de elementos na fila

Peca pilha[MAX_PILHA];
int topo = 0; // número de elementos na pilha (topo aponta para próxima posição livre)

// Contador global para gerar ids únicos
int proximoId = 1;

typedef struct {
    Peca fila[MAX_FILA];
    int head, tail, count;
    Peca pilha[MAX_PILHA];
    int topo;
    int proximoId;
    int valido; // indica se existe um estado válido para desfazer
} Snapshot;

Snapshot ultimoSnapshot;

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

int enqueue(Peca p) {
    if (estaCheiaFila()) return 0;
    fila[tail] = p;
    tail = (tail + 1) % MAX_FILA;
    count++;
    return 1;
}

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

int pushPilha(Peca p) {
    if (estaCheiaPilha()) return 0;
    pilha[topo++] = p;
    return 1;
}

Peca popPilha() {
    Peca vazio;
    vazio.id = -1;
    if (estaVaziaPilha()) return vazio;
    topo--;
    return pilha[topo];
}


void salvarSnapshot() {
    memcpy(ultimoSnapshot.fila, fila, sizeof(fila));
    ultimoSnapshot.head = head;
    ultimoSnapshot.tail = tail;
    ultimoSnapshot.count = count;
    memcpy(ultimoSnapshot.pilha, pilha, sizeof(pilha));
    ultimoSnapshot.topo = topo;
    ultimoSnapshot.proximoId = proximoId;
    ultimoSnapshot.valido = 1;
}

void restaurarSnapshot() {
    if (!ultimoSnapshot.valido) return;
    memcpy(fila, ultimoSnapshot.fila, sizeof(fila));
    head = ultimoSnapshot.head;
    tail = ultimoSnapshot.tail;
    count = ultimoSnapshot.count;
    memcpy(pilha, ultimoSnapshot.pilha, sizeof(pilha));
    topo = ultimoSnapshot.topo;
    proximoId = ultimoSnapshot.proximoId;
    ultimoSnapshot.valido = 0; // só permite desfazer uma vez até nova ação
}


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
    for (int i = topo - 1; i >= 0; i--) {
        Peca p = pilha[i];
        printf("  Nivel %d (topo=%d): Tipo '%c' | id=%d\n", i + 1, i, p.nome, p.id);
    }
}

void visualizarEstados() {
    visualizarFila();
    visualizarPilha();
}

// --- Inicialização ---
void inicializarSistema() {
    head = tail = count = 0;
    topo = 0;
    proximoId = 1;
    ultimoSnapshot.valido = 0;
    for (int i = 0; i < MAX_FILA; i++) {
        Peca p = gerarPeca();
        enqueue(p);
    }
}

// 1 - Jogar peça: dequeue frente e enfileira nova peça gerada automaticamente
void operarJogarPeca() {
    salvarSnapshot();
    Peca removida = dequeue();
    if (removida.id == -1) {
        printf("\nNão há peças na fila para jogar.\n");
        // mesmo que nada mude, deixamos snapshot válido (poder desfazer sem efeito)
    } else {
        printf("\nVocê jogou a peça: Tipo '%c' | id=%d\n", removida.nome, removida.id);
        Peca nova = gerarPeca();
        if (enqueue(nova)) {
            printf("Peça nova gerada automaticamente inserida no final: Tipo '%c' | id=%d\n", nova.nome, nova.id);
        } else {
            printf("Falha ao inserir nova peça na fila (fila cheia).\n");
        }
    }
}

// 2 - Reservar peça: mover a frente da fila para a pilha e enfileirar nova peça gerada
void operarReservarPeca() {
    if (estaCheiaPilha()) {
        printf("\nNão é possível reservar: pilha de reserva cheia (max %d).\n", MAX_PILHA);
        return;
    }
    if (estaVaziaFila()) {
        printf("\nNão há peças na fila para reservar.\n");
        return;
    }
    salvarSnapshot();
    Peca removida = dequeue();
    if (pushPilha(removida)) {
        printf("\nPeça reservada: Tipo '%c' | id=%d (empilhada)\n", removida.nome, removida.id);
        Peca nova = gerarPeca();
        if (enqueue(nova)) {
            printf("Peça nova gerada automaticamente inserida no final: Tipo '%c' | id=%d\n", nova.nome, nova.id);
        } else {
            printf("Falha ao inserir nova peça na fila (fila cheia).\n");
        }
    } else {
        // Não deve ocorrer pois checamos antes, mas mantemos mensagem
        printf("\nErro: pilha cheia, não foi possível reservar.\n");
    }
}

// 3 - Usar peça reservada: pop e reportar (não altera a fila)
void operarUsarReservada() {
    if (estaVaziaPilha()) {
        printf("\nPilha de reserva vazia: não há peças reservadas para usar.\n");
        return;
    }
    salvarSnapshot();
    Peca usada = popPilha();
    printf("\nVocê usou a peça reservada: Tipo '%c' | id=%d\n", usada.nome, usada.id);
    // A fila permanece inalterada
}

// 4 - Trocar topo da pilha com frente da fila
void operarTrocarTopoComFrente() {
    if (estaVaziaFila()) {
        printf("\nNão há peça na frente da fila para trocar.\n");
        return;
    }
    if (estaVaziaPilha()) {
        printf("\nNão há peça no topo da pilha para trocar.\n");
        return;
    }
    salvarSnapshot();
    // índice da frente é head
    Peca tempFila = fila[head];
    Peca tempPilha = pilha[topo - 1];
    fila[head] = tempPilha;
    pilha[topo - 1] = tempFila;
    printf("\nTroca realizada: topo da pilha <-> frente da fila\n");
}

// 5 - Desfazer última jogada (restaurar snapshot)
void operarDesfazer() {
    if (!ultimoSnapshot.valido) {
        printf("\nNão há operação para desfazer.\n");
        return;
    }
    restaurarSnapshot();
    printf("\nÚltima ação desfeita. Estado restaurado.\n");
}


void operarInverterFilaComPilha() {
    // Se não há nada para trocar e ambas vazias, nada a fazer. Mas fila sempre tende a estar cheia.
    salvarSnapshot();

    // Salva cópia temporária da fila antiga
    Peca filaAntiga[MAX_FILA];
    int countAntiga = count;
    int idx = head;
    for (int i = 0; i < countAntiga; i++) {
        filaAntiga[i] = fila[idx];
        idx = (idx + 1) % MAX_FILA;
    }

    // Salva cópia temporária da pilha antiga
    Peca pilhaAntiga[MAX_PILHA];
    int topoAntiga = topo;
    for (int i = 0; i < topoAntiga; i++) {
        pilhaAntiga[i] = pilha[i];
    }

    // Limpa fila e pilha atuais
    head = tail = count = 0;
    topo = 0;

    // Nova fila: inserir elementos da pilha antiga do topo para base (topo vira frente)
    for (int i = topoAntiga - 1; i >= 0; i--) {
        enqueue(pilhaAntiga[i]);
    }
    // Completa com novas peças se necessário para atingir MAX_FILA
    while (count < MAX_FILA) {
        Peca gerada = gerarPeca();
        enqueue(gerada);
    }

    // Nova pilha: pega os primeiros MAX_PILHA elementos da fila antiga (na ordem da frente) e empilha na mesma ordem
    int mover = (countAntiga < MAX_PILHA) ? countAntiga : MAX_PILHA;
    for (int i = 0; i < mover; i++) {
        pushPilha(filaAntiga[i]);
    }

    printf("\nInversão realizada entre fila e pilha.\n");
    printf("  - A nova fila foi construída a partir da pilha antiga (topo -> frente) e preenchida com peças geradas quando necessário.\n");
    printf("  - A nova pilha recebeu até %d primeiros elementos da fila antiga (frente -> ...), mantendo ordem de empilhamento.\n", MAX_PILHA);
}

// --- Utilitário de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// --- Programa principal ---
int main() {
    srand((unsigned int) time(NULL));
    inicializarSistema();

    printf("=== Tetris Stack ===\n");
    printf("Fila fixa de %d peças + Pilha de reserva (max %d)\n", MAX_FILA, MAX_PILHA);

    int opcao = -1;
    do {
        printf("\nMenu:\n");
        printf("  1 - Jogar peça\n");
        printf("  2 - Reservar peça\n");
        printf("  3 - Usar peça reservada\n");
        printf("  4 - Trocar peça do topo da pilha com a da frente da fila\n");
        printf("  5 - Desfazer última jogada\n");
        printf("  6 - Inverter fila com pilha\n");
        printf("  0 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }

        switch (opcao) {
            case 1:
                operarJogarPeca();
                visualizarEstados();
                break;
            case 2:
                operarReservarPeca();
                visualizarEstados();
                break;
            case 3:
                operarUsarReservada();
                visualizarEstados();
                break;
            case 4:
                operarTrocarTopoComFrente();
                visualizarEstados();
                break;
            case 5:
                operarDesfazer();
                visualizarEstados();
                break;
            case 6:
                operarInverterFilaComPilha();
                visualizarEstados();
                break;
            case 0:
                printf("\nSaindo. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Escolha 0-6.\n");
        }

    } while (opcao != 0);

    return 0;
}