#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <algorithm>
#include <map>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const int PORT = 54000;
mutex mtx;

// ====== SERVER PART ======
map<int, string> clientsUsernames;

void broadcastMessage(const string& msg, int senderSocket) {
    lock_guard<mutex> lock(mtx);
    for (auto& [sock, name] : clientsUsernames) {
        if (sock != senderSocket) {
            send(sock, msg.c_str(), msg.size(), 0);
        }
    }
}

void handleClient(int clientSocket) {
    char buffer[4096];

    // Receive username first
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
        close(clientSocket);
        return;
    }
    buffer[bytesReceived] = '\0';
    string username = buffer;

    {
        lock_guard<mutex> lock(mtx);
        clientsUsernames[clientSocket] = username;
    }

    string joinMsg = username + " joined the chat.\n";
    cout << joinMsg;
    broadcastMessage(joinMsg, clientSocket);

    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            cerr << username << " disconnected.\n";
            close(clientSocket);

            string leaveMsg = username + " left the chat.\n";
            {
                lock_guard<mutex> lock(mtx);
                clientsUsernames.erase(clientSocket);
            }
            broadcastMessage(leaveMsg, clientSocket);
            break;
        }
        buffer[bytesReceived] = '\0';
        string msg = username + ": " + buffer;
        cout << msg;
        broadcastMessage(msg, clientSocket);
    }
}

void runServer() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Error creating socket.\n";
        return;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed.\n";
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        cerr << "Listen failed.\n";
        close(serverSocket);
        return;
    }

    cout << "Server started on port " << PORT << ". Waiting for clients...\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket < 0) {
            cerr << "Accept failed.\n";
            continue;
        }

        thread t(handleClient, clientSocket);
        t.detach();
    }

    close(serverSocket);
}

// ====== CLIENT PART ======
void receiveMessages(int sock) {
    char buffer[4096];
    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            cout << "Disconnected from server.\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        cout << "\n" << buffer << endl;
    }
}

void runClient() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Error creating socket.\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Connection failed.\n";
        close(sock);
        return;
    }

    // Ask for username
    string username;
    cout << "Enter your username: ";
    getline(cin, username);
    send(sock, username.c_str(), username.size(), 0);

    cout << "Connected to chat server. Type messages below:\n";

    thread t(receiveMessages, sock);
    t.detach();

    string msg;
    while (true) {
        getline(cin, msg);
        if (msg == "/quit") break;
        send(sock, msg.c_str(), msg.size(), 0);
    }

    close(sock);
}

// ====== MAIN ======
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " server|client\n";
        return 1;
    }

    string mode = argv[1];
    if (mode == "server") {
        runServer();
    } else if (mode == "client") {
        runClient();
    } else {
        cerr << "Invalid mode. Use 'server' or 'client'.\n";
    }

    return 0;
}