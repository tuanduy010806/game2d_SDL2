#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <map>

class AudioManager {
public:
    static AudioManager* Instance();

    bool LoadMusic(const std::string& id, const std::string& path);
    bool LoadSound(const std::string& id, const std::string& path);
    void PlayMusic(const std::string& id, int loops = -1);
    void PlaySound(const std::string& id, int loops = 0);

    void ToggleMute();
    bool IsMuted() const { return m_muted; }
    void Clean();

private:
    AudioManager();
    ~AudioManager();
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, Mix_Music*> m_musicMap;
    std::map<std::string, Mix_Chunk*> m_soundMap;
    static AudioManager* s_instance;
    bool m_muted;
};

#endif // AUDIOMANAGER_H
