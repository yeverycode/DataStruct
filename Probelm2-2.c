#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DNode {
    int number;
    char name[20];
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* create_dnode(int number, const char* name) {
    DNode* new_node = (DNode*)malloc(sizeof(DNode));
    new_node->number = number;
    strcpy(new_node->name, name);
    new_node->prev = new_node->next = NULL;
    return new_node;
}

void print_dlist(DNode* head) {
    if (!head) return;

    DNode* temp = head;
    do {
        printf("%02d-%s ", temp->number, temp->name);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

DNode* remove_dnode(DNode* head, DNode* target) {
    if (head == target && head->next == head) {
        free(target);
        return NULL;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

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

    DNode* head = create_dnode(1, names[0]);
    DNode* prev = head;
    for (int i = 2; i <= 20; i++) {
        DNode* new_node = create_dnode(i, names[i - 1]);
        prev->next = new_node;
        new_node->prev = prev;
        prev = new_node;
    }
    prev->next = head;
    head->prev = prev;

    srand(time(NULL));
    int start_num = rand() % 20 + 1;
    DNode* curr = head;
    while (curr->number != start_num) {
        curr = curr->next;
    }

    printf("시작 번호: %02d-%s\n", curr->number, curr->name);

    int count = 20;
    int turn = 1;

    while (count > 4) {
        DNode* target = curr;

        if (turn % 2 == 1) {
            for (int i = 0; i < 2; i++) target = target->next;
        }
        else {
            for (int i = 0; i < 7; i++) target = target->prev;
        }

        DNode* next_target = (turn % 2 == 1) ? target->next : target->prev;

        head = remove_dnode(head, target);
        count--;

        print_dlist(head);

        curr = next_target;
        turn++;
    }

    printf("\n최종 생존자:\n");
    print_dlist(head);

    DNode* temp = head;
    while (count--) {
        DNode* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}
