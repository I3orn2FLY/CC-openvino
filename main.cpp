//
// Created by kenny on 15/01/2021.
//
#include <iostream>
#include "yolov2_detector.h"
#include <chrono>

int main() {
    auto cap = cv::VideoCapture("../data/videos/demo.mp4");

//    auto detector = YOLOV2Detector("yolo-v2-ava-0001");
    auto detector = YOLOV2Detector("yolo-v2-tiny-ava-sparse-30-0001");
    cv::Mat frame;
    auto bf = std::chrono::high_resolution_clock::now();
    float frame_n = 0;
    while (cap.read(frame)) {
        frame_n += 1;
        Detections dets;
        detector.Predict(frame, dets);
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds spend = std::chrono::duration_cast<std::chrono::duration<int>>(now - bf);
        std::cout << "\r" << frame_n * 1000.f / spend.count();
        std::flush(std::cout);

        cv::imshow("Window", frame);
        cv::waitKey(1);
    }
}