#pragma once

#include "constants.h"

#include <array>
#include <memory>

namespace c8
{
    class Memory
    {
    public:
        Memory();

        u8 get(u32 address) const;
        void set(u32 address, u8 value);

    private:
        std::unique_ptr<std::array<u8, MEMORY_SIZE>> m_memory;
    };
}