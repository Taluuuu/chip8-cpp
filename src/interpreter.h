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
        void ins_1nnn(u16 instruction);
        void ins_6xkk(u16 instruction);
        void ins_7xkk(u16 instruction);
        void ins_Annn(u16 instruction);
        void ins_Dxyn(u16 instruction);

    private:
        Emulator& m_emu;
        bool m_pending_redraw;

        std::array<u8, 16> m_registers;
        u16 m_pc = PROGRAM_START;
        u16 m_i;
    };
}