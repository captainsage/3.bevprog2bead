#include "widget.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;
using namespace std;

Widget::Widget(int x, int y, int size_x, int size_y, int font_size) : _x(x), _y(y), _size_x(size_x), _size_y(size_y), _font_size(font_size){
        _size_y = max(_size_y, int(font_size*1.2));
        _display.open(_size_x, _size_y);
        _display.load_font("LiberationMono-Bold.ttf", _font_size, true);
    }

void Widget::draw_widget(genv::canvas *target) {
    *target << stamp(_display, _x,_y);
}

bool Widget::is_selected(int mpos_x, int mpos_y) {
    int counter = _selected;
    _selected = mpos_x > _x && mpos_y > _y && mpos_x < _x + _size_x && mpos_y < _y + _size_y;
    counter += _selected;
    if(counter == 1) _changed = true;
    return _selected;
}

void Widget::co_caller_int(Widget* w, int arg){w->btn_action_int(arg);}

vector<Widget*> Widget::get_sub_widgets() {return {};}

canvas Widget::get_display() {
    return _display;
}

/*Stored_value Widget::the_stored_value_is() {
    return _stored_value;
}*/
