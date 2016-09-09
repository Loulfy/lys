//
// Created by loulfy on 11/08/16.
//

#include "lys/Response.hpp"

using namespace std;

namespace lys
{
    Response::Response() : m_code("HTTP/1.1 200 OK\r\n")
    {
        time_t now = time(NULL);
        strftime(m_date, sizeof(m_date), "Date: %a, %d %b %Y %H:%M:%S %Z\r\n", gmtime(&now));
        m_head+= m_date;
        m_head+= "Connection: Close\r\n";
        m_head+= "Server: lys\r\n";
    }

    void Response::send(string message)
    {
        m_body+= message;
    }

    void Response::code(size_t code)
    {
        switch(code)
        {
            case 200:
                m_code = "HTTP/1.1 200 OK\r\n";
                break;

            case 403:
                m_code = "HTTP/1.1 403 Forbidden\r\n";
                break;

            case 404:
                m_code = "HTTP/1.1 404 Not Found\r\n";
                break;

            case 400:
                m_code = "HTTP/1.1 400 Bad Request\r\n";
                break;

            case 101:
                m_code = "HTTP/1.1 101 Switching Protocols\r\n";
                m_head+= "Upgrade: websocket\r\n";
                m_head+= "Connection: Upgrade\r\n";
                break;

            default:
                throw runtime_error("Code not implemented!");
                break;
        }
    }

    void Response::head(string head)
    {
        m_head+= head + "\r\n";
    }

    void Response::redirect(string url)
    {
        m_code = "HTTP/1.1 302 Moved Temporarily\r\n";
        m_head+= "Location: " + url + "\r\n";
    }

    void Response::reject(string message)
    {
        this->code(403);
        this->send(message);
    }

    void Response::end(string& data)
    {
        data+= m_code;
        data+= m_head;

        if(!m_body.empty())
        {
            data+= "Content-Type: text/html; charset=UTF-8\r\n";
            data+= "Content-Length: " + to_string(m_body.size()) + "\r\n";
        }

        data+= "\r\n";
        data+= m_body;
    }
}

