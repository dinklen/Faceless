#include "LogViewer.hpp"

#include <iostream>
#include <string>
#include <csignal>
#include <atomic>

#include <zmq.hpp>

std::atomic<bool> gRunning{true};

void signalHandler(int) {
    ::gRunning = false;
}

void log_viewer::logViewer() {
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    try {
        zmq::context_t context(1);
        zmq::socket_t receiver(context, ZMQ_PULL);

        receiver.bind("tcp://localhost:45875");

        std::cout << "Log viewer started. Waiting for messages..." << std::endl;
        while (::gRunning) {
            zmq::message_t message;

            if (zmq::recv_result_t result = receiver.recv(message, zmq::recv_flags::dontwait)) {
                std::string msgStr(static_cast<char*>(message.data()), message.size());
                std::cout << message << std::endl;
            }
        }
    } catch (const zmq::error_t& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Configure ZeroMQ errors
        return;
    }

    std::cout << "\nEnd." << std::endl;

    return;
}