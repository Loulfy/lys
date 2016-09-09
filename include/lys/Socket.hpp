//
// Created by loulfy on 14/08/16.
//

#ifndef LYS_SOCKET_HPP
#define LYS_SOCKET_HPP

#include <string>

namespace lys
{
    class Socket
    {
        public:

            virtual ~Socket(){};
            virtual void send(std::string message) = 0;
            virtual void close() = 0;

    };
}

#endif //LYS_SOCKET_HPP
