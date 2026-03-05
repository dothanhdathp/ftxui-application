#include <FtxApp.hpp>
#include <iostream>
#include <utilities/defined.hpp>
#include <functional>
#include <vector>
#include <string>
#include <ranges>
#include <initializer_list>
#include <AudioGenerator.hpp>

static std::string m_display_message = "";

void do_nothing() {
    // do nothing
};

FtxApp::FtxApp(int argc, const char *args[]) : mScreenInteractive(ftxui::ScreenInteractive::TerminalOutput())
{
    unused(argc);
    unused(args);
}

FtxApp::~FtxApp() {
    // Your cleanup code here
}

void FtxApp::RunLoop() {
    mScreenInteractive.Loop(mScreen);
}

void FtxApp::Notify(std::string message = std::string()) {
    m_display_message = message;
}

void FtxApp::RefressScreen() {
    mScreenInteractive.PostEvent(ftxui::Event::Custom);
}

void FtxApp::RenderScreen() {
        // Add to Horizonetal elements list
    // ftxui::Component list_vertical_component = ftxui::Container::Vertical(
    //     std::vector<ftxui::Component>(std::views::values(mComponentMap).begin(), std::views::values(mComponentMap).end())
    // );
    ftxui::Component list_vertical_component = ftxui::Container::Vertical({
        mComponentMap[COMP_DROPDOWN_SAMPLE_RATE],
        mComponentMap[COMP_INPUT_AMPLITUDE],
        mComponentMap[COMP_DROPDOWN_CHANNEL],
        mComponentMap[COMP_INPUT_FREQ],
        mComponentMap[COMP_DROPDOWN_BPS],
        mComponentMap[COMP_INPUT_DURATION],
        mComponentMap[COMP_TXT_FILENAME],
        mComponentMap[COMP_DROPDOWN_FILETYPE],
        mComponentMap[COMP_BTN_GENERATE],
        mComponentMap[COMP_BTN_HELP],
    });

    mScreen = ftxui::Renderer(list_vertical_component, [&] {
        auto vbox = ftxui::vbox(ftxui::Elements({
            ftxui::text("Simple Audio Sinway Generator") | ftxui::center | ftxui::flex,
            ftxui::hbox(ftxui::text("Sample Rate     : ") | ftxui::center, mComponentMap[COMP_DROPDOWN_SAMPLE_RATE]->Render()),
            ftxui::hbox(ftxui::text("Amplitude       : ") | ftxui::center, mComponentMap[COMP_INPUT_AMPLITUDE]->Render()),
            ftxui::hbox(ftxui::text("Channel         : ") | ftxui::center, mComponentMap[COMP_DROPDOWN_CHANNEL]->Render()),
            ftxui::hbox(ftxui::text("Frequency       : ") | ftxui::center, mComponentMap[COMP_INPUT_FREQ]->Render()),
            ftxui::hbox(ftxui::text("Bits per sample : ") | ftxui::center, mComponentMap[COMP_DROPDOWN_BPS]->Render()),
            ftxui::hbox(ftxui::text("Duration        : ") | ftxui::center, mComponentMap[COMP_INPUT_DURATION]->Render())   | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,3),
            ftxui::hbox(ftxui::text("File name       : ") | ftxui::center, mComponentMap[COMP_TXT_FILENAME]->Render())     | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,3),
            ftxui::hbox(ftxui::text("File type       : ") | ftxui::center, mComponentMap[COMP_DROPDOWN_FILETYPE]->Render()),
            ftxui::separator(),
            ftxui::hbox(mComponentMap[COMP_BTN_GENERATE]->Render(), mComponentMap[COMP_BTN_HELP]->Render()),
            ftxui::gauge(AudioGenerator::getInstance().m_thread_render_progress) | ftxui::color(ftxui::Color::Green) | ftxui::border,
            ftxui::separator(),
            ftxui::paragraph(this->m_display_message) | ftxui::size(ftxui::HEIGHT,ftxui::GREATER_THAN,1),
        })) | ftxui::border;
        return vbox;
    });
}

