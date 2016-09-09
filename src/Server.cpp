//
// Created by loulfy on 13/08/16.
//

#include "lys/Server.hpp"

using namespace std;

namespace lys
{
    bool Server::RUN = true;

    Server::Server(uint16_t port) : m_server(socket(AF_INET, SOCK_STREAM, 0)), m_epoll(epoll_create1(0))
    {
        // Set SIGINT signal
        signal(SIGINT, Server::stop);

        // Make server
        sockaddr_in sin = {0};
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(port);

        if(bind(m_server, reinterpret_cast<sockaddr*>(&sin), sizeof(sin)) < 0)
        {
            throw runtime_error("EADDRINUSE, Address already in use");
        }

        // Register server
        m_event = {0};
        m_event.data.fd = m_server;
        m_event.events = EPOLLIN | EPOLLET;
        epoll_ctl(m_epoll, EPOLL_CTL_ADD, m_server, &m_event);
    }

    Server::~Server()
    {
        close(m_server);
    }

    void Server::run()
    {
        // Start server
        listen(m_server, SOMAXCONN);

        int fd;

        // Main loop
        while(Server::RUN)
        {
            int waiting = epoll_wait(m_epoll, m_events, MAXEVENTS, 5);

            // For each events
            for(int i = 0; i < waiting; ++i)
            {
                // Accept new client
                if(m_events[i].data.fd == m_server)
                {
                    if((fd = accept(m_server, nullptr, nullptr)) != -1)
                    {
                        auto c = new Connexion(fd, &m_controller);
                        this->push(c);
                    }
                }
                else
                {
                    if(m_events[i].data.ptr == nullptr) continue;

                    // Read data
                    auto c = static_cast<Connexion*>(m_events[i].data.ptr);
                    c->consume();

                    // Release the connection
                    if(c->done())
                    {
                        delete c;
                        m_events[i].data.ptr = nullptr;
                    }
                }
            }
        }
    }

    void Server::push(Connexion* conn, int fd)
    {
        m_event.data.ptr = conn;
        m_event.events = EPOLLIN | EPOLLET;
        epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &m_event);
    }

    void Server::push(Connexion* conn)
    {
        auto fd = conn->fd();
        this->push(conn, fd[0]);
        this->push(conn, fd[1]);
    }

    void Server::stop(int s)
    {
        Server::RUN = false;
        cout << "Goodbye..." << endl;
    }
}
