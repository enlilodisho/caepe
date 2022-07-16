//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENT_H
#define CAEPE_COMPONENT_H

#include "Result.h"

#include <string>
#include <thread>
#include <memory>

namespace caepe {

    class Component {
    private:
        std::unique_ptr<std::thread> _thread;
        bool _started = false;

        void componentThread();

    public:
        const std::string _name;

        explicit Component(std::string name);
        ~Component();

        Result start();
        Result stop();

        virtual void onStart();
        virtual void onLoop();
        virtual void onEnd();

        [[nodiscard]]
        bool isStarted() const;
    };

} // caepe

#endif //CAEPE_COMPONENT_H
