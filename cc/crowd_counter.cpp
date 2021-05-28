//
// Created by kenny on 15/01/2021.
//
#include "crowd_counter.h"

CrowdCounter::CrowdCounter(const std::string &model_name) {

    net = std::make_shared<IENetwork>("../data/models/" + model_name + ".xml", "../data/models/" + model_name + ".bin");
    net->Build(netOptions);

    auto inp_shape = net->GetInputShape();
    auto out_shape = net->GetOutputShape();
    inp_h = static_cast<float>(inp_shape[2]);
    inp_w = static_cast<float>(inp_shape[3]);

    out_h = static_cast<float>(out_shape[1]);
    out_w = static_cast<float>(out_shape[2]);
}

void CrowdCounter::Predict(const cv::Mat &img) {

    auto img_h = static_cast<float>(img.rows);
    auto img_w = static_cast<float>(img.cols);
    float scaled_h, scaled_w;

    if (img_w / img_h > inp_w / inp_h) {
        scaled_w = inp_w;
        scaled_h = inp_w * img_h / img_w;
    } else {
        scaled_h = inp_h;
        scaled_w = inp_h * img_w / img_h;
    }

    cv::Mat scaled, padded = cv::Mat(static_cast<int>(inp_h), static_cast<int>(inp_w), CV_8UC3);
    cv::resize(img, scaled, {static_cast<int>(scaled_w), static_cast<int>(scaled_h)});
    cv::cvtColor(scaled, scaled, cv::COLOR_RGB2BGR);

    padded = 0;
    scaled.copyTo(padded(cv::Rect(0, 0, static_cast<int>(scaled_w), static_cast<int>(scaled_h))));

    net->SetInput(padded);
    net->Predict();

    auto truncated_h = std::min(out_h, ceil(scaled_h / inp_h * out_h));
    auto truncated_w = std::min(out_w, ceil(scaled_w / inp_w * out_w));

    float cc = 0.f;
    auto res = net->GetOutput();
    for (float i = 0; i < truncated_h;  ++i) {
        for (float j = 0; j < truncated_w; ++j) {
            cc += res[int(i * out_w + j)];
        }
    }

    std::cout << cc << std::endl;

}
