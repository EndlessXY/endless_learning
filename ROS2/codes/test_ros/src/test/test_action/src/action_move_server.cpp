//
// Created by dsz on 23-8-16.
//
#include "../include/test_action/action_move_server.h"


AIShip::ActionMoveServer::ActionMoveServer(const rclcpp::NodeOptions & options) : Node("action_move_server", options){
    using namespace std::placeholders;
    action_server_ = rclcpp_action::create_server<MoveCircle>(
            this,
            "move_circle",
            std::bind(&AIShip::ActionMoveServer::handle_goal, this, _1, _2),
            std::bind(&AIShip::ActionMoveServer::handle_cancel, this, _1),
            std::bind(&AIShip::ActionMoveServer::handle_accepted, this, _1));
}


rclcpp_action::GoalResponse AIShip::ActionMoveServer::handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const MoveCircle::Goal> goal)
{
    (void)uuid;
    // For demonstration purposes, we will accept all goals.
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse AIShip::ActionMoveServer::handle_cancel(
        const std::shared_ptr<GoalHandleMoveCircle> goal_handle)
{
    (void)goal_handle;
    // For demonstration purposes, we will not handle canceling, and just let the goal run until completion.
    return rclcpp_action::CancelResponse::REJECT;
}

void AIShip::ActionMoveServer::handle_accepted(const std::shared_ptr<GoalHandleMoveCircle> goal_handle)
{
    // This needs its own thread so that it can work concurrently with other goals.
    std::thread{std::bind(&AIShip::ActionMoveServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void AIShip::ActionMoveServer::execute(const std::shared_ptr<GoalHandleMoveCircle> goal_handle)
{
    RCLCPP_INFO(this->get_logger(), "Executing goal...");
    rclcpp::Rate loop_rate(1);
    auto feedback = std::make_shared<MoveCircle::Feedback>();
    auto & state = feedback->state;
    auto result = std::make_shared<MoveCircle::Result>();

    for (int i = 0; i <= 360; i+=30) {
        if (goal_handle->is_canceling()) {
            goal_handle->canceled(result);
            RCLCPP_INFO(this->get_logger(), "Goal Canceled");
            return;
        }

        state = i;
        goal_handle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(), "Publishing Feedback: %d", state);

        loop_rate.sleep();
    }

    result->finish = true;
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "Goal Succeeded");
}

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto action_server = std::make_shared<AIShip::ActionMoveServer>();
    rclcpp::spin(action_server);
    rclcpp::shutdown();
    return 0;
}