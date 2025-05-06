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

// 스택 연산
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

// 미로 출력
void print_maze(char maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 이동 가능 여부
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
    int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // 상하좌우

    // 시작 좌표 (수동 지정)
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

        // 이미 방문했으면 skip
        if (visited[x][y]) continue;

        visited[x][y] = 1;
        move_count++;

        // 기억 조각(G) 통과
        if (maze[x][y] == 'G') memory_count++;

        // 현재 위치 마킹
        if (maze[x][y] == '0' || maze[x][y] == 'G') {
            maze[x][y] = '.';
        }

        printf("현재 미로 상태:\n");
        print_maze(maze);

        // 출구 도달
        if (maze[x][y] == 'E') {
            if (memory_count > 0) {
                success = 1;
            }
            break;
        }

        // 4방향 탐색
        for (int d = 0; d < 4; d++) {
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];

            if (is_valid(nx, ny, maze, visited)) {
                Position next = { nx, ny };
                push(&stack, next, step++);
            }
        }
    }

    // 최종 결과 출력
    printf("\n==== 최종 미로 상태 ====\n");
    print_maze(maze);

    if (success) {
        printf("출구에 도달하였으며, 기억 조각을 통과하였습니다.\n");
    }
    else {
        printf("출구 도달 실패 또는 기억 조각을 통과하지 않았습니다.\n");
    }

    printf("총 이동 횟수: %d\n", move_count);
    printf("기억 조각 통과 횟수: %d\n", memory_count);

    return 0;
}
