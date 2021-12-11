#include "memory.h"

#include <iostream>

namespace c8
{
    Memory::Memory()
    {
        m_memory = std::make_unique<std::array<u8, MEMORY_SIZE>>();
        m_memory->fill(0); // Default value 0 for all memory locations
    }

    u8 Memory::get(u32 address) const
    {
        try
        {
            return m_memory->at(address);
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "[MEMORY] Index " << address << " out of range for memory size " << MEMORY_SIZE << ". Using value 0." << std::endl;
            return 0;
        }
    }

    void Memory::set(u32 address, u8 value)
    {
        try
        {
            m_memory->at(address) = value;
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "[MEMORY] Index " << address << " out of range for memory size " << MEMORY_SIZE << ". Value not set." << std::endl;
        }
    }
}