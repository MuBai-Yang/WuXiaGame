#include "combat.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int determine_order(int player_speed, int enemy_speed) {
    return player_speed >= enemy_speed ? 1 : 0;
}

void battle_system(Character *player, Character *enemy) {
    int round = 1;
    int first_move = determine_order(player->speed, enemy->speed);
    
    printf("\n===== 第%d回合 =====", round);
    
    while(player->hp > 0 && enemy->hp > 0) {
        Character *attacker = first_move ? player : enemy;
        Character *defender = first_move ? enemy : player;
        
        int damage = attacker->attack - (defender->defense / 2);
        damage = damage > 0 ? damage : 1;
        defender->hp -= damage;
        
        printf("\n%s发动攻击！造成%d点伤害", attacker->name, damage);
        printf("\n%s剩余生命：%d", defender->name, defender->hp);
        
        if(defender->hp <= 0) break;
        
        first_move = !first_move;
        round++;
    }
    
    printf("\n\n战斗结束！");
    show_status(player);
}