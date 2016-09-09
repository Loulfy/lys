//
// Created by loulfy on 11/08/16.
//

#ifndef LYS_RESPONSE_HPP
#define LYS_RESPONSE_HPP

#include <ctime>
#include <string>
#include <iostream>
#include <stdexcept>

namespace lys
{
    class Response
    {
        public:

            Response();
            void send(std::string message);
            void code(size_t code);
            void head(std::string head);
            void redirect(std::string url);
            void reject(std::string message);
            void end(std::string& data);



        private:

            std::string m_code;
            std::string m_head;
            std::string m_body;

            char m_date[40];
    };
}

#endif //LYS_RESPONSE_HPP
