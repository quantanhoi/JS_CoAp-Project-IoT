//
// Created by 49152 on 10.05.2023.
//

#ifndef INC_4X4_GEWINNT_CONTROLLER_H
#define INC_4X4_GEWINNT_CONTROLLER_H


#include <SDL.h>
#include "ControllerMessage.h"
#include <queue>

class Controller {
public:
    Controller();
    ~Controller();
    ControllerMessage readMessage();
    void processEvents();
    uint8_t generatePayload(bool controllerIsConnected, uint8_t button);

private:
    SDL_Joystick* joystick_;
    std::queue<ControllerMessage> messages_;
};


#endif //INC_4X4_GEWINNT_CONTROLLER_H
