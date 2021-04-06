#include "nes6502.h"
#include "log.h"
#include "bus.h"

void set_status(cpu6502 * state, StatusType type, bool value) {
    if (value) {
        state->status = state->status | type;
    } else {
        state->status = state->status & ~type;
    }
}

bool check_status(cpu6502 * state, StatusType type) {
    return (state->status & type) > 0 ? 1 : 0;
}

// Addressing Mode

uint8_t IMP(cpu6502 * state) {
    log_debug("IMP ");
    return 0;
}

uint8_t IMM(cpu6502 * state) {
    state->abs_addr = state->pc;
    state->pc++;
    log_debug("IMM - %x ", state->abs_addr);
    return 0;
}

uint8_t ZP0(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = nesbus_read(ram, state->pc) & 0x00FF;
    state->pc++;
    log_debug("ZP0 - %x ", state->abs_addr);
    return 0;
}

uint8_t ZPX(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = (nesbus_read(ram, state->pc) + state->x) & 0x00FF;
    state->pc++;
    log_debug("ZPX - %x ", state->abs_addr);
    return 0;
}

uint8_t ZPY(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = (nesbus_read(ram, state->pc) + state->y) & 0x00FF;
    state->pc++;
    log_debug("ZPY - %x ", state->abs_addr);
    return 0;
}

uint8_t ABS(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = nesbus_read(ram, state->pc) | nesbus_read(ram, state->pc + 1) << 8;
    state->pc += 2;
    log_debug("ABS - %x ", state->abs_addr);
    return 0;
}

uint8_t ABX(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = nesbus_read(ram, state->pc) | nesbus_read(ram, state->pc + 1) << 8;
    state->abs_addr += state->x;
    state->pc += 2;
    log_debug("ABX - %x ", state->abs_addr);
    return 0;
}

uint8_t ABY(cpu6502 * state, uint8_t * ram) {
    state->abs_addr = nesbus_read(ram, state->pc) | nesbus_read(ram, state->pc + 1) << 8;
    state->abs_addr += state->y;
    state->pc += 2;
    log_debug("ABY - %x ", state->abs_addr);
    return 0;
}

uint8_t IND(cpu6502 * state, uint8_t * ram) {
    uint16_t ptr = nesbus_read(ram, state->pc) | nesbus_read(ram, state->pc + 1) << 8;
    if ((ptr & 0x00FF) == 0x00FF) {
        state->abs_addr = nesbus_read(ram, ptr) | nesbus_read(ram, ptr & 0xFF00) << 8;
    } else {
        state->abs_addr = nesbus_read(ram, ptr) | nesbus_read(ram, ptr + 1) << 8;
    }
    state->pc += 2;
    log_debug("IND - %x ", state->abs_addr);
    return 0;
}

uint8_t INDX(cpu6502 * state, uint8_t * ram) {
    uint16_t ptr = nesbus_read(ram, state->pc);
    state->abs_addr = (nesbus_read(ram, ptr + state->x) & 0x00FF) | (nesbus_read(ram, ptr + state->x + 1) & 0x00FF) << 8;
    state->pc++;
    log_debug("INDX - %x ", state->abs_addr);
    return 0;
}

uint8_t INDY(cpu6502 * state, uint8_t * ram) {
    uint16_t ptr = nesbus_read(ram, state->pc);
    state->abs_addr = ((nesbus_read(ram, ptr) & 0x00FF) | (nesbus_read(ram, ptr + 1) & 0x00FF) << 8) + state->y;
    state->pc++;
    log_debug("INY - %x ", state->abs_addr);
    return 0;
}

uint8_t REL(cpu6502 * state, uint8_t * ram) {
    state->rel_addr = nesbus_read(ram, state->pc);
	state->pc++;
    if (state->rel_addr & 0x80)
		state->rel_addr |= 0xFF00;
    log_debug("REL - %x ", state->rel_addr);
    return 0;
}

// Instructions by opcode

uint8_t ADC(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint16_t c = ((uint16_t)m & 0x00FF) + 0xf0;
    uint16_t val = ((uint16_t)m & 0x00FF) + ((uint16_t)state->a & 0x00FF) + ((uint16_t)check_status(state, C) & 0x000F);
    if (((state->a & m) & 0x80) == 0x80 && (val & 0x80) == 0x00) {
        set_status(state, V, 1);
    } else if (((state->a | m) & 0x80) == 0x00 && (val & 0x80) == 0x80) {
        set_status(state, V, 1);
    } else {
        set_status(state, V, 0);
    }
    set_status(state, C, val & 0x0100);
    state->a = val & 0x00FF;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("ADC %x", state->a);
    return 0;
}

