#include "memory.h"

#include <fstream>
#include <iostream>

namespace c8
{
    Memory::Memory()
    {
        m_memory = std::make_unique<std::array<u8, MEMORY_SIZE>>();
        m_memory->fill(0); // Default value 0 for all memory locations

        // Copy font into memory
        for(u32 i = 0; i < 80; i++)
            m_memory->operator[](i) = FONT[i];
    }

    void Memory::load_rom(const std::string& path)
    {
        // Open file
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // Get file length
            file.open(path, std::ifstream::binary);
            file.seekg(0, std::ios::end);
            u32 length = file.tellg();
            file.seekg(0, std::ios::beg);

            // Make sure the rom is smaller than the memory
            if (length > MAX_PROGRAM_SIZE)
            {
                length = MAX_PROGRAM_SIZE;
                std::cout << "[MEMORY] The ROM is too large for the chip-8's memory. Max size is " << MAX_PROGRAM_SIZE << "." << std::endl;
            }

            // Read file
            file.read(reinterpret_cast<char*>(m_memory->data() + PROGRAM_START), length);
            std::cout << "[MEMORY] Loaded rom file '" << path << "' into memory." << std::endl;
        }
        catch(const std::ifstream::failure& e)
        {
            std::cout << "[MEMORY] Failed to load rom file '" << path << "'." << e.what() << std::endl;
        }
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