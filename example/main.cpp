#include <iostream>

#include <lys/Server.hpp>

int main(int argc, char* argv[])
{
    std::cout << "-- START HTTP SERVER --" << std::endl;

    lys::Server server(6666);
    server.run();

    return EXIT_SUCCESS;
}