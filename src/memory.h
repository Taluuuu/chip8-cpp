#pragma once

#include "constants.h"
#include "types.h"

#include <array>
#include <memory>
#include <string>

namespace c8
{
    class Memory
    {
    public:
        Memory();

        void load_rom(const std::string& path);

        u8 get(u32 address) const;
        void set(u32 address, u8 value);

    private:
        std::unique_ptr<std::array<u8, MEMORY_SIZE>> m_memory;
    };
}