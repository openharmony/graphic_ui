/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
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

#include "components/ui_abstract_scroll.h"
#include "animator/interpolation.h"
#include "components/ui_abstract_scroll_bar.h"
#include "graphic_timer.h"

#if RECTANGLE_SCREEN
#include "components/ui_box_scroll_bar.h"
#define BAR_OP(obj, op, ...)              \
    do {                                  \
        obj.yScrollBar_->op(__VA_ARGS__); \
        obj.xScrollBar_->op(__VA_ARGS__); \
    } while (0)
#else
#include "components/ui_arc_scroll_bar.h"
#define BAR_OP(obj, op, ...) obj.yScrollBar_->op(__VA_ARGS__)
#endif

namespace {
#if ENABLE_ROTATE_INPUT
constexpr float DEFAULT_ABSTRACT_SCROLL_ROTATE_FACTOR = 2.5;
constexpr uint8_t DEFAULT_ROTATE_THRESHOLD = 4;
#endif
}

namespace OHOS {
#if DEFAULT_ANIMATION
class BarEaseInOutAnimator final : private AnimatorCallback {
public:
    BarEaseInOutAnimator() = delete;
    BarEaseInOutAnimator(const BarEaseInOutAnimator&) = delete;
    BarEaseInOutAnimator& operator=(const BarEaseInOutAnimator&) = delete;
    BarEaseInOutAnimator(BarEaseInOutAnimator&&) = delete;
    BarEaseInOutAnimator& operator=(BarEaseInOutAnimator&&) = delete;

    BarEaseInOutAnimator(UIAbstractScroll& scrollView)
        : scrollView_(scrollView),
          timer_(APPEAR_PERIOD, TimerCb, this),
          animator_(this, nullptr, ANIMATOR_DURATION, false) {}

    ~BarEaseInOutAnimator()
    {
        timer_.Stop();
        animator_.Stop();
    }

    void RefreshBar()
    {
        if (animator_.GetState() == Animator::START) {
            if (!isEaseIn_) {
                animator_.SetRunTime(ANIMATOR_DURATION - animator_.GetRunTime());
            }
        } else if (scrollView_.yScrollBar_->GetOpacity() == OPA_TRANSPARENT) {
            animator_.Start();
        } else {
            timer_.Start(); // updates the start time of timer, ensuring that timer is triggered two seconds after the
                            // last operation
        }
        isEaseIn_ = true;
    }

private:
    void Callback(UIView* view) override
    {
        uint8_t opa = OPA_OPAQUE * animator_.GetRunTime() / ANIMATOR_DURATION;
        if (!isEaseIn_) {
            opa = OPA_OPAQUE - opa;
        }
        float bezielY = opa;
        bezielY =
            Interpolation::GetBezierY(bezielY / OPA_OPAQUE, 0, BEZIER_CONTROL_POINT_Y_1, BEZIER_CONTROL_POINT_X_2, 1);
        opa = static_cast<uint8_t>(bezielY * opa);
        BAR_OP(scrollView_, SetOpacity, opa);
        scrollView_.Invalidate();
    }

    void OnStop(UIView& view) override
    {
        if (isEaseIn_) {
            BAR_OP(scrollView_, SetOpacity, OPA_OPAQUE);
            timer_.Start(); // The timer is triggered when animation stops.
        } else {
            BAR_OP(scrollView_, SetOpacity, OPA_TRANSPARENT);
        }
        scrollView_.Invalidate();
    }

