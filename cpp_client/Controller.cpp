//
// Created by 49152 on 10.05.2023.
//
#include "Controller.h"
#include <iostream>
#include <sstream>

Controller::Controller() {
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    joystick_ = SDL_JoystickOpen(0);
    if (!joystick_) {
        std::cerr << "Failed to open joystick: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
}

Controller::~Controller() {
    SDL_JoystickClose(joystick_);
    SDL_Quit();
}

/*ControllerMessage Controller::readMessage() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_JOYBUTTONDOWN) {
            std::ostringstream message;
            message << "Button: " << static_cast<int>(e.jbutton.button) << ", " << "State: " << static_cast<int>(e.jbutton.state);
            return ControllerMessage(message.str());
        }
    }
    return ControllerMessage("");
}*/

ControllerMessage Controller::readMessage() {
    if (!messages_.empty()) {
        ControllerMessage msg = messages_.front();
        messages_.pop();
        return msg;
    }
    return ControllerMessage(0);
}


void Controller::processEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_JOYBUTTONDOWN) {
            uint8_t testMessage = generatePayload(1,static_cast<uint8_t>(e.jbutton.button));
            // std::ostringstream message;
            // message << static_cast<int>(e.jbutton.button);
            // messages_.push(ControllerMessage(message.str()));
            // std::cout << "BUTTON: "<< static_cast<uint8_t>(e.jbutton.button) << std::endl;
            messages_.push(ControllerMessage(testMessage));
        }
    }
}

uint8_t Controller::generatePayload(bool controllerIsConnected, uint8_t button) {
    if (button > 127) {
        std::cerr << "invalid button, button number should be less than 127\n";
        return 0;
    }
    uint8_t payload = 0;
    payload |= (controllerIsConnected ? 1 : 0) << 7;
    payload |= button;
    return payload;
}


