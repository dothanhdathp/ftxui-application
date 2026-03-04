#include <ftxui/component/component.hpp>          // for Button, Horizontal, Renderer, Dropdown, Horizontal, Vertical
#include <ftxui/component/component_base.hpp>     // for ComponentBase
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive
#include <ftxui/component/captured_mouse.hpp>     // for ftxui
#include <vector>
#include <unordered_map>

enum ComponentId {
    COMP_SAMPLE_RATE,
    COMP_AMPLITUDE,
    COMP_CHANNEL,
    COMP_FREQUENCY,
    COMP_BITS_PERSAMPLE,
    COMP_TXT_DURATION,
    COMP_TXT_FILENAME,
    COMP_BTN_GENERATE,
    COMP_BTN_HELP,
    COMP_MAX,
};

class AppMain {
public:
    AppMain(int argc, const char *args[]);
    ~AppMain();

private:
    const std::vector<std::string> list_sample_rate = { "48000", "44100", "16000", "8000" };
    const std::vector<std::string> list_channel = {
        "1 Channels", "2 Channels", "3 Channels", "4 Channels",
        "5 Channels", "6 Channels", "7 Channels", "8 Channels"
    };
    const std::vector<std::string> list_bits_persample = { "16", "32" };
    ftxui::Component mScreen;
    std::unordered_map<int, ftxui::Component>
        mComponentMap;

    int mAmplitude = 1000;
    double mFrequency = 0;
    // String display
    std::string mDisplayDuration = "";
    std::string mDisplayFilename = "";
    std::string mDisplayAmplitude = "";
    std::string mDisplayFrequency = "";
    std::string mNotifyMessage = "";
    // Selection
    int Sel_SampleRate    = 0; // ??
    int Sel_Channel       = 1; // ??
    int Sel_BitsPersample = 0; // ??

    ftxui::Component mCompSampleRate;
    ftxui::Element mVBox;
public:
    void Init();
    void RenderScreen();
    void RunLoop();
    
private:
    ftxui::ButtonOption ButtonStyle(bool border = true);
    void                Notify(std::string);
    void                on_button_set_amplitude();
    void                on_button_minus_amplitude();
    void                on_button_plus_amplitude();
    void                on_show_help();
};