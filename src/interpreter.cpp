#include "interpreter.h"

#include "emulator.h"
#include "memory.h"

#include <bitset>
#include <iostream>
#include <memory>

namespace c8
{
    Interpreter::Interpreter(Emulator& emu)
        :m_emu(emu)
    {
        // Set registers to 0
        m_registers.fill(0);
    }

    void Interpreter::step()
    {
        // Get a reference to the memory
        auto& memory = m_emu.memory();

        m_pending_redraw = false;
        while(!m_pending_redraw)
        {
            u16 instruction = memory->get(m_pc) << 8 | memory->get(m_pc + 1);

            switch(instruction & 0xF000)
            {
            case 0x0000:
                switch(instruction)
                {
                case 0x00E0:
                    ins_00E0();
                    break;

                default:
                    unknown_instruction(instruction);
                    break;
                }
                break;

            case 0x1000:
                ins_1nnn(instruction);
                break;

            case 0x6000:
                ins_6xkk(instruction);
                break;

            case 0x7000:
                ins_7xkk(instruction);
                break;

            case 0xA000:
                ins_Annn(instruction);
                break;

            case 0xD000:
                ins_Dxyn(instruction);
                break;

            default:
                unknown_instruction(instruction);
                break;
            }
        }
    }

    void Interpreter::unknown_instruction(u16 instruction)
    {
        std::cout << "[INTERPRETER] Unknown instruction " << std::hex << instruction 
            << " at memory location " << std::hex << m_pc << std::endl;

        m_pending_redraw = true; // Don't hang the emulator
    }

    void Interpreter::ins_00E0()
    {
        m_emu.screen()->clear();
        m_pc += 2;
    }

    void Interpreter::ins_1nnn(u16 instruction)
    {
        u16 nnn = instruction & 0xFFF;

        // Check for end of program execution
        if(nnn == m_pc)
            m_pending_redraw = true;

        m_pc = nnn;
    }

    void Interpreter::ins_6xkk(u16 instruction)
    {
        u8 kk = instruction & 0xFF;
        u8 x = (instruction >> 8) & 0xF;
        m_registers[x] = kk; // Safe to use [] as the max value of x is 16
        m_pc += 2;
    }

    void Interpreter::ins_7xkk(u16 instruction)
    {
        u8 kk = instruction & 0xFF;
        u8 x = (instruction >> 8) & 0xF;
        m_registers[x] += kk;
        m_pc += 2;
    }

    void Interpreter::ins_Annn(u16 instruction)
    {
        m_i = instruction & 0xFFF;
        m_pc += 2;
    }

    void Interpreter::ins_Dxyn(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;
        u8 n = instruction & 0xF;
        m_emu.screen()->draw_from_array(m_emu.memory(), m_i, n, m_registers[x], m_registers[y]);
        m_pending_redraw = true;
        m_pc += 2;
    }
}