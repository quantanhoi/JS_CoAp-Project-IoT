//
// Created by 49152 on 10.05.2023.
//

#include "MessageQueue.h"

void MessageQueue::push(const ControllerMessage& message) {
    queue_.push(message);
}

ControllerMessage MessageQueue::pop() {
    if (!queue_.empty()) {
        ControllerMessage msg = queue_.front();
        queue_.pop();
        return msg;
    }
    return ControllerMessage(0);
}
