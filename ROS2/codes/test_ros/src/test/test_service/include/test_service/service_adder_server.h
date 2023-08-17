//
// Created by dsz on 23-8-17.
//

#ifndef TEST_SERVICE_ADDER_SERVER_H
#define TEST_SERVICE_ADDER_SERVER_H

#include "rclcpp/rclcpp.hpp"
#include "test_interfaces/srv/add_two_ints.hpp"

class ServiceAdderServer: public rclcpp::Node {
public:
    ServiceAdderServer();
    ~ServiceAdderServer();
private:
    void handle_service(
            const std::shared_ptr<test_interfaces::srv::AddTwoInts::Request> request,
            std::shared_ptr<test_interfaces::srv::AddTwoInts::Response> response);
    rclcpp::Service<test_interfaces::srv::AddTwoInts>::SharedPtr service_;
};

#endif //TEST_SERVICE_ADDER_SERVER_H
