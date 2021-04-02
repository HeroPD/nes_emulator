#include <stdio.h>
#include <string.h>
#include <bus.h>
#include <nes6502.h>
#include <log.h>

// Adressing Modes

// IMM TEST 1
int addr_mode_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA #$20
    */
    uint8_t code [] = "a9 20";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (cpustate.a == 0x20 && cpustate.abs_addr == cpustate.pc - 1) {
        return 0;
    }
    return 1;
}

// ZP0 TEST 2
int addr_mode_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA $20
    */
    uint8_t code [] = "a5 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x15);
    clock(&cpustate, ram);
    if (cpustate.a == 0x15 && cpustate.abs_addr == 0x20) {
        return 0;
    }
    return 1;
}

// ZPX TEST 3
int addr_mode_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA $20, X
    */
    uint8_t code [] = "b5 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x05;
    nesbus_write(ram, 0x0025, 0x15);
    clock(&cpustate, ram);
    if (cpustate.a == 0x15 && cpustate.abs_addr == 0x25) {
        return 0;
    }
    return 1;
}

// ZPY TEST 4
int addr_mode_zpy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDX $20, Y
    */
    uint8_t code [] = "B6 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x05;
    nesbus_write(ram, 0x0025, 0x15);
    clock(&cpustate, ram);
    if (cpustate.x == 0x15 && cpustate.abs_addr == 0x25) {
        return 0;
    }
    return 1;
}

// ABS TEST 5
int addr_mode_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA $0120
    */
    uint8_t code [] = "ad 20 01";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0120, 0x15);
    clock(&cpustate, ram);
    if (cpustate.a == 0x15 && cpustate.abs_addr == 0x0120) {
        return 0;
    }
    return 1;
}

// ABX TEST 6
int addr_mode_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA $0120, X
    */
    uint8_t code [] = "bd 20 01";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x05;
    nesbus_write(ram, 0x0125, 0x15);
    clock(&cpustate, ram);
    if (cpustate.a == 0x15 && cpustate.abs_addr == 0x0125) {
        return 0;
    }
    return 1;
}

// ABY TEST 7
int addr_mode_aby() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA $0120, y
    */
    uint8_t code [] = "b9 20 01";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x05;
    nesbus_write(ram, 0x0125, 0x15);
    clock(&cpustate, ram);
    if (cpustate.a == 0x15 && cpustate.abs_addr == 0x0125) {
        return 0;
    }
    return 1;
}

// IND TEST 8
int addr_mode_ind() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        JMP ($0009)
    */
    uint8_t code [] = "6c 09 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0009, 0x09);
    nesbus_write(ram, 0x000a, 0x80);
    clock(&cpustate, ram);
    if (cpustate.abs_addr == 0x8009) {
        return 0;
    }
    return 1;
}

// INDX TEST 9
int addr_mode_indx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA ($09, X)
    */
    uint8_t code [] = "a1 09";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x000e, 0x09);
    nesbus_write(ram, 0x000f, 0x80);
    cpustate.x = 0x05;
    clock(&cpustate, ram);
    if (cpustate.abs_addr == 0x8009) {
        return 0;
    }
    return 1;
}

// INDY TEST 10
int addr_mode_indy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        LDA ($09), Y
    */
    uint8_t code [] = "b1 09";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0009, 0x09);
    nesbus_write(ram, 0x000a, 0x80);
    cpustate.y = 0x05;
    clock(&cpustate, ram);
    if (cpustate.abs_addr == 0x800e) {
        return 0;
    }
    return 1;
}

// REL TEST 11
int addr_mode_rel() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    /*source
        BCC 04
    */
    uint8_t code [] = "90 04";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (cpustate.rel_addr == 0x04) {
        return 0;
    }
    return 1;
}

// ADC TESTS 1

// AND TESTS 2

// ASL TESTS 3

// BCC TESTS 4

int bcc() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate; 
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 0);
    /*source
        LDA #$20
        BCC THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "a9 20 90 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 3; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BCS TESTS 5

int bcs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 1);
    /*source
        LDA #$20
        BCS THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "a9 20 b0 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 3; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BEQ TESTS 6

int beq() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, Z, 1);
    /*source
        BEQ THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "f0 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BIT TESTS 7

int bit() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$f2
        STA $20
        LDA #$81
        BIT $20
    */
    uint8_t code [] = "a9 f2 85 20 a9 81 24 20";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 4; i++)
    {
        clock(&cpustate, ram);
    }
    
    if (check_status(&cpustate, N) && check_status(&cpustate, V)) {
        return 0;
    }
    return 1;
}

