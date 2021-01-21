//
// Created by kenny on 15/01/2021.
//
#include "crowd_counter.h"

CrowdCounter::CrowdCounter(const std::string &model_name) {
    net = std::make_shared<IENetwork>("../data/models/" + model_name + ".xml", "../data/models/" + model_name + ".bin");
    net->Build(netOptions);
}

void CrowdCounter::Predict(const cv::Mat &input) {

}
