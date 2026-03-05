#ifndef H_AUDIO_GENERATOR
#define H_AUDIO_GENERATOR

#include <audio/wav.hpp>
#include <utilities/defined.hpp>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <cmath>
#include <atomic>
#include <functional>

class IAudioGeneratorCallback {
public:
    virtual ~IAudioGeneratorCallback() = default;
    virtual void Notify(std::string) = 0;
    virtual void RefressScreen() = 0;
};

class AudioGenerator {
public:
    static AudioGenerator& getInstance() {
        static AudioGenerator inst;
        return inst;
    };
    AudioGenerator(const AudioGenerator&) = delete;
    void  operator=(const AudioGenerator&) = delete;
    const std::vector<std::string> listSimpleRate    = { "48000", "44100", "16000", "8000" };
    const std::vector<std::string> listChannels      = { "1 Channel","2 Channel","3 Channel","4 Channel","5 Channel","6 Channel","7 Channel","8 Channel" };
    const std::vector<std::string> listBitsPerSample = { "16", "32" };
    const std::vector<std::string> listFileTypes     = { "PCM (RAW)", "WAV" };

    /** Passing selection data to this */
    void GenerateAudioFile(
        audio_info data,
        std::string filename,
        IAudioGeneratorCallback* callback);
    std::atomic<float> m_thread_render_progress{0.0f}; // Thread-safe progress tracking
private:
    virtual ~AudioGenerator() = default;
    AudioGenerator() {};
    template<typename T>
      void GenerateAudioTask(audio_info data, std::string filename, IAudioGeneratorCallback* callback);
};
#endif // H_AUDIO_GENERATOR