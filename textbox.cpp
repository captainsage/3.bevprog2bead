#include <string>
#include "graphics.hpp"
#include "widget.hpp"
#include "textbox.hpp"

using namespace std;
using namespace genv;

Text_box::Text_box(int x,int y,int size_x,int size_y,int font_size,std::string value) :Widget(x,y,size_x,size_y,font_size) {
    _stored_value.s = value;
    _stored_value.contains_value = true;
    display_update();
}

void Text_box::display_update(){
    if(_changed) {
        _display << move_to(0,0)
                 << color(255,255*!_selected,255*!_selected)
                 << box(_size_x,_size_y)
                 << color(150*_checked,0,0)
                 << move_to(1,1)
                 << box(_size_x-2, _size_y-2)
                 << move_to(4,(_size_y-_display.cascent())/2)
                 << color(255,255,255)
                 << text(_stored_value.s);
        _changed = false;
    }
}

void Text_box::action(genv::event &ev) {
    if(ev.button == btn_left) {
        check_change();
    }
}

void Text_box::check_change() {
        _checked = !_checked;
        _changed = true;
}

void text_change() {
    _stored_value.s = "sanyi";
}

void Text_box::btn_action_int(int arg) {text_change();}
