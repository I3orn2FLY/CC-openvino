//
// Created by kenny on 15/01/2021.
//

#ifndef OPENVINO_DETECTOR_CROWDCOUNTER_H
#define OPENVINO_DETECTOR_CROWDCOUNTER_H

#include "ie_network.h"
#include <string>


typedef std::vector<Detection> Detections;

class CrowdCounter {
public:
    explicit CrowdCounter(const std::string &model_name);

    virtual void Predict(const cv::Mat &input) = 0;


protected:
    INetwork::Ptr net;
    NetworkOptions netOptions;
};

#endif //OPENVINO_DETECTOR_CROWDCOUNTER_H
