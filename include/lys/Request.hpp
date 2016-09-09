//
// Created by loulfy on 31/07/16.
//

#ifndef LYS_REQUEST_HPP
#define LYS_REQUEST_HPP

#include <http_parser.h>
#include <iostream>
#include <string>
#include <map>

namespace lys
{
    class Request
    {
        public:

            enum State {WAIT, DONE, FAIL};

            Request();
            void execute(const char data[], ssize_t size);
            void reset();
            void done();

            bool upgrade() const;

            const Request::State state() const;
            const std::string get(std::string field) const;

            int pushField(std::string field);
            int pushValue(std::string value);

        private:

            // callbacks http_parser
            static http_parser_settings settings;
            static int on_header_field(http_parser* parser, const char* at, size_t len);
            static int on_header_value(http_parser* parser, const char* at, size_t len);
            static int on_url(http_parser* parser, const char* at, size_t len);
            static int on_headers_complete(http_parser* parser);
            static int on_message_complete(http_parser* parser);
            static int on_message_begin(http_parser* parser);

            // Status
            State m_state;

            // http_parser
            http_parser m_parser;

            // tmp string
            std::string m_field;

            // HTTP request fields
            std::map<std::string, std::string> m_headers;
    };
}

#endif //LYS_REQUEST_HPP