    static void TimerCb(void* arg)
    {
        BarEaseInOutAnimator* barAnimator = reinterpret_cast<BarEaseInOutAnimator*>(arg);
        barAnimator->isEaseIn_ = false;
        barAnimator->animator_.Start();
    }
    static constexpr uint16_t ANIMATOR_DURATION = 250;
    static constexpr uint16_t APPEAR_PERIOD = 2000;
    static constexpr float BEZIER_CONTROL_POINT_Y_1 = 0.33f;
    static constexpr float BEZIER_CONTROL_POINT_X_2 = 0.67f;
    UIAbstractScroll& scrollView_;
    GraphicTimer timer_;
    Animator animator_;
    bool isEaseIn_ = true;
};
#endif

UIAbstractScroll::UIAbstractScroll()
    : direction_(VERTICAL),
      deltaYIndex_(0),
      reserve_(0),
      easingFunc_(EasingEquation::CubicEaseOut),
      scrollAnimator_(&animatorCallback_, this, 0, true)
{
#if RECTANGLE_SCREEN
    xScrollBar_ = new UIBoxScrollBar();
    if (xScrollBar_ == nullptr) {
        GRAPHIC_LOGE("new UIBoxScrollBar fail");
        return;
    }
    yScrollBar_ = new UIBoxScrollBar();
#else
    yScrollBar_ = new UIArcScrollBar();
#endif
    if (yScrollBar_ == nullptr) {
        GRAPHIC_LOGE("new ScrollBar fail");
        return;
    }
#if DEFAULT_ANIMATION
    barEaseInOutAnimator_ = new BarEaseInOutAnimator(*this);
    if (barEaseInOutAnimator_ == nullptr) {
        GRAPHIC_LOGE("new BarEaseInOutAnimator fail");
        return;
    }
#endif
#if ENABLE_FOCUS_MANAGER
    focusable_ = true;
#endif
#if ENABLE_ROTATE_INPUT
    rotateFactor_ = DEFAULT_ABSTRACT_SCROLL_ROTATE_FACTOR;
    threshold_ = DEFAULT_ROTATE_THRESHOLD;
#endif
    isViewGroup_ = true;
    touchable_ = true;
    draggable_ = true;
    dragParentInstead_ = false;
}

UIAbstractScroll::~UIAbstractScroll()
{
#if DEFAULT_ANIMATION
    delete barEaseInOutAnimator_;
    barEaseInOutAnimator_ = nullptr;
#endif
#if RECTANGLE_SCREEN
    delete xScrollBar_;
    xScrollBar_ = nullptr;
#endif
    delete yScrollBar_;
    yScrollBar_ = nullptr;
}

void UIAbstractScroll::MoveChildByOffset(int16_t offsetX, int16_t offsetY)
{
    if ((offsetX == 0) && (offsetY == 0)) {
        return;
    }
    UIView* view = GetChildrenHead();
    int16_t x;
    int16_t y;
    while (view != nullptr) {
        x = view->GetX() + offsetX;
        y = view->GetY() + offsetY;
        view->SetPosition(x, y);
        view = view->GetNextSibling();
    }

    Rect childrenRect = GetAllChildRelativeRect();
    /* calculate scrollBar's the proportion of foreground */
    int16_t totalLen = childrenRect.GetHeight() + 2 * scrollBlankSize_; // 2: two blank space on both sizes
    int16_t len = GetHeight();
    yScrollBar_->SetForegroundProportion(static_cast<float>(len) / totalLen);
    /* calculate scrolling progress */
    yScrollBar_->SetScrollProgress(static_cast<float>(scrollBlankSize_ - childrenRect.GetTop()) / (totalLen - len));
#if RECTANGLE_SCREEN
    /* so do x-bar */
    totalLen = childrenRect.GetWidth() + 2 * scrollBlankSize_; // 2: two blank space on both sizes
    len = GetWidth();
    xScrollBar_->SetForegroundProportion(static_cast<float>(len) / totalLen);
    xScrollBar_->SetScrollProgress(static_cast<float>(scrollBlankSize_ - childrenRect.GetLeft()) / (totalLen - len));
#endif
    Invalidate();
}

int16_t UIAbstractScroll::GetMaxDeltaY() const
{
    int16_t result = 0;
    for (int16_t i = 0; i < MAX_DELTA_Y_SIZE; i++) {
        if (result < MATH_ABS(lastDeltaY_[i])) {
            result = MATH_ABS(lastDeltaY_[i]);
        }
    }
    return result;
}

void UIAbstractScroll::StopAnimator()
{
    scrollAnimator_.Stop();
    animatorCallback_.RsetCallback();
    isDragging_ = false;
}

bool UIAbstractScroll::DragThrowAnimator(Point currentPos, Point lastPos)
{
    if (!throwDrag_ && (reboundSize_ == 0)) {
        return false;
    }
    int16_t dragDistanceX = 0;
    int16_t dragDistanceY = 0;
    if (throwDrag_) {
        CalculateDragDistance(currentPos, lastPos, dragDistanceX, dragDistanceY);
    }
    if (reboundSize_ != 0) {
        CalculateReboundDistance(dragDistanceX, dragDistanceY);
    }
    StartAnimator(dragDistanceX, dragDistanceY);
    return true;
}

void UIAbstractScroll::StartAnimator(int16_t dragDistanceX, int16_t dragDistanceY)
{
    int16_t dragTimes = MATH_MAX(MATH_ABS(dragDistanceX), MATH_ABS(dragDistanceY)) / DRAG_TIMES_COEFFICIENT;
    if (dragTimes < MIN_DRAG_TIMES) {
        dragTimes = MIN_DRAG_TIMES;
    }
    animatorCallback_.RsetCallback();
    animatorCallback_.SetDragStartValue(0, 0);
    animatorCallback_.SetDragEndValue(dragDistanceX, dragDistanceY);
    animatorCallback_.SetDragTimes(dragTimes * DRAG_ACC_FACTOR / GetDragACCLevel());
    scrollAnimator_.Start();
}

void UIAbstractScroll::CalculateDragDistance(Point currentPos,
                                             Point lastPos,
                                             int16_t& dragDistanceX,
                                             int16_t& dragDistanceY)
{
    if ((direction_ == VERTICAL) || (direction_ == HORIZONTAL_AND_VERTICAL)) {
        dragDistanceY = (currentPos.y - lastPos.y) * DRAG_DISTANCE_COEFFICIENT;
        if (dragDistanceY > 0) {
            dragDistanceY += GetMaxDeltaY() * GetSwipeACCLevel() / DRAG_ACC_FACTOR;
        } else {
            dragDistanceY -= GetMaxDeltaY() * GetSwipeACCLevel() / DRAG_ACC_FACTOR;
        }
    }

    if ((direction_ == HORIZONTAL) || (direction_ == HORIZONTAL_AND_VERTICAL)) {
        dragDistanceX = (currentPos.x - lastPos.x) * DRAG_DISTANCE_COEFFICIENT;
    }

    if (maxScrollDistance_ != 0) {
        if (MATH_ABS(dragDistanceY) > maxScrollDistance_) {
            int16_t calculatedValue = (dragDistanceY > 0) ? 1 : -1;
            dragDistanceY = calculatedValue * maxScrollDistance_;
        }
        if (MATH_ABS(dragDistanceX) > maxScrollDistance_) {
            int16_t calculatedValue = (dragDistanceX > 0) ? 1 : -1;
            dragDistanceX = calculatedValue * maxScrollDistance_;
        }
    }
}

void UIAbstractScroll::ListAnimatorCallback::Callback(UIView* view)
{
    if (view == nullptr) {
        return;
    }

    UIAbstractScroll* scrollView = static_cast<UIAbstractScroll*>(view);
    scrollView->isDragging_ = true;
    curtTime_++;
    if (curtTime_ <= dragTimes_) {
        bool needStopX = false;
        bool needStopY = false;
        if (startValueY_ != endValueY_) {
            int16_t actY = scrollView->easingFunc_(startValueY_, endValueY_, curtTime_, dragTimes_);
            if (!scrollView->DragYInner(actY - previousValueY_)) {
                needStopY = true;
            }
            previousValueY_ = actY;
        } else {
            needStopY = true;
        }
        if (startValueX_ != endValueX_) {
            int16_t actX = scrollView->easingFunc_(startValueX_, endValueX_, curtTime_, dragTimes_);
            if (!scrollView->DragXInner(actX - previousValueX_)) {
                needStopX = true;
            }
            previousValueX_ = actX;
        } else {
            needStopX = true;
        }
        if (needStopX && needStopY) {
            scrollView->StopAnimator();
        }
    } else {
        scrollView->StopAnimator();
    }
}

void UIAbstractScroll::OnPostDraw(BufferInfo& gfxDstBuffer, const Rect& invalidatedArea)
{
    Rect scrollRect = GetRect();
    uint8_t opa = GetMixOpaScale();
#if RECTANGLE_SCREEN
    if (yScrollBarVisible_) {
        yScrollBar_->SetPosition(scrollRect.GetRight() - SCROLL_BAR_WIDTH + 1, scrollRect.GetTop(), SCROLL_BAR_WIDTH,
                                 scrollRect.GetHeight());
        yScrollBar_->OnDraw(gfxDstBuffer, invalidatedArea, opa);
    }
    if (xScrollBarVisible_) {
        xScrollBar_->SetPosition(scrollRect.GetLeft(), scrollRect.GetBottom() - SCROLL_BAR_WIDTH + 1,
                                 scrollRect.GetWidth() - SCROLL_BAR_WIDTH, SCROLL_BAR_WIDTH);
        xScrollBar_->OnDraw(gfxDstBuffer, invalidatedArea, opa);
    }
#else
    if (yScrollBarVisible_) {
        int16_t x = scrollRect.GetX() + (GetWidth() / 2); // 2: half
        int16_t y = scrollRect.GetY() + (GetHeight() / 2); // 2: half
        yScrollBar_->SetPosition(x, y, SCROLL_BAR_WIDTH, GetWidth() / 2); // 2: half
        yScrollBar_->OnDraw(gfxDstBuffer, invalidatedArea, opa);
    }
#endif
    UIView::OnPostDraw(gfxDstBuffer, invalidatedArea);
}

void UIAbstractScroll::RefreshAnimator()
{
#if DEFAULT_ANIMATION
    barEaseInOutAnimator_->RefreshBar();
#endif
}
} // namespace OHOS
