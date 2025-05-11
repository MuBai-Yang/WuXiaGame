#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

/**
 * 初始化随机地图（草地70%、墙壁20%、水域10%）
 * @param map 地图指针
 * @warning 需提前调用srand初始化随机种子
 */
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