#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

class Timer {
public:
    Timer();

    void Start();
    void Stop();
    void Pause();
    void Resume();

    Uint32 GetTicks() const;
    float GetSeconds() const { return GetTicks() / 1000.0f; }
    bool IsStarted() const { return m_started; }
    bool IsPaused() const { return m_paused; }

private:
    Uint32 m_startTicks;
    Uint32 m_pausedTicks;
    bool m_started;
    bool m_paused;
};
#endif
