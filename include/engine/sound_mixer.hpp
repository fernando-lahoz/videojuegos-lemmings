#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "lib/error.hpp"

// Music represents a long lasting sound, that is decoded while being played
//  in order to keep the less memory used as possible
class Music
{
private:
    std::shared_ptr<Mix_Music> music {nullptr, Mix_FreeMusic};

public:

    void load(const std::string& file)
    {
        
            std::cout << "OA" << std::endl;
        auto raw = Mix_LoadMUS(file.c_str());
        if (raw == nullptr) {
            throw error::sdl_exception(ERROR_CONTEXT);
        }
            
        music = std::shared_ptr<Mix_Music>{raw, Mix_FreeMusic};
    }

    // Returns the raw Mix_Music pointer
    Mix_Music* get() const
    {
        return music.get();
    }
};

// Sound should be relatively short (a few seconds) as they are decoded once, and
//  kept in memory until they are freed
class Sound
{
private:
    std::shared_ptr<Mix_Chunk> sound {nullptr, Mix_FreeChunk};

public:
    void load(const std::string& file)
    {
        auto raw = Mix_LoadWAV(file.c_str());
        if (!raw)
            throw error::sdl_exception(ERROR_CONTEXT);
        sound = std::shared_ptr<Mix_Chunk>{raw, Mix_FreeChunk};
    }

    // Returns the raw Mix_Music pointer
    Mix_Chunk* get() const
    {
        return sound.get();
    }
};

class SoundMixer
{
private:
    std::unordered_map<std::string, Music> music_cache;
    std::unordered_map<std::string, Sound> sound_cache;
    int reserved_channels, free_channels;

    bool is_music_paused = false;
    std::vector<bool> is_channel_paused;

public:
    SoundMixer(const SoundMixer& other) = delete;
    SoundMixer(SoundMixer&& other) = delete;

    inline SoundMixer(int reserved_channels = 0, int free_channels = 8)
        : reserved_channels{reserved_channels}, free_channels{free_channels},
          is_channel_paused(reserved_channels + free_channels, false)
    {
        // These magic numbers should work fine
        if ( Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 512) != 0 )
            throw error::sdl_exception(ERROR_CONTEXT);

        if (reserved_channels + free_channels > 0) {
            Mix_AllocateChannels(reserved_channels + free_channels);
            Mix_ReserveChannels(reserved_channels);
        }
    }

    inline Music load_music(const std::string& file)
    {
        auto it = music_cache.find(file);
        if (it != music_cache.end()) {
            return it->second;
        }
        else {
            Music music;
            music.load(file);
            music_cache[file] = music;

            return music;
        }
    }

    inline Sound load_sound(const std::string& file)
    {
        auto it = sound_cache.find(file);
        if (it != sound_cache.end()) {
            return it->second;
        }
        else {
            Sound sound;
            sound.load(file);
            sound_cache[file] = sound;

            return sound;
        }
    }

    //Plays music from the beginning
    inline void play_music(Music music, bool loop = false)
    {
        std::cout << "PLAY" << std::endl;
        is_music_paused = false;
        Mix_PlayMusic(music.get(), loop ? -1 : 0);
    }

    inline void pause_music()
    {
        is_music_paused = true;
        Mix_PauseMusic();
    }

    inline void resume_music()
    {
        is_music_paused = false;
        Mix_ResumeMusic();
    }

    inline bool is_playing_music()
    {
        return Mix_PlayingMusic() && !Mix_PausedMusic();
    }

    inline bool is_playing_any_sound()
    {
        for (int i = 0; i < reserved_channels + free_channels; i++)
        {
            if (Mix_Playing(i) && !Mix_Paused(i))
                return true;
        }

        return is_playing_music();
    }

    //Should not be called if any sound is currently being played in a free
    // channel, as some of them may (or may not) be muted.
    // It is safe to call while music is been played.
    inline void set_reserved_channels(int n)
    {
        if (n < 0)
            return;
            
        reserved_channels = n;
        Mix_ReserveChannels(n);
        Mix_AllocateChannels(reserved_channels + free_channels);

        is_channel_paused.resize(reserved_channels + free_channels, false);
    }

    //Should not be called if any sound is currently being played in a free
    // channel, as some of them may (or may not) be muted.
    inline void set_free_channels(int n)
    {
        if (n < 0)
            return;
            
        free_channels = n;
        Mix_AllocateChannels(reserved_channels + free_channels);

        is_channel_paused.resize(reserved_channels + free_channels, false);
    }

    inline int get_reserved_channels()
    {
        return reserved_channels;
    }

    inline int get_free_channels()
    {
        return free_channels;
    }

    //Plays sound on a free channel
    inline void play_sound(Sound sound, bool loop = false)
    {
        int channel = Mix_PlayChannel(-1, sound.get(), loop ? -1 : 0);

        is_channel_paused[channel] = false;
    }

    //Plays sound on a reserved channel
    inline void play_sound_on_channel(Sound sound, int channel, bool loop = false)
    {
        Mix_PlayChannel(channel, sound.get(), loop ? -1 : 0);

        is_channel_paused[channel] = false;
    }

    inline void pause_sound_on_channel(int channel)
    {
        Mix_Pause(channel);

        is_channel_paused[channel] = true;
    }

    inline void pause_all_sounds()
    {
        Mix_Pause(-1);

        for (auto e : is_channel_paused)
            e = true;
    }

    inline void resume_all_paused_sounds()
    {
        Mix_Resume(-1);

        for (auto e : is_channel_paused)
            e = false;
    }

    inline void resume_sound_on_channel(int channel)
    {
        Mix_Resume(channel);

        is_channel_paused[channel] = false;
    }

    // Sets the channel volume to a value between 0 (no sound) and 1 (max value)
    inline void set_channel_volume(int channel, float volume)
    {
        Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
    }

    inline void set_general_volume(float volume)
    {
        int mapped_volume = (int)(volume * MIX_MAX_VOLUME);
        Mix_VolumeMusic(mapped_volume);
        Mix_Volume(-1, mapped_volume);
    }

    inline void set_music_volume(float volume)
    {
        Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
    }

    inline ~SoundMixer()
    {
        music_cache.clear();
        sound_cache.clear();
        Mix_CloseAudio();
    }


    inline void block_sound()
    {
        Mix_PauseMusic();
        Mix_Pause(-1);
    }

    inline void release_sound()
    {
        if (!is_music_paused)
            Mix_ResumeMusic();

        for (std::size_t i = 0; i < is_channel_paused.size(); i++)
            if (!is_channel_paused[i])
                Mix_Resume(i);
    }
};