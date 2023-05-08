#ifndef CONTROLLSYSTEM_HPP_INCLUDED
#define CONTROLLSYSTEM_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <string>
#include <vector>

class Controll_system{
protected:
    std::vector<Widget*> _widgets;
public:
    void widget_load_in(Widget* new_w);
    void run();
    void file_output();
};

#endif // CONTROLLSYSTEM_HPP_INCLUDED
