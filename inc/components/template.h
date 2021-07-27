#pragma once
#include <components/component.h>

class TemplateComponent : public Component {
    public:
        // All  components need an empty constructor for now
        TemplateComponent(); 
        
        // This is called only once after adding this component to a game object
        virtual void start();

        // Called every frame, right before the physics and render steps
        virtual void update(float dt);
};
