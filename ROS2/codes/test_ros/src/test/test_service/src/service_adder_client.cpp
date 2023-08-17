//
// Created by dsz on 23-8-17.
//

#include "../include/test_service/service_adder_client.h"

ServiceAdderClient::ServiceAdderClient() {
    node_ = rclcpp::Node::make_shared("add_two_ints_client");
    client_ = node_->create_client<test_interfaces::srv::AddTwoInts>("add_two_ints");
}

ServiceAdderClient::~ServiceAdderClient() {

}

void ServiceAdderClient::send_request() {
    auto request = std::make_shared<test_interfaces::srv::AddTwoInts::Request>();
    request->a = 2;
    request->b = 3;

    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting for the service. Exiting.");
            return;
        }
        RCLCPP_INFO(node_->get_logger(), "service not available, waiting again...");
    }

    auto result_future = client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node_, result_future) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(node_->get_logger(), "Result: %ld", result_future.get()->sum);
    }
    else
    {
        RCLCPP_ERROR(node_->get_logger(), "Failed to call service");
    }
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    ServiceAdderClient client;
    client.send_request();
    rclcpp::shutdown();
    return 0;
}
