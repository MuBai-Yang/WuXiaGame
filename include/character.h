#pragma once

#define MAX_NAME_LEN 32

typedef struct {
    char name[MAX_NAME_LEN];
    int hp;
    int mp;
    int attack;
    int defense;
    int speed;
    // 新增坐标字段
    int x; 
    int y;
} Character;

void init_player(Character *player);
void init_enemy(Character *enemy, int level);
void show_status(Character *ch);