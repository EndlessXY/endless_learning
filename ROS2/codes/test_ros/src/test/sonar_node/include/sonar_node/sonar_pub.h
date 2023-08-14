//
// Created by dsz on 23-8-11.
//

#ifndef TEST_SONAR_PUB_H
#define TEST_SONAR_PUB_H
#include <iostream>
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/msg/image.hpp"
#include "image_transport/image_transport.hpp"


namespace AIShip {
class SonarPub: public rclcpp::Node {
public:
    SonarPub();
    ~SonarPub();
private:
    cv::Mat image;
    int pHeight;
    int pWidth;
    int pChannels;
    int mFrameIndex;
    image_transport::Publisher mSonarImgPub;

    void GetImagData();
    void GetVideo();
};
}

#endif //TEST_SONAR_PUB_H
