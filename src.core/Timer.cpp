#include "core/Timer.h"

Timer::Timer()
    : m_startTicks(0), m_pausedTicks(0), m_started(false), m_paused(false) {}

void Timer::Start() {
    m_started = true;
    m_paused = false;
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void Timer::Stop() {
    m_started = false;
    m_paused = false;
    m_startTicks = 0;
    m_pausedTicks = 0;
}

void Timer::Pause() {
    if (m_started && !m_paused) {
        m_paused = true;
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
    }
}

void Timer::Resume() {
    if (m_started && m_paused) {
        m_paused = false;
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

Uint32 Timer::GetTicks() const {
    if (m_started) {
        if (m_paused) {
            return m_pausedTicks;
        } else {
            return SDL_GetTicks() - m_startTicks;
        }
    }
    return 0;
}
