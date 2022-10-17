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
    static void SetUpTestCase(void) {}
    static void TearDownTestCase(void) {}
};

/**
 * @tc.name: UIEditTextGetViewType_001
 * @tc.desc: Verify GetViewType and GetHeight function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextGetViewType_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    EXPECT_EQ(editText->GetViewType(), UI_EDIT_TEXT);
    delete editText;
}

/**
 * @tc.name: UIEditTextResize_001
 * @tc.desc: Verify Resize function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextResize_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    editText->Resize(INIT_WIDTH, INIT_HEIGHT);
    EXPECT_EQ(editText->GetWidth(), INIT_WIDTH);
    EXPECT_EQ(editText->GetHeight(), INIT_HEIGHT);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetText_001
 * @tc.desc: Verify SetText function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetText_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    const char* text = "abc";
    editText->Resize(INIT_WIDTH, INIT_HEIGHT);
    editText->SetText(text);

    const char* textTmp = editText->GetText();
    ASSERT_TRUE(textTmp);
    EXPECT_EQ(strcmp(textTmp, text), 0);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetPlaceholder_001
 * @tc.desc: Verify SetPlaceholder function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetPlaceholder_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    const char* placeholder = "Name:";
    editText->Resize(INIT_WIDTH, INIT_HEIGHT);
    editText->SetPlaceholder(placeholder);

    const char* placeholderTmp = editText->GetPlaceholder();
    ASSERT_TRUE(placeholderTmp);
    EXPECT_EQ(strcmp(placeholderTmp, placeholder), 0);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetMaxLength_001
 * @tc.desc: Verify SetMaxLength function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetMaxLength_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    uint16_t length1 = 20;
    editText->SetMaxLength(length1);
    EXPECT_EQ(editText->GetMaxLength(), length1);

    uint16_t length2 = 0;
    editText->SetMaxLength(length2);
    EXPECT_EQ(editText->GetMaxLength(), length2);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetInputType_001
 * @tc.desc: Verify SetInputType function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetInputType_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    // check the default type
    EXPECT_EQ(editText->GetInputType(), InputType::TEXT_TYPE);

    InputType type = InputType::TEXT_TYPE;
    editText->SetInputType(type);
    EXPECT_EQ(editText->GetInputType(), type);

    type = InputType::PASSWORD_TYPE;
    editText->SetInputType(type);
    EXPECT_EQ(editText->GetInputType(), type);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetTextColor_001
 * @tc.desc: Verify SetTextColor function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetTextColor_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    ColorType color = Color::White();

    editText->SetTextColor(color);
    EXPECT_EQ(editText->GetTextColor().full, color.full);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetPlaceholderColor_001
 * @tc.desc: Verify SetPlaceholderColor function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetPlaceholderColor_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    ColorType color = Color::White();

    editText->SetPlaceholderColor(color);
    EXPECT_EQ(editText->GetPlaceholderColor().full, color.full);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetCursorColor_001
 * @tc.desc: Verify SetCursorColor function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetCursorColor_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    ColorType color = Color::White();

    editText->SetCursorColor(color);
    EXPECT_EQ(editText->GetCursorColor().full, color.full);
    delete editText;
}

/**
 * @tc.name: UIEditTextSetFont_001
 * @tc.desc: Verify SetFont function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetFont_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    uint16_t fontId = editText->GetFontId();

    const uint8_t fontSize = 20; // 20: font size for test
    editText->SetFont("error_font_name", fontSize);

    EXPECT_EQ(editText->GetFontId(), fontId);
    delete editText;
}

/**
 * @tc.name: UIEditTextGetTextWidth_001
 * @tc.desc: Verify GetTextWidth function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextGetTextWidth_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    const char* text = "abc";
    editText->SetText(text);
    uint16_t width = editText->GetTextWidth();
    EXPECT_EQ(width, 0); // no font file case
    delete editText;
}

/**
 * @tc.name: UIEditTextGetTextHeight_001
 * @tc.desc: Verify GetTextHeight function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextGetTextHeight_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    const char* text = "abc";
    editText->SetText(text);
    uint16_t height = editText->GetTextHeight();
    EXPECT_EQ(height, 0); // no font file case
    delete editText;
}

/**
 * @tc.name: UIEditTextSetOnChangeListener_001
 * @tc.desc: Verify SetOnChangeListener function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetOnChangeListener_001, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    EditTextOnChangeListener* listener = new EditTextOnChangeListener();
    editText->SetOnChangeListener(listener);
    EXPECT_EQ(editText->GetOnChangeListener(), listener);
    delete listener;
    delete editText;
}

/**
 * @tc.name: UIEditTextSetOnChangeListener_002
 * @tc.desc: Verify OnChangeListener OnChange function.
 * @tc.type: FUNC
 * @tc.require: issueI5AD4A
 */
HWTEST_F(UIEditTextTest, UIEditTextSetOnChangeListener_002, TestSize.Level1)
{
    UIEditText* editText = new UIEditText();
    EditTextOnChangeListener* listener = new EditTextOnChangeListener();
    editText->SetOnChangeListener(listener);
    const char* text = "abc";
    editText->SetText(text);
    const char* textTmp = editText->GetText();
    const char* valueTmp = listener->GetValue();
    if ((textTmp == nullptr) || (valueTmp == nullptr)) {
        EXPECT_EQ(1, 0);
        delete listener;
        delete editText;
        return;
    }
    bool ret = strcmp(textTmp, valueTmp);
    EXPECT_EQ(ret, 0);
    delete listener;
    delete editText;
}
} // namespace OHOS
