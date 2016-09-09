//
// Created by loulfy on 14/08/16.
//

#include "lys/Http.hpp"

using namespace std;

namespace lys
{
    Http::Http(int fd, Controller* controller) : Handler(fd, controller), m_ws(false)
    {

    }

    Http::~Http()
    {
        cout << "delete HTTP" << endl;
    }

    bool Http::consume()
    {
        ssize_t count;

        do
        {
            count = ::read(m_socket, m_buffer, sizeof(m_buffer));
            if(count == -1)
            {
                if(errno != EAGAIN || errno != EWOULDBLOCK)
                {
                    throw runtime_error("Unknow HTTP read error!");
                }
            }
            else if(count == 0)
            {
                return true;
            }
            else
            {
                m_req.execute(m_buffer, count);

                string data;

                switch(m_req.state())
                {
                    case Request::FAIL:
                        m_res.code(400);
                        m_res.end(data);
                        this->send(data);
                        this->close();
                        count = 0;
                        return false;

                    case Request::DONE:
                        if(m_req.upgrade())
                        {
                            SHA1 key;
                            key.update(m_req.get("Sec-WebSocket-Key") + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

                            m_res.code(101);
                            m_res.head("Sec-WebSocket-Accept: " + key.final());

                            m_ws = true;
                        }

                        m_controller->action(&m_req, &m_res);
                        m_res.end(data);
                        this->send(data);
                        return false;

                    case Request::WAIT:
                        break;
                }
            }
        }
        while(count > 0);

        return false;
    }

    bool Http::timeout()
    {
        return true;
    }

    void Http::send(string message)
    {
        ::write(m_socket, message.data(), message.size());
    }

    void Http::close()
    {
        shutdown(m_socket, SHUT_RD);
    }

    bool Http::upgrade()
    {
        return m_ws;
    }
}