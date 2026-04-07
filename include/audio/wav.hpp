/**
 * 
 */

#ifndef WAV_HPP
#define WAV_HPP

#include <inttypes.h>

enum e_file_t {
    E_PCM_FILE,
    E_WAV_FILE,
};

struct audio_info {
  uint16_t sample_rate;
  uint16_t amplitude;
  uint16_t channel;
  uint16_t frequence;
  uint16_t bit_per_sample;
  uint16_t duration;
  e_file_t filetype;
};

struct WAVHeader {
  char riff[4] = {'R', 'I', 'F', 'F'};
  uint32_t chunkSize;
  char wave[4] = {'W', 'A', 'V', 'E'};
  char fmt[4] = {'f', 'm', 't', ' '};
  uint32_t subchunk1Size = 16;
  uint16_t audioFormat = 1;
  uint16_t numChannels = 2;
  uint32_t sampleRate = 48000;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample = 16;
  char data[4] = {'d', 'a', 't', 'a'};
  uint32_t subchunk2Size;
};

#endif // #define WAV_HPPWAV_HPP