// BMI TESTS 8

int bmi() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, N, 1);
    /*source
        BMI THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "30 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BNE TESTS 9

int bne() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, Z, 0);
    /*source
        BNE THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "d0 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BPL TESTS 10

int bpl() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, N, 0);
    /*source
        BPL THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "10 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BRK TESTS 11
// BVC TESTS 12

int bvc() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, V, 0);
    /*source
        BVC THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "50 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// BVS TESTS 13

int bvs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, V, 1);
    /*source
        BVS THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$02
    */
    uint8_t code [] = "70 04 a9 12 85 20 a9 02";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 2; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x02) {
        return 0;
    }
    return 1;
}

// CLC TESTS 14

int clc() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 1);
    /*source
        CLC
    */
    uint8_t code [] = "18";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (!check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// CLD TESTS 15

int cld() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, D, 1);
    /*source
        CLD
    */
    uint8_t code [] = "d8";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (!check_status(&cpustate, D)) {
        return 0;
    }
    return 1;
}

// CLI TEST 16

int cli() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, I, 1);
    /*source
        CLI
    */
    uint8_t code [] = "58";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (!check_status(&cpustate, I)) {
        return 0;
    }
    return 1;
}

// CLV TEST 17

int clv() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, V, 1);
    /*source
        CLV
    */
    uint8_t code [] = "b8";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (!check_status(&cpustate, V)) {
        return 0;
    }
    return 1;
}

// CMP TEST 18

int cmp_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 0);
    /*source
        CMP #$20
    */
    uint8_t code [] = "c9 20 ";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x21;
    clock(&cpustate, ram);
    if (check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// CPX TEST 19

int cpx_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 0);
    /*source
        CMP #$20
    */
    uint8_t code [] = "e0 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x21;
    clock(&cpustate, ram);
    if (check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// CPY TEST 20

int cpy_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    set_status(&cpustate, C, 0);
    /*source
        CMP #$20
    */
    uint8_t code [] = "c0 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x21;
    clock(&cpustate, ram);
    if (check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// DEC TEST 21

int dec_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        DEC $20
    */
    uint8_t code [] = "c6 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x1f) {
        return 0;
    }
    return 1;
}

// DEX TEST 22

int dex() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        DEX
    */
    uint8_t code [] = "ca";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x20;
    clock(&cpustate, ram);
    if (cpustate.x == 0x1f) {
        return 0;
    }
    return 1;
}

// DEY TEST 23

int dey() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        DEY
    */
    uint8_t code [] = "88";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x20;
    clock(&cpustate, ram);
    if (cpustate.y == 0x1f) {
        return 0;
    }
    return 1;
}

// EOR TEST 24

int eor_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        EOR #$21
    */
    uint8_t code [] = "49 21";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x20;
    clock(&cpustate, ram);
    if (cpustate.a == (0x20 ^ 0x21)) {
        return 0;
    }
    return 1;
}

// INC TEST 25

int inc_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        INC $20
    */
    uint8_t code [] = "e6 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x15);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x16) {
        return 0;
    }
    return 1;
}

// INX TEST 26

int inx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        INX
    */
    uint8_t code [] = "e8";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x15;
    clock(&cpustate, ram);
    if (cpustate.x == 0x16) {
        return 0;
    }
    return 1;
}

// INY TEST 27

int iny() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        INY
    */
    uint8_t code [] = "c8";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x15;
    clock(&cpustate, ram);
    if (cpustate.y == 0x16) {
        return 0;
    }
    return 1;
}

// JMP TEST 28

int jmp_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY #$15
        JMP THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$3
        STA $21
    */
    uint8_t code [] = "a0 15 4c 09 80 a9 12 85 20 a9 03 85 21 ";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 4; i++)
    {
        clock(&cpustate, ram);
    }

    if (cpustate.a == 0x3 && nesbus_read(ram, 0x0020) == 0x0 && nesbus_read(ram, 0x0021) == 0x3) {
        return 0;
    }
    return 1;
}

