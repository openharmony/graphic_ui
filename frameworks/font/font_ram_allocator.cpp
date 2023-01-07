/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "font/font_ram_allocator.h"
#include "font/ui_font_header.h"

namespace OHOS {
FontRamAllocator::FontRamAllocator() : ramAddr_(0), ramLen_(0), currentRamAddr_(0), dynamicAddr_(0) {}
FontRamAllocator::~FontRamAllocator() {}

void FontRamAllocator::SetRamAddr(uintptr_t ramAddr, uint32_t ramLen)
{
    if (ramAddr_ != 0) {
        return;
    }

    ramAddr_ = ramAddr;
    ramLen_ = ramLen;
    if (!IsAligned(ramAddr)) {
        currentRamAddr_ = AlignUp(ramAddr);
    } else {
        currentRamAddr_ = ramAddr;
    }
}

void* FontRamAllocator::Allocate(uint32_t size)
{
    if ((ramAddr_ == 0) || (size == 0)) {
        return nullptr;
    }

    if (!IsAligned(size)) {
        size = AlignUp(size);
    }

    if ((size + currentRamAddr_) > (ramAddr_ + ramLen_)) {
        return nullptr;
    }

    void* addr = reinterpret_cast<void *>(currentRamAddr_);
    currentRamAddr_ += size;
    return addr;
}

uint32_t FontRamAllocator::GetRamUsedLen()
{
    return (currentRamAddr_ - ramAddr_);
}

void FontRamAllocator::ClearRam()
{
    if (dynamicAddr_) {
        currentRamAddr_ = dynamicAddr_;
        dynamicAddr_ = 0;
        allocator_.SetRamAddr(0, 0);
    }
}

void* FontRamAllocator::DynamicAllocate(uint32_t size)
{
    if (!dynamicAddr_) {
        dynamicAddr_ = currentRamAddr_;
        allocator_.SetRamAddr(reinterpret_cast<uint8_t*>(dynamicAddr_), ramLen_ - dynamicAddr_ + ramAddr_);
        allocator_.SetMinChunkSize(4); // 4: min align size
        currentRamAddr_ = ramAddr_ + ramLen_;
    }

    return allocator_.Allocate(size);
}

void FontRamAllocator::DynamicFree(void* addr)
{
    return allocator_.Free(addr);
}

uint32_t FontRamAllocator::GetMemSize(void* addr)
{
    return allocator_.GetSize(addr);
}

uint32_t FontRamAllocator::AlignUp(uint32_t addr)
{
    return (((addr + (1 << RAM_ALIGN)) >> RAM_ALIGN) << RAM_ALIGN);
}

bool FontRamAllocator::IsAligned(uint32_t addr)
{
    return ((addr % (1 << RAM_ALIGN)) == 0);
}
} // namespace OHOS
