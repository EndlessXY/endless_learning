//
// Created by dsz on 23-8-3.
//
#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char** argv) {
    cv::VideoCapture cap("/home/dsz/Ubinavi/Data/aiship_st/崇明数据/001/aiship_data_20230710/drain_outlet/video/camera_left_2023_0710_095629.mp4");
    if(!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "video width: " << frame_width << std::endl;
    std::cout << "video height: " << frame_height << std::endl;

    cv::VideoWriter video("/home/dsz/Downloads/out.mp4", cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 30, cv::Size(frame_width, frame_height));
    cv::Mat frame;
    while(1) {
        cap >> frame;
        if(frame.empty()) {
            break;
        }
        video.write(frame);
        cv::imshow("Frame", frame);
        char c = (char)cv::waitKey(25);
        if(c == 27){
            break;
        }
    }
    cap.release();
    video.release();
    cv::destroyAllWindows();
    return 0;
}