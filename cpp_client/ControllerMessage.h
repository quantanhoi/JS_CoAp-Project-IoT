//
// Created by 49152 on 10.05.2023.
//

#ifndef INC_4X4_GEWINNT_CONTROLLERMESSAGE_H
#define INC_4X4_GEWINNT_CONTROLLERMESSAGE_H

#include <string>

// class ControllerMessage {
// public:
//     explicit ControllerMessage(std::string payload) : payload_(std::move(payload)) {}
//     const std::string& payload() const { return payload_; }

// private:
//     std::string payload_;
// };
class ControllerMessage {
public:
    explicit ControllerMessage(uint8_t payload) : payload_(payload) {}
    uint8_t payload() const { return payload_; }

private:
    uint8_t payload_;
};


#endif //INC_4X4_GEWINNT_CONTROLLERMESSAGE_H
