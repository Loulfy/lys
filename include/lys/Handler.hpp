//
// Created by loulfy on 14/08/16.
//

#ifndef LYS_HANDLER_HPP
#define LYS_HANDLER_HPP

#include <string>

#include "lys/Controller.hpp"

namespace lys
{
    class Handler
    {
        public:

            Handler(int fd, Controller* controller);
            virtual ~Handler();
            virtual bool consume() = 0;
            virtual bool timeout() = 0;
            virtual void send(std::string message) = 0;
            virtual void close() = 0;

            virtual bool upgrade() = 0;

        protected:

            int m_socket;
            Controller* m_controller;

            char m_buffer[512];
    };
}

#endif //LYS_HANDLER_HPP
