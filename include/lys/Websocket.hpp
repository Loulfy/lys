//
// Created by loulfy on 14/08/16.
//

#ifndef LYS_WEBSOCKET_HPP
#define LYS_WEBSOCKET_HPP

#include <unistd.h>

#include "lys/Handler.hpp"

namespace lys
{
    class Websocket : public Handler
    {
        public:

            enum State
            {
                WS_OPCODE,
                WS_LENGTH,
                WS_LENGTH_16_0,
                WS_LENGTH_16_1,
                WS_LENGTH_64_0,
                WS_LENGTH_64_1,
                WS_LENGTH_64_2,
                WS_LENGTH_64_3,
                WS_LENGTH_64_4,
                WS_LENGTH_64_5,
                WS_LENGTH_64_6,
                WS_LENGTH_64_7,
                WS_MASK_0,
                WS_MASK_1,
                WS_MASK_2,
                WS_MASK_3,
                WS_PAYLOAD,
            };

            enum Frame
            {
                WS_FRAME_TEXT   = 0x1,
                WS_FRAME_BINARY = 0x2,
                WS_FRAME_CLOSE  = 0x8,
                WS_FRAME_PING   = 0x9,
                WS_FRAME_PONG   = 0xA,
            };

            Websocket(int fd, Controller* controller, Socket* ws);
            ~Websocket();

            bool consume() override;
            bool timeout() override;
            void send(std::string message) override;
            void close() override;

            bool upgrade() override;

            int parser_execute(size_t len);

        private:

            Socket* m_ws;
            bool m_ping;

            State m_state;
    };
}

#endif //LYS_WEBSOCKET_HPP
