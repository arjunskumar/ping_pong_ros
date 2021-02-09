/*
Copyright (c) 2021, Arjun S  Kumar
*/
#include "Ping.hpp"

#include "engine/core/logger.hpp"
#include "boost/next_prior.hpp"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros/callback_queue.h"

namespace isaac {
  namespace rosbridge {

    namespace {
      class CallbackFunctor {
      public:
        explicit CallbackFunctor(Ping* bridge) {
          bridge_ = bridge;
        }
        
        CallbackFunctor(const CallbackFunctor&) = default;
        ~CallbackFunctor() = default;

        void operator()(const std_msgs::String::ConstPtr& msg) {
                        
          const std::string& text = msg->data.c_str();
        
          auto _msg = bridge_->tx_ping().initProto();
          _msg.setMessage(text);
          bridge_->tx_ping().publish();

        }
        private:
          Ping* bridge_;
      };

    }
   
    struct Ping::RosMsgData {
      ros::NodeHandle node;
      ros::Subscriber sub;
      ros::CallbackQueue callbackQueue;
    };

    void Ping::start() {

      ros::M_string args;
      if (!ros::isInitialized()) {
        ros::init(args, "PingROS", ros::init_options::NoSigintHandler);
      }
      
      ping_data_ = std::make_unique<RosMsgData>();
      ping_data_->node.setCallbackQueue(&(ping_data_->callbackQueue));
      ping_data_->sub = ping_data_->node.subscribe<std_msgs::String>(
          get_subscriber_channel_name(), get_subscriber_queue_size(), CallbackFunctor(this));

      tickPeriodically();
    }

    void Ping::tick() {
    
      if (ros::ok()) {
        ping_data_->callbackQueue.callAvailable();
      } 
      else {
        LOG_ERROR("An error has occurred within ROS.");
      }


    }


    Ping::~Ping() {
    }

    Ping::Ping() {
    }


  } // namespace rosbridge 
}  // namespace isaac
