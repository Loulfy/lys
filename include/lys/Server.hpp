//
// Created by loulfy on 13/08/16.
//

#ifndef LYS_SERVER_HPP
#define LYS_SERVER_HPP

#include <string>
#include <stdexcept>

#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>

#include "lys/Connexion.hpp"
#include "lys/Controller.hpp"

namespace lys
{
    class Server
    {
        public:

            Server(uint16_t port);
            ~Server();
            void run();
            void push(Connexion* conn, int fd);
            void push(Connexion* conn);

            static void stop(int s);

        private:

            static bool RUN;
            const int m_server;

            const static int MAXEVENTS = 8192;

            int m_epoll;
            struct epoll_event m_events[MAXEVENTS];
            struct epoll_event m_event;

            Controller m_controller;
    };
}

#endif //LYS_SERVER_HPP
