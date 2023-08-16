//
// Created by dsz on 23-8-16.
//
#include "../include/test_action/action_move_client.h"


AIShip::ActionMoveClient::ActionMoveClient(const std::string & node_name): rclcpp::Node(node_name) {
    action_client_ = rclcpp_action::create_client<MoveCircle>(this, "move_circle");
}

AIShip::ActionMoveClient::~ActionMoveClient() {

}

void AIShip::ActionMoveClient::send_goal(bool enable)
{
    using namespace std::placeholders;

    if (!action_client_->wait_for_action_server()) {
        RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
        rclcpp::shutdown();
    }

    auto goal_msg = MoveCircle::Goal();
    goal_msg.enable = enable;

    auto send_goal_options = rclcpp_action::Client<MoveCircle>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&AIShip::ActionMoveClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback = std::bind(&AIShip::ActionMoveClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback = std::bind(&AIShip::ActionMoveClient::result_callback, this, _1);
    action_client_->async_send_goal(goal_msg, send_goal_options);
}

void AIShip::ActionMoveClient::goal_response_callback(GoalHandleMoveCircle::SharedPtr goal_handle)
{
//    auto goal_handle = future.get();
    if (!goal_handle)
    {
        RCLCPP_INFO(get_logger(), "Goal rejected :(");
        return;
    }

    RCLCPP_INFO(get_logger(), "Goal accepted :)");
}

void AIShip::ActionMoveClient::feedback_callback(GoalHandleMoveCircle::SharedPtr,
        const std::shared_ptr<const MoveCircle::Feedback> feedback)
{
    RCLCPP_INFO(get_logger(), "Received feedback: {%d}", feedback->state);
}

void AIShip::ActionMoveClient::result_callback(const GoalHandleMoveCircle::WrappedResult & result)
{
    switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
            return;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
            return;
        default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            return;
    }
    RCLCPP_INFO(get_logger(), "Result: {%d}", result.result->finish);
}

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AIShip::ActionMoveClient>("action_move_client");
    node->send_goal(false);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
