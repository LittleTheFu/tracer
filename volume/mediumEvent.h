#ifndef _MEDIUM_EVENT_H_
#define _MEDIUM_EVENT_H_

enum class MediumEventType {
    Scatter, // 发生了真实散射事件
    Absorb,  // 发生了真实吸收事件
    Transmit // 光线无交互地穿透到了 tMax
};

#endif