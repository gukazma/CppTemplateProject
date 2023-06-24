/*
 * @Author       : gukazma && gukazma@proton.me
 * @Date         : 2023-06-24 14:39:17
 * @FilePath     : \CppTemplateProject\Modules\Common\Primitives\Include\LibName\Timer.hpp
 * @Description  : The Timer class uses the high-resolution clock from the C++ standard library to
 * measure elapsed time MIT License
 *
 * Copyright (c) 2023 gukazma
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files, to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *
 */
#pragma once

#include <chrono>

namespace LibName {

class Timer
{
public:
    using Clock        = std::chrono::high_resolution_clock;
    using TimePoint    = Clock::time_point;
    using TimeDuration = Clock::duration;

    Timer() = default;

    [[nodiscard]] TimePoint    GetStartTime() const noexcept { return m_start_time; }
    [[nodiscard]] TimeDuration GetElapsedDuration() const noexcept
    {
        return Clock::now() - m_start_time;
    }
    [[nodiscard]] uint32_t GetElapsedSecondsU() const noexcept
    {
        return GetElapsedSeconds<uint32_t>();
    }
    [[nodiscard]] double GetElapsedSecondsD() const noexcept { return GetElapsedSeconds<double>(); }
    [[nodiscard]] float  GetElapsedSecondsF() const noexcept { return GetElapsedSeconds<float>(); }

    template<typename T> [[nodiscard]] T GetElapsedSeconds() const noexcept
    {
        return std::chrono::duration_cast<std::chrono::duration<T>>(GetElapsedDuration()).count();
    }

    void Reset() noexcept { Reset(Clock::now()); }

    void Reset(TimeDuration duration) noexcept { Reset(Clock::now() - duration); }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void ResetToSeconds(T seconds) noexcept
    {
        Reset(std::chrono::duration_cast<TimeDuration>(
            std::chrono::duration<T>(seconds)));   // NOSONAR
    }

protected:
    void Reset(TimePoint time_point) { m_start_time = time_point; }

private:
    TimePoint m_start_time = Clock::now();
};

}   // namespace LibName
