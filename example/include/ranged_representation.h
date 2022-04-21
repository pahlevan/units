// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "validated_type.h"
#include <algorithm>
#include <type_traits>

template<auto Min, auto Max>
inline constexpr auto is_in_range = [](const auto& v) { return std::clamp(v, Min, Max) == v; };

template<typename T, T Min, T Max>
class ranged_representation : public validated_type<T, decltype(is_in_range<Min, Max>)> {
public:
  using base = validated_type<T, decltype(is_in_range<Min, Max>)>;
  using base::validated_type;
  constexpr ranged_representation() : base(T{}) {}

  [[nodiscard]] constexpr ranged_representation operator-() const { return ranged_representation(-this->value()); }
};

template<typename T, T Min, T Max>
struct std::common_type<std::intmax_t, ranged_representation<T, Min, Max>> :
    std::type_identity<
      ranged_representation<std::common_type_t<std::intmax_t, T>, std::common_type_t<std::intmax_t, T>{Min},
                            std::common_type_t<std::intmax_t, T>{Max}>> {};

template<typename T, T Min, T Max>
struct std::common_type<ranged_representation<T, Min, Max>, std::intmax_t> :
    std::type_identity<
      ranged_representation<std::common_type_t<T, std::intmax_t>, std::common_type_t<T, std::intmax_t>{Min},
                            std::common_type_t<T, std::intmax_t>{Max}>> {};
