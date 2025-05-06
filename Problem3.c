#define _CRT_SECURE_NO_WARNIGNS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 노드 추가
void append(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// 리스트 출력
void print_list(Node* head) {
    Node* temp = head;
    int idx = 1;
    while (temp != NULL) {
        printf("[%d] %d\n", idx++, temp->data);
        temp = temp->next;
    }
}

// 선택 정렬
void selection_sort(Node* head) {
    Node* i = head;
    while (i != NULL) {
        Node* min = i;
        Node* j = i->next;

        while (j != NULL) {
            if (j->data < min->data) {
                min = j;
            }
            j = j->next;
        }

        // swap
        if (min != i) {
            int tmp = i->data;
            i->data = min->data;
            min->data = tmp;
        }

        i = i->next;
    }
}

// 리스트 크기 반환
int list_size(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// 인덱스 번째 노드 가져오기 (0부터 시작)
Node* get_node(Node* head, int index) {
    for (int i = 0; i < index && head != NULL; i++) {
        head = head->next;
    }
    return head;
}

// Linked List를 이용한 Binary Search
void binary_search(Node* head, int key) {
    int left = 0;
    int right = list_size(head) - 1;
    int found = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        Node* mid_node = get_node(head, mid);

        if (mid_node->data == key) {
            printf("True, 위치: %d번째 노드\n", mid + 1);
            found = 1;
            break;
        }
        else if (mid_node->data < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("False, No Result in List\n");
    }
}

int main() {
    int data[31] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6,
                    70, 71, 73, 75, 48, 12, 14, 7, 15, 24,
                    26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };

    Node* head = NULL;

    // 삽입
    for (int i = 0; i < 31; i++) {
        append(&head, data[i]);
    }

    printf("정렬 전 리스트:\n");
    print_list(head);

    // 정렬
    selection_sort(head);

    printf("\n정렬 후 리스트:\n");
    print_list(head);

    // 검색 테스트
    int search_keys[10] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 };

    printf("\n=== 검색 결과 ===\n");
    for (int i = 0; i < 10; i++) {
        printf("(%d) %d -> ", i + 1, search_keys[i]);
        binary_search(head, search_keys[i]);
    }

    // 메모리 해제
    Node* temp = head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}
