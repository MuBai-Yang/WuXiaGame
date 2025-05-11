#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "display.h"  // 添加地图尺寸常量定义

/**
 * 初始化玩家角色属性
 * @param p 角色指针
 * @note 初始位置设置在地图中心
 */
void init_player(Character *p) {
    strncpy(p->name, "侠客", MAX_NAME_LEN-1);
    p->hp = 100;
    p->attack = 15;
    p->defense = 10;
    p->x = MAP_WIDTH/2;
    p->y = MAP_HEIGHT/2;
}

/**
 * 初始化敌人角色属性（根据等级成长）
 * @param e 敌人指针
 * @param level 当前关卡等级
 */
void init_enemy(Character *e, int level) {
    snprintf(e->name, MAX_NAME_LEN, "黑衣人%d号", level);
    e->hp = 50 + level*10;
    e->attack = 8 + level*2;
    e->defense = 5 + level;
    e->x = rand()%MAP_WIDTH;
    e->y = rand()%MAP_HEIGHT;
}

void show_status(Character *ch) {
    clear_screen();
    printf("=== 角色状态 ===\n");
    printf("姓名：%s\n生命：%d\n攻击：%d\n防御：%d\n", 
           ch->name, ch->hp, ch->attack, ch->defense);
    printf("\n按回车返回...");
    fflush(stdout);
    getchar();
}