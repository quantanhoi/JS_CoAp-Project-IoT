#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    int num_joysticks = SDL_NumJoysticks();
    if (num_joysticks < 1) {
        std::cerr << "No joysticks connected" << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (!joystick) {
        std::cerr << "Failed to open joystick: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_JOYBUTTONDOWN || e.type == SDL_JOYBUTTONUP) {
                std::cout << "Button: " << (int)e.jbutton.button << ", State: " << (int)e.jbutton.state << std::endl;
            } else if (e.type == SDL_JOYAXISMOTION) {
                std::cout << "Axis: " << (int)e.jaxis.axis << ", Value: " << e.jaxis.value << std::endl;
            }
        }
    }

    SDL_JoystickClose(joystick);
    SDL_Quit();

    return 0;
}