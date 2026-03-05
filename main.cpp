#include <audio/wav.hpp>
#include <FtxApp.hpp>

int main(int argc, const char *args[]) {
    FtxApp app = FtxApp(argc, args);
    app.Init();
    app.RenderScreen();
    app.RunLoop();
    return 0;
}

// #ifndef M_PI
//   #define M_PI 3.14159265358979323846
// #endif

// template<typename T>
// bool generate_audio(
//     audio_info &data,
//     std::string filename,
//     int duration
//   ) {
  
//   WAVHeader header;
  
//   header.subchunk1Size = 16;
//   header.audioFormat = 1;
//   header.numChannels = data.channel;
//   header.sampleRate = data.sample_rate;
//   header.bitsPerSample = data.bitrate;

//   uint32_t dataSize = data.sample_rate * duration;

//   std::ofstream file_pcm((filename + ".pcm").c_str(), std::ios::binary);
//   std::ofstream file_wav((filename + ".wav").c_str(), std::ios::binary);

//   if (!file_pcm || !file_wav) {
//     return false;
//   }

//   // Write HEADER wav file into a media file
//   file_wav.write(reinterpret_cast<const char*>(&header),  sizeof(header));

//   for (uint32_t i = 0; i < dataSize; ++i) {
//     double t = static_cast<double>(i) / data.sample_rate;
//     for (uint16_t channel = 0; channel < data.channel; ++channel) {
//       uint16_t D = (channel%2);
//       double sample  = data.amplitude * std::sin(2.0*M_PI*(data.frequence)*t + D*M_PI);
//       T sample_int  = static_cast<T>(sample);
//       file_pcm.write(reinterpret_cast<const char*>(&sample_int),  sizeof(sample_int));
//       file_wav.write(reinterpret_cast<const char*>(&sample_int),  sizeof(sample_int));
//     }
//   }

//   file_pcm.close();
//   file_wav.close();

//   return true;
// }