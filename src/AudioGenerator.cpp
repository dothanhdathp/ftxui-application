#include <AudioGenerator.hpp>
#include <format>

void AudioGenerator::GenerateAudioFile(audio_info data, std::string filename, IAudioGeneratorCallback* callback) {
    // Create new task
    if(thread_generate != nullptr) {
        __terminate = true;
        thread_generate->join();
        thread_generate = nullptr;
        __terminate = false;
    } else {
        if(16 == data.bit_per_sample) {
            thread_generate = new std::thread(&AudioGenerator::GenerateAudioTask<int16_t>, this, data, filename, callback);
        } else {
            thread_generate = new std::thread(&AudioGenerator::GenerateAudioTask<int32_t>, this, data, filename, callback);
        }
    }
}

template<typename T>
void AudioGenerator::GenerateAudioTask(audio_info data, std::string filename, IAudioGeneratorCallback* callback) {
    std::ofstream file_out;
    if(E_PCM_FILE == data.filetype) {
        file_out = std::ofstream((filename + ".pcm").c_str(), std::ios::binary);
    } if (E_WAV_FILE == data.filetype) {
        WAVHeader header;
    
        header.subchunk1Size = 16;
        header.audioFormat = 1;
        header.numChannels = data.channel;
        header.sampleRate = data.sample_rate;
        header.bitsPerSample = data.bit_per_sample;
        file_out = std::ofstream((filename + ".wav").c_str(), std::ios::binary);
        // Write HEADER wav file into a media file
        file_out.write(reinterpret_cast<const char*>(&header),  sizeof(header));
    }
    
    uint32_t data_size = data.sample_rate * data.duration;
    if (!file_out) {
        callback->Notify("Can not creat audio file.");
        return;
    }

    // Pushing data
    uint32_t cnt = 1000;
    callback->Notify("Generating ...");
    for (uint32_t i = 0; i < data_size; ++i) {
        double t = static_cast<double>(i) / data.sample_rate;
        if(__terminate) goto terminate;
        for (uint16_t channel = 0; channel < data.channel; ++channel) {
            // uint16_t D = (channel%2);
            double sample = data.amplitude * std::sin(2.0*M_PI*(data.frequence)*t);
            T sample_int = static_cast<T>(sample);
            file_out.write(reinterpret_cast<const char*>(&sample_int),  sizeof(sample_int));
        }
        if(--cnt == 0) {
            // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            m_thread_render_progress.store(static_cast<float>(t)/static_cast<float>(data.duration));
            callback->Refresh();
            cnt = 1000;
        }
    }
    m_thread_render_progress.store(1.0f);
    file_out.close();
    callback->Notify("Done!");
    callback->Refresh();
    thread_generate = nullptr;
    return;

terminate:
    file_out.close();
    m_thread_render_progress.store(0.0f);
    callback->Notify("Terminated!");
    callback->Refresh();
    thread_generate = nullptr;
    return;
}