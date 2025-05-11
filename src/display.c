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
    // 地图瓦片初始化
    if (!load_map_from_file(map, "data/maps/default.map")) {
        srand(time(NULL));
        for(int y=0; y<MAP_HEIGHT; y++) {
            for(int x=0; x<MAP_WIDTH; x++) {
                int r = rand()%10;
                map->tiles[y][x] = (r > 7) ? WALL : (r > 5) ? WATER : GRASS;
            }
        }
    }
    
    // 敌人生成逻辑
    for(int i=0; i<MAX_ENEMIES; i++) {
        do {
            map->enemies[i].x = rand() % MAP_WIDTH;
            map->enemies[i].y = rand() % MAP_HEIGHT;
        } while(map->tiles[map->enemies[i].y][map->enemies[i].x] == WALL || 
              (map->enemies[i].x == MAP_WIDTH/2 && map->enemies[i].y == MAP_HEIGHT/2));
        map->enemies[i].active = 1;
    }
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}