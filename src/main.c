#include <stdio.h>
#include <time.h>
#include <conio.h>
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

        printf("\n\n===== 武侠世界 =====\n");
        printf("1. 闯荡江湖\n2. 查看状态\n3. 地图移动\n4. 退出游戏\n请选择：");
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = -1;
        }
        while(getchar() != '\n');

        if(choice == 4) break;

        switch(choice) {
            case 3: {
                printf("进入地图移动模式（按回车退出）\n");
                while(1) {
                    int moved = 0;
                    if(_kbhit()) {
                        int ch = _getch();
                        if(ch == '\r') break;
                        
                        if(ch == 0 || ch == 0xE0) {
                            ch = _getch();
                            switch(ch) {
                                case 72: // 上
                                    if(player.y > 0 && world.tiles[player.y-1][player.x] != WALL) {
                                        player.y--;
                                        moved = 1;
                                    }
                                    break;
                                case 80: // 下
                                    if(player.y < MAP_HEIGHT-1 && world.tiles[player.y+1][player.x] != WALL) {
                                        player.y++;
                                        moved = 1;
                                    }
                                    break;
                                case 75: // 左
                                    if(player.x > 0 && world.tiles[player.y][player.x-1] != WALL) {
                                        player.x--;
                                        moved = 1;
                                    }
                                    break;
                                case 77: // 右
                                    if(player.x < MAP_WIDTH-1 && world.tiles[player.y][player.x+1] != WALL) {
                                        player.x++;
                                        moved = 1;
                                    }
                                    break;
                            }
                        }
                        moved = 1; // 强制刷新以响应快速按键
                    }
                    
                    // 在移动检测逻辑后添加碰撞检测
                    if(moved) {
                        for(int i=0; i<MAX_ENEMIES; i++) {
                            if(world.enemies[i].active && 
                               world.enemies[i].x == player.x && 
                               world.enemies[i].y == player.y) {
                                Character enemy;
                                init_enemy(&enemy, battle_count++);
                                battle_system(&player, &enemy);
                                world.enemies[i].active = 0;
                                break;
                            }
                        }
                        
                        clear_screen();
                        draw_map(&world);
                        // 绘制敌人
                        for(int i=0; i<MAX_ENEMIES; i++) {
                            if(world.enemies[i].active) {
                                draw_entity(world.enemies[i].x, world.enemies[i].y, 'E');
                            }
                        }
                        draw_entity(player.x, player.y, '@');
                        moved = 0;
                    }
                    Sleep(50); // 提高响应频率
                }
                fflush(stdin);
                break;
            }
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

// 删除main.c中的init_map函数实现