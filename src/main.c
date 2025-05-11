#include <stdio.h>
#include <time.h>
#include "character.h"
#include "combat.h"
#include <windows.h>

// 模块化后的主程序入口

int main() {
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    Character player, enemy;
    init_player(&player);
    
    printf("武侠世界开启！\n");
    
    int choice;
    int battle_count = 0;
    
    while(1) {
        printf("\n===== 武侠世界 =====\n");
        printf("1. 闯荡江湖\n2. 查看状态\n3. 退出游戏\n请选择：");
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = -1;
        }
        while(getchar() != '\n');
        
        if(choice == 3) break;
        
        switch(choice) {
            case 1: {
                battle_count++;
                Character enemy;
                init_enemy(&enemy, (battle_count-1)/3 + 1);
                battle_system(&player, &enemy);
                
                if(player.hp <= 0) {
                    printf("\n游戏结束！共经历%d场战斗\n", battle_count);
                    return 0;
                }
                break;
            }
            case 2:
                show_status(&player);
                break;
            default:
                printf("无效选择！\n");
        }
    }
    printf("\n后会有期！\n");
    return 0;
}