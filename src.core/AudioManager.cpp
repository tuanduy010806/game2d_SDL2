
#include "core/AudioManager.h"
#include <iostream>

AudioManager* AudioManager::s_instance = nullptr;

AudioManager* AudioManager::Instance() {
    if (!s_instance) {
        s_instance = new AudioManager();
    }
    return s_instance;
}

AudioManager::AudioManager() : m_muted(false) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! " << Mix_GetError() << std::endl;
    }
}

AudioManager::~AudioManager() {
    Clean();
    Mix_CloseAudio();
}

bool AudioManager::LoadMusic(const std::string& id, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << path << " - " << Mix_GetError() << std::endl;
        return false;
    }
    m_musicMap[id] = music;
    return true;
}

bool AudioManager::LoadSound(const std::string& id, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound: " << path << " - " << Mix_GetError() << std::endl;
        return false;
    }
    m_soundMap[id] = chunk;
    return true;
}
// phát nhạc
void AudioManager::PlayMusic(const std::string& id, int loops) {
    if (m_musicMap.count(id)) {
        if (Mix_PlayMusic(m_musicMap[id], loops) == -1) {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Music id '" << id << "' not found!" << std::endl;
    }
}
// phát âm thanh hiệu ứng
void AudioManager::PlaySound(const std::string& id, int loops) {
    if (m_soundMap.count(id)) {
        if (Mix_PlayChannel(-1, m_soundMap[id], loops) == -1) {
            std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Sound id '" << id << "' not found!" << std::endl;
    }
}
void AudioManager::StopMusic() {
    Mix_HaltMusic();
}
// tắt bật toàn bộ âm thanh và hiệu ứng âm thanh trong game
void AudioManager::ToggleMute() {
    m_muted = !m_muted;
    if (m_muted) {
        Mix_VolumeMusic(0); // 0 là phát 1 lần
        Mix_Volume(-1, 0); // Mute all
    } else {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
        Mix_Volume(-1, MIX_MAX_VOLUME);
    }
}

void AudioManager::Clean() {
    for (auto const& [key, val] : m_musicMap) {
        Mix_FreeMusic(val);
    }
    for (auto const& [key, val] : m_soundMap) {
        Mix_FreeChunk(val);
    }
    m_musicMap.clear();
    m_soundMap.clear();
}
