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

#include "components/ui_edit_text.h"

#include <climits>
#include <gtest/gtest.h>

#include "securec.h"

using namespace testing::ext;
namespace OHOS {
namespace {
constexpr int16_t INIT_WIDTH = 100;
constexpr int16_t INIT_HEIGHT = 150;
} // namespace

class EditTextOnChangeListener : public UIEditText::OnChangeListener {
public:
    void OnChange(UIView& view, const char* value) override
    {
        uint32_t textLen = static_cast<uint32_t>(strlen(value));
        if (value_ != nullptr) {
            UIFree(value_);
            value_ = nullptr;
        }
        value_ = static_cast<char*>(UIMalloc(textLen + 1));
        if (value_ == nullptr) {
            return;
        }
        if (strncpy_s(value_, textLen + 1, value, textLen) != EOK) {
            UIFree(value_);
            value_ = nullptr;
            return;
        }
    }

    const char* GetValue()
    {
        return value_;
    }

    virtual ~EditTextOnChangeListener()
    {
        if (value_ != nullptr) {
            delete value_;
            value_ = nullptr;
        }
    }

private:
    char* value_ = nullptr;
};

class UIEditTextTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    static UIEditText* editText_;
};

UIEditText* UIEditTextTest::editText_ = nullptr;

void UIEditTextTest::SetUpTestCase(void)
{
    if (editText_ == nullptr) {
        editText_ = new UIEditText();
    }
}

void UIEditTextTest::TearDownTestCase(void)
{
    if (editText_ != nullptr) {
        delete editText_;
        editText_ = nullptr;
    }
}

/**
 * @tc.name: UIEditTextGetViewType_001
 * @tc.desc: Verify GetViewType and GetHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextGetViewType_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EXPECT_EQ(editText_->GetViewType(), UI_EDIT_TEXT);
}

/**
 * @tc.name: UIEditTextResize_001
 * @tc.desc: Verify Resize function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextResize_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    editText_->Resize(INIT_WIDTH, INIT_HEIGHT);
    EXPECT_EQ(editText_->GetWidth(), INIT_WIDTH);
    EXPECT_EQ(editText_->GetHeight(), INIT_HEIGHT);
}

/**
 * @tc.name: UIEditTextSetText_001
 * @tc.desc: Verify SetText function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetText_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    const char* text = "abc";
    editText_->Resize(INIT_WIDTH, INIT_HEIGHT);
    editText_->SetText(text);

    const char* textTmp = editText_->GetText();
    ASSERT_TRUE(textTmp);
    EXPECT_EQ(strcmp(textTmp, text), 0);
}

/**
 * @tc.name: UIEditTextSetPlaceholder_001
 * @tc.desc: Verify SetPlaceholder function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetPlaceholder_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    const char* placeholder = "Name:";
    editText_->Resize(INIT_WIDTH, INIT_HEIGHT);
    editText_->SetPlaceholder(placeholder);

    const char* placeholderTmp = editText_->GetPlaceholder();
    ASSERT_TRUE(placeholderTmp);
    EXPECT_EQ(strcmp(placeholderTmp, placeholder), 0);
}

/**
 * @tc.name: UIEditTextSetMaxLength_001
 * @tc.desc: Verify SetMaxLength function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetMaxLength_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    uint16_t length1 = 20;
    editText_->SetMaxLength(length1);
    EXPECT_EQ(editText_->GetMaxLength(), length1);

    uint16_t length2 = 0;
    editText_->SetMaxLength(length2);
    EXPECT_EQ(editText_->GetMaxLength(), length2);
}

/**
 * @tc.name: UIEditTextSetInputType_001
 * @tc.desc: Verify SetInputType function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetInputType_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    // check the default type
    EXPECT_EQ(editText_->GetInputType(), InputType::TEXT_TYPE);

    InputType type = InputType::TEXT_TYPE;
    editText_->SetInputType(type);
    EXPECT_EQ(editText_->GetInputType(), type);

    type = InputType::PASSWORD_TYPE;
    editText_->SetInputType(type);
    EXPECT_EQ(editText_->GetInputType(), type);
}

/**
 * @tc.name: UIEditTextSetTextColor_001
 * @tc.desc: Verify SetTextColor function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetTextColor_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::White();

    editText_->SetTextColor(color);
    EXPECT_EQ(editText_->GetTextColor().full, color.full);
}

/**
 * @tc.name: UIEditTextSetPlaceholderColor_001
 * @tc.desc: Verify SetPlaceholderColor function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetPlaceholderColor_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::White();

    editText_->SetPlaceholderColor(color);
    EXPECT_EQ(editText_->GetPlaceholderColor().full, color.full);
}

/**
 * @tc.name: UIEditTextSetCursorColor_001
 * @tc.desc: Verify SetCursorColor function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetCursorColor_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    ColorType color = Color::White();

    editText_->SetCursorColor(color);
    EXPECT_EQ(editText_->GetCursorColor().full, color.full);
}

/**
 * @tc.name: UIEditTextSetFont_001
 * @tc.desc: Verify SetFont function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetFont_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    uint8_t fontId = editText_->GetFontId();

    const uint8_t fontSize = 20; // 20: font size for test
    editText_->SetFont("error_font_name", fontSize);

    EXPECT_EQ(editText_->GetFontId(), fontId);
}

/**
 * @tc.name: UIEditTextGetTextWidth_001
 * @tc.desc: Verify GetTextWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextGetTextWidth_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    const char* text = "abc";
    editText_->SetText(text);
    uint16_t width = editText_->GetTextWidth();
    EXPECT_NE(width, 0);
}

/**
 * @tc.name: UIEditTextGetTextHeight_001
 * @tc.desc: Verify GetTextHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextGetTextHeight_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    const char* text = "abc";
    editText_->SetText(text);
    uint16_t height = editText_->GetTextHeight();
    EXPECT_NE(height, 0);
}

/**
 * @tc.name: UIEditTextSetOnChangeListener_001
 * @tc.desc: Verify SetOnChangeListener function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetOnChangeListener_001, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EditTextOnChangeListener* listener = new EditTextOnChangeListener();
    editText_->SetOnChangeListener(listener);
    EXPECT_NE(editText_->GetOnChangeListener(), listener);
}

/**
 * @tc.name: UIEditTextSetOnChangeListener_002
 * @tc.desc: Verify OnChangeListener OnChange function.
 * @tc.type: FUNC
 */
HWTEST_F(UIEditTextTest, UIEditTextSetOnChangeListener_002, TestSize.Level1)
{
    if (editText_ == nullptr) {
        EXPECT_EQ(1, 0);
        return;
    }
    EditTextOnChangeListener* listener = new EditTextOnChangeListener();
    editText_->SetOnChangeListener(listener);
    const char* text = "abc";
    editText_->SetText(text);
    const char* textTmp = editText_->GetText();
    const char* valueTmp = listener->GetValue();
    if ((textTmp == nullptr) || (valueTmp == nullptr)) {
        EXPECT_EQ(1, 0);
        return;
    }
    bool ret = strcmp(textTmp, valueTmp);
    EXPECT_NE(ret, 0);
}
} // namespace OHOS
