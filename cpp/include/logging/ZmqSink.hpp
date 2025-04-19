#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <zmq.h>

template<typename Mutex>
class ZmqSink: public spdlog::sinks::base_sink<Mutex> {
public:
    ZmqSink(zmq::socket_t&& socket): socket_(std::move(socket)) {}

protected:
    void sinkIt(const spdlog::details::log_msg& msg) override;
    void flush() override;

private:
    zmq::socket_t socket_;
};