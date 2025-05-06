#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// 새로운 노드 생성
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// 노드 삽입 (재귀)
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// 중위 순회 (재귀)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// 탐색 (재귀)
int search(Node* root, int target) {
    if (root == NULL)
        return 0;  // 찾지 못함

    if (root->key == target)
        return 1;  // 찾음
    else if (target < root->key)
        return search(root->left, target);
    else
        return search(root->right, target);
}

int main() {
    // 초기 트리 만들기
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
    int n = sizeof(values) / sizeof(values[0]);

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    // 중위 순회 결과 출력
    printf("중위 순회 결과: ");
    inorder(root);
    printf("\n");

    // 검색
    int target;
    printf("검색할 숫자 입력: ");
    scanf("%d", &target);

    if (search(root, target))
        printf("검색 결과: %d은(는) 트리에 존재합니다.\n", target);
    else
        printf("검색 결과: %d은(는) 트리에 존재하지 않습니다.\n", target);

    return 0;
}
