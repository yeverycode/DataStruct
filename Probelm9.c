#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

// 큐 초기화
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// 큐에 추가 (enqueue)
void enqueue(Queue* q, int value) {
    if (q->rear < SIZE) {
        q->data[q->rear++] = value;
    }
    else {
        printf("큐가 가득 찼습니다!\n");
    }
}

// 큐에서 제거하고 반환 (dequeue)
int dequeue(Queue* q) {
    if (q->front < q->rear) {
        return q->data[q->front++];
    }
    else {
        printf("큐가 비었습니다!\n");
        return -1;  // 비어있을 때
    }
}

int main() {
    Queue q;
    init_queue(&q);

    int cards[SIZE] = { 3, 7, 2, 9, 5 };

    // 카드 큐에 저장
    for (int i = 0; i < SIZE; i++) {
        enqueue(&q, cards[i]);
    }

    // 카드 공개
    printf("카드 공개 순서: ");
    for (int i = 0; i < SIZE; i++) {
        int card = dequeue(&q);
        if (card != -1) {
            printf("%d ", card);
        }
    }
    printf("\n");

    return 0;
}
