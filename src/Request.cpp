//
// Created by loulfy on 31/07/16.
//

#include "lys/Request.hpp"

using namespace std;

namespace lys
{
    http_parser_settings Request::settings = {
            .on_message_begin = on_message_begin,
            .on_url = on_url,
            .on_status_complete = nullptr,
            .on_header_field = on_header_field,
            .on_header_value = on_header_value,
            .on_headers_complete = on_headers_complete,
            .on_body = nullptr,
            .on_message_complete = on_message_complete,
    };

    Request::Request() : m_state(WAIT)
    {
        m_parser.data = this;
        this->reset();
    }

    void Request::execute(const char data[], ssize_t size)
    {
        ssize_t nparsed = http_parser_execute(&m_parser, &settings, data, static_cast<size_t>(size));
        if(nparsed != size)
        {
            cout << "INFO: shity request throw in the trash !" << endl;
            m_state = FAIL;
        }
    }

    void Request::reset()
    {
        m_field.clear();
        m_headers.clear();
        http_parser_init(&m_parser, HTTP_REQUEST);
    }

    void Request::done()
    {
        m_state = DONE;
    }

    bool Request::upgrade() const
    {
        return m_parser.upgrade == 1;
    }

    const Request::State Request::state() const
    {
        return m_state;
    }

    const std::string Request::get(string field) const
    {
        if(m_headers.find(field) == m_headers.end())
        {
            return string();
        }
        else
        {
            return m_headers.at(field);
        }
    }

    int Request::pushField(string field)
    {
        if(m_field.empty())
        {
            m_field = field;
            return 0;
        }
        else
        {
            return 1;
        }
    }

    int Request::pushValue(std::string value)
    {
        if(!m_field.empty())
        {
            m_headers[m_field] = value;
            m_field.clear();
            return 0;
        }
        else
        {
            return 1;
        }
    }

    int Request::on_message_begin(http_parser *parser)
    {
        //cout << "new" << endl;
        return 0;
    }

    int Request::on_headers_complete(http_parser *parser)
    {
        //cout << "complete"<< endl;
        return 0;
    }

    int Request::on_message_complete(http_parser *parser)
    {
        //cout << "message end" << endl;
        Request* req = static_cast<Request*>(parser->data);
        req->done();
        return 0;
    }

    int Request::on_header_field(http_parser *parser, const char *at, size_t len)
    {
        Request* req = static_cast<Request*>(parser->data);
        return req->pushField(string(at, len));
    }

    int Request::on_header_value(http_parser *parser, const char *at, size_t len)
    {
        Request* req = static_cast<Request*>(parser->data);
        return req->pushValue(string(at, len));
    }

    int Request::on_url(http_parser *parser, const char *at, size_t len)
    {
        //cout << string(at, len) << endl;
        return 0;
    }
}


