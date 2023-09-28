//
// Created by dsz on 23-8-11.
//
#include "../include/sonar_node/sonar_pub.h"
#define WINDOW_WIDTH 1280 //603 // 1920 * 480
#define WINDOW_HEIGHT 230 //201


AIShip::SonarPub::SonarPub():Node("Sonar_pub") {
    pHeight = 1;
    pWidth = 1920;
    pChannels = 3;
    mHeight = 960;
    mWidth = 1920;
    mChannels = 3;
    mWindowHeight = WINDOW_HEIGHT;
    mWindowWidth = WINDOW_WIDTH;
    mImgSize = mHeight * mWidth * mChannels;
    mSonarImageData = new unsigned char[mImgSize];
    mFrameIndex = 0;
    mPingIndex = 0;
    image = cv::Mat(pHeight, pWidth, CV_8UC3);

    rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_sensor_data;
    custom_qos_profile.reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
//    rmw_qos_profile_t custom_qos_profile = rmw_qos_profile_sensor_data;
//    custom_qos_profile.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;//RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT; RMW_QOS_POLICY_RELIABILITY_RELIABLE
    custom_qos_profile.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    custom_qos_profile.depth = 1;

    mSonarImgPub = image_transport::create_publisher(this, "sonar/sonar_live", custom_qos_profile);
    mSonarImg = cv::imread("/opt/ubiai/aiship/data/test/image/sonar.jpg");
    cv::cvtColor(mSonarImg, mSonarImg, CV_RGB2BGR);
    GetSonarData(mSonarImg);

//    GetImagData();
//    GetVideo();
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
        cv::resize(frame, frame, cv::Size(250, 250));
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

void AIShip::SonarPub::fillWithColor(unsigned char* imageData, int width, int height, int channels, unsigned char r, unsigned char g, unsigned char b) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * channels;
            imageData[index] = r;
            imageData[index + 1] = g;
            imageData[index + 2] = b;
        }
    }
}

void AIShip::SonarPub::GetSonarData(cv::Mat sonarImg) {
    while(true) {
        mPingIndex %= mHeight;
        unsigned char* rowImg = sonarImg.ptr<unsigned char>(mPingIndex);
        int newSize = mChannels * 1 * mWidth;
        memmove(mSonarImageData + newSize, mSonarImageData, mImgSize-newSize);
        memcpy(mSonarImageData, rowImg, newSize);

        cv::Mat mSonarImageMat = cv::Mat(mHeight, mWidth, CV_8UC3);
        memcpy(mSonarImageMat.data, mSonarImageData, mImgSize);
        cv::cvtColor(mSonarImageMat, mSonarImageMat, CV_RGB2BGR);

        cv::namedWindow("sonar", 0);
        cv::resizeWindow("sonar", mWindowWidth, mWindowHeight);
        cv::Mat showImg = mSonarImageMat(cv::Range(0, round((double)mWidth*mWindowHeight/mWindowWidth)), cv::Range(0, mWidth));
        cv::resize(showImg, showImg, cv::Size(mWindowWidth, mWindowHeight));
        cv::imshow("sonar", showImg);
        cv::waitKey(5);

        // Publish sonar image
        std_msgs::msg::Header header;
        header.stamp = this->get_clock()->now();
        header.frame_id = "sonar_ping_" + std::to_string(mPingIndex);
        sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(header, "bgr8", showImg).toImageMsg();
        mSonarImgPub.publish(img_msg);
        RCLCPP_INFO(this->get_logger(), "sonar pub %d", mPingIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++mPingIndex;
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AIShip::SonarPub>());
    rclcpp::shutdown();
    return 0;
}