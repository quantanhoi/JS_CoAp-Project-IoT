//
// Created by 49152 on 10.05.2023.
//

#include "Process.h"

Process::Process(Controller& controller, MessageQueue& queue)
        : controller_(controller), queue_(queue) {}

void Process::operator()() {
    while (true) {
        controller_.processEvents();
        ControllerMessage msg = controller_.readMessage();
        if (msg.payload() != 0) {
            queue_.push(msg);
        }
    }
}
