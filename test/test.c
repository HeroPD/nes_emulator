#include <stdio.h>
#include <string.h>
#include <bus.h>
#include <nes6502.h>
#include <log.h>

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

int lda_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
        STA $01
        LDA #$01
        LDA $01
    */
    uint8_t code [] = "a9 25 85 01 a9 01 a5 01";
    load_code(ram, cpustate, code, sizeof code);
    for(int i = 0; i < 4; i++) {
        clock(&cpustate, ram);
    }
    if (nesbus_read(ram, 0x0001) == 0x25 && cpustate.a == 0x25) {
        return 0;
    }
    return 1;
}

int lda_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
        LDX #$01
        STA $01, X
        LDA #$01
        LDA $01, X
    */
    uint8_t code [] = "a9 25 a2 01 95 01 a9 01 b5 01";
    load_code(ram, cpustate, code, sizeof code);
    for(int i = 0; i < 5; i++) {
        clock(&cpustate, ram);
    }
    if (nesbus_read(ram, 0x01 + cpustate.x) == 0x25 && cpustate.a == 0x25 && cpustate.x == 0x01) {
        return 0;
    }
    return 1;
}

int lda_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
        STA $0003
        LDA #$01
        LDA $0003
    */
    uint8_t code [] = "a9 25 8d 03 00 a9 01 ad 03 00";
    load_code(ram, cpustate, code, sizeof code);
    for(int i = 0; i < 4; i++) {
        clock(&cpustate, ram);
    }
    if (nesbus_read(ram, 0x0003) == 0x25 && cpustate.a == 0x25) {
        return 0;
    }
    return 1;
}

int lda_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
        STA $0004
        LDA #$01
        LDX #$01
        LDA $0003, X
    */
    uint8_t code [] = "a9 25 8d 04 00 a9 01 a2 01 bd 03 00";
    load_code(ram, cpustate, code, sizeof code);
    for(int i = 0; i < 5; i++) {
        clock(&cpustate, ram);
    }
    if (nesbus_read(ram, 0x0004) == 0x25 && cpustate.a == 0x25) {
        return 0;
    }
    return 1;
}

int lda_aby() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDA #$25
        STA $0004
        LDA #$01
        LDY #$01
        LDA $0003, Y
    */
    uint8_t code [] = "a9 25 8d 04 00 a9 01 a0 01 b9 03 00";
    load_code(ram, cpustate, code, sizeof code);
    for(int i = 0; i < 5; i++) {
        clock(&cpustate, ram);
    }
    if (nesbus_read(ram, 0x0004) == 0x25 && cpustate.a == 0x25) {
        return 0;
    }
    return 1;
}

int lda_indX() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX #$01
        LDA ($19, X)
    */
    uint8_t code [] = "a2 01 a1 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0021, 0x20);
    nesbus_write(ram, 0x0022, 0x21);
    nesbus_write(ram, 0x2120, 0xf2);
    for(int i = 0; i < 2; i++) {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0xf2) {
        return 0;
    }
    return 1;
}

int lda_indY() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY #$1
        LDA ($20), Y
    */
    uint8_t code [] = "a0 01 b1 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    nesbus_write(ram, 0x0021, 0x21);
    nesbus_write(ram, 0x2121, 0xf2);
    for(int i = 0; i < 2; i++) {
        clock(&cpustate, ram);
    }
    if (cpustate.a == 0xf2) {
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

int ldx_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX $20
    */
    uint8_t code [] = "a6 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    clock(&cpustate, ram);
    if (cpustate.x == 0x21) {
        return 0;
    }
    return 1;
}

int ldx_zpy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX $20, Y
    */
    uint8_t code [] = "b6 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0022, 0x21);
    cpustate.y = 0x02;
    clock(&cpustate, ram);
    if (cpustate.x == 0x21) {
        return 0;
    }
    return 1;
}

int ldx_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX $2000
    */
    uint8_t code [] = "ae 00 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x2000, 0x21);
    clock(&cpustate, ram);
    if (cpustate.x == 0x21) {
        return 0;
    }
    return 1;
}

int ldx_aby() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDX $2000, Y
    */
    uint8_t code [] = "be 00 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x2002, 0x21);
    cpustate.y = 0x02;
    clock(&cpustate, ram);
    if (cpustate.x == 0x21) {
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

int ldy_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY $20
    */
    uint8_t code [] = "a4 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0xcb);
    clock(&cpustate, ram);
    if (cpustate.y == 0xcb) {
        return 0;
    }
    return 1;
}

int ldy_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY $20, X
    */
    uint8_t code [] = "b4 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0025, 0xcf);
    cpustate.x = 0x05;
    clock(&cpustate, ram);
    if (cpustate.y == 0xcf) {
        return 0;
    }
    return 1;
}

int ldy_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY $2001
    */
    uint8_t code [] = "ac 01 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x2001, 0xde);
    clock(&cpustate, ram);
    if (cpustate.y == 0xde) {
        return 0;
    }
    return 1;
}

