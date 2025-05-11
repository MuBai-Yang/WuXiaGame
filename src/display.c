#include <stdio.h>  // 标准C输入输出
#include <stdlib.h> // 内存管理
#include <time.h>   // 时间函数
#include "display.h"

void draw_map(const GameMap *map) {  // 实现
    for(int y=0; y<MAP_HEIGHT; y++) {
        for(int x=0; x<MAP_WIDTH; x++) {
            printf("%c", map->tiles[y][x]);
        }
        printf("\n");
    }
}

void draw_entity(int x, int y, char symbol) {
    // 使用ANSI转义码定位光标
    printf("\033[%d;%dH%c", y+1, x+1, symbol);
    fflush(stdout);
}

void init_map(GameMap *map) {
    srand(time(NULL));
    for(int y=0; y<MAP_HEIGHT; y++) {
        for(int x=0; x<MAP_WIDTH; x++) {
            int r = rand()%10;
            map->tiles[y][x] = (r > 7) ? WALL : (r > 5) ? WATER : GRASS;
        }
    }
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}