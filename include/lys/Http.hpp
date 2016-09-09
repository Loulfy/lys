//
// Created by loulfy on 14/08/16.
//

#ifndef LYS_HTTP_HPP
#define LYS_HTTP_HPP

#include <iostream>
#include <stdexcept>

#include <unistd.h>
#include <sys/socket.h>

#include "lys/Sha1.hpp"
#include "lys/Handler.hpp"
#include "lys/Request.hpp"
#include "lys/Response.hpp"

namespace lys
{
    class Http : public Handler
    {
        public:

            Http(int fd, Controller* controller);
            ~Http();

            bool consume() override;
            bool timeout() override;
            void send(std::string message) override;
            void close() override;

            bool upgrade() override;

        private:

            Request  m_req;
            Response m_res;

            bool m_ws;
    };
}

#endif //LYS_HTTP_HPP
