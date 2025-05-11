#include <stdio.h>
#include <time.h>
// 假设 character.h 文件在 include 目录下，根据错误提示修改包含路径
#include "../include/character.h"
// 尝试修正头文件包含路径，可能 combat.h 文件在其他目录，这里假设在当前目录下
// 假设 combat.h 文件在 include 目录下，更新包含路径
#include "../include/combat.h"
#include <windows.h>
#include "../include/display.h"

// 模块化后的主程序入口

int main() {
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    Character player;
    init_player(&player);
    
    printf("武侠世界开启！\n");
    
    int choice;
    int battle_count = 0;
    
    GameMap world;
    init_map(&world);
    
    // 初始化玩家位置
    player.x = MAP_WIDTH/2;
    player.y = MAP_HEIGHT/2;
    
    while(1) {
        clear_screen();
        draw_map(&world);
        draw_entity(player.x, player.y, '@');
        Sleep(100);

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
                init_enemy(&enemy, battle_count);
                battle_system(&player, &enemy);
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