//
// Created by loulfy on 14/08/16.
//

#include "lys/Handler.hpp"

namespace lys
{
    Handler::Handler(int fd, Controller* controller) : m_socket(fd), m_controller(controller)
    {

    }

    Handler::~Handler()
    {

    }
}