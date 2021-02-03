//
// Created by kenny on 15/01/2021.
//
#include "crowd_counter.h"

CrowdCounter::CrowdCounter(const std::string &model_name) {
    net = std::make_shared<IENetwork>("../data/models/" + model_name + ".xml", "../data/models/" + model_name + ".bin");
    net->Build(netOptions);
}

void CrowdCounter::Predict(const cv::Mat &img) {
    auto inp_shape = net->GetInputShape();
    size_t inp_h = inp_shape[2];
    size_t inp_w = inp_shape[3];
    int new_height, new_width;
    if (img.rows > img.cols) {
        new_height = inp_h;
        new_width = int(img.cols * (inp_w * 1.f / img.rows));
    } else {
        new_width = inp_w;
        new_height = int(img.rows * (inp_h * 1.f / img.cols));
    }
    cv::Mat scaled;
    cv::resize(img, scaled, {new_width, new_height});
    cv::cvtColor(scaled, scaled, cv::COLOR_RGB2BGR);
    cv::Mat padded(inp_h, inp_w, CV_8UC3);
    padded = 0;
    scaled.copyTo(padded(cv::Rect(0, 0, new_width, new_height)));

    net->SetInput(padded);
    net->Predict();
    auto shape = net->GetOutputShape(0);
    float cc = 0.f;
    size_t n = 1;
    for (const auto &s: shape) {
        n *= s;
    }
    auto res = net->GetOutput();
    for (size_t i = 0; i < n; ++i) {
        cc += res[i];
    }


    std::cout << "cc: " << cc << std::endl;
}
