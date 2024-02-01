#include "ChronosWindow.h"
#include "Utils.h"
int main() {
    auto win = Chronos::CreateWin();
    if(win == nullptr) {
        Panic("no");
    }
    win->init();
    win->show();
    win->loop();
    return 0;
}