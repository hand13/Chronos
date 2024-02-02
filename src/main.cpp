#include "ChronosWindow.h"
#include "Utils.h"
#include "Log.h"
int main() {
    Chronos::Log(L"start");
    auto win = Chronos::CreateWin();
    if(win == nullptr) {
        Panic(L"create window failed");
    }
    win->init();
    win->show();
    win->loop();
    return 0;
}