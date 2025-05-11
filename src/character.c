#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void init_player(Character *player) {
    strcpy(player->name, "江湖侠客");
    player->hp = 100;
    player->attack = 20;
    player->defense = 15;
    player->speed = 25;
}

void init_enemy(Character *enemy, int level) {
    strcpy(enemy->name, "黑衣杀手");
    enemy->hp = 80 + level * 30;
    enemy->attack = 18 + level * 5;
    enemy->defense = 12 + level * 3;
    enemy->speed = 20 + level * 2;
}

void show_status(Character *character) {
    printf("\n===== 角色状态 =====");
    printf("\n姓名：%s", character->name);
    printf("\n生命：%d", character->hp);
    printf("\n攻击：%d", character->attack);
    printf("\n防御：%d", character->defense);
    printf("\n身法：%d\n", character->speed);
}