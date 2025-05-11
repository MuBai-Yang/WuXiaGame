#pragma once
#include "character.h"

#define MAP_WIDTH 20    // 地图宽度
#define MAP_HEIGHT 10   // 地图高度

typedef struct {
    char tiles[MAP_HEIGHT][MAP_WIDTH];
} GameMap;

// 新增地形符号定义
#define GRASS '.'
#define WALL '#'
#define WATER '~'

void init_map(GameMap *map);
void draw_map(const GameMap *map);  // 声明
void draw_entity(int x, int y, char symbol);
void clear_screen();