#include "controllsystem.hpp"
#include "graphics.hpp"
#include "widget.hpp"
#include "string"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace genv;
using namespace std;


void Controll_system::widget_load_in(Widget* new_w) {
    _widgets.push_back(new_w);
    vector<Widget*> sub_widgets = new_w->get_sub_widgets();
    for(Widget* &cursor:sub_widgets) {_widgets.push_back(cursor);}
    for(Widget* &cursor:_widgets) {cursor->draw_widget(&gout);}
}

void Controll_system::run() {
    event ev;
    int posx(0), posy(0);
    while(gin >> ev && ev.keycode != key_escape) {
        gout << color(0,0,0)
             << move_to(0,0)
             << box(400,400);
        if(ev.keycode == key_enter) {file_output();}
        for(Widget* cursor:_widgets) {
            if(ev.type == ev_mouse) {posx = ev.pos_x; posy = ev.pos_y;}
            if(cursor->is_selected(posx,posy)) cursor->action(ev);
            cursor->display_update();
            cursor->draw_widget(&gout);
        }
        gout << refresh;
    }
}

void Controll_system::file_output() {
    ofstream output;
    output.open("widgetoutput.txt");
    if(!output) {cout << "nim a jao";}
    for(Widget* cursor:_widgets) {
        Stored_value new_value = cursor->the_stored_value_is();
        if(new_value.contains_value) {
            if(new_value.i) {output << new_value.i << endl;}
            else output << new_value.s << endl;
        }
    }
    output.close();
}