int jmp_ind() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY #$15
        JMP ($0009)
        LDA #$12
        STA $20
        LDA #$3
        STA $21
    */
    uint8_t code [] = "a0 15 6c 09 00 a9 12 85 20 a9 03 85 21";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0009, 0x09);
    nesbus_write(ram, 0x000a, 0x80);
    for (int i = 0; i < 4; i++)
    {
        clock(&cpustate, ram);
    }

    if (cpustate.a == 0x3 && nesbus_read(ram, 0x0020) == 0x0 && nesbus_read(ram, 0x0021) == 0x3) {
        return 0;
    }
    return 1;
}

int jmp_ind_bug() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY #$15
        JMP ($03ff)
        LDA #$12
        STA $20
        LDA #$3
        STA $21
    */
    uint8_t code [] = "a0 15 6c ff 03 a9 12 85 20 a9 03 85 21";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x03ff, 0x09);
    nesbus_write(ram, 0x0300, 0x80);
    for (int i = 0; i < 4; i++)
    {
        clock(&cpustate, ram);
    }

    if (cpustate.a == 0x3 && nesbus_read(ram, 0x0020) == 0x0 && nesbus_read(ram, 0x0021) == 0x3) {
        return 0;
    }
    return 1;
}

// JSR TEST 29

int jsr() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        LDY #$15
        JSR THERE
        LDA #$12
        STA $20
        THERE:
        LDA #$3
        STA $21
    */
    uint8_t code [] = "a0 15 20 09 80 a9 12 85 20 a9 03 85 21";
    load_code(ram, cpustate, code, sizeof code);
    for (int i = 0; i < 4; i++)
    {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0x3 && nesbus_read(ram, 0x0020) == 0x0 && nesbus_read(ram, 0x0021) == 0x3 && cpustate.sp == 0xfd && nesbus_read(ram, 0x01ff) == 0x80 && nesbus_read(ram, 0x01fe) == 0x09) {
        return 0;
    }
    return 1;
}

// LDA TESTS 30
int lda_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
    */
    uint8_t code [] = "a9 25";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (cpustate.a == 0x25) {
        return 0;
    }
    return 1;
}

// LDX TESTS 31

int ldx_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX #$25
    */
    uint8_t code [] = "a2 26";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (cpustate.x == 0x26) {
        return 0;
    }
    return 1;
}

// LDY TESTS 32

int ldy_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY #$f2
    */
    uint8_t code [] = "a0 f2";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (cpustate.y == 0xf2) {
        return 0;
    }
    return 1;
}

// LSR TESTS 33

int lsr_a() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LSR A
    */
    uint8_t code [] = "4a";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x20;
    clock(&cpustate, ram);
    if (cpustate.a == 0x10) {
        return 0;
    }
    return 1;
}

int lsr_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LSR $20
    */
    uint8_t code [] = "46 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

// NOP TESTS 34

// ORA TESTS 35

int ora_imm() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA #$20
    */
    uint8_t code [] = "09 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

// PHA TESTS 36

int pha() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        PHA
    */
    uint8_t code [] = "48";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.sp = 0xff;
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x01ff) == 0x11 && cpustate.sp == 0xfe) {
        return 0;
    }
    return 1;
}

// PHP TESTS 37

int php() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        PHP
    */
    uint8_t code [] = "08";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.sp = 0xff;
    cpustate.status = 0x31;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x01ff) == 0x031 && cpustate.sp == 0xfe) {
        return 0;
    }
    return 1;
}

// PLA TESTS 38

int pla() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        PLA
    */
    uint8_t code [] = "68";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x01ff, 0xf2);
    cpustate.sp = 0xfe;
    clock(&cpustate, ram);
    if (cpustate.sp == 0xff && cpustate.a == 0xf2) {
        return 0;
    }
    return 1;
}

// PLP TESTS 39

int plp() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        PLP
    */
    uint8_t code [] = "28";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x01ff, 0xf2);
    cpustate.sp = 0xfe;
    clock(&cpustate, ram);
    if (cpustate.sp == 0xff && cpustate.status == 0xf2) {
        return 0;
    }
    return 1;
}

// ROL TESTS 40

int rol_a() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROL A
    */
    uint8_t code [] = "2a";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x21;
    clock(&cpustate, ram);
    if (cpustate.a == 0x42) {
        return 0;
    }
    return 1;
}

int rol_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROL $20
    */
    uint8_t code [] = "26 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x42) {
        return 0;
    }
    return 1;
}

// ROR TESTS 41

int ror_a() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROR A
    */
    uint8_t code [] = "6a";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x21;
    clock(&cpustate, ram);
    if (cpustate.a == 0x10) {
        return 0;
    }
    return 1;
}

int ror_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROR $20
    */
    uint8_t code [] = "66 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

// RTI TESTS 42

int rti() {
    return 1;
}

// RTS TESTS 43

int rts() {
    return 1;
}

// SBC TESTS 44

int sbc() {
    return 1;
}

// SEC TESTS 45

int sec() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        SEC
    */
    uint8_t code [] = "38";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// SED TESTS 46

int sed() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        SEC
    */
    uint8_t code [] = "f8";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (!check_status(&cpustate, C)) {
        return 0;
    }
    return 1;
}

// SEI TESTS 47

int sei() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        SEI
    */
    uint8_t code [] = "78";
    load_code(ram, cpustate, code, sizeof code);
    clock(&cpustate, ram);
    if (check_status(&cpustate, I)) {
        return 0;
    }
    return 1;
}

// STA TESTS 48

int sta_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA $20
    */
    uint8_t code [] = "85 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x15) {
        return 0;
    }
    return 1;
}

// STX TESTS 49

int stx_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STX $20
    */
    uint8_t code [] = "86 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x3d;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x3d) {
        return 0;
    }
    return 1;
}

// STY TESTS 50

int sty_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STY $20
    */
    uint8_t code [] = "84 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x3d;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x3d) {
        return 0;
    }
    return 1;
}

// TAX TESTS 51

int tax() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TAX
    */
    uint8_t code [] = "aa";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.x == 0x3d) {
        return 0;
    }
    return 1;
}

// TAY TESTS 52

int tay() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TAY
    */
    uint8_t code [] = "a8";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.y == 0x3d) {
        return 0;
    }
    return 1;
}

// TSX TESTS 53

int tsx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TSX
    */
    uint8_t code [] = "ba";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.sp = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.x == 0x3d) {
        return 0;
    }
    return 1;
}

// TXA TESTS 54

int txa() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TXA
    */
    uint8_t code [] = "8a";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.a == 0x3d) {
        return 0;
    }
    return 1;
}

// TXS TESTS 55

int txs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TXS
    */
    uint8_t code [] = "9a";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.sp == 0x3d) {
        return 0;
    }
    return 1;
}

// TYA TESTS 56

