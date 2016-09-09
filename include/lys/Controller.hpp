//
// Created by loulfy on 14/08/16.
//

#ifndef LYS_CONTROLLER_HPP
#define LYS_CONTROLLER_HPP

#include "lys/Socket.hpp"
#include "lys/Request.hpp"
#include "lys/Response.hpp"

namespace lys
{
    class Controller
    {
        public:

            virtual ~Controller();
            virtual void action(Request* req, Response* res);
            virtual void on_connect(Socket* ws);

    };
}

#endif //LYS_CONTROLLER_HPP
