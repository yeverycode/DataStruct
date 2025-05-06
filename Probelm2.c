#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    int number;
    char name[20];
    struct Node* next;
} Node;

Node* create_node(int number, const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->number = number;
    strcpy(new_node->name, name);
    new_node->next = NULL;
    return new_node;
}

void print_list(Node* head) {
    if (!head) return;

    Node* temp = head;
    do {
        printf("%02d-%s ", temp->number, temp->name);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

Node* remove_node(Node* head, Node* target) {
    if (head == target && head->next == head) {
        free(target);
        return NULL;
    }

    Node* prev = head;
    while (prev->next != target) {
        prev = prev->next;
    }

    prev->next = target->next;
    if (target == head) {
        head = target->next;
    }

    printf("탈락: %02d-%s\n", target->number, target->name);
    free(target);
    return head;
}

int main() {
    char* names[20] = {
        "Kim","Lee","Choi","Yoon","Jung","Kang","Han","Lim","Seo","Park",
        "Jang","Shin","Kwon","Cho","Baek","Hwang","Oh","Joo","Nam","Song"
    };

    Node* head = create_node(1, names[0]);
    Node* prev = head;
    for (int i = 2; i <= 20; i++) {
        Node* new_node = create_node(i, names[i - 1]);
        prev->next = new_node;
        prev = new_node;
    }
    prev->next = head;

    srand(time(NULL));
    int start_num = rand() % 20 + 1;
    Node* curr = head;
    while (curr->number != start_num) {
        curr = curr->next;
    }

    printf("시작 번호: %02d-%s\n", curr->number, curr->name);

    int count = 20;
    while (count > 4) {
        Node* target = curr;
        for (int i = 0; i < 2; i++) {
            target = target->next;
        }

        Node* next_target = target->next;

        head = remove_node(head, target);
        count--;

        print_list(head);
        curr = next_target;
    }

    printf("\n최종 생존자:\n");
    print_list(head);

    Node* temp = head;
    while (count--) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}
