#include <stdio.h>
#include <time.h>
#include "../include/character.h"
#include "../include/combat.h"
#include <windows.h>
#include "../include/display.h"

/**
 * 游戏主循环模块
 * @note 包含地图渲染、菜单交互和战斗触发
 * 使用Windows控制台API进行编码配置
 */
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