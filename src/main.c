#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bus.h"
#include <curses.h>
#include <unistd.h>
#include "nes6502.h"
#include "log.h"

#define REDPAIR 1
#define GREENPAIR 2

void display_ram(uint8_t * ram) {
    int row = 1;
    int col = 1;
    for (int i = 0; i < 16; i++) {
        int ccol = col;
        mvprintw(row, ccol, "%.4x",i*16);
        ccol += 5;
        for (int j = 0; j < 16; j++) {
            mvprintw(row, ccol, "%.2x", nesbus_read(ram, i * 16 + j));
            ccol += 3;
        }
        row++;
    }
    row++;
    for (int i = 2048; i < 2048 + 16; i++) {
        int ccol = col;
        mvprintw(row, ccol, "%.4x", i*16);
        ccol += 5;
        for (int j = 0; j < 16; j++) {
            mvprintw(row, ccol, "%.2x", nesbus_read(ram, i * 16 + j));
            ccol += 3;
        }
        row++;
    }
}

void display_cpustate(cpu6502 * state) {
    int row = 1;
    int col = 56;
    mvprintw(row, col, "CPU STATE");
    row++;
    mvprintw(row, col, "A         %.2x", state->a);
    row++;
    mvprintw(row, col, "X         %.2x", state->x);
    row++;
    mvprintw(row, col, "Y         %.2x", state->y);
    row++;
    mvprintw(row, col, "SP        %.2x", state->sp);
    row++;
    mvprintw(row, col, "PC        %.2x", state->pc);
    row++;
    mvprintw(row, col, "ABS_ADDR  %.4x", state->abs_addr);
    row++;
    mvprintw(row, col, "STATUS");
    col += 7;
    check_status(state, N) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "N");
    col +=2;
    check_status(state, V) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "V");
    col +=2;
    check_status(state, U) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "U");
    col +=2;
    check_status(state, B) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "B");
    col +=2;
    check_status(state, D) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "D");
    col +=2;
    check_status(state, I) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "I");
    col +=2;
    check_status(state, Z) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "Z");
    col +=2;
    check_status(state, C) ? attrset(COLOR_PAIR(GREENPAIR)) : attrset(COLOR_PAIR(REDPAIR));
    mvprintw(row, col, "C");
    attrset(COLOR_PAIR(0));
}

void display_menu() {
    int row = 36;
    int col = 1;
    mvprintw(row, col, "MENU");
    row++;
    mvprintw(row, col, "Press C: STEP    Press R: Reset");
}

void display_render(cpu6502 * state, uint8_t * ram) {
	display_ram(ram);
    display_cpustate(state);
    display_menu();
    refresh();
}

int main() {
    init_logfile();
    log_debug("\n\nEmulator started\n\n");
    // RAM connected to CPU BUS
    uint8_t * ram;
    // accumulator
    
    ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;

    /*source
        LDA #$01
        STA $0100
        LDA #$05
        STA $0200
        LDA #$08
        STA $0300
    */

    // uint8_t code [] = "a9 01 8d 01 00 ad ff 00 8d 02 00 a9 08 8d 03 00";
    uint8_t code [] = "a9 10 85 25 a9 11 85 26 a2 24 81 01 a9 01 a1 01";
    load_code(ram, cpustate, code, sizeof code);
    initscr();
    use_default_colors();
    start_color();
    init_pair(REDPAIR, COLOR_RED, -1);
    init_pair(GREENPAIR, COLOR_GREEN, -1);
    int isBreak = 1; 
    while (isBreak) {
        display_render(&cpustate, ram);
        char c = getch();
        switch (c) {
            case 'c':
                clock(&cpustate, ram);
                break;
            case 'r':
                break;
            default:
                isBreak = 0;
                break;
        }
    }
    endwin();
    return 0;
}