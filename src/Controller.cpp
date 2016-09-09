//
// Created by loulfy on 14/08/16.
//

#include "lys/Controller.hpp"

namespace lys
{
    Controller::~Controller()
    {

    }

    void Controller::action(Request* req, Response* res)
    {
        res->send("<h1>POUET</h1>\n");
    }

    void Controller::on_connect(Socket* ws)
    {
        std::cout << "nouveau client websocket" << std::endl;
    }
}