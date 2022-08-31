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

/**
 * This file mocks "umutex.h" in icu library when using IAR toolchain which do not support multi-thread library.
 * Build-system should pre-define UMUTEX_H to inactive umutex.h and active this mock header.
 * This file must be included before any header of icu in source file.
 */
#ifdef UMUTEX_H
#ifndef ICU_UMUTEX_STUB_H
#define ICU_UMUTEX_STUB_H

#include <atomic>
#include "unicode/utypes.h"
#include "unicode/uclean.h"
#include "unicode/uobject.h"

#include "putilimp.h"
typedef std::atomic<int32_t> u_atomic_int32_t;

#endif
#endif