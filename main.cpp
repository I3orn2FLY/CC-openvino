//
// Created by kenny on 15/01/2021.
//
#include <iostream>
#include "crowd_counter.h"
#include <chrono>

int main() {
    auto detector = CrowdCounter("TargetAINet");
    cv::Mat frame = cv::imread("../data/images/old_trafford.jpg");
//    cv::Mat frame = cv::imread("../data/images/asd.jpg");
    auto bf = std::chrono::high_resolution_clock::now();
    float frame_n = 0;

    detector.Predict(frame);
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds spend = std::chrono::duration_cast<std::chrono::duration<int>>(now - bf);
//    std::cout << "\r" << frame_n * 1000.f / spend.count();
//    std::flush(std::cout);

    cv::imshow("Window", frame);
    cv::waitKey(0);

}