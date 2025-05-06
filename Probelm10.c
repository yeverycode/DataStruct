#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// ���ο� ��� ����
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// ��� ���� (���)
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

// ���� ��ȸ (���)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Ž�� (���)
int search(Node* root, int target) {
    if (root == NULL)
        return 0;  // ã�� ����

    if (root->key == target)
        return 1;  // ã��
    else if (target < root->key)
        return search(root->left, target);
    else
        return search(root->right, target);
}

int main() {
    // �ʱ� Ʈ�� �����
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
    int n = sizeof(values) / sizeof(values[0]);

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    // ���� ��ȸ ��� ���
    printf("���� ��ȸ ���: ");
    inorder(root);
    printf("\n");

    // �˻�
    int target;
    printf("�˻��� ���� �Է�: ");
    scanf("%d", &target);

    if (search(root, target))
        printf("�˻� ���: %d��(��) Ʈ���� �����մϴ�.\n", target);
    else
        printf("�˻� ���: %d��(��) Ʈ���� �������� �ʽ��ϴ�.\n", target);

    return 0;
}
