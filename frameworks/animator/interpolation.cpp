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

#include "animator/interpolation.h"

#include "gfx_utils/graphic_math.h"

namespace OHOS {
/* B(t) = P0*(1-t)^3 + 3*P1*t*(1-t)^2 + 3*P2*t^2*(1-t) + P3*t^3 */
int16_t Interpolation::GetBezierInterpolation(int16_t t, int16_t u0, int16_t u1, int16_t u2, int16_t u3)
{
    int64_t invT = INTERPOLATION_RANGE - t;
    int64_t invT2 = invT * invT;
    int64_t invT3 = invT2 * invT;
    int64_t t2 = t * t;
    int64_t t3 = t2 * t;

    int64_t ret = invT3 * u0;
    ret += BESSEL_COEFFICIENT * invT2 * t * u1;
    ret += BESSEL_COEFFICIENT * invT * t2 * u2;
    ret += t3 * u3;
    ret = ret >> CUBIC_BEZIER_CALCULATE_OFFSET;
    return static_cast<int16_t>(ret);
}

/* B(t) = 3(P1-P0)(1-t)^2 + 6(P2-P1)t(1-t) + 3(P3-P2)t^2 */
int16_t Interpolation::GetBezierDerivative(int16_t t, int16_t u0, int16_t u1, int16_t u2, int16_t u3)
{
    int64_t invT = INTERPOLATION_RANGE - t;
    int64_t d0 = u1 - u0;
    int64_t d1 = u2 - u1;
    int64_t d2 = u3 - u2;
    constexpr int32_t BESSEL_SQUARE_COEFFICIENT = (BESSEL_COEFFICIENT - 1) * BESSEL_COEFFICIENT;
    constexpr int32_t BESSEL_SQUARE_OFFSET = 20;

    int64_t ret = BESSEL_COEFFICIENT * d0 * invT * invT;
    ret += BESSEL_SQUARE_COEFFICIENT * d1 * invT * t;
    ret += BESSEL_COEFFICIENT * d2 * t * t;
    ret = ret >> BESSEL_SQUARE_OFFSET;
    return static_cast<int16_t>(ret);
}

int16_t Interpolation::GetBezierY(int16_t x, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    /* P={x,y}; P0={0,0}; P1={x1,y1}; P2={x2,y2}; P3={1,1}
     * P = P0*(1-t)^3 + 3*P1*t*(1-t)^2 + 3*P2*t^2*(1-t) + P3*t^3
     */
    int16_t t = x;
    int16_t xt = GetBezierInterpolation(t, 0, x1, x2, INTERPOLATION_RANGE);
    /* Attention: precision must be carefully selected
     * too small may lead to misconvergence and a decrease of performance
     * too large may cause the curve rugged even make some points outlier */
    constexpr int8_t PRECISION = 50; // 50 make serveral outliers near inflection point

    /* Newton Method to solve t from x */
    while (MATH_ABS(xt - x) > PRECISION) {
        t = t + (x - xt) * INTERPOLATION_RANGE / GetBezierDerivative(t, 0, x1, x2, INTERPOLATION_RANGE);
        xt = GetBezierInterpolation(t, 0, x1, x2, INTERPOLATION_RANGE);
    }
    return GetBezierInterpolation(t, 0, y1, y2, INTERPOLATION_RANGE);
}
} // namespace OHOS
