/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GRAPHIC_LITE_LINE_BREAK_H
#define GRAPHIC_LITE_LINE_BREAK_H

#include "graphic_config.h"
#if ENABLE_ICU
#include "font/ui_font_header.h"
#include "gfx_utils/file.h"
#include "gfx_utils/mem_api.h"
#include <cstdint>
#include <string>
namespace OHOS {
class UILineBreakProxy;
/**
 * @brief 使用ICU作为换行引擎核心部分
 *
 * @since 3.0
 * @version 5.0
 */
class UILineBreakEngine : public HeapBase {
public:
    /**
     * @brief 获取UILineBreakEngine实例
     *
     * @return UILineBreakEngine&
     * @since 3.0
     * @version 5.0
     */
    static UILineBreakEngine& GetInstance()
    {
        if (instance_ == nullptr) {
            instance_ = new UILineBreakEngine();
        }
        return *instance_;
    }

    /**
     * @brief 初始化换行引擎，加载换行规则文件
     *
     * @since 3.0
     * @version 5.0
     */
    void Init()
    {
        LoadRule();
    }

    /**
     * @brief 获取下一个换行位置
     *
     * @param record UILineBreakProxy实例
     * @return uint16_t 换行位置
     * @since 3.0
     * @version 5.0
     */
    uint16_t GetNextBreakPos(UILineBreakProxy& record);

    /**
     * @brief 设置规则文件信息
     *
     * @param fp 文件fp
     * @param offset 偏移量
     * @param size 文件大小
     * @return int32_t 设置规则文件返回值
     * @since 3.0
     * @version 5.0
     */
    int32_t SetRuleBinInfo(int32_t fp, int32_t offset, uint32_t size)
    {
        fp_ = fp;
        offset_ = offset;
        int32_t fRet = lseek(fp_, offset, SEEK_SET);
        if (fRet != offset) {
            return fRet;
        }
        size_ = size;
        return 0;
    }

    /**
     * @brief 设置规则文件加载位置
     *
     * @param addr 规则文件加载位置
     * @since 3.0
     * @version 5.0
     */
    void SetRuleFileLoadAddr(char* addr)
    {
        addr_ = addr;
    }

    /**
     * @brief 获取规则文件加载位置
     *
     * @return char* 规则文件加载位置
     * @since 3.0
     * @version 5.0
     */
    char* GetRuleFileLoadAddr() const
    {
        return addr_;
    }

    /**
     * @brief 获取规则文件大小
     *
     * @return int32_t 规则文件大小
     * @since 3.0
     * @version 5.0
     */
    int32_t GetRuleFileSize() const
    {
        return size_;
    }

    // 0xFFFF: unlimit the length until the end null.
    uint32_t
        GetNextLineAndWidth(const char* text, int16_t space, bool allBreak, int16_t& maxWidth, uint16_t len = 0xFFFF);
    bool IsBreakPos(uint32_t unicode, int32_t& state);

private:
    UILineBreakEngine()
        : initSuccess_(false), addr_(nullptr), size_(0), fp_(0), offset_(0), lineBreakTrie_(nullptr), stateTbl_(nullptr)
    {
    }
    ~UILineBreakEngine() {}

    void LoadRule();
    static constexpr const int32_t LINE_BREAK_STATE_START = 1;
    static constexpr const int32_t LINE_BREAK_STATE_STOP = 0;
    static UILineBreakEngine* instance_;
    bool initSuccess_;
    char* addr_;
    int32_t size_;
    int32_t fp_;
    int32_t offset_;
    void* lineBreakTrie_;
    const void* stateTbl_;
};

/**
 * @brief 换行代理类
 */
class UILineBreakProxy : public HeapBase {
public:
    UILineBreakProxy() = delete;

    /**
     * @brief UILineBreakProxy对象构造函数
     *
     * @param str 输入字符串
     * @param len 输入字符的长度
     * @since 3.0
     * @version 5.0
     */
    UILineBreakProxy(uint16_t* str, uint16_t len) : str_(str), len_(len), prePos_(0) {}

    ~UILineBreakProxy()
    {
        str_ = nullptr;
        len_ = 0;
        prePos_ = 0;
    }

    /**
     * @brief 获取下一个换行位置
     *
     * @return uint16_t 下一个换行位置
     * @since 3.0
     * @version 5.0
     */
    uint16_t GetNextBreakPos()
    {
        uint16_t offsetFromPrePos = UILineBreakEngine::GetInstance().GetNextBreakPos(*this);
        prePos_ += offsetFromPrePos;
        return prePos_;
    }

    /**
     * @brief 获取字符串的长度
     *
     * @return uint16_t 字符串的长度
     * @since 3.0
     * @version 5.0
     */
    uint16_t GetStrLen() const
    {
        if (prePos_ < len_) {
            return len_ - prePos_;
        }
        return 0;
    }

    /**
     * @brief 获取字符串
     *
     * @return uint16_t* 字符串位置
     * @since 3.0
     * @version 5.0
     */
    const uint16_t* GetStr() const
    {
        if (prePos_ < len_) {
            return &(str_[prePos_]);
        }
        return nullptr;
    }

private:
    uint16_t* str_;
    uint16_t len_;
    uint16_t prePos_;
};
} // namespace OHOS
#endif // ENABLE_ICU
#endif // GRAPHIC_LITE_LINE_BREAK_H
