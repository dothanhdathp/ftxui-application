#include <ftxapp.hpp>
#include <iostream>
#include <utilities/defined.hpp>
#include <functional>
#include <vector>
#include <string>
#include <ranges>
#include <initializer_list>

int dump;

void do_nothing() {
    // do nothing
};

AppMain::AppMain(int argc, const char *args[]) {
    unused(argc);
    unused(args);
}

AppMain::~AppMain() {
    // Your cleanup code here
}

void AppMain::RunLoop() {
    ftxui::ScreenInteractive::TerminalOutput().Loop(mScreen);
}

void inline AppMain::Notify(std::string message = std::string()) {
    mNotifyMessage = message;
}

void AppMain::RenderScreen() {
        // Add to Horizonetal elements list
    // ftxui::Component list_vertical_component = ftxui::Container::Vertical(
    //     std::vector<ftxui::Component>(std::views::values(mComponentMap).begin(), std::views::values(mComponentMap).end())
    // );
    ftxui::Component list_vertical_component = ftxui::Container::Vertical({
        mComponentMap[COMP_SAMPLE_RATE],
        mComponentMap[COMP_AMPLITUDE],
        mComponentMap[COMP_CHANNEL],
        mComponentMap[COMP_FREQUENCY],
        mComponentMap[COMP_BITS_PERSAMPLE],
        mComponentMap[COMP_TXT_DURATION],
        mComponentMap[COMP_TXT_FILENAME],
        mComponentMap[COMP_BTN_GENERATE],
        mComponentMap[COMP_BTN_HELP],
    });

    mScreen = ftxui::Renderer(list_vertical_component, [&] {
        auto vbox = ftxui::vbox(ftxui::Elements({
            ftxui::text("Simple Audio Sinway Generator") | ftxui::center | ftxui::flex,
            ftxui::hbox(ftxui::text("Sample Rate     : ") | ftxui::center, mComponentMap[COMP_SAMPLE_RATE]->Render()),
            ftxui::hbox(ftxui::text("Amplitude       : ") | ftxui::center, mComponentMap[COMP_AMPLITUDE]->Render()),
            ftxui::hbox(ftxui::text("Channel         : ") | ftxui::center, mComponentMap[COMP_CHANNEL]->Render()),
            ftxui::hbox(ftxui::text("Frequency       : ") | ftxui::center, mComponentMap[COMP_FREQUENCY]->Render()),
            ftxui::hbox(ftxui::text("Bits per sample : ") | ftxui::center, mComponentMap[COMP_BITS_PERSAMPLE]->Render()),
            ftxui::hbox(ftxui::text("Duration        : ") | ftxui::center, mComponentMap[COMP_TXT_DURATION]->Render())   | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,3),
            ftxui::hbox(ftxui::text("File name       : ") | ftxui::center, mComponentMap[COMP_TXT_FILENAME]->Render())   | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,3),
            ftxui::separator(),
            ftxui::hbox(mComponentMap[COMP_BTN_GENERATE]->Render(), mComponentMap[COMP_BTN_HELP]->Render()),
            ftxui::separator(),
            ftxui::paragraph(this->mNotifyMessage) | ftxui::size(ftxui::HEIGHT,ftxui::GREATER_THAN,1),
        })) | ftxui::border;
        return vbox;
    });
}

void AppMain::Init() {
    // Create component Sample Rate
    mComponentMap[COMP_SAMPLE_RATE] = ftxui::Dropdown(list_sample_rate, &Sel_SampleRate) | ftxui::flex;

    // Create component Amplitude
    ftxui::Components amplitude_childs = {
        ftxui::Input(&mDisplayAmplitude, "1000") | ftxui::border | ftxui::vcenter | ftxui::flex,
        ftxui::Button("  Set  ", std::bind(&AppMain::on_button_set_amplitude, this), ButtonStyle(true)),
        ftxui::Button("   -   ", std::bind(&AppMain::on_button_minus_amplitude, this), ButtonStyle(true)),
        ftxui::Button("   +   ", std::bind(&AppMain::on_button_plus_amplitude, this), ButtonStyle(true)),
    };
    mComponentMap[COMP_AMPLITUDE] = ftxui::Container::Horizontal(amplitude_childs, &dump) | ftxui::flex;

    // Create component Channel
    mComponentMap[COMP_CHANNEL] = ftxui::Dropdown(&list_channel, &Sel_Channel) | ftxui::flex;

    // Create component
    ftxui::Components frequency_childs = {
        ftxui::Input(&mDisplayFrequency, "0.0") | ftxui::border | ftxui::vcenter | ftxui::flex,
        ftxui::Button("   -   ", std::bind(&do_nothing), ButtonStyle(true)),
        ftxui::Button("   +   ", std::bind(&do_nothing), ButtonStyle(true)),
    };

    // Create component
    mComponentMap[COMP_FREQUENCY]      = ftxui::Container::Horizontal(frequency_childs, &dump) | ftxui::flex;

    // Create component
    mComponentMap[COMP_BITS_PERSAMPLE] = ftxui::Dropdown(&list_bits_persample, &Sel_BitsPersample) | ftxui::flex;

    // Create component
    mComponentMap[COMP_TXT_DURATION]   = ftxui::Input(&(mDisplayDuration), "seconds") | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,1) | ftxui::center;

    // Create component
    mComponentMap[COMP_TXT_FILENAME]   = ftxui::Input(&mDisplayFilename, "filename")  | ftxui::size(ftxui::HEIGHT,ftxui::EQUAL,1) | ftxui::center;

    // Create component
    mComponentMap[COMP_BTN_GENERATE]   = ftxui::Button("Generate", std::bind(&do_nothing), ButtonStyle(false)) | ftxui::flex;
    
    // Create component
    mComponentMap[COMP_BTN_HELP] = ftxui::Button("!", std::bind(&AppMain::on_show_help, this), ButtonStyle(false));
    RenderScreen();
}

ftxui::ButtonOption AppMain::ButtonStyle(bool border) {
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


void AppMain::on_button_set_amplitude() {
    try {
        mAmplitude = std::stoi(mDisplayAmplitude);
        if(mAmplitude < 0 | mAmplitude > 20000) {
            Notify("Amplitude = " + mDisplayAmplitude);
        } else {
            Notify("Amplitude = " + mDisplayAmplitude);
        }
    }
    catch(...)
    {
        mAmplitude = 1000;
        Notify("Input invalid!");
    }
}

void AppMain::on_button_minus_amplitude() {
    if(mAmplitude > 0) {
        mAmplitude -= 100;
        mDisplayAmplitude = std::to_string(mAmplitude);
        Notify();
    } else {
        Notify("Amplitude Minumumed (0)");
    }
}

void AppMain::on_button_plus_amplitude() {
    if(mAmplitude < 20000) {
        mAmplitude += 100;
        mDisplayAmplitude = std::to_string(mAmplitude);
        Notify();
    } else {
        Notify("Amplitude Maximumed (20000)");
    }
}

void AppMain::on_show_help() {
    Notify("This Application generate sinway signal audio file in pcm(raw), wav, ... by input parameter.\nRegards, Tad!");
}