void FtxApp::Init() {
    // Create component Sample Rate
    // ListSimpleRate
    // ListChannels
    mComponentMap[COMP_DROPDOWN_SAMPLE_RATE] = ftxui::Dropdown(
        &AudioGenerator::getInstance().listSimpleRate,
        &m_sel_sample_rate) | ftxui::flex;

    // Create component Amplitude
    ftxui::Components amplitude_childs = {
        ftxui::Input(&m_display_amplitude, "dBFS") | ftxui::border | ftxui::vcenter | ftxui::flex,
        ftxui::Button("  Set  ", std::bind(&FtxApp::on_button_set_amplitude, this), ButtonStyle(true)),
        ftxui::Button("   -   ", std::bind(&FtxApp::on_button_minus_amplitude, this), ButtonStyle(true)),
        ftxui::Button("   +   ", std::bind(&FtxApp::on_button_plus_amplitude, this), ButtonStyle(true)),
    };
    mComponentMap[COMP_INPUT_AMPLITUDE] = ftxui::Container::Horizontal(amplitude_childs, nullptr) | ftxui::flex;

    // Create component Channel
    mComponentMap[COMP_DROPDOWN_CHANNEL] = ftxui::Dropdown(
        &AudioGenerator::getInstance().listChannels,
        &m_sel_channel)| ftxui::flex;

    // Create component
    ftxui::Components frequency_childs = {
        ftxui::Input(&m_display_frequency, "Hz") | ftxui::border | ftxui::vcenter | ftxui::flex,
        ftxui::Button("  Set  ", std::bind(&FtxApp::on_button_set_frequency, this), ButtonStyle(true)),
        ftxui::Button("   -   ", std::bind(&FtxApp::on_button_minus_frequency, this), ButtonStyle(true)),
        ftxui::Button("   +   ", std::bind(&FtxApp::on_button_plus_frequency, this), ButtonStyle(true)),
    };

    // Create component
    mComponentMap[COMP_INPUT_FREQ] = ftxui::Container::Horizontal(frequency_childs, nullptr) | ftxui::flex;

    // Create component
    mComponentMap[COMP_DROPDOWN_BPS] = ftxui::Dropdown(&AudioGenerator::getInstance().listBitsPerSample, &m_sel_bits_per_sample) | ftxui::flex;

    // Create component
    mComponentMap[COMP_INPUT_DURATION] = ftxui::Input(&m_display_duration, "seconds") | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,1) | ftxui::center;
  
    // Create component
    mComponentMap[COMP_TXT_FILENAME]   = ftxui::Input(&m_display_filename, "filename")  | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,1) | ftxui::center;

    // Create component
    mComponentMap[COMP_DROPDOWN_FILETYPE] = ftxui::Dropdown(&AudioGenerator::getInstance().listFileTypes, &m_sel_file_type) | ftxui::flex;

    // Create component
    mComponentMap[COMP_BTN_GENERATE] = ftxui::Button("Generate", std::bind(&FtxApp::on_button_generate, this), ButtonStyle(false)) | ftxui::flex;
    
    // Create component
    mComponentMap[COMP_BTN_HELP] = ftxui::Button("!", std::bind(&FtxApp::on_show_help, this), ButtonStyle(false));
    RenderScreen();
}

ftxui::ButtonOption FtxApp::ButtonStyle(bool border) {
    ftxui::ButtonOption option = ftxui::ButtonOption::Animated();
    option.transform = [border](const ftxui::EntryState& s) {
        auto element = ftxui::text(s.label);
        if (s.focused)
            element |= ftxui::bold;
        
        element |= (border ? ftxui::border : ftxui::borderEmpty);
        element |= ftxui::center;
        return element;
    };
    return option;
};


void FtxApp::on_button_set_amplitude() {
    try {
        m_amplitude = std::stoi(m_display_amplitude);
        if(0 <= m_frequency | m_frequency <= 20000) {
            Notify("Amplitude = " + m_display_amplitude);
        } else {
            Notify("Amplitude = " + m_display_amplitude);
        }
    }
    catch(...)
    {
        m_amplitude = 1000;
        Notify("Input invalid!");
    }
}

void FtxApp::on_button_minus_amplitude() {
    if(m_amplitude >= 0) {
        m_amplitude -= 100;
        m_display_amplitude = std::to_string(m_amplitude);
        Notify();
    } else {
        Notify("Amplitude Minumumed (0)");
    }
}

void FtxApp::on_button_plus_amplitude() {
    if(m_amplitude <= 20000) {
        m_amplitude += 100;
        m_display_amplitude = std::to_string(m_amplitude);
        Notify();
    } else {
        Notify("Amplitude Maximumed (20000)");
    }
}

void FtxApp::on_button_set_frequency() {
    try {
        m_frequency = std::stod(m_display_frequency);
        if(0 <= m_frequency | m_frequency <= 10000) {
            Notify("Frequency = " + m_display_frequency);
        } else {
            Notify("Frequency = " + m_display_frequency);
        }
    }
    catch(...)
    {
        m_frequency = 1000;
        Notify("Input invalid!");
    }
}

void FtxApp::on_button_minus_frequency() {
    if(m_frequency >= 0) {
        m_frequency -= 100;
        m_display_frequency = std::to_string(m_frequency);
        Notify();
    } else {
        Notify("Frequency Minumumed (0)");
    }
}

void FtxApp::on_button_plus_frequency() {
    if(m_frequency<= 10000) {
        m_frequency += 100;
        m_display_frequency = std::to_string(m_frequency);
        Notify();
    } else {
        Notify("Frequency Maximumed (10000)");
    }
}

void FtxApp::on_button_generate() {
    audio_info info;
    try {
        info.sample_rate = std::stoi(AudioGenerator::getInstance().listSimpleRate[m_sel_sample_rate]);
        info.amplitude = m_amplitude;
        info.channel = AudioGenerator::getInstance().listChannels[m_sel_channel][0] - '0'; // Get first value reduce to '0' becasue channels from 1->8
        info.frequence = m_frequency;
        info.bit_per_sample  = std::stoi(AudioGenerator::getInstance().listBitsPerSample[m_sel_bits_per_sample]);
        info.duration = std::stoi(m_display_duration);
        info.filetype = static_cast<e_file_t>(m_sel_file_type);
        if(info.duration < 0) {
            Notify("Duration can not be negative numbers.");
            return;
        }
    }
    catch(...)
    {
        Notify("Duration get fail. Please check input again!");
        return;
    }
    std::string invalid_character = R"(<>:"/\|?*)";
    std::string true_filename;
    for(auto c : m_display_filename) {
        bool valid = true;
        for(auto i : invalid_character) {
            if(c==i) {
                valid = false;
                break;
            }
        }
        true_filename += c;
    }
    AudioGenerator::getInstance().GenerateAudioFile(info, true_filename, reinterpret_cast<IAudioGeneratorCallback*>(this));
}

void FtxApp::on_show_help() {
    Notify("This Application generate sinway signal audio file in pcm(raw), wav, ... by input parameter.\nRegards, Tad!");
}