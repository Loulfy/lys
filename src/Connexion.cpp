//
// Created by loulfy on 13/08/16.
//

#include "lys/Connexion.hpp"

using namespace std;

namespace lys
{
    Connexion::Connexion(int fd, Controller* controller) : m_done(false), m_handler(new Http(fd, controller)), m_controller(controller)
    {
        // Socket fd
        m_fd[0] = fd;

        // Unblock socket
        int flags;
        if((flags = fcntl(m_fd[0], F_GETFL, 0)) == -1)
        {
            throw runtime_error("FCNTL");
        }

        flags |= O_NONBLOCK;
        if(fcntl(m_fd[0], F_SETFL, flags) == -1)
        {
            throw runtime_error("FCNTL");
        }

        // Timer fd
        m_fd[1] = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);

        // Set the delay
        m_timer.it_interval.tv_sec = TIMEOUT;
        m_timer.it_interval.tv_nsec = 0;
        m_timer.it_value.tv_sec = TIMEOUT;
        m_timer.it_value.tv_nsec = 0;

        timerfd_settime(m_fd[1], 0, &m_timer, nullptr);
    }

    Connexion::~Connexion()
    {
        shutdown(m_fd[0], SHUT_RDWR);
        shutdown(m_fd[1], SHUT_RDWR);
        ::close(m_fd[0]);
        ::close(m_fd[1]);

        delete m_handler;
    }

    void Connexion::consume()
    {
        uint64_t s = 0;
        if(read(m_fd[1], &s, 8) < 0)
        {
            // Consume data & close
            if(m_handler->consume())
            {
                m_done = true;
            }
            else
            {
                if(m_handler->upgrade())
                {
                    delete m_handler;
                    m_handler = new Websocket(m_fd[0], m_controller, this);
                }
            }

            // Reset timer
            timerfd_settime(m_fd[1], 0, &m_timer, nullptr);
        }
        else
        {
            if(m_handler->timeout())
            {
                m_done = true;
            }
        }
    }

    void Connexion::send(string message)
    {
        m_handler->send(message);
    }

    void Connexion::close()
    {
        m_handler->close();
    }

    const int* Connexion::fd() const
    {
        return m_fd;
    }

    const bool Connexion::done() const
    {
        return m_done;
    }
}