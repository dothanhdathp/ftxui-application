#include <ftxui/component/component.hpp>          // for Button, Horizontal, Renderer, Dropdown, Horizontal, Vertical
#include <ftxui/component/component_base.hpp>     // for ComponentBase
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/component/captured_mouse.hpp>     // for ftxui
#include <AudioGenerator.hpp>
#include <vector>
#include <unordered_map>
#include <memory>

enum ComponentId {
    COMP_DROPDOWN_SAMPLE_RATE,
    COMP_INPUT_AMPLITUDE,
    COMP_DROPDOWN_CHANNEL,
    COMP_INPUT_FREQ,
    COMP_DROPDOWN_BPS,
    COMP_INPUT_DURATION,
    COMP_TXT_FILENAME,
    COMP_DROPDOWN_FILETYPE,
    COMP_BTN_GENERATE,
    COMP_BTN_HELP,
    COMP_MAX,
};

class FtxApp : public IAudioGeneratorCallback {
public:
    FtxApp(int argc, const char *args[]);
    ~FtxApp();

private:
    // Member variable
    ftxui::Component mScreen;
    ftxui::ScreenInteractive mScreenInteractive;
    std::unordered_map<int, ftxui::Component>
        mComponentMap;

    int m_amplitude = 1000;
    int m_frequency = 1000;
    // String display
    std::string m_display_duration  = "0";
    std::string m_display_filename  = "";
    std::string m_display_amplitude = "1000";
    std::string m_display_frequency = "1000";
    std::string m_display_message   = "";
    // Selection
    int m_sel_sample_rate     = 0;
    int m_sel_channel         = 1;
    int m_sel_bits_per_sample = 0;
    int m_sel_file_type       = 0;
    ftxui::Element mElementVbox;
public:
    void Init();
    void RenderScreen();
    void RunLoop();
    void Notify(std::string);
    void RefressScreen();

private:
    ftxui::ButtonOption 
        ButtonStyle(bool border = true);
    void on_button_set_amplitude();
    void on_button_minus_amplitude();
    void on_button_plus_amplitude();
    void on_button_set_frequency();
    void on_button_minus_frequency();
    void on_button_plus_frequency();
    void on_button_generate();
    void on_show_help();
};

// std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Just for testing!