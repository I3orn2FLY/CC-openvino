//
// Created by kenny on 15/01/2021.
//

#ifndef OPENVINO_DETECTOR_CROWD_COUNTER_H
#define OPENVINO_DETECTOR_CROWD_COUNTER_H

#include "ie_network.h"
#include <string>


typedef std::vector<Detection> Detections;

class CrowdCounter {
public:
    explicit CrowdCounter(const std::string &model_name);

    void Predict(const cv::Mat &input);


protected:
    INetwork::Ptr net;
    NetworkOptions netOptions;
};

#endif //OPENVINO_DETECTOR_CROWD_COUNTER_H
