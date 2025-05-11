#include "combat.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/**
 * 决定战斗出手顺序
 * @param player_speed 玩家角色速度值
 * @param enemy_speed 敌人速度值
 * @return 1-玩家先手 0-敌人先手
 */
int determine_order(int player_speed, int enemy_speed) {
    return player_speed >= enemy_speed ? 1 : 0;
}

/**
 * 计算战斗伤害值（攻击-防御/2，最小伤害1点）
 * @param attacker 攻击方角色指针
 * @param defender 防御方角色指针
 * @return 计算后的伤害值
 */
int calculate_damage(Character *attacker, Character *defender) {
    int damage = attacker->attack - (defender->defense / 2);
    return damage > 0 ? damage : 1;
}

void battle_system(Character *player, Character *enemy) {
    int round = 1;
    int first_move = determine_order(player->speed, enemy->speed);
    
    while(player->hp > 0 && enemy->hp > 0) {
        Character *attacker = first_move ? player : enemy;
        Character *defender = first_move ? enemy : player;
        
        printf("\n===== 第%d回合 =====\n", round++);
        
        int damage = calculate_damage(attacker, defender);
        defender->hp -= damage;
        
        printf("%s发动攻击！造成%d点伤害\n", attacker->name, damage);
        printf("%s剩余生命：%d\n", defender->name, defender->hp);
        
        fflush(stdout);
        Sleep(1500);
        first_move = !first_move;
    }
}

