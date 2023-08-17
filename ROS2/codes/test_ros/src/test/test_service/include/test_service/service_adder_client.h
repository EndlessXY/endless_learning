//
// Created by dsz on 23-8-17.
//

#ifndef TEST_SERVICE_ADDER_CLIENT_H
#define TEST_SERVICE_ADDER_CLIENT_H

#include "rclcpp/rclcpp.hpp"
#include "test_interfaces/srv/add_two_ints.hpp"

class ServiceAdderClient {
public:
    ServiceAdderClient();
    ~ServiceAdderClient();
    void send_request();

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<test_interfaces::srv::AddTwoInts>::SharedPtr client_;
};

#endif //TEST_SERVICE_ADDER_CLIENT_H
