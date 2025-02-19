#include <iostream> // For standard I/O operations
#include <cstring> // For memset function
#include <arpa/inet.h> // For sockaddr_in and inet_ntoa functions
#include <unistd.h> // For close function

#define PORT 8000 // Port number for the server
#define BUFFER_SIZE 1024 // Size of the buffer for receiving data

// Example usage: 
// tejus@tejusAI:~$ nc -u localhost 8000

int main() {
    int sockfd; // Socket file descriptor
    char buffer[BUFFER_SIZE]; // Buffer to store received data
    struct sockaddr_in server_addr, client_addr; // Server and client address structures
    socklen_t addr_len = sizeof(client_addr); // Length of the client address

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { // Create a UDP socket
        std::cerr << "Socket creation failed!" << std::endl; // Print error message if socket creation fails
        return -1; // Return error code
    }

    // Fill server information
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    server_addr.sin_port = htons(PORT); // Convert port number to network byte order

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { // Bind the socket to the server address
        std::cerr << "Bind failed!" << std::endl; // Print error message if bind fails
        close(sockfd); // Close the socket
        return -1; // Return error code
    }

    std::cout << "UDP Echo Server is running on port " << PORT << std::endl; // Print server running message

    while (true) {
        // Receive data from client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, // Receive data from client
                         (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0'; // Null-terminate the received string

        std::cout << "Received: " << buffer << std::endl; // Print received data

        // Send the same data back to the client
        sendto(sockfd, buffer, n, MSG_CONFIRM, // Send data back to client
               (const struct sockaddr *)&client_addr, addr_len);
        std::cout << "Echoed back: " << buffer << std::endl; // Print echoed data
    }

    close(sockfd); // Close the socket
    return 0; // Return success code
}
