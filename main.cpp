#include "graphics.hpp"
#include "widget.hpp"
#include "widgetcontrol.hpp"
#include "gamemanager.hpp"

#include <vector>

using namespace std;
using namespace genv;


int main() {
    WidgetControl game(50);
    game.start_game();
    return 0;
}
