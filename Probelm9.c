#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 5

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

// ť �ʱ�ȭ
void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// ť�� �߰� (enqueue)
void enqueue(Queue* q, int value) {
    if (q->rear < SIZE) {
        q->data[q->rear++] = value;
    }
    else {
        printf("ť�� ���� á���ϴ�!\n");
    }
}

// ť���� �����ϰ� ��ȯ (dequeue)
int dequeue(Queue* q) {
    if (q->front < q->rear) {
        return q->data[q->front++];
    }
    else {
        printf("ť�� ������ϴ�!\n");
        return -1;  // ������� ��
    }
}

int main() {
    Queue q;
    init_queue(&q);

    int cards[SIZE] = { 3, 7, 2, 9, 5 };

    // ī�� ť�� ����
    for (int i = 0; i < SIZE; i++) {
        enqueue(&q, cards[i]);
    }

    // ī�� ����
    printf("ī�� ���� ����: ");
    for (int i = 0; i < SIZE; i++) {
        int card = dequeue(&q);
        if (card != -1) {
            printf("%d ", card);
        }
    }
    printf("\n");

    return 0;
}
