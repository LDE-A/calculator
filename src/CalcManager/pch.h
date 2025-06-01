// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

// The CalcManager project should be able to be compiled with or without a precompiled header
// in - order to support other toolchains besides MSVC. When adding new system headers, make sure
// that the relevant source file includes all headers it needs, but then also add the system headers
// here so that MSVC users see the performance benefit.

// Windows SDKより前に標準ライブラリを確実にインクルード
#include <cstddef>

// byteマクロの衝突を事前に回避
#pragma push_macro("byte")
#ifdef byte
#undef byte
#endif

// Windows APIヘッダーのインクルード
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#include <windows.h>

// 標準ライブラリの後処理
#pragma pop_macro("byte")

// その他必要なヘッダー
#include <algorithm>
#include <array>
#include <cassert>
#include <intsafe.h>
#include <list>
#include <future>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <winerror.h>
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <map>
#include <functional>
