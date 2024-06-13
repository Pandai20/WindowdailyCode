#ifndef PROTOBUF_CODEC_H
#define PROTOBUF_CODEC_H

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#ifndef _WIN32
#include <arpa/inet.h>  // htonl, ntohl
#endif
#include <stdint.h>
#include <iostream>
#include "blowfish.h"

namespace vms
{
class ProtobufCodec
{
public:
    ProtobufCodec();
   
    ~ProtobufCodec();

    static ProtobufCodec& GetInstance() {static ProtobufCodec codec; return codec;}

    std::string Encode(const google::protobuf::Message& message);

    google::protobuf::Message* Decode(const std::string& buf);

private:
    google::protobuf::Message* CreateMessage(const std::string& type_name);

private:
    CBlowFish* m_blowfish;
};
}//namespace vms

#endif  // PROTOBUF_CODEC_H
