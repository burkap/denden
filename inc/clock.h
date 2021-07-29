#pragma once

class Clock {
   private:
    static Clock* instance;
    static double last_time;
    static double delta_time;
   public:
    static Clock* the();
    Clock();
    ~Clock();
    double now();
    double dt(); // get delta_time
    void update();
};
