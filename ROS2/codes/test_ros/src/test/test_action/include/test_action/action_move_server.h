//
// Created by dsz on 23-8-16.
//

#ifndef TEST_ACTION_MOVE_SERVER_H
#define TEST_ACTION_MOVE_SERVER_H

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "test_interfaces/action/move_circle.hpp"

namespace AIShip {
class ActionMoveServer: public rclcpp::Node {
public:
    using MoveCircle = test_interfaces::action::MoveCircle;
    using GoalHandleMoveCircle = rclcpp_action::ServerGoalHandle<MoveCircle>;
    explicit ActionMoveServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
private:
    rclcpp_action::Server<MoveCircle>::SharedPtr action_server_;
    rclcpp_action::GoalResponse handle_goal(
            const rclcpp_action::GoalUUID & uuid,
            std::shared_ptr<const MoveCircle::Goal> goal);
    rclcpp_action::CancelResponse handle_cancel(
            const std::shared_ptr<GoalHandleMoveCircle> goal_handle);
    void handle_accepted(const std::shared_ptr<GoalHandleMoveCircle> goal_handle);
    void execute(const std::shared_ptr<GoalHandleMoveCircle> goal_handle);

};
}

#endif //TEST_ACTION_MOVE_SERVER_H