int ldy_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LDY $2015, X
    */
    uint8_t code [] = "bc 15 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x203a, 0xcf);
    cpustate.x = 0x25;
    clock(&cpustate, ram);
    if (cpustate.y == 0xcf) {
        return 0;
    }
    return 1;
}

// LDY TESTS 33

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

int lsr_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LSR $1b, X
    */
    uint8_t code [] = "56 1b";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.x = 0x5;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

int lsr_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LSR $0020
    */
    uint8_t code [] = "4e 20 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

int lsr_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        LSR $001b, X
    */
    uint8_t code [] = "5e 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.x = 0x5;
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

int ora_zp0() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA $20
    */
    uint8_t code [] = "05 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA $1b, X
    */
    uint8_t code [] = "15 1b";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.x = 0x5;
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA $0020
    */
    uint8_t code [] = "0d 20 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA $001b, X
    */
    uint8_t code [] = "1d 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.x = 0x5;
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_aby() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA $001b, Y
    */
    uint8_t code [] = "19 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x20);
    cpustate.y = 0x5;
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_indx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA ($1b, X)
    */
    uint8_t code [] = "01 05";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x11);
    nesbus_write(ram, 0x0021, 0x12);
    nesbus_write(ram, 0x1211, 0x20);
    cpustate.x = 0x1b;
    cpustate.a = 0x11;
    clock(&cpustate, ram);
    if (cpustate.a == 0x31) {
        return 0;
    }
    return 1;
}

int ora_indy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    /*source
        ORA ($20), Y
    */
    uint8_t code [] = "11 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x11);
    nesbus_write(ram, 0x0021, 0x12);
    nesbus_write(ram, 0x1216, 0x20);
    cpustate.y = 0x5;
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

int rol_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROL $20, X
    */
    uint8_t code [] = "36 1b";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    cpustate.x = 0x5;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x42) {
        return 0;
    }
    return 1;
}

int rol_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROL $0020
    */
    uint8_t code [] = "2e 20 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x42) {
        return 0;
    }
    return 1;
}

int rol_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROL $0020, X
    */
    uint8_t code [] = "3e 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    cpustate.x = 0x5;
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

int ror_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROR $1b, X
    */
    uint8_t code [] = "76 1b";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    cpustate.x = 0x5;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

int ror_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROR $0020
    */
    uint8_t code [] = "6e 20 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x10) {
        return 0;
    }
    return 1;
}

int ror_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        ROR $001b, X
    */
    uint8_t code [] = "7e 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x21);
    cpustate.x = 0x5;
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

int sta_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA $20
    */
    uint8_t code [] = "95 1b";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x5;
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x15) {
        return 0;
    }
    return 1;
}

int sta_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA $0020
    */
    uint8_t code [] = "8d 20 00";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x15) {
        return 0;
    }
    return 1;
}

int sta_abx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA $001b, X
    */
    uint8_t code [] = "9d 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x5;
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x15) {
        return 0;
    }
    return 1;
}

int sta_aby() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA $001b, Y
    */
    uint8_t code [] = "99 1b 00";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x5;
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x15) {
        return 0;
    }
    return 1;
}

int sta_indx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA ($20), X
    */
    uint8_t code [] = "81 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0025, 0x11);
    nesbus_write(ram, 0x0026, 0x12);
    cpustate.x = 0x5;
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x1211) == 0x15) {
        return 0;
    }
    return 1;
}

int sta_indy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STA ($0020), Y
    */
    uint8_t code [] = "91 20";
    load_code(ram, cpustate, code, sizeof code);
    nesbus_write(ram, 0x0020, 0x11);
    nesbus_write(ram, 0x0021, 0x12);
    cpustate.y = 0x5;
    cpustate.a = 0x15;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x1216) == 0x15) {
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

int stx_zpy() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STX $20, Y
    */
    uint8_t code [] = "96 1b";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.x = 0x3d;
    cpustate.y = 0x5;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0020) == 0x3d) {
        return 0;
    }
    return 1;
}

int stx_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STX $0020
    */
    uint8_t code [] = "8e 20 00";
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

int sty_zpx() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STY $20, X
    */
    uint8_t code [] = "94 20";
    load_code(ram, cpustate, code, sizeof code);
    cpustate.y = 0x3d;
    cpustate.x = 0x5;
    clock(&cpustate, ram);
    if (nesbus_read(ram, 0x0025) == 0x3d) {
        return 0;
    }
    return 1;
}

