/*
Copyright (c) 2021, Arjun S Kumar
*/
#include "Pong.hpp"
#include "std_msgs/String.h"
#include <string>

namespace isaac {

  namespace rosbridge{

    struct Pong::RosMsgData{
    ros::NodeHandle node;
    ros::Publisher pub;
    };

    void Pong::start() {

      ros::M_string args;
      if (!ros::isInitialized()) {
        ros::init(args, "PingROS", ros::init_options::NoSigintHandler);
      }
      
      pong_data_ = std::make_unique<RosMsgData>();
      pong_data_->pub = pong_data_->node.advertise<std_msgs::String>( 
          get_ros_publisher_channel_name(), get_ros_publisher_queue_size());
      
      tickOnMessage(rx_trigger());
    }

    void Pong::tick() {

      if (!ros::ok()) {
        LOG_ERROR("An error has occurred within ROS.");
        return;
      }
      
      if (pong_data_->pub.getNumSubscribers() == 0)
        return;
      
      auto proto_reader = rx_trigger().getProto();

      const std::string txt = proto_reader.getMessage();

      std_msgs::String msg;
      msg.data = txt; 
      pong_data_->pub.publish(msg);

    }

    void Pong::stop() {
      pong_data_->pub.shutdown();
      pong_data_ = nullptr;

    }

    Pong::~Pong() {

    }

    Pong::Pong() {

    }

  } // namespace rosbridge
}  // namespace isaac
