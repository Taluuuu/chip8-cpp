#include "interpreter.h"

#include "emulator.h"
#include "memory.h"

#include <bitset>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

namespace c8
{
    Interpreter::Interpreter(Emulator& emu)
        :m_emu(emu)
    {
        // Fill arrays with 0's
        m_registers.fill(0);
        m_stack.fill(0);
    }

    void Interpreter::step()
    {
        // Get a reference to the memory
        auto& memory = m_emu.memory();

        m_pending_redraw = false;
        while(!m_pending_redraw)
        {
            u16 instruction = memory->get(m_pc) << 8 | memory->get(m_pc + 1);

            // TODO: Handle delay timer for real
            if(m_dt > 0)
                m_dt -= 1;

            switch(instruction & 0xF000)
            {
            case 0x0000:
                switch(instruction)
                {
                case 0x00E0:
                    ins_00E0();
                    break;

                case 0x00EE:
                    ins_00EE();
                    break;

                default:
                    unknown_instruction(instruction);
                    break;
                }
                break;

            case 0x1000:
                ins_1nnn(instruction);
                break;

            case 0x2000:
                ins_2nnn(instruction);
                break;

            case 0x3000:
                ins_3xkk(instruction);
                break;

            case 0x4000:
                ins_4xkk(instruction);
                break;

            case 0x5000:
                ins_5xy0(instruction);
                break;

            case 0x6000:
                ins_6xkk(instruction);
                break;

            case 0x7000:
                ins_7xkk(instruction);
                break;

            case 0x8000:
                switch(instruction & 0xF00F)
                {
                case 0x8000:
                    ins_8xy0(instruction);
                    break;

                case 0x8001:
                    ins_8xy1(instruction);
                    break;

                case 0x8002:
                    ins_8xy2(instruction);
                    break;

                case 0x8003:
                    ins_8xy3(instruction);
                    break;

                case 0x8004:
                    ins_8xy4(instruction);
                    break;

                case 0x8005:
                    ins_8xy5(instruction);
                    break;

                case 0x8006:
                    ins_8xy6(instruction);
                    break;

                case 0x800E:
                    ins_8xyE(instruction);
                    break;

                default:
                    unknown_instruction(instruction);
                    break;
                }
                break;

            case 0x9000:
                ins_9xy0(instruction);
                break;

            case 0xA000:
                ins_Annn(instruction);
                break;

            case 0xC000:
                ins_Cxkk(instruction);
                break;

            case 0xD000:
                ins_Dxyn(instruction);
                break;

            case 0xE000:
                switch(instruction & 0xF0FF)
                {
                    case 0xE09E:
                        ins_Ex9E(instruction);
                        break;

                    default:
                        unknown_instruction(instruction);
                        break;
                }
                break;

            case 0xF000:
                switch(instruction & 0xF0FF)
                {
                case 0xF007:
                    ins_Fx07(instruction);
                    break;

                case 0xF00A:
                    ins_Fx0A(instruction);
                    break;

                case 0xF015:
                    ins_Fx15(instruction);
                    break;

                case 0xF01E:
                    ins_Fx1E(instruction);
                    break;

                case 0xF029:
                    ins_Fx29(instruction);
                    break;

                case 0xF033:
                    ins_Fx33(instruction);
                    break;

                case 0xF055:
                    ins_Fx55(instruction);
                    break;

                case 0xF065:
                    ins_Fx65(instruction);
                    break;

                default:
                    unknown_instruction(instruction);
                    break;
                }
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
        //m_pc += 2;
    }

    void Interpreter::ins_00E0()
    {
        m_emu.screen()->clear();
        m_pc += 2;
    }

    void Interpreter::ins_00EE()
    {
        try
        {
            m_pc = m_stack.at(--m_sp);
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "[INTERPRETER] Error: Invalid stack pointer value in instruction 00EE." << std::endl;
        }
        
        
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

    void Interpreter::ins_2nnn(u16 instruction)
    {
        u16 nnn = instruction & 0xFFF;
        m_stack.at(m_sp++) = m_pc;
        m_pc = nnn;
    }

    void Interpreter::ins_3xkk(u16 instruction)
    {
        u8 kk = instruction & 0xFF;
        u8 x = (instruction >> 8) & 0xF;

        if(m_registers[x] == kk)
            m_pc += 2;

        m_pc += 2;
    }

    void Interpreter::ins_4xkk(u16 instruction)
    {
        u8 kk = instruction & 0xFF;
        u8 x = (instruction >> 8) & 0xF;

        if(m_registers[x] != kk)
            m_pc += 2;

        m_pc += 2;
    }

    void Interpreter::ins_5xy0(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        if(m_registers[x] == m_registers[y])
            m_pc += 2;

        m_pc += 2;
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

    void Interpreter::ins_8xy0(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;
        m_registers[x] = m_registers[y];
        m_pc += 2;
    }

    void Interpreter::ins_8xy1(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        m_registers[x] |= m_registers[y];

        m_pc += 2;
    }

    void Interpreter::ins_8xy2(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        m_registers[x] &= m_registers[y];

        m_pc += 2;
    }

    void Interpreter::ins_8xy3(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        m_registers[x] ^= m_registers[y];

        m_pc += 2;
    }

    void Interpreter::ins_8xy4(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;
        u16 result = static_cast<u32>(m_registers[x]) + m_registers[y];

        // Check for carry
        if(result & 0xFF00)
            m_registers[0xF] = 1;

        m_registers[x] = result;
        m_pc += 2;
    }

    void Interpreter::ins_8xy5(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        m_registers[0xF] = m_registers[x] > m_registers[y];
        m_registers[x] -= m_registers[y];

        m_pc += 2;
    }

    void Interpreter::ins_8xy6(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        m_registers[0xF] = m_registers[x] & 0x1;
        m_registers[x] /= 2;

        m_pc += 2;
    }

    void Interpreter::ins_8xyE(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        if(m_registers[x] & 0x80)
            m_registers[0xF] = 1;

        m_registers[x] *= 2;

        m_pc += 2;
    }

    void Interpreter::ins_9xy0(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;

        if(m_registers[x] != m_registers[y])
            m_pc += 2;

        m_pc += 2;
    }

    void Interpreter::ins_Annn(u16 instruction)
    {
        m_i = instruction & 0xFFF;
        m_pc += 2;
    }

    void Interpreter::ins_Cxkk(u16 instruction)
    {
        u8 kk = instruction & 0xFF;
        u8 x = (instruction >> 8) & 0xF;

        std::srand(m_emu.clock().getElapsedTime().asMilliseconds());
        m_registers[x] = std::rand() & kk;
        m_pc += 2;
    }

    void Interpreter::ins_Dxyn(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        u8 y = (instruction >> 4) & 0xF;
        u8 n = instruction & 0xF;
        m_registers[0xF] = m_emu.screen()->draw_from_array(m_emu.memory(), m_i, n, m_registers[x], m_registers[y]);
        m_pending_redraw = true;
        m_pc += 2;
    }

    void Interpreter::ins_Ex9E(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        // TODO: Keypress
        m_pc += 2;
    }

    void Interpreter::ins_Fx07(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        m_registers[x] = m_dt;
        m_pc += 2;
    }

    void Interpreter::ins_Fx0A(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        // TODO: Keypress
        m_pc += 2;
    }

    void Interpreter::ins_Fx15(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        m_dt = m_registers[x];
        m_pc += 2;
    }

    void Interpreter::ins_Fx1E(u16 instruction)
    {
        u8 x = (instruction >> 8) & 0xF;
        m_i += m_registers[x];
        m_pc += 2;
    }

    void Interpreter::ins_Fx29(u16 instruction)
    {
        auto& memory = m_emu.memory();

        u8 x = (instruction >> 8) & 0xF;
        m_i = m_registers[x] * 5;

        m_pc += 2;
    }

    void Interpreter::ins_Fx33(u16 instruction)
    {
        auto& memory = m_emu.memory();

        u8 x = (instruction >> 8) & 0xF;
        u8 n = m_registers[x];

        memory->set(m_i + 0, n / 100);
        memory->set(m_i + 1, (n / 10) % 10);
        memory->set(m_i + 2, n % 10);

        m_pc += 2;
    }

    void Interpreter::ins_Fx55(u16 instruction)
    {
        auto& memory = m_emu.memory();

        u8 x = (instruction >> 8) & 0xF;

        u32 i = 0;
        try
        {
            // Set registers to values starting at memory location i
            for(; i <= x; i++)
                memory->set(m_i + i, m_registers.at(i));
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "[INTERPRETER] Error: Index " << i << " out of range for registers array in instruction Fx55." << std::endl;
        }

        m_pc += 2;
    }

    void Interpreter::ins_Fx65(u16 instruction)
    {
        auto& memory = m_emu.memory();

        u8 x = (instruction >> 8) & 0xF;

        u32 i = 0;
        try
        {
            // Set registers to values starting at memory location i
            for(; i <= x; i++)
                m_registers.at(i) = memory->get(m_i + i);
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "[INTERPRETER] Error: Index " << i << " out of range for registers array in instruction Fx65." << std::endl;
        }

        m_pc += 2;
    }
}