CC = gcc
CFLAGS = -Iinclude -Wall -Werror
LDFLAGS = -lwinmm
BIN_DIR = bin
SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

all: $(BIN_DIR)/wuxia.exe

$(BIN_DIR)/wuxia.exe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	cmd /C "if not exist "$@" mkdir "$@""

clean:
	rm -f bin/*.o bin/wuxia.exe

# 新增编码配置验证步骤
check-encoding:
	@echo [INFO] 正在验证终端编码配置...
	powershell -Command "if (!(Test-Path $PROFILE)) { New-Item -Type File -Path $PROFILE -Force }; Add-Content $PROFILE '[Console]::OutputEncoding = [System.Text.Encoding]::UTF8'; . $PROFILE"
	@echo [SUCCESS] 已永久配置控制台UTF-8编码

run: all
	@echo "======== 运行游戏 ========"
	.\$(BIN_DIR)\wuxia.exe

.PHONY: all clean run