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
