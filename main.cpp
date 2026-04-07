#include <audio/wav.hpp>
#include <FtxApp.hpp>

int main(int argc, const char *args[]) {
    FtxApp app = FtxApp(argc, args);
    app.Init();
    app.RenderScreen();
    app.RunLoop();
    return 0;
}