int tya() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        TYA
    */
    uint8_t code [] = "98";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x3d;
    clock(&cpustate, ram);
    if (cpustate.a == 0x3d) {
        return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    init_logfile();
    char * test_name = argv[1];
    if (strcmp(test_name, "IMM") == 0) {
        return addr_mode_imm();
    } else if (strcmp(test_name, "ZP0") == 0) {
        return addr_mode_zp0();
    } else if (strcmp(test_name, "ZPX") == 0) {
        return addr_mode_zpx();
    } else if (strcmp(test_name, "ZPY") == 0) {
        return addr_mode_zpy();
    } else if (strcmp(test_name, "ABS") == 0) {
        return addr_mode_abs();
    } else if (strcmp(test_name, "ABX") == 0) {
        return addr_mode_abx();
    } else if (strcmp(test_name, "ABY") == 0) {
        return addr_mode_aby();
    } else if (strcmp(test_name, "IND") == 0) {
        return addr_mode_ind();
    } else if (strcmp(test_name, "INDX") == 0) {
        return addr_mode_indx();
    } else if (strcmp(test_name, "INDY") == 0) {
        return addr_mode_indy();
    } else if (strcmp(test_name, "REL") == 0) {
        return addr_mode_rel();
    } else if (strcmp(test_name, "BCC") == 0) {
        return bcc();
    } else if (strcmp(test_name, "BCS") == 0) {
        return bcs();
    } else if (strcmp(test_name, "BEQ") == 0) {
        return beq();
    } else if (strcmp(test_name, "BIT") == 0) {
        return bit();
    } else if (strcmp(test_name, "BMI") == 0) {
        return bmi();
    } else if (strcmp(test_name, "BNE") == 0) {
        return bne();
    } else if (strcmp(test_name, "BPL") == 0) {
        return bpl();
    } else if (strcmp(test_name, "BVC") == 0) {
        return bvc();
    } else if (strcmp(test_name, "BVS") == 0) {
        return bvs();
    }  else if (strcmp(test_name, "CLC") == 0) {
        return clc();
    } else if (strcmp(test_name, "CLD") == 0) {
        return cld();
    } else if (strcmp(test_name, "CLI") == 0) {
        return cli();
    } else if (strcmp(test_name, "CLV") == 0) {
        return clv();
    } else if (strcmp(test_name, "CMP_IMM") == 0) {
        return cmp_imm();
    } else if (strcmp(test_name, "CPX_IMM") == 0) {
        return cpx_imm();
    } else if (strcmp(test_name, "CPY_IMM") == 0) {
        return cpy_imm();
    } else if (strcmp(test_name, "DEC_ZP0") == 0) {
        return dec_zp0();
    } else if (strcmp(test_name, "DEX") == 0) {
        return dex();
    } else if (strcmp(test_name, "DEY") == 0) {
        return dey();
    } else if (strcmp(test_name, "EOR_IMM") == 0) {
        return eor_imm();
    } else if (strcmp(test_name, "INC_ZP0") == 0) {
        return inc_zp0();
    } else if (strcmp(test_name, "INX") == 0) {
        return inx();
    } else if (strcmp(test_name, "INY") == 0) {
        return iny();
    } else if (strcmp(test_name, "JMP_ABS") == 0) {
        return jmp_abs();
    } else if (strcmp(test_name, "JMP_IND") == 0) {
        return jmp_ind();
    } else if (strcmp(test_name, "JMP_IND_BUG") == 0) {
        return jmp_ind_bug();
    } else if (strcmp(test_name, "JSR") == 0) {
        return jsr();
    } else if (strcmp(test_name, "LDA IMM") == 0) {
        return lda_imm();
    } else if (strcmp(test_name, "LDX IMM") == 0) {
        return ldx_imm();
    } else if (strcmp(test_name, "LDY IMM") == 0) {
        return ldy_imm();
    } else if (strcmp(test_name, "LSR A") == 0) {
        return lsr_a();
    } else if (strcmp(test_name, "LSR ZP0") == 0) {
        return lsr_zp0();
    } else if (strcmp(test_name, "ORA IMM") == 0) {
        return ora_imm();
    } else if (strcmp(test_name, "PHA") == 0) {
        return pha();
    } else if (strcmp(test_name, "PHP") == 0) {
        return php();
    } else if (strcmp(test_name, "PLA") == 0) {
        return pla();
    } else if (strcmp(test_name, "PLP") == 0) {
        return plp();
    } else if (strcmp(test_name, "ROLA") == 0) {
        return rol_a();
    } else if (strcmp(test_name, "ROL_ZP0") == 0) {
        return rol_zp0();
    } else if (strcmp(test_name, "RORA") == 0) {
        return ror_a();
    } else if (strcmp(test_name, "ROR_ZP0") == 0) {
        return ror_zp0();
    } else if (strcmp(test_name, "RTI") == 0) {
        return rti();
    } else if (strcmp(test_name, "RTS") == 0) {
        return rts();
    } else if (strcmp(test_name, "SBC") == 0) {
        return rts();
    } else if (strcmp(test_name, "SEC") == 0) {
        return sec();
    } else if (strcmp(test_name, "SED") == 0) {
        return sed();
    } else if (strcmp(test_name, "SEI") == 0) {
        return sei();
    } else if (strcmp(test_name, "STA_ZP0") == 0) {
        return sta_zp0();
    } else if (strcmp(test_name, "STX_ZP0") == 0) {
        return stx_zp0();
    } else if (strcmp(test_name, "STY_ZP0") == 0) {
        return sty_zp0();
    } else if (strcmp(test_name, "TAX") == 0) {
        return tax();
    } else if (strcmp(test_name, "TAY") == 0) {
        return tay();
    } else if (strcmp(test_name, "TSX") == 0) {
        return tsx();
    } else if (strcmp(test_name, "TXA") == 0) {
        return txa();
    } else if (strcmp(test_name, "TXS") == 0) {
        return txs();
    } else if (strcmp(test_name, "TYA") == 0) {
        return tya();
    }
    return 1;
}