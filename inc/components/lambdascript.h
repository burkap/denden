#pragma once
#include <component.h>
#include <functional>

class LambdaScript : public Component {
    std::function<void(LambdaScript*)> start_func;
    std::function<void(LambdaScript*, float)> update_func = [](LambdaScript* ref, float dt) {};
    public:
    LambdaScript(std::function<void(LambdaScript*)> func = [](LambdaScript* ref) {}) : start_func(func) {}
    void start() override{
        std::cout << this << "\n";
        start_func(this);
    }

    void update(float dt) override{
        update_func(this, dt);
    }

    void set_update_func(std::function<void(LambdaScript*, float)> func){ update_func = func; }
};
