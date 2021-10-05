// Server side C/C++ program to demonstrate Socket programming
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>

int main(int argc, char const *argv[])
{
    int PORT = 0;
    switch (argc)
    {
    case 1:
        std::cerr << "No command line arguments given";
        exit(EXIT_FAILURE);
        break;
    default:
        PORT = std::stoi(argv[1]);
        break;
    }
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    std::string hello;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("waiting for server connection...\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    if (!(valread = read(new_socket, buffer, 1024)))
    {
        perror("error reading");
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> temp = {""};
    for (int i = 0; i < 1024; ++i)
    {

        switch (buffer[i])
        {
        case ' ':
            temp.push_back("");
            break;

        default:
            temp.back() = temp.back() + buffer[i];
            break;
        }
    }

    uint32_t sub = std::stoi(temp.front());
    std::cout << "Message received: ";
    for (auto i = temp.begin(); i != temp.end(); ++i)
    {
        if (i == temp.begin())
        {
            continue;
        }
        std::cout << *i << ' ';
        sub = sub - stoi(*i);
    }
    hello = std::to_string(sub);
    std::cout << "\nMessage sent: " << hello << std::endl;
    send(new_socket, hello.c_str(), hello.length(), 0);
    return 0;
}