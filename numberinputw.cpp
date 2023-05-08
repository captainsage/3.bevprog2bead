#include "numberinputw.hpp"
#include "graphics.hpp"
#include "widget.hpp"
#include "string"
#include <iostream>
#include <cmath>
#include <vector>

using namespace genv;
using namespace std;



Number_input_w::Number_input_w(int x, int y, int size_x, int size_y, int font_size, int value, int range_floor, int range_ceiling)
    : Widget(max(x,10),y,size_x,size_y,font_size), _range_floor(range_floor), _range_ceiling(range_ceiling){
        _stored_value.i = value;
        _stored_value.contains_value = true;
        value_validator();
        _size_x = max(max(_size_x, _display.twidth(to_string(_range_floor))),_display.twidth(to_string(_range_ceiling)));
        canvas k;
        k.open(_size_x,_size_y);
        _display = k;
        _display.load_font("LiberationMono-Bold.ttf", _font_size, true);
        display_update();
        vector<canvas> skin_storage = button_generate();

        _increase_btn = new Push_button(_x-10,_y,10,10,8,skin_storage[0],co_caller_int,this,1);
        _decrease_btn = new Push_button(_x-10,_y+10,10,10,8,skin_storage[1],co_caller_int,this,-1);
}

vector<canvas> Number_input_w::button_generate() {
        canvas inc, dec;
        inc.open(10,10);
        dec.open(10,10);
        inc << move_to(0,0)
            << color(255,255,255)
            << box(10,10)
            << color(0,0,0);
        dec << move_to(0,0)
            << color(255,255,255)
            << box(10,10)
            << color(0,0,0);
        for(int y = 1; y < 10; y++) {
            for(int x = 1; x < 10; x++) {
                if(abs(x-5)-(y/2) < 1) {
                    inc << move_to(x,y)
                        << dot;
                }
                if(abs(x-5)-((10-y)/2) < 1) {
                    dec << move_to(x,y)
                        << dot;
                }
            }
        }
       return {inc,dec};
}

void Number_input_w::display_update() {
    if(_changed) {
    string v = to_string(_stored_value.i);
    _display << move_to(0,0)
             << color(255,255*!_selected,255*!_selected)
             << box(_size_x, _size_y)
             << move_to(1,1)
             << color(0,0,0)
             << box(_size_x-2, _size_y-2)
             << move_to((_size_x - _display.twidth(v))/2,(_size_y - _display.cascent())/2)
             << color (255,255,255)
             << text(v);
    _changed = false;
    }
}

void Number_input_w::value_validator() {
    if(_stored_value.i < _range_floor) _stored_value.i = _range_floor;
    if(_stored_value.i > _range_ceiling) _stored_value.i = _range_ceiling;
}

void Number_input_w::value_change(int diff) {
    _stored_value.i += diff;
    _changed = true;
    value_validator();
}

void Number_input_w::action(event &ev) {
    if(ev.keycode == key_down) value_change(-1);
    if(ev.keycode == key_up) value_change(+1);
    if(ev.keycode == key_pgdn) value_change(-10);
    if(ev.keycode == key_pgup) value_change(+10);
}

void Number_input_w::btn_action_int(int arg) {
    value_change(arg);
}

std::vector<Widget*> Number_input_w::get_sub_widgets() {
    return {_increase_btn,_decrease_btn};
}
