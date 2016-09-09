//
// Created by loulfy on 14/08/16.
//

#include "lys/Websocket.hpp"

using namespace std;

namespace lys
{
    Websocket::Websocket(int fd, Controller* controller, Socket* ws) : Handler(fd, controller), m_ws(ws), m_ping(false), m_state(WS_OPCODE)
    {
        m_controller->on_connect(m_ws);
    }

    Websocket::~Websocket()
    {
        cout << "delete WS" << endl;
    }

    bool Websocket::consume()
    {
        ssize_t count;

        count = ::read(m_socket, m_buffer, sizeof(m_buffer));
        cout << "consume:" << count << endl;

        this->parser_execute(count);

        return count == 0;
    }

    bool Websocket::timeout()
    {
        return m_ping;
    }

    void Websocket::send(string message)
    {

    }

    void Websocket::close()
    {

    }

    bool Websocket::upgrade()
    {
        return false;
    }

    int Websocket::parser_execute(size_t len)
    {
        uint8_t byte;
        uint8_t opcode;

        while(len)
        {
            byte = static_cast<uint8_t>(m_buffer[0]);

            switch(m_state)
            {
                case WS_OPCODE:
                    opcode = (uint8_t) (byte & 0x0f);
                    break;

                case WS_LENGTH:
                    break;

                case WS_LENGTH_16_0:
                    break;

                case WS_LENGTH_16_1:
                    break;

                case WS_LENGTH_64_0:
                    break;

                case WS_LENGTH_64_1:
                    break;

                case WS_LENGTH_64_2:
                    break;

                case WS_LENGTH_64_3:
                    break;

                case WS_LENGTH_64_4:
                    break;

                case WS_LENGTH_64_5:
                    break;

                case WS_LENGTH_64_6:
                    break;

                case WS_LENGTH_64_7:
                    break;

                case WS_MASK_0:
                    break;

                case WS_MASK_1:
                    break;

                case WS_MASK_2:
                    break;

                case WS_MASK_3:
                    break;

                case WS_PAYLOAD:
                    break;
            }
        }

        return 0;
    }
}