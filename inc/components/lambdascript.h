#pragma once
#include <components/component.h>
#include <functional>

class LambdaScript : public Component {
    std::function<void(LambdaScript*)> start_func;
    std::function<void(LambdaScript*)> update_func = [](LambdaScript* ref) {};
    public:
    LambdaScript(std::function<void(LambdaScript*)> func = [](LambdaScript* ref) {}) : start_func(func) {}
    void start() override{
        std::cout << this << "\n";
        start_func(this);
    }

    void update() override{
        update_func(this);
    }

    void set_update_func(std::function<void(LambdaScript*)> func){ update_func = func; }
};
