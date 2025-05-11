#pragma once

typedef struct {
    char name[20];
    int hp;
    int mp;
    int attack;
    int defense;
    int speed;
} Character;

void init_player(Character *player);
void init_enemy(Character *enemy, int level);
void show_status(Character *ch);