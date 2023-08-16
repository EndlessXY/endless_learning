//
// Created by dsz on 23-8-16.
//

#ifndef TEST_ACTION_MOVE_CLIENT_H
#define TEST_ACTION_MOVE_CLIENT_H

#include <iostream>
#include <future>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "test_interfaces/action/move_circle.hpp"

namespace AIShip {
class ActionMoveClient: public rclcpp::Node {
public:
    using MoveCircle = test_interfaces::action::MoveCircle;
    using GoalHandleMoveCircle = rclcpp_action::ClientGoalHandle<MoveCircle>;
    ActionMoveClient(const std::string & node_name);
    ~ActionMoveClient();
    void send_goal(bool enable);
private:
    rclcpp_action::Client<test_interfaces::action::MoveCircle>::SharedPtr action_client_;

    void goal_response_callback(GoalHandleMoveCircle::SharedPtr goal_handle);
    void feedback_callback(rclcpp_action::ClientGoalHandle<MoveCircle>::SharedPtr, const std::shared_ptr<const MoveCircle::Feedback> feedback);
    void result_callback(const GoalHandleMoveCircle::WrappedResult & result);

};
}

#endif //TEST_ACTION_MOVE_CLIENT_H
