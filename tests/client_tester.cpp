#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main(int argc, char const *argv[])
{
    int port = 0;
    switch (argc)
    {
    case 1:
        perror("No command line arguments given");
        exit(EXIT_FAILURE);
        break;
    case 2:
        perror("only port is given");
        exit(EXIT_FAILURE);
        break;
    default:
        port = std::stoi(argv[1]);
        break;
    }
    std::cout << "number of command line arguments: " << argc - 1 << std::endl;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    std::string messageToSend = "";
    for (int i = 2; i < argc; ++i)
    {
        messageToSend = messageToSend + argv[i];
        if (i != argc - 1)
        {
            messageToSend = messageToSend + ' ';
        }
    }
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, messageToSend.c_str(), messageToSend.length(), 0);
    std::cout << "Message sent from client: " << messageToSend << std::endl;
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}
