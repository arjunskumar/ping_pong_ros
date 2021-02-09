/*
Copyright (c) 2021, Arjun S Kumar
*/
#pragma once

#include "engine/alice/alice.hpp"
#include "messages/messages.hpp"
#include "boost/next_prior.hpp"

#include "ros/callback_queue.h"
#include "ros/ros.h"

namespace isaac {

  namespace rosbridge{

    class Pong : public alice::Codelet {
    public:

      Pong();
      virtual ~Pong();
      void start() override;
      void tick() override;
      void stop() override;
      ISAAC_PROTO_RX(PingProto, trigger);

      ISAAC_PARAM(int, ros_publisher_queue_size, 10);
      ISAAC_PARAM(std::string, ros_publisher_channel_name, "pong_msg");

      private:

      struct RosMsgData;
      std::unique_ptr<RosMsgData> pong_data_;

    };

  } // namespace rosbridge
}  // namespace isaac

ISAAC_ALICE_REGISTER_CODELET(isaac::rosbridge::Pong);

