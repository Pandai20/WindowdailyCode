#include "protobuf_codec.h"
//#include "config.h"
#include <winsock2.h>

namespace vms
{
static const uint8_t key[] = {0xA0, 0xF1, 0xDE, 0x7A, 0x30, 0x5B, 0x91, 0x88};
#define ENABLE_ENCRYPT 0

ProtobufCodec::ProtobufCodec()
    : m_blowfish(NULL)
{
    m_blowfish = new CBlowFish(key, sizeof(key));
}

ProtobufCodec::~ProtobufCodec()
{
    delete m_blowfish;
}

std::string ProtobufCodec::Encode(const google::protobuf::Message& message)
{
#if !ENABLE_ENCRYPT
    std::string res;
    const std::string& typeName = message.GetTypeName();
    std::cout << "typeName :" << typeName << std::endl;;
    uint32_t typeNameLen = typeName.length();
    uint32_t typeNameNetLen = htonl(typeNameLen);
    res.resize(sizeof(uint32_t));
    res.append(reinterpret_cast<char*>(&typeNameNetLen), sizeof(uint32_t)); // add type's length
    res.append(typeName.c_str(), typeNameLen);                    // add type's type
    if (message.AppendToString(&res)) {
        uint32_t len = htonl(res.length());
        std::copy(reinterpret_cast<char*>(&len),
                  reinterpret_cast<char*>(&len) + sizeof(len),
                  res.begin());
    } else {
        std::cout<<"protobuf_encode() error !!!";
        res.clear();
    }
    return res;
#else
    std::string res, res2;
    const std::string& typeName = message.GetTypeName();
    uint32_t typeNameLen = typeName.length();
    uint32_t typeNameNetLen = htonl(typeNameLen);
    res.append(reinterpret_cast<char*>(&typeNameNetLen), sizeof(uint32_t)); // add type's length
    res.append(typeName.c_str(), typeNameLen);                    // add type's type
    if (!message.AppendToString(&res)) {
        std::cout<<"protobuf_encode() error !!!";
        res.clear();
    }

    if (res.empty())
        return res;

    //PWaitAndSignal m(m_mtxEnc);
    //assert(res.length() < MAX_TCP_PACKET_SIZE);
    m_encBuf.SetMinSize(res.length() + 1024);
    uint32_t encLen = m_blowfish->Encrypt((uint8_t*)res.data(), m_encBuf.GetPointer(), res.length());
    res2.resize(encLen + sizeof(uint32_t));

    uint32_t pktNetLen = htonl(encLen + sizeof(uint32_t));
    std::copy(reinterpret_cast<char*>(&pktNetLen),
              reinterpret_cast<char*>(&pktNetLen) + sizeof(uint32_t),
              res2.begin());

    std::copy(m_encBuf.GetPointer(), m_encBuf.GetPointer() + encLen, res2.begin() + sizeof(uint32_t));
    return res2;
#endif
}

google::protobuf::Message* ProtobufCodec::Decode(const std::string& buf)
{
    if (buf.empty())
        return NULL;

#if !ENABLE_ENCRYPT
    if (buf.length() < sizeof(uint32_t)) {
        std::cout<<"Receved invalid buf !!!";
        return NULL;
    }
    const char* ptr = buf.data();
    uint32_t packet_len = ntohl(*( (uint32_t*)ptr ));
    //std::cout << "buf.length: " << buf.length() << std::endl;
    std::cout << "packet_len: " << packet_len << std::endl;
    if (buf.length() != packet_len || packet_len <= (2 * sizeof(uint32_t))) {              // check the packet's length
        std::cout<<"Receved invalid buf !!!";
        return NULL;
    }

    uint32_t typeNameLen = ntohl(*(uint32_t*)(ptr + sizeof(uint32_t)));
    if (typeNameLen > packet_len - 2 * sizeof(uint32_t)) {
        std::cout<<"Type name length invalid, packet Len:" <<packet_len <<" ,typeNameLen: " <<typeNameLen;
        return NULL;
    }

    const char* typeNameBegin = ptr + 2 * sizeof(uint32_t);
    const char* typeNameEnd = typeNameBegin + typeNameLen;
    std::string typeName(typeNameBegin, typeNameEnd);                        // get the typename
    //std::cout << "typeNameLen: " << typeNameLen << std::endl;
    //std::cout << "typeName: " << typeName << std::endl;
    google::protobuf::Message* result = CreateMessage(typeName);      // create the protobuf message
    if (!result) {
        std::cout<<"Create message error, typename:"<<typeName<<" is not right";
        return result;
    }
    std::string packet(typeNameEnd, buf.length() - 2 * sizeof(uint32_t) - typeNameLen);
    if (!result->ParseFromString(packet)) {
        std::cout<<"ParseFromString() error !!!";
        delete result;
        return NULL;
    }
    return result;
#else
    const char* ptr = buf.data();
    if (buf.length() != ntohl(*((uint32_t*)ptr))) {
        std::cout<<"Receved invalid buf !!!";
        return NULL;
    }

    PWaitAndSignal m(m_mtxDec);
    m_decBuf.SetMinSize(buf.length() + 1024);
    uint32_t bufLen = m_blowfish->Decrypt((uint8_t*)buf.data() + sizeof(uint32_t),
                                          m_decBuf.GetPointer(),
                                          buf.length() - sizeof(uint32_t));
    if (bufLen <= sizeof(uint32_t)) {
        std::cout<<"Decrypt failed !!!";
        return NULL;
    }

    ptr = (char*)m_decBuf.GetPointer();
    uint32_t typeNameLen = ntohl(*(uint32_t*)(ptr));
    if (typeNameLen > bufLen - sizeof(uint32_t)) {
        std::cout<<"Type name length invalid, packet Len:" <<bufLen <<" ,typeNameLen: " <<typeNameLen;
        return NULL;
    }

    const char* typeNameBegin = ptr + sizeof(uint32_t);
    const char* typeNameEnd = typeNameBegin + typeNameLen;
    std::string typeName(typeNameBegin, typeNameEnd);                 // get the typename

    google::protobuf::Message* result = CreateMessage(typeName);      // create the protobuf message
    if (!result) {
        std::cout<<"Create message error, typename is not right";
        return result;
    }

    std::string packet(typeNameEnd, bufLen - sizeof(uint32_t) - typeNameLen);
    if (!result->ParseFromString(packet)) {
        std::cout<<"ParseFromString() error !!!";
        delete result;
        return NULL;
    }

    return result;
#endif
}

google::protobuf::Message* ProtobufCodec::CreateMessage(const std::string& typeName)
{
    google::protobuf::Message* message = NULL;
    const google::protobuf::Descriptor* descriptor =
            google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
    if (descriptor) {
        const google::protobuf::Message* prototype =
                google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (prototype) {
            message = prototype->New();
        }
    }
    return message;
}
}//namespace vms
