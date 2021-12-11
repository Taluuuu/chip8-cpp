#pragma once

#include "constants.h"
#include "types.h"

#include <array>

namespace c8
{
    class Emulator; // Forward declaration

    class Interpreter
    {
    public:
        /**
         * @brief Create the interpreter
         * 
         * @param emu A reference to the emulator class for access to the screen, memory, etc.
         */
        Interpreter(Emulator& emu);

        /**
         * @brief Run the program until the next time the screen needs to be drawn
         * 
         */
        void step();

    private:
        void unknown_instruction(u16 instruction);
        void ins_00E0();
        void ins_00EE();
        void ins_1nnn(u16 instruction);
        void ins_2nnn(u16 instruction);
        void ins_3xkk(u16 instruction);
        void ins_4xkk(u16 instruction);
        void ins_5xy0(u16 instruction);
        void ins_6xkk(u16 instruction);
        void ins_7xkk(u16 instruction);
        void ins_8xy0(u16 instruction);
        void ins_8xy1(u16 instruction);
        void ins_8xy2(u16 instruction);
        void ins_8xy3(u16 instruction);
        void ins_8xy4(u16 instruction);
        void ins_8xy5(u16 instruction);
        void ins_8xy6(u16 instruction);
        void ins_8xyE(u16 instruction);
        void ins_9xy0(u16 instruction);
        void ins_Annn(u16 instruction);
        void ins_Cxkk(u16 instruction);
        void ins_Dxyn(u16 instruction);
        void ins_Ex9E(u16 instruction);
        void ins_Fx07(u16 instruction);
        void ins_Fx0A(u16 instruction);
        void ins_Fx15(u16 instruction);
        void ins_Fx1E(u16 instruction);
        void ins_Fx29(u16 instruction);
        void ins_Fx33(u16 instruction);
        void ins_Fx55(u16 instruction);
        void ins_Fx65(u16 instruction);

    private:
        Emulator& m_emu;
        bool m_pending_redraw;

        std::array<u16, 16> m_stack;
        u8 m_sp = 0;

        std::array<u8,  16> m_registers;
        u16 m_pc = PROGRAM_START;
        u16 m_i = 0;
        u8  m_dt = 0;
    };
}