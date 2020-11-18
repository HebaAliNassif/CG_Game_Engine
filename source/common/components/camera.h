#ifndef CAMERA_H
#define CAMERA_H

#include "ecs/component.h"
namespace CGEngine {

    class Camera: public Component {
    public:
        Camera():Component("camera"){};
    };
}

#endif //CAMERA_H
