#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position data[100];
    int top;
} Stack;

// ���� ����
void push(Stack* stack, Position pos, int step) {
    stack->data[++(stack->top)] = pos;
    printf("[Step %d] Push (x=%d, y=%d)\n", step, pos.x, pos.y);
}

Position pop(Stack* stack, int step) {
    Position pos = stack->data[(stack->top)--];
    printf("[Step %d] Pop (x=%d, y=%d)\n", step, pos.x, pos.y);
    return pos;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

// �̷� ���
void print_maze(char maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// �̵� ���� ����
int is_valid(int x, int y, char maze[SIZE][SIZE], int visited[SIZE][SIZE]) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && maze[x][y] != '1' && !visited[x][y];
}

int main() {
    char maze[SIZE][SIZE] = {
        {'1','1','1','1','1','1','1','1','1','1'},
        {'1','0','0','0','G','1','0','0','E','1'},
        {'1','1','1','0','1','1','1','0','1','1'},
        {'1','0','0','0','0','0','1','0','0','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','0','1','G','1','0','1','G','0','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','0','0','0','0','0','0','0','0','1'},
        {'1','1','1','1','1','1','1','1','0','1'},
        {'1','1','1','1','1','1','1','1','1','1'},
    };

    int visited[SIZE][SIZE] = { 0 };
    Stack stack = { .top = -1 };
    int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // �����¿�

    // ���� ��ǥ (���� ����)
    Position start = { 1, 1 };
    int step = 1;
    int move_count = 0;
    int memory_count = 0;
    int success = 0;

    push(&stack, start, step++);

    while (!is_empty(&stack)) {
        Position curr = pop(&stack, step++);
        int x = curr.x;
        int y = curr.y;

        // �̹� �湮������ skip
        if (visited[x][y]) continue;

        visited[x][y] = 1;
        move_count++;

        // ��� ����(G) ���
        if (maze[x][y] == 'G') memory_count++;

        // ���� ��ġ ��ŷ
        if (maze[x][y] == '0' || maze[x][y] == 'G') {
            maze[x][y] = '.';
        }

        printf("���� �̷� ����:\n");
        print_maze(maze);

        // �ⱸ ����
        if (maze[x][y] == 'E') {
            if (memory_count > 0) {
                success = 1;
            }
            break;
        }

        // 4���� Ž��
        for (int d = 0; d < 4; d++) {
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];

            if (is_valid(nx, ny, maze, visited)) {
                Position next = { nx, ny };
                push(&stack, next, step++);
            }
        }
    }

    // ���� ��� ���
    printf("\n==== ���� �̷� ���� ====\n");
    print_maze(maze);

    if (success) {
        printf("�ⱸ�� �����Ͽ�����, ��� ������ ����Ͽ����ϴ�.\n");
    }
    else {
        printf("�ⱸ ���� ���� �Ǵ� ��� ������ ������� �ʾҽ��ϴ�.\n");
    }

    printf("�� �̵� Ƚ��: %d\n", move_count);
    printf("��� ���� ��� Ƚ��: %d\n", memory_count);

    return 0;
}
