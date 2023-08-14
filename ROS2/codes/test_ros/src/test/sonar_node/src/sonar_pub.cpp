//
// Created by dsz on 23-8-11.
//
#include "../include/sonar_node/sonar_pub.h"


AIShip::SonarPub::SonarPub():Node("Sonar_pub") {
    pHeight = 1;
    pWidth = 1920;
    pChannels = 3;
    mFrameIndex = 0;
    image = cv::Mat(pHeight, pWidth, CV_8UC3);

    rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_sensor_data;
    custom_qos_profile.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    mSonarImgPub = image_transport::create_publisher(this, "sonar/image_raw", custom_qos_profile);

//    GetImagData();
    GetVideo();
}

AIShip::SonarPub::~SonarPub() {

}

void AIShip::SonarPub::GetVideo() {
    cv::VideoCapture cap("/home/dsz/Ubinavi/Data/aiship_st/chongming/001/aiship_data_20230713/drain_outlet/video/camera_left_2023_0713_115110.mp4");
    if(!cap.isOpened()) {
        RCLCPP_INFO(this->get_logger(), "Cannot open video");
        return;
    }
    cv::Mat frame;
    while(true) {
        mFrameIndex++;
        cap >> frame;
        if(frame.empty()) {
            RCLCPP_INFO(this->get_logger(), "End of video");
            break;
        }
        cv::resize(frame, frame, cv::Size(420, 420));
        // Publish sonar image
        std_msgs::msg::Header header;
        header.stamp = this->get_clock()->now();
        header.frame_id = "sonar_ping_" + std::to_string(mFrameIndex);
        sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
        mSonarImgPub.publish(img_msg);
        RCLCPP_INFO(this->get_logger(), "sonar pub %d", mFrameIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void AIShip::SonarPub::GetImagData() {

    int blue = 128, green = 128, red = 128;
    while(true) {
        mFrameIndex++;
        for (int row = 0; row < image.rows; ++row) {
            for (int col = 0; col < image.cols; ++col) {
                image.at<cv::Vec3b>(row, col) = cv::Vec3b(blue, green, red);
            }
        }
        // Publish sonar image
        std_msgs::msg::Header header;
        header.stamp = this->get_clock()->now();
        header.frame_id = "sonar_ping_" + std::to_string(mFrameIndex);
        sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(header, "bgr8", image).toImageMsg();
        mSonarImgPub.publish(img_msg);
        RCLCPP_INFO(this->get_logger(), "sonar pub %d", mFrameIndex);


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        blue++;
        if (blue > 255) {
            blue = 255;
            green++;
            if (green > 255) {
                green = 255;
                red++;
                if (red > 255) {
                    blue = 128;
                    green = 128;
                    red = 128;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AIShip::SonarPub>());
    rclcpp::shutdown();
    return 0;
}