#include "graphics.hpp"
#include "widget.hpp"
#include "controllsystem.hpp"
#include "numberinputw.hpp"
#include "textbox.hpp"
#include "menu.hpp"
#include <vector>

using namespace std;
using namespace genv;


int main()
{
    gout.open(400,400);
    gout << move_to(0,0)
         << color(0,0,0)
         << box(400,400);
    Controll_system CS;
    Text_box * b1 = new Text_box(10,10,10,5,20,"bela");
    canvas k;
    k.open(100,200);
    k << move_to(0,0) << color(255,255,255) << box(100,200);
    Push_button * b2 = new Push_button(100,100,100,200,20,k,Widget::co_caller_int,b1,1);
    /*Menu * b3 = new Menu(250,150,130,50,20,{"sanyi","hagyma"});
    Menu * b4 = new Menu(250,30,130,50,10,{"sanyi","hagyma","bab","krumpli","hal", "hagymas bab","krumplis hal"});*/
    CS.widget_load_in(b1);
    CS.widget_load_in(b2);
    /*CS.widget_load_in(b3);
    CS.widget_load_in(b4);*/
    gout << refresh;
    CS.run();
    return 0;
}
