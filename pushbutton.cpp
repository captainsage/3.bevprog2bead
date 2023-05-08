#include "pushbutton.hpp"
#include "widget.hpp"
#include "graphics.hpp"

using namespace genv;

Push_button::Push_button(int x, int y, int size_x, int size_y, int font_size, canvas skin, FuncInt fi,  Widget* target, int arg) :Widget(x,y,size_x,size_y,font_size),  _arg_func(arg) {
    _func_int = fi;
    _int_target = target;
    _display.open(_size_x,_size_y);
    _display << stamp(skin,0,0);
}

Push_button::Push_button(int x, int y, int size_x, int size_y, int font_size, canvas skin, FuncVoid fv,  Widget* target) :Widget(x,y,size_x,size_y,font_size) {
    _void_target = target;
    _func_void = fv;
    _display.open(_size_x,_size_y);
    _display << stamp(skin,0,0);
}

void Push_button::action(event &ev) {
    if(ev.button == btn_left) {
        if(_func_int) _func_int(_int_target,_arg_func);
        if(_func_void) _func_void(_void_target);
    }
}

void Push_button::btn_action_int(int arg) {}

void Push_button::display_update() {
    if(_changed) {
            _display << color(255,255*!_selected,255*!_selected)
             << move_to(0,0)
             << line_to(_size_x,0)
             << line_to(_size_x, _size_y)
             << line_to(0,_size_y)
             << move_to(0,0)
             << line_to(0,_size_y);
             _changed = false;
    }
}
