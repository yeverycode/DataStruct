#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[20];
    int arrival_time;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

// ť �ʱ�ȭ
void init_queue(Queue* q) {
    q->front = q->rear = NULL;
}

// �Ϲ� �� �߰�
void enqueue(Queue* q, const char* name, int current_time) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->arrival_time = current_time;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }

    printf("[00:%02d] �Ϲ� �� �߰�: %s �� ť ����: ", current_time, name);
    Node* temp = q->front;
    while (temp) {
        printf("%s", temp->name);
        if (temp->next) printf(" �� ");
        temp = temp->next;
    }
    printf("\n");
}

// VIP �� �߰�
void enqueue_front(Queue* q, const char* name, int current_time) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->arrival_time = current_time;

    new_node->next = q->front;
    q->front = new_node;
    if (q->rear == NULL) {
        q->rear = new_node;
    }

    printf("[00:%02d] VIP �� �߰�: %s �� ť ����: ", current_time, name);
    Node* temp = q->front;
    while (temp) {
        printf("%s", temp->name);
        if (temp->next) printf(" �� ");
        temp = temp->next;
    }
    printf("\n");
}

// �ð� �ʰ� �� ����
void dequeue_timeout(Queue* q, int current_time, int timeout_limit) {
    if (q->front == NULL) return;

    Node* target = q->front;

    if (current_time - target->arrival_time >= timeout_limit) {
        printf("[00:%02d] �ð� �ʰ��� %s ���� �� ť ����: ", current_time, target->name);
        q->front = target->next;
        free(target);

        if (q->front == NULL) {
            q->rear = NULL;
            printf("�������\n");
            return;
        }

        Node* temp = q->front;
        while (temp) {
            printf("%s", temp->name);
            if (temp->next) printf(" �� ");
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Queue q;
    init_queue(&q);

    int current_time = 1;
    int timeout_limit = 5;

    // �ùķ��̼� ���� (�ּ� 10ȸ �̻�)
    for (; current_time <= 12; current_time++) {
        // �̺�Ʈ �߻�
        if (current_time == 1) enqueue(&q, "Kim", current_time);
        if (current_time == 2) enqueue(&q, "Lee", current_time);
        if (current_time == 3) enqueue_front(&q, "Park", current_time);
        if (current_time == 4) enqueue(&q, "Choi", current_time);
        if (current_time == 5) enqueue(&q, "Yoon", current_time);
        if (current_time == 6) enqueue_front(&q, "VIP_Jung", current_time);
        if (current_time == 7) enqueue(&q, "Shin", current_time);
        if (current_time == 8) enqueue(&q, "Kwon", current_time);
        if (current_time == 9) enqueue_front(&q, "VIP_Baek", current_time);
        if (current_time == 10) enqueue(&q, "Han", current_time);

        // �ð� �ʰ� üũ
        dequeue_timeout(&q, current_time, timeout_limit);
    }

    // ���� ť ���� ���
    printf("\n=== ���� ť ���� ===\n");
    if (q.front == NULL) {
        printf("�������\n");
    }
    else {
        Node* temp = q.front;
        while (temp) {
            printf("%s", temp->name);
            if (temp->next) printf(" �� ");
            temp = temp->next;
        }
        printf("\n");
    }

    // �޸� ����
    Node* temp = q.front;
    while (temp) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}
