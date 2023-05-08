#include "textbox.hpp"
#include "graphics.hpp"
#include "widget.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "menu.hpp"

using namespace std;
using namespace genv;

Menu::Menu(int x,int y,int size_x,int size_y,int font_size,std::vector<std::string> values) :Widget(x,y,size_x,size_y,font_size){
    _text_box_list.open(_size_x,font_size*1.2*values.size());
    _size_y = min(int(font_size*1.2*values.size()),_size_y);
    int ty = 0;
    for(string cursor:values) {
        int fs = font_size*1.2;
        Text_box* new_option = new Text_box(0,ty,size_x,fs,font_size,cursor);
        _menu_options.push_back(new_option);
        ty += fs;
    }
}

void Menu::display_update(){
    for(Text_box* &cursor:_menu_options) {
        cursor->display_update();
    }
}

void Menu::draw_widget(genv::canvas *target) {
    for(Widget* cursor:_menu_options) {
            cursor->draw_widget(&_text_box_list);
    }
    *target << stamp(_text_box_list,0,_list_ycoord,_size_x,_size_y,_x,_y);
}

void Menu::action(event &ev){
    if(ev.type == ev_mouse ){
        int coorx, coory;
        coorx = ev.pos_x-_x;
        coory = ev.pos_y-_y+_list_ycoord;
        ev.pos_x = coorx;
        ev.pos_y = coory;
        for(Text_box* cursor:_menu_options) {
            if(cursor->is_selected(coorx, coory)) {
                if(ev.button == btn_left) {
                    if(_selected_item) _selected_item->action(ev);
                    cursor->action(ev);
                    if(_selected_item == cursor) {
                            _selected_item->action(ev);
                            _selected_item = 0;
                            _stored_value.contains_value = false;
                    }
                    else {
                        _selected_item = cursor;
                        _stored_value = cursor->the_stored_value_is();
                    }
                }
            }
        }
        if(ev.button == btn_wheeldown) {
            if(_list_ycoord < _font_size*1.2*_menu_options.size()-_size_y) _list_ycoord+=2;
        }
        if(ev.button == btn_wheelup) {
            if(_list_ycoord) _list_ycoord -=2;
        }
    }
}

bool Menu::is_selected(int mpos_x, int mpos_y) {
    int counter = _selected;
    _selected = mpos_x > _x && mpos_y > _y && mpos_x < _x + _size_x && mpos_y < _y + _size_y;
    counter += _selected;
    if(counter == 1) _changed = true;
    if(!_selected) {
        for(Text_box* cursor:_menu_options) {
            cursor->is_selected(-1,-1);
        }
    }
    return _selected;
}

void Menu::btn_action_int(int arg){}
