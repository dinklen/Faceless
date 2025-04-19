#include "../../include/logging/ZmqSink.hpp"

void ZmqSink::sinkIt(const spdlog::details::log_msg& msg) override {
    spdlog::memory_buf_t formatted;
    spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);

    zmq::message_t zmqMsg(formatted.size());
    memcpy(zmqMsg.data(), formatted.data(), formatted.size());
    socket_.send(zmqMsg, zmq::send_flags::dontwait);
}

void ZmqSink::flush() override {}