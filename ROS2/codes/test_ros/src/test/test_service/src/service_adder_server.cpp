//
// Created by dsz on 23-8-17.
//
#include "../include/test_service/service_adder_server.h"

ServiceAdderServer::ServiceAdderServer(): Node("add_two_ints") {
    service_ = this->create_service<test_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(&ServiceAdderServer::handle_service, this, std::placeholders::_1, std::placeholders::_2));
}

ServiceAdderServer::~ServiceAdderServer() {

}

void ServiceAdderServer::handle_service(
        const std::shared_ptr<test_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<test_interfaces::srv::AddTwoInts::Response> response)
{
    response->sum = request->a + request->b;
    RCLCPP_INFO(this->get_logger(), "Incoming request: %ld + %ld", request->a, request->b);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServiceAdderServer>());
    rclcpp::shutdown();
    return 0;
}
