#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 정의
typedef struct Node {
    char name[30];
    struct Node* next;
} Node;

// 큐의 앞과 뒤를 가리키는 포인터
Node* front = NULL;
Node* rear = NULL;

// 현재 큐 상태를 출력하는 함수
void print_queue() {
    Node* temp = front;
    printf("현재 큐 상태: ");
    if (temp == NULL) {
        printf("비어있음\n");
        return;
    }
    while (temp != NULL) {
        printf("%s", temp->name);
        if (temp->next != NULL) {
            printf(" → ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// 일반 피난민 추가 (enqueue)
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

// VIP 피난민 추가 (enqueue_front)
void enqueue_front(const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->next = front;

    front = new_node;

    if (rear == NULL) {  // 처음 추가하는 노드일 경우 rear도 설정
        rear = new_node;
    }

    print_queue();
}

// 피난민 퇴소 (dequeue)
void dequeue() {
    if (front == NULL) {
        printf("대기열이 비어있어 퇴소할 피난민이 없습니다.\n");
        return;
    }

    Node* temp = front;
    printf("퇴소: %s\n", temp->name);
    front = front->next;

    if (front == NULL) {  // 모두 제거했을 때 rear도 NULL로 설정
        rear = NULL;
    }

    free(temp);

    print_queue();
}

// 메인 함수 (테스트 시나리오)
int main() {
    enqueue("Alice");
    enqueue("Bob");
    enqueue_front("Zena");
    dequeue();
    enqueue("Tom");

    return 0;
}
