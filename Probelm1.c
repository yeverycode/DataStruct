#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��� ����ü ����
typedef struct Node {
    char name[30];
    struct Node* next;
} Node;

// ť�� �հ� �ڸ� ����Ű�� ������
Node* front = NULL;
Node* rear = NULL;

// ���� ť ���¸� ����ϴ� �Լ�
void print_queue() {
    Node* temp = front;
    printf("���� ť ����: ");
    if (temp == NULL) {
        printf("�������\n");
        return;
    }
    while (temp != NULL) {
        printf("%s", temp->name);
        if (temp->next != NULL) {
            printf(" �� ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// �Ϲ� �ǳ��� �߰� (enqueue)
void enqueue(const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->next = NULL;

    if (rear == NULL) {
        front = rear = new_node;
    }
    else {
        rear->next = new_node;
        rear = new_node;
    }

    print_queue();
}

// VIP �ǳ��� �߰� (enqueue_front)
void enqueue_front(const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->next = front;

    front = new_node;

    if (rear == NULL) {  // ó�� �߰��ϴ� ����� ��� rear�� ����
        rear = new_node;
    }

    print_queue();
}

// �ǳ��� ��� (dequeue)
void dequeue() {
    if (front == NULL) {
        printf("��⿭�� ����־� ����� �ǳ����� �����ϴ�.\n");
        return;
    }

    Node* temp = front;
    printf("���: %s\n", temp->name);
    front = front->next;

    if (front == NULL) {  // ��� �������� �� rear�� NULL�� ����
        rear = NULL;
    }

    free(temp);

    print_queue();
}

// ���� �Լ� (�׽�Ʈ �ó�����)
int main() {
    enqueue("Alice");
    enqueue("Bob");
    enqueue_front("Zena");
    dequeue();
    enqueue("Tom");

    return 0;
}
