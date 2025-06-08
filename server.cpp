
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>

#define PORT 51355
#define BUFFER_SIZE 1000
#define MAX_CONNECTIONS 4

bool areAnagrams(const std::string &a, const std::string &b) {
    std::string sa = a, sb = b;
    std::sort(sa.begin(), sa.end());
    std::sort(sb.begin(), sb.end());
    return sa == sb;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (client_fd < 0) {
        std::cerr << "Greska pri konekcija. Obidete se povtorno!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected with client: " << inet_ntoa(address.sin_addr) 
              << " on port " << ntohs(address.sin_port) << std::endl;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);
        std::string msg(buffer);

        std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
        std::cout << "Primena poraka: " << msg << std::endl;

        if (msg == "KRAJVRSKA") {
            std::string response = "Kraj na vrska";
            send(client_fd, response.c_str(), response.size(), 0);
            break;
        }

        int firstComma = msg.find('/');
        int secondComma = msg.find('/', firstComma + 1);
        int thirdComma = msg.find('/', secondComma + 1);

        if (firstComma != std::string::npos && secondComma != std::string::npos && thirdComma != std::string::npos) {
            std::string prv = msg.substr(0, firstComma);
            std::string vtor = msg.substr(firstComma + 1, secondComma - firstComma - 1);
            std::string tret = msg.substr(secondComma + 1, thirdComma - secondComma - 1);
            std::string cetvrt = msg.substr(thirdComma + 1);

            bool cond1 = areAnagrams(prv, vtor);
            bool cond2 = areAnagrams(tret, cetvrt);

            if (cond1 && !cond2) {
                std::string resp = "1Anagrami";
                send(client_fd, resp.c_str(), resp.size(), 0);
            } else if (!cond1 && cond2) {
                std::string resp = "2Anagrami";
                send(client_fd, resp.c_str(), resp.size(), 0);
            } else if (cond1 && cond2) {
                std::string resp = "12Anagrami";
                send(client_fd, resp.c_str(), resp.size(), 0);
                break;
            } else {
                std::string resp = "SILENT";
                send(client_fd, resp.c_str(), resp.size(), 0);
            }
        } else {
            std::string response = "Ve molime vnesete nova poraka";
            send(client_fd, response.c_str(), response.size(), 0);
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
