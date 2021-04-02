# Testing Adressing mode
add_test(NAME "IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "IMM")
add_test(NAME "ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ZP0")
add_test(NAME "ZPX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ZPX")
add_test(NAME "ZPY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ZPY")
add_test(NAME "ABS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ABS")
add_test(NAME "ABX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ABX")
add_test(NAME "ABY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ABY")
add_test(NAME "IND" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "IND")
add_test(NAME "INDX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "INDX")
add_test(NAME "INDY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "INDY")
add_test(NAME "REL" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "REL")

# Testing instructions

add_test(NAME "BCC" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BCC")
add_test(NAME "BCS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BCS")
add_test(NAME "BEQ" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BEQ")
add_test(NAME "BIT" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BIT")
add_test(NAME "BMI" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BMI")
add_test(NAME "BNE" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BNE")
add_test(NAME "BPL" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BPL")
add_test(NAME "BVC" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BVC")
add_test(NAME "BVS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "BVS")

add_test(NAME "CLC" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CLC")
add_test(NAME "CLD" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CLD")
add_test(NAME "CLI" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CLI")
add_test(NAME "CLV" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CLV")

add_test(NAME "CMP_IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CMP_IMM")

add_test(NAME "CPX_IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CPX_IMM")

add_test(NAME "CPY_IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "CPY_IMM")

add_test(NAME "DEC_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "DEC_ZP0")

add_test(NAME "DEX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "DEX")

add_test(NAME "DEY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "DEY")

add_test(NAME "EOR_IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "EOR_IMM")

add_test(NAME "INC_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "INC_ZP0")

add_test(NAME "INX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "INX")

add_test(NAME "INY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "INY")

add_test(NAME "JMP_ABS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "JMP_ABS")
add_test(NAME "JMP_IND" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "JMP_IND")
add_test(NAME "JMP_IND_BUG" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "JMP_IND_BUG")

add_test(NAME "JSR" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "JSR")

add_test(NAME "LDA IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "LDA IMM")

add_test(NAME "LDX IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "LDX IMM")

add_test(NAME "LDY IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "LDY IMM")

add_test(NAME "LSR A" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "LSR A")
add_test(NAME "LSR ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "LSR ZP0")

add_test(NAME "ORA IMM" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ORA IMM")

add_test(NAME "PHA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "PHA")
add_test(NAME "PHP" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "PHP")
add_test(NAME "PLA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "PLA")
add_test(NAME "PLP" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "PLP")

add_test(NAME "ROLA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ROLA")
add_test(NAME "ROL_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ROL_ZP0")

add_test(NAME "RORA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "RORA")
add_test(NAME "ROR_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "ROR_ZP0")

add_test(NAME "RTI" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "RTI")
add_test(NAME "RTS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "RTS")
add_test(NAME "SBC" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "SBC")

add_test(NAME "SEC" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "SEC")
add_test(NAME "SED" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "SED")
add_test(NAME "SEI" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "SEI")

add_test(NAME "STA_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "STA_ZP0")

add_test(NAME "STX_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "STX_ZP0")

add_test(NAME "STY_ZP0" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "STY_ZP0")

add_test(NAME "TAX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TAX")
add_test(NAME "TAY" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TAY")
add_test(NAME "TSX" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TSX")
add_test(NAME "TXA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TXA")
add_test(NAME "TXS" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TXS")
add_test(NAME "TYA" COMMAND ${CMAKE_BINARY_DIR}/unit_tests "TYA")
