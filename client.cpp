
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 51355
#define BUFFER_SIZE 1000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "172.171.241.218", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    std::cout << "Uspesno vospostavena konekcija so serverot" << std::endl;

    while (true) {
        std::string input;
        std::cout << "Vnesi poraka vo format Prv/Vtor/Tret/Cetvrt: ";
        std::getline(std::cin, input);

        send(sock, input.c_str(), input.size(), 0);

        memset(buffer, 0, BUFFER_SIZE);
        read(sock, buffer, BUFFER_SIZE);
        std::cout << "Odgovor od server: " << buffer << std::endl;

        if (input == "KrajVrska" || std::string(buffer) == "12Anagrami") {
            break;
        }
    }

    close(sock);
    return 0;
}
