#pragma once

class Clock {
   private:
    static Clock* instance;
    static double last_time;
    static double delta_time;
   public:
    Clock();
    ~Clock();
    double now();
    double dt(); // get delta_time
    void update();

    static Clock* the();
    // not cloneable
    Clock(Clock &other) = delete;
    // not assignable
    void operator=(const Clock &) = delete;
};