int sty_abs() {
    uint8_t * ram = calloc(64 * 1024, sizeof(uint8_t));
    cpu6502 cpustate;
    cpustate.pc = 0x8000;
    cpustate.sp = 0xff;
    /*source
        STY $0020
    */
    uint8_t code [] = "8c 20 00";
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
    printf("hello world %d %s\n", argc, argv[1]);
    char * test_name = argv[1];
    if (strcmp(test_name, "LDA IMM") == 0) {
        return lda_imm();
    } else if (strcmp(test_name, "LDA ZP0") == 0) {
        return lda_zp0();
    } else if (strcmp(test_name, "LDA ZPX") == 0) {
        return lda_zpx();
    } else if (strcmp(test_name, "LDA ABS") == 0) {
        return lda_abs();
    } else if (strcmp(test_name, "LDA ABX") == 0) {
        return lda_abx();
    } else if (strcmp(test_name, "LDA ABY") == 0) {
        return lda_aby();
    } else if (strcmp(test_name, "LDA INDX") == 0) {
        return lda_indX();
    } else if (strcmp(test_name, "LDA INDY") == 0) {
        return lda_indY();
    } else if (strcmp(test_name, "LDX IMM") == 0) {
        return ldx_imm();
    } else if (strcmp(test_name, "LDX ZP0") == 0) {
        return ldx_imm();
    } else if (strcmp(test_name, "LDX ZPY") == 0) {
        return ldx_zpy();
    } else if (strcmp(test_name, "LDX ABS") == 0) {
        return ldx_abs();
    } else if (strcmp(test_name, "LDX ABY") == 0) {
        return ldx_aby();
    } else if (strcmp(test_name, "LDY IMM") == 0) {
        return ldy_imm();
    } else if (strcmp(test_name, "LDY ZP0") == 0) {
        return ldy_zp0();
    } else if (strcmp(test_name, "LDY ZPX") == 0) {
        return ldy_zpx();
    } else if (strcmp(test_name, "LDY ABS") == 0) {
        return ldy_abs();
    } else if (strcmp(test_name, "LDY ABX") == 0) {
        return ldy_abx();
    } else if (strcmp(test_name, "LSR A") == 0) {
        return lsr_a();
    } else if (strcmp(test_name, "LSR ZP0") == 0) {
        return lsr_zp0();
    } else if (strcmp(test_name, "LSR ZPX") == 0) {
        return lsr_zpx();
    } else if (strcmp(test_name, "LSR ABS") == 0) {
        return lsr_abs();
    } else if (strcmp(test_name, "LSR ABX") == 0) {
        return lsr_abx();
    } else if (strcmp(test_name, "ORA IMM") == 0) {
        return ora_imm();
    } else if (strcmp(test_name, "ORA ZP0") == 0) {
        return ora_zp0();
    } else if (strcmp(test_name, "ORA ZPX") == 0) {
        return ora_zpx();
    } else if (strcmp(test_name, "ORA ABS") == 0) {
        return ora_abs();
    } else if (strcmp(test_name, "ORA ABX") == 0) {
        return ora_abx();
    } else if (strcmp(test_name, "ORA ABY") == 0) {
        return ora_aby();
    } else if (strcmp(test_name, "ORA INDX") == 0) {
        return ora_indx();
    } else if (strcmp(test_name, "ORA INDY") == 0) {
        return ora_indy();
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
    } else if (strcmp(test_name, "ROL_ZPX") == 0) {
        return rol_zpx();
    } else if (strcmp(test_name, "ROL_ABS") == 0) {
        return rol_abs();
    } else if (strcmp(test_name, "ROL_ABX") == 0) {
        return rol_abx();
    } else if (strcmp(test_name, "RORA") == 0) {
        return ror_a();
    } else if (strcmp(test_name, "ROR_ZP0") == 0) {
        return ror_zp0();
    } else if (strcmp(test_name, "ROR_ZPX") == 0) {
        return ror_zpx();
    } else if (strcmp(test_name, "ROR_ABS") == 0) {
        return ror_abs();
    } else if (strcmp(test_name, "ROR_ABX") == 0) {
        return ror_abx();
    } else if (strcmp(test_name, "RTI") == 0) {
        return rti();
    } else if (strcmp(test_name, "RTS") == 0) {
        return rts();
    } else if (strcmp(test_name, "SEC") == 0) {
        return sec();
    } else if (strcmp(test_name, "SED") == 0) {
        return sed();
    } else if (strcmp(test_name, "SEI") == 0) {
        return sei();
    } else if (strcmp(test_name, "STA_ZP0") == 0) {
        return sta_zp0();
    } else if (strcmp(test_name, "STA_ZPX") == 0) {
        return sta_zpx();
    } else if (strcmp(test_name, "STA_ABS") == 0) {
        return sta_abs();
    } else if (strcmp(test_name, "STA_ABX") == 0) {
        return sta_abx();
    } else if (strcmp(test_name, "STA_ABY") == 0) {
        return sta_aby();
    } else if (strcmp(test_name, "STA_INDX") == 0) {
        return sta_indx();
    } else if (strcmp(test_name, "STA_INDY") == 0) {
        return sta_indy();
    } else if (strcmp(test_name, "STX_ZP0") == 0) {
        return stx_zp0();
    } else if (strcmp(test_name, "STX_ZPY") == 0) {
        return stx_zpy();
    } else if (strcmp(test_name, "STX_ABS") == 0) {
        return stx_abs();
    } else if (strcmp(test_name, "STY_ZP0") == 0) {
        return sty_zp0();
    } else if (strcmp(test_name, "STY_ZPX") == 0) {
        return sty_zpx();
    } else if (strcmp(test_name, "STY_ABS") == 0) {
        return sty_abs();
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