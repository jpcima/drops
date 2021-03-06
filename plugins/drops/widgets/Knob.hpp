/*  license  */

#ifndef KNOB_HPP
#define KNOB_HPP

#include "Window.hpp"
#include "Widget.hpp"
#include "NanoVG.hpp"
#include <iostream>
#include <string>

START_NAMESPACE_DISTRHO

class Knob : public NanoWidget
{
public:
    class Callback
    {
    public:
        virtual ~Callback() {}
        virtual void knobDragStarted(Knob *knob) = 0;
        virtual void knobDragFinished(Knob *knob) = 0;
        virtual void knobValueChanged(Knob *knob, float value) = 0;
    };
    explicit Knob(Window &parent) noexcept;
    explicit Knob(Widget *widget) noexcept;
    void setCallback(Callback *cb);
    void setValue(float val) noexcept;
    float getValue() noexcept;

    std::string label; // public, no getter or setter
    float labelSize;
    float gauge_width;
    Color background_color;
    Color foreground_color;
    Color highlight_color;
    Color text_color;
    float margin;
    float default_value;
    float step_value;
    float min;
    float max;

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent &) override;
    bool onMotion(const MotionEvent &) override;
    bool onScroll(const ScrollEvent &) override;

private:
    Callback *callback;
    bool dragging_;
    float value_;
    float value_tmp_;
    int mouseY_;
    FontId font_;
    Color fill_color_;
    bool has_mouse_;

    float tmp_value_;
    bool using_default_;
    bool using_log_;

    int last_mouse_x_;
    int last_mouse_y_;
    bool is_ready_;
    float _logscale(float value) const;
    float _invlogscale(float value) const;

    DISTRHO_LEAK_DETECTOR(Knob)
};

END_NAMESPACE_DISTRHO

#endif // SCROLLBAR_HPP
