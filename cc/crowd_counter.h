//
// Created by kenny on 15/01/2021.
//

#ifndef OPENVINO_DETECTOR_CROWD_COUNTER_H
#define OPENVINO_DETECTOR_CROWD_COUNTER_H

#include "ie_network.h"
#include <string>




class CrowdCounter {
public:
    explicit CrowdCounter(const std::string &model_name);

    void Predict(const cv::Mat &img);

private:
    float inp_h, inp_w, out_h, out_w;

protected:
    INetwork::Ptr net;
    NetworkOptions netOptions;
};

#endif //OPENVINO_DETECTOR_CROWD_COUNTER_H
