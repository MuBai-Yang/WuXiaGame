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
int load_map_from_file(GameMap *map, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    
    for (int y=0; y<MAP_HEIGHT; y++) {
        for (int x=0; x<MAP_WIDTH; x++) {
            int c = fgetc(fp);
            map->tiles[y][x] = (c == EOF || c == '\n') ? GRASS : c;
        }
    }
    fclose(fp);
    return 1;
}

void init_map(GameMap *map) {
    if (!load_map_from_file(map, "data/maps/default.map")) {
        srand(time(NULL));
        for(int y=0; y<MAP_HEIGHT; y++) {
            for(int x=0; x<MAP_WIDTH; x++) {
                int r = rand()%10;
                map->tiles[y][x] = (r > 7) ? WALL : (r > 5) ? WATER : GRASS;
            }
        }
    }
    // 预留SDL3纹理初始化位置
    //map->sdl_texture = NULL;
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}