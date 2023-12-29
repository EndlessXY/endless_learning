//
// Created by dsz on 23-8-3.
//
#include <opencv2/opencv.hpp>
#include <iostream>


int main(int argc, char** argv) {
    cv::VideoCapture cap("/Users/dsz/Study/Data/video/test.mp4");
    if(!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "video width: " << frame_width << std::endl;
    std::cout << "video height: " << frame_height << std::endl;

    cv::VideoWriter video("/Users/dsz/Study/Data/video/out.mp4", cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 30, cv::Size(frame_width, frame_height));
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


//  g++ -std=c++11 video_read_save.cpp -o test `pkg-config --cflags --libs opencv4`