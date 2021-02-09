/*
Copyright (c) 2021, Arjun S Kumar
*/

#pragma once

#include <string>

#include "engine/alice/alice.hpp"
#include "messages/messages.hpp"

namespace isaac {

  namespace rosbridge {

    class Ping : public alice::Codelet {
      
      public:

        Ping();
        virtual ~Ping();

        void start() override;
        void tick() override;

        ISAAC_PROTO_TX(PingProto, ping);

        ISAAC_PARAM(int, subscriber_queue_size, 1000);
        ISAAC_PARAM(std::string, subscriber_channel_name, "/ping_msg");

      private: 

        struct RosMsgData;
        std::unique_ptr<RosMsgData> ping_data_;

    };

  }  // namespace rosbridge
}  // namespace isaac

ISAAC_ALICE_REGISTER_CODELET(isaac::rosbridge::Ping);