uint8_t AND(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    state->a = state->a & m;
    set_status(state, Z, state->a == 0x00);
    set_status(state, N, state->a & 0x80);
    log_debug("AND %x", state->a);
    return 0;
}

uint8_t ASLA(cpu6502 * state, uint8_t * ram) {
    set_status(state, C, state->a & 0x80);
    state->a = state->a << 1;
    set_status(state, Z, state->a == 0x00);
    set_status(state, N, state->a & 0x80);
    log_debug("ASL %x", state->a);
    return 0;
}

uint8_t ASL(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    set_status(state, C, m & 0x80);
    state->a = m << 1;
    set_status(state, Z, state->a == 0x00);
    set_status(state, N, state->a & 0x80);
    log_debug("ASL %x", state->a);
    return 0;
}

uint8_t BCC(cpu6502 * state) {
    if (!check_status(state, C)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BCC %x", state->pc);
    return 0;
}

uint8_t BCS(cpu6502 * state) {
    if (check_status(state, C)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BCS %x", state->pc);
    return 0;
}

uint8_t BEQ(cpu6502 * state) {
    if (check_status(state, Z)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BEQ %x", state->pc);
    return 0;
}

uint8_t BIT(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint8_t v = state->a & m;
    set_status(state, Z, v == 0x00);
    set_status(state, V, m & 0x40);
    set_status(state, N, m & 0x80);
    log_debug("BIT %x", v);
    return 0;
}

uint8_t BMI(cpu6502 * state) {
    if (check_status(state, N)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BMI %x", state->pc);
    return 0;
}

uint8_t BNE(cpu6502 * state) {
    if (!check_status(state, Z)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BNE %x", state->pc);
    return 0;
}

uint8_t BPL(cpu6502 * state) {
    if (!check_status(state, N)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BPL %x", state->pc);
    return 0;
}

uint8_t BRK(cpu6502 * state, uint8_t *ram) {
    state->status = nesbus_read(ram, 0x0100 + state->sp);
    nesbus_write(ram, 0x0100 + state->sp, state->pc >> 8);
    nesbus_write(ram, 0x0100 + state->sp - 1, state->pc & 0x00FF);
    set_status(state, B, 1);
    nesbus_write(ram, 0x0100 + state->sp - 2, state->status);
    set_status(state, B, 0);
    state->sp -= 3;
    state->pc = nesbus_read(ram, 0xFFFE) | nesbus_read(ram, 0xFFFF) << 8;
    log_debug("BRK %x", state->pc);
    return 0;
}

uint8_t BVC(cpu6502 * state) {
    if (!check_status(state, V)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BVC %x", state->pc);
    return 0;
}

uint8_t BVS(cpu6502 * state) {
    if (check_status(state, V)) {
        state->pc = state->pc + state->rel_addr;
    }
    log_debug("BVS %x", state->pc);
    return 0;
}

uint8_t CLC(cpu6502 * state) {
    set_status(state, C, 0);
    log_debug("CLC %d", check_status(state, C));
    return 0;
}

uint8_t CLD(cpu6502 * state) {
    set_status(state, D, 0);
    log_debug("CLD %d", check_status(state, D));
    return 0;
}

uint8_t CLI(cpu6502 * state) {
    set_status(state, I, 0);
    log_debug("CLI %d", check_status(state, I));
    return 0;
}

uint8_t CLV(cpu6502 * state) {
    set_status(state, V, 0);
    log_debug("CLV %d", check_status(state, V));
    return 0;
}

uint8_t CMP(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint8_t t = state->a - m;
    set_status(state, C, state->a >= m);
    set_status(state, Z, t == 0x00);
    set_status(state, N, t & 0x80);
    log_debug("CMP %x", t);
    return 0;
}

uint8_t CPX(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint8_t t = state->x - m;
    set_status(state, C, state->x >= m);
    set_status(state, Z, t == 0x00);
    set_status(state, N, t & 0x80);
    log_debug("CPX %x", t);
    return 0;
}

uint8_t CPY(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint8_t t = state->y - m;
    set_status(state, C, state->y >= m);
    set_status(state, Z, t == 0x00);
    set_status(state, N, t & 0x80);
    log_debug("CPY %x", t);
    return 0;
}

uint8_t DEC(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    m = m - 0x01;
    nesbus_write(ram, state->abs_addr, m);
    set_status(state, Z, m == 0x00);
    set_status(state, N, m & 0x80);
    log_debug("DEC %x", m);
    return 0;
}

uint8_t DEX(cpu6502 * state) {
    state->x = state->x - 0x01;
    set_status(state, Z, state->x == 0x00);
    set_status(state, N, state->x & 0x80);
    log_debug("DEX %x", state->x);
    return 0;
}

uint8_t DEY(cpu6502 * state) {
    state->y = state->y - 0x01;
    set_status(state, Z, state->y == 0x00);
    set_status(state, N, state->y & 0x80);
    log_debug("DEY %x", state->y);
    return 0;
}

uint8_t EOR(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    state->a = state->a ^ m;
    set_status(state, Z, state->a == 0x00);
    set_status(state, N, state->a & 0x80);
    log_debug("EOR %x", state->a);
    return 0;
}

uint8_t INC(cpu6502 * state, uint8_t *ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    m = m + 0x01;
    nesbus_write(ram, state->abs_addr, m);
    set_status(state, Z, m == 0x00);
    set_status(state, N, m & 0x80);
    log_debug("INC %x", m);
    return 0;
}

uint8_t INX(cpu6502 * state) {
    state->x = state->x + 0x01;
    set_status(state, Z, state->x == 0x00);
    set_status(state, N, state->x & 0x80);
    log_debug("INX %x", state->x);
    return 0;
}

uint8_t INY(cpu6502 * state) {
    state->y = state->y + 0x01;
    set_status(state, Z, state->y == 0x00);
    set_status(state, N, state->y & 0x80);
    log_debug("INY %x", state->y);
    return 0;
}

uint8_t JMP(cpu6502 * state) {
    state->pc = state->abs_addr;
    log_debug("JMP %x", state->pc);
    return 0;
}

uint8_t JSR(cpu6502 * state, uint8_t * ram) {
    state->pc--;
    nesbus_write(ram, 0x0100 + state->sp, state->pc >> 8);
    state->sp--;
    nesbus_write(ram, 0x0100 + state->sp, state->pc & 0x00FF);
    state->sp--;
    state->pc = state->abs_addr;
    log_debug("JSR %x %x", state->pc, state->sp);
    return 0;
}

uint8_t LDA(cpu6502 * state, uint8_t * ram) {
    state->a = nesbus_read(ram, state->abs_addr);
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("LDA %x", state->a);
    return 0;
}

uint8_t LDX(cpu6502 * state, uint8_t * ram) {
    state->x = nesbus_read(ram, state->abs_addr);
    set_status(state, N, state->x & 0x80);
    set_status(state, Z, state->x == 0x00);
    log_debug("LDX %x", state->x);
    return 0;
}

uint8_t LDY(cpu6502 * state, uint8_t * ram) {
    state->y = nesbus_read(ram, state->abs_addr);
    set_status(state, N, state->y & 0x80);
    set_status(state, Z, state->y == 0x00);
    log_debug("LDY %x", state->y);
    return 0;
}

uint8_t LSRA(cpu6502 * state) {
    set_status(state, C, state->a & 0x01);
    state->a = state->a >> 1;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("LSRA %x", state->y);
    return 0;
}

uint8_t LSR(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    set_status(state, C, m & 0x01);
    m = m >> 1;
    nesbus_write(ram, state->abs_addr, m);
    set_status(state, N, m & 0x80);
    set_status(state, Z, m == 0x00);
    log_debug("LSR %x", m);
    return 0;
}

uint8_t NOP() {
    log_debug("NOP");
    return 0;
}

uint8_t ORA(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    state->a = state->a | m;
    set_status(state, Z, state->a == 0x00);
    set_status(state, N, state->a & 0x80);
    log_debug("ORA %x", state->a);
    return 0;
}

uint8_t PHA(cpu6502 * state, uint8_t * ram) {
    nesbus_write(ram, 0x0100 + state->sp, state->a);
    state->sp--;
    log_debug("PHA %x", state->a);
    return 0;
}

uint8_t PHP(cpu6502 * state, uint8_t * ram) {
    nesbus_write(ram, 0x0100 + state->sp, state->status);
    state->sp--;
    log_debug("PHP %x", state->status);
    return 0;
}

uint8_t PLA(cpu6502 * state, uint8_t * ram) {
    state->sp++;
    state->a = nesbus_read(ram, 0x0100 + state->sp);
    log_debug("PLA %x", state->a);
    return 0;
}

uint8_t PLP(cpu6502 * state, uint8_t * ram) {
    state->sp++;
    state->status = nesbus_read(ram, 0x0100 + state->sp);
    log_debug("PLP %x", state->status);
    return 0;
}

uint8_t ROLA(cpu6502 * state) {
    set_status(state, C, state->a & 0x80);
    state->a = state->a << 1;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("ROLA %x", state->a);
    return 0;
}

uint8_t ROL(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    set_status(state, C, m & 0x80);
    m = m << 1;
    nesbus_write(ram, state->abs_addr, m);
    set_status(state, N, m & 0x80);
    set_status(state, Z, m == 0x00);
    log_debug("ROL %x", m);
    return 0;
}

uint8_t RORA(cpu6502 * state) {
    set_status(state, C, state->a & 0x01);
    state->a = state->a >> 1;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("RORA %x", state->a);
    return 0;
}

uint8_t ROR(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    set_status(state, C, m & 0x01);
    m = m >> 1;
    nesbus_write(ram, state->abs_addr, m);
    set_status(state, N, m & 0x80);
    set_status(state, Z, m == 0x00);
    log_debug("ROR %x", m);
    return 0;
}

uint8_t RTI(cpu6502 * state, uint8_t * ram) {
    state->status = nesbus_read(ram, 0x0100 + state->sp);
    state->pc = nesbus_read(ram, 0x0100 + state->sp + 1) << 8 | nesbus_read(ram, 0x0100 + state->sp + 2);
    state->sp += 3;
    log_debug("RTI %x", state->pc);
    return 0;
}

uint8_t RTS(cpu6502 * state, uint8_t * ram) {
    state->pc = nesbus_read(ram, 0x0100 + state->sp) << 8 | nesbus_read(ram, 0x0100 + state->sp + 1);
    state->sp += 2;
    log_debug("RTS %x", state->pc);
    return 0;
}

uint8_t SBC(cpu6502 * state, uint8_t * ram) {
    uint8_t m = nesbus_read(ram, state->abs_addr);
    uint16_t v = state->a - m - (1 - check_status(state, C));
    
    return 0;
}

uint8_t SEC(cpu6502 * state) {
    set_status(state, C, 1);
    log_debug("SEC %d", check_status(state, C));
    return 0;
}

uint8_t SED(cpu6502 * state) {
    set_status(state, D, 1);
    log_debug("SED %d", check_status(state, D));
    return 0;
}

uint8_t SEI(cpu6502 * state) {
    set_status(state, I, 1);
    log_debug("SEI %d", check_status(state, I));
    return 0;
}

uint8_t STA(cpu6502 * state, uint8_t * ram) {
    nesbus_write(ram, state->abs_addr, state->a);
    log_debug("STA %x", state->a);
    return 0;
}

uint8_t STX(cpu6502 * state, uint8_t * ram) {
    nesbus_write(ram, state->abs_addr, state->x);
    log_debug("STX %x", state->x);
    return 0;
}

uint8_t STY(cpu6502 * state, uint8_t * ram) {
    nesbus_write(ram, state->abs_addr, state->y);
    log_debug("STY %x", state->y);
    return 0;
}

uint8_t TAX(cpu6502 * state) {
    state->x = state->a;
    set_status(state, N, state->x & 0x80);
    set_status(state, Z, state->x == 0x00);
    log_debug("TAX %x", state->x);
    return 0;
}

uint8_t TAY(cpu6502 * state) {
    state->y = state->a;
    set_status(state, N, state->y & 0x80);
    set_status(state, Z, state->y == 0x00);
    log_debug("TAY %x", state->y);
    return 0;
}

uint8_t TSX(cpu6502 * state) {
    state->x = state->sp;
    set_status(state, N, state->x & 0x80);
    set_status(state, Z, state->x == 0x00);
    log_debug("TSX %x", state->x);
    return 0;
}

uint8_t TXA(cpu6502 * state) {
    state->a = state->x;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("TXA %x", state->a);
    return 0;
}

uint8_t TXS(cpu6502 * state) {
    state->sp = state->x;
    set_status(state, N, 0);
    set_status(state, Z, 0);
    log_debug("TXS %x", state->sp);
    return 0;
}

uint8_t TYA(cpu6502 * state) {
    state->a = state->y;
    set_status(state, N, state->a & 0x80);
    set_status(state, Z, state->a == 0x00);
    log_debug("TAY %x", state->y);
    return 0;
}

cpu6502 init_state() {
    cpu6502 state;
    state.sp = 0xFF;
    return state;
}

uint8_t run_instruction(uint8_t opcode, cpu6502 * state, uint8_t * ram) {
    state->pc++;
    switch (opcode) {
        // ADC 1
        case 0x69:
            return IMM(state) + ADC(state, ram);
        case 0x65:
            return ZP0(state, ram) + ADC(state, ram);
        case 0x75:
            return ZPX(state, ram) + ADC(state, ram);
        case 0x6D:
            return ABS(state, ram) + ADC(state, ram);
        case 0x7D:
            return ABX(state, ram) + ADC(state, ram);
        case 0x79:
            return ABY(state, ram) + ADC(state, ram);
        case 0x61:
            return INDX(state, ram) + ADC(state, ram);
        case 0x71:
            return INDY(state, ram) + ADC(state, ram);
        // AND 2
        case 0x29:
            return IMM(state) + AND(state, ram);
        case 0x25:
            return ZP0(state, ram) + AND(state, ram);
        case 0x35:
            return ZPX(state, ram) + AND(state, ram);
        case 0x2D:
            return ABS(state, ram) + AND(state, ram);
        case 0x3D:
            return ABX(state, ram) + AND(state, ram);
        case 0x39:
            return ABY(state, ram) + AND(state, ram);
        case 0x21:
            return INDX(state, ram) + AND(state, ram);
        case 0x31:
            return INDY(state, ram) + AND(state, ram);
        // ASL 3
        case 0x0a:
            return ASLA(state, ram);
        case 0x06:
            return ZP0(state, ram) + ASL(state, ram);
        case 0x16:
            return ZPX(state, ram) + ASL(state, ram);
        case 0x0e:
            return ABS(state, ram) + ASL(state, ram);
        case 0x1e:
            return ABX(state, ram) + ASL(state, ram);
        // BCC 4
        case 0x90:
            return REL(state, ram) + BCC(state);
        // BCS 5
        case 0xB0:
            return REL(state, ram) + BCS(state);
        // BEQ 6
        case 0xF0:
            return REL(state, ram) + BEQ(state);
        // BIT 7
        case 0x24:
            return ZP0(state, ram) + BIT(state, ram);
        case 0x2C:
            return ABS(state, ram) + BIT(state, ram);
        // BMI 8
        case 0x30:
            return REL(state, ram) + BMI(state);
        // BNE 9
        case 0xD0:
            return REL(state, ram) + BNE(state);
        // BPL 10
        case 0x10:
            return REL(state, ram) + BPL(state);
        // BRK 11
        case 0x00:
            return IMP(state) + BRK(state, ram);
        // BVC 12
        case 0x50:
            return REL(state, ram) + BVC(state);
        // BVS 13
        case 0x70:
            return REL(state, ram) + BVS(state);
        // CLC 14
        case 0x18:
            return IMP(state) + CLC(state);
        // CLD 15
        case 0xD8:
            return IMP(state) + CLD(state);
        // CLI 16
        case 0x58:
            return IMP(state) + CLI(state);
        // CLV 17
        case 0xB8:
            return IMP(state) + CLV(state);
        // CMP 18
        case 0xC9:
            return IMM(state) + CMP(state, ram);
        case 0xC5:
            return ZP0(state, ram) + CMP(state, ram);
        case 0xD5:
            return ZPX(state, ram) + CMP(state, ram);
        case 0xCD:
            return ABS(state, ram) + CMP(state, ram);
        case 0xDD:
            return ABX(state, ram) + CMP(state, ram);
        case 0xD9:
            return ABY(state, ram) + CMP(state, ram);
        case 0xC1:
            return INDX(state, ram) + CMP(state, ram);
        case 0xD1:
            return INDY(state, ram) + CMP(state, ram);
        // CMX 19
        case 0xE0:
            return IMM(state) + CPX(state, ram);
        case 0xE4:
            return ZP0(state, ram) + CPX(state, ram);
        case 0xEC:
            return ABS(state, ram) + CPX(state, ram);
        // CMY 20
        case 0xC0:
            return IMM(state) + CPY(state, ram);
        case 0xC4:
            return ZP0(state, ram) + CPY(state, ram);
        case 0xCC:
            return ABS(state, ram) + CPY(state, ram);
        // DEC 21
        case 0xC6:
            return ZP0(state, ram) + DEC(state, ram);
        case 0xD6:
            return ZPX(state, ram) + DEC(state, ram);
        case 0xCE:
            return ABS(state, ram) + DEC(state, ram);
        case 0xDE:
            return ABX(state, ram) + DEC(state, ram);
        // DEX 22
        case 0xCA:
            return IMP(state) + DEX(state);
        // DEY 23
        case 0x88:
            return IMP(state) + DEY(state);
        // EOR 24
        case 0x49:
            return IMM(state) + EOR(state, ram);
        case 0x45:
            return ZP0(state, ram) + EOR(state, ram);
        case 0x55:
            return ZPX(state, ram) + EOR(state, ram);
        case 0x4D:
            return ABS(state, ram) + EOR(state, ram);
        case 0x5D:
            return ABX(state, ram) + EOR(state, ram);
        case 0x59:
            return ABY(state, ram) + EOR(state, ram);
        case 0x41:
            return INDX(state, ram) + EOR(state, ram);
        case 0x51:
            return INDY(state, ram) + EOR(state, ram);
        // INC 25
        case 0xE6:
            return ZP0(state, ram) + INC(state, ram);
        case 0xF6:
            return ZPX(state, ram) + INC(state, ram);
        case 0xEE:
            return ABS(state, ram) + INC(state, ram);
        case 0xFE:
            return ABX(state, ram) + INC(state, ram);
        // INX 26
        case 0xE8:
            return IMP(state) + INX(state);
        // INY 27
        case 0xC8:
            return IMP(state) + INY(state);
        // JMP 28
        case 0x4C:
            return ABS(state, ram) + JMP(state);
        case 0x6C:
            return IND(state, ram) + JMP(state);
        // JSR 29
        case 0x20:
            return ABS(state, ram) + JSR(state, ram);
        // LDA 30
        case 0xA9:
            return IMM(state) + LDA(state, ram);
        case 0xA5:
            return ZP0(state, ram) + LDA(state, ram);
        case 0xB5:
            return ZPX(state, ram) + LDA(state, ram);
        case 0xAD:
            return ABS(state, ram) + LDA(state, ram);
        case 0xBD:
            return ABX(state, ram) + LDA(state, ram);
        case 0xB9:
            return ABY(state, ram) + LDA(state, ram);
        case 0xA1:
            return INDX(state, ram) + LDA(state, ram);
        case 0xB1:
            return INDY(state, ram) + LDA(state, ram);
        // LDX 31
        case 0xA2:
            return IMM(state) + LDX(state, ram);
        case 0xA6:
            return ZP0(state, ram) + LDX(state, ram);
        case 0xB6:
            return ZPY(state, ram) + LDX(state, ram);
        case 0xAE:
            return ABS(state, ram) + LDX(state, ram);
        case 0xBE:
            return ABY(state, ram) + LDX(state, ram);
        // LDY 32
        case 0xA0:
            return IMM(state) + LDY(state, ram);
        case 0xA4:
            return ZP0(state, ram) + LDY(state, ram);
        case 0xB4:
            return ZPX(state, ram) + LDY(state, ram);
        case 0xAC:
            return ABS(state, ram) + LDY(state, ram);
        case 0xBC:
            return ABX(state, ram) + LDY(state, ram);
        // LSR 33
        case 0x4A:
            return LSRA(state);
        case 0x46:
            return ZP0(state, ram) + LSR(state, ram);
        case 0x56:
            return ZPX(state, ram) + LSR(state, ram);
        case 0x4E:
            return ABS(state, ram) + LSR(state, ram);
        case 0x5E:
            return ABX(state, ram) + LSR(state, ram);
        // NOP 34
        case 0xEA:
            return NOP();
        // ORA 35
        case 0x09:
            return IMM(state) + ORA(state, ram);
        case 0x05:
            return ZP0(state, ram) + ORA(state, ram);
        case 0x15:
            return ZPX(state, ram) + ORA(state, ram);
        case 0x0D:
            return ABS(state, ram) + ORA(state, ram);
        case 0x1D:
            return ABX(state, ram) + ORA(state, ram);
        case 0x19:
            return ABY(state, ram) + ORA(state, ram);
        case 0x01:
            return INDX(state, ram) + ORA(state, ram);
        case 0x11:
            return INDY(state, ram) + ORA(state, ram);
        // PHA 36
        case 0x48:
            return IMP(state) + PHA(state, ram);
        // PHP 37
        case 0x08:
            return IMP(state) + PHP(state, ram);
        // PLA 38
        case 0x68:
            return IMP(state) + PLA(state, ram);
        // PLP 39
        case 0x28:
            return IMP(state) + PLP(state, ram);
        // ROL 40
        case 0x2A:
            return ROLA(state);
        case 0x26:
            return ZP0(state, ram) + ROL(state, ram);
        case 0x36:
            return ZPX(state, ram) + ROL(state, ram);
        case 0x2E:
            return ABS(state, ram) + ROL(state, ram);
        case 0x3E:
            return ABX(state, ram) + ROL(state, ram);
        // ROR 41
        case 0x6A:
            return RORA(state);
        case 0x66:
            return ZP0(state, ram) + ROR(state, ram);
        case 0x76:
            return ZPX(state, ram) + ROR(state, ram);
        case 0x6E:
            return ABS(state, ram) + ROR(state, ram);
        case 0x7E:
            return ABX(state, ram) + ROR(state, ram);
        // RTI 42
        case 0x40:
            return IMP(state) + RTI(state, ram);
        // RTS 43
        case 0x60:
            return IMP(state) + RTS(state, ram);
        // SBC 44

        // SEC 45
        case 0x38:
            return IMP(state) + SEC(state);
        // SED 46
        case 0xF8:
            return IMP(state) + SED(state);
        // SEI 47
        case 0x78:
            return IMP(state) + SEI(state);
        // STA 48
        case 0x85:
            return ZP0(state, ram) + STA(state, ram);
        case 0x95:
            return ZPX(state, ram) + STA(state, ram);
        case 0x8D:
            return ABS(state, ram) + STA(state, ram);
        case 0x9D:
            return ABX(state, ram) + STA(state, ram);
        case 0x99:
            return ABY(state, ram) + STA(state, ram);
        case 0x81:
            return INDX(state, ram) + STA(state, ram);
        case 0x91:
            return INDY(state, ram) + STA(state, ram);
        // STX 49
        case 0x86:
            return ZP0(state, ram) + STX(state, ram);
        case 0x96:
            return ZPY(state, ram) + STX(state, ram);
        case 0x8E:
            return ABS(state, ram) + STX(state, ram);
        // STY 50
        case 0x84:
            return ZP0(state, ram) + STY(state, ram);
        case 0x94:
            return ZPX(state, ram) + STY(state, ram);
        case 0x8C:
            return ABS(state, ram) + STY(state, ram);
        // TAX 51
        case 0xAA:
            return IMP(state) + TAX(state);
        // TAY 52
        case 0xA8:
            return IMP(state) + TAY(state);
        // TSX 53
        case 0xBA:
            return IMP(state) + TSX(state);
        // TXA 54
        case 0x8A:
            return IMP(state) + TXA(state);
        // TXS 55
        case 0x9A:
            return IMP(state) + TXS(state);
        // TYA 56
        case 0x98:
            return IMP(state) + TYA(state);
        default:
            return 0;
    }
}


void clock(cpu6502 * state, uint8_t * ram) {
    uint8_t opcode = nesbus_read(ram, state->pc);
    log_debug("opcode %x ", opcode);
    run_instruction(opcode, state, ram);
    log_debug("\n");
}

uint8_t char_to_hex(uint8_t a) {
    if (a < 0x40) {
        return a - 0x30;
    } else if (a < 0x47) {
        return a - 0x37;
    } else {
        return a - 0x57;
    }
}

uint8_t str_to_hex(uint8_t *a) {
    return char_to_hex(*a) << 4 | char_to_hex(*(a+1));
}

void load_code(uint8_t * ram, cpu6502 state, uint8_t code [], int code_size) {
    int counter = 0;
    for (int i = 0; i < code_size; i += 2)
    {
        uint8_t hexval = str_to_hex(&code[i]);
        nesbus_write(ram, state.pc + counter, hexval);
        i++;
        counter++;
    }
}
