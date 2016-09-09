//
// Created by loulfy on 13/08/16.
//

#ifndef LYS_CONNEXION_HPP
#define LYS_CONNEXION_HPP

#include <string>
#include <iostream>
#include <stdexcept>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/timerfd.h>

#include "lys/Http.hpp"
#include "lys/Socket.hpp"
#include "lys/Handler.hpp"
#include "lys/Websocket.hpp"

namespace lys
{
    class Connexion : public Socket
    {
        public:

            Connexion(int fd, Controller* controller);
            ~Connexion();
            void consume();

            void send(std::string message) override;
            void close() override;

            const int* fd() const;
            const bool done() const;

        private:

            int m_fd[2];
            bool m_done;
            itimerspec m_timer;

            static const int TIMEOUT = 10;

            Handler*    m_handler;
            Controller* m_controller;
    };
}

#endif //LYS_CONNEXION_HPP
