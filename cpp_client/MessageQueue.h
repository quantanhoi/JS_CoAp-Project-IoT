//
// Created by 49152 on 10.05.2023.
//

#ifndef INC_4X4_GEWINNT_MESSAGEQUEUE_H
#define INC_4X4_GEWINNT_MESSAGEQUEUE_H


#include <queue>
#include "ControllerMessage.h"

class MessageQueue {
public:
    void push(const ControllerMessage& message);
    ControllerMessage pop();

private:
    std::queue<ControllerMessage> queue_;
};



#endif //INC_4X4_GEWINNT_MESSAGEQUEUE_H
