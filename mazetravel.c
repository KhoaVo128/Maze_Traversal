#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// prototype from mazecreation.c
void generate_maze(char *maze, int n, int *entrance_x, int *entrance_y, int *exit_x, int *exit_y);

static void draw_linear(char *maze, int n, int a, int b){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==a && i==b){
                printf(" x ");
            } else {
                printf(" %c ", maze[i*n + j]);
            }
        }
        printf("\n");
    }
}

void traverse_linear(char *maze, int n, int x, int y, char a, int endx, int endy){
    char dir = a;
    if(x==endx && y==endy){
        draw_linear(maze, n, x, y);
        printf("you made it\n");
        return;
    }

    draw_linear(maze, n, x, y);

    if(dir=='R'){
        if(maze[(y+1)*n + x] == '#'){
            if(maze[y*n + (x+1)] != '#'){
                x++; dir='R';
            }else{
                if(maze[(y-1)*n + x] == '#' && maze[y*n + (x+1)] == '#'){
                    x--; dir='L';
                }else{ y--; dir='U'; }
            }
        } else { y++; dir='D'; }
    }
    if(dir=='L'){
        if(maze[(y-1)*n + x] == '#'){
            if(maze[y*n + (x-1)] != '#'){
                x--; dir='L';
            }else{
                if(maze[y*n + (x-1)] == '#' && maze[(y+1)*n + x] == '#'){
                    x++; dir='R';
                }else{ y++; dir='D'; }
            }
        } else { y--; dir='U'; }
    }
    if(dir=='U'){
        if(maze[y*n + (x+1)] == '#'){
            if(maze[(y-1)*n + x] != '#'){
                y--; dir='U';
            }else{
                if(maze[(y-1)*n + x] == '#' && maze[y*n + (x-1)] == '#'){
                    y++; dir='D';
                }else{ x--; dir='L'; }
            }
        } else { x++; dir='R'; }
    }
    if(dir=='D'){
        if(maze[y*n + (x-1)] == '#'){
            if(maze[(y+1)*n + x] != '#'){
                y++; dir='D';
            }else{
                if(maze[y*n + (x+1)] == '#' && maze[(y+1)*n + x] == '#'){
                    y--; dir='U';
                }else{ x++; dir='R'; }
            }
        } else { x--; dir='L'; }
    }

    Sleep(100);
    system("cls");
    traverse_linear(maze, n, x, y, dir, endx, endy);
}

int main(int argc, char **argv){
    int n = 21;
    if(argc > 1) n = atoi(argv[1]);
    if(n < 3) n = 3;
    if(n % 2 == 0) n++;

    char *maze = malloc(n * n);
    if(!maze) return 1;

    srand((unsigned)time(NULL));
    int sx, sy, ex, ey;
    generate_maze(maze, n, &sx, &sy, &ex, &ey);

    // start just inside entrance, heading right
    int startx = sx;
    int starty = sy;
    char dir = 'R';

    traverse_linear(maze, n, startx, starty, dir, ex, ey);

    free(maze);
    return 0;
}
