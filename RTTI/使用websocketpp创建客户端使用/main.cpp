#include "WebsocketClient.h"
#include "ccs_common_message.pb.h"
#include "ccs_conference_message.pb.h"
#include "ccs_gateway_message.pb.h"

#include "protobuf_codec.h"
HANDLE hEvent;
bool running = false;

void creatConferance(ccs_msg::CreateMeetingReq& confSetupParam)
{
    try
    {
        confSetupParam.set_room_id("80010");
        confSetupParam.set_meeting_id("6666666");
        confSetupParam.set_name("abs_demo");
        confSetupParam.set_creator("ITC");
        confSetupParam.set_conf_password("");
        confSetupParam.set_invite_mode(ccs_msg::InviteMode::e_alwaysInvite);
        confSetupParam.set_audio_codec("G.722-64k{sw}");
        confSetupParam.set_member_count_limit(5);
        confSetupParam.set_conf_media_type(ccs_msg::ConferenceMediaType::e_BothVideoAndAudio);
        confSetupParam.set_proto_type(ccs_msg::ProtoType::e_ProtoH323);
        confSetupParam.set_start_time("2024-04-29 00:00:00"); // 这里需要根据具体时间来设置
        confSetupParam.set_end_time("2024-05-29 23:59:59");   // 这里需要根据具体时间来设置
        ccs_msg::VideoCodec* exVideoCodec = confSetupParam.mutable_ex_video_codec();

        ccs_msg::VideoParams* videoparams = new ccs_msg::VideoParams();
        ccs_msg::MixerParams* mixer_params = videoparams->add_mixer_params_list();
        ccs_msg::VideoCodec* video_codecs = mixer_params->add_video_codecs_list();
        confSetupParam.set_allocated_video_params(videoparams);

        ccs_msg::VideoLayout* layout = confSetupParam.mutable_layout();
        layout->set_layout_id(1);
        layout->set_windows(2);
        //videoparams->set_codec("afaf");
        //ccs_msg::MixerParams* mixerParams = videoparams->add_mixer_params();
        //mixerParams->set_ip("12314");
        //ccs_msg::MixerParams* mixerParams1 = videoparams->add_mixer_params();
        //mixerParams1->set_ip("7890");
        std::cout << "1111111111111111111111\n" << confSetupParam.DebugString() << std::endl;
        //// 创建并赋值 exVideoCodec
        //ccs_msg::VideoCodec* exVideoCodec = confSetupParam.mutable_exvideocodec();
        //exVideoCodec->set_codec("Auto");
        //exVideoCodec->set_bitrate(1024);
        //exVideoCodec->set_bitratecontrol(ccs_msg::VideoCodec::e_VBR); // 可变比特率
        //exVideoCodec->set_keyframeinterval(3);
        //exVideoCodec->set_enablemultislicemode(false); // 不启用多片模式
        //exVideoCodec->set_channelid(0);

        //// 设置主流编码设置
        //ccs_msg::MixerParams* mixerParams = confSetupParam.mutable_video_params()->add_mixer_params();
        //mixerParams->set_ip(""); // 设置 ip 字段为空字符串
        //mixerParams->set_channels_count(1); // 设置 channels_count 为 1

        //mixerParams->set_banner_text(""); // 设置横幅
        //mixerParams->set_rolling_text(""); // 设置设置滚动

        //// 循环设置 videoCodecs 数组中的每个 VideoCodec 对象的值
        //for (int j = 0; j < mixerParams->channels_count(); j++) {
        //    ccs_msg::VideoCodec* videoCodec = mixerParams->add_video_codecs();
        //    videoCodec->set_codec("H.264");
        //    videoCodec->set_bitrate(2048);
        //    videoCodec->set_keyframeinterval(3);
        //    videoCodec->set_enablemultislicemode(false);
        //    videoCodec->set_channelid(0);
        //    videoCodec->set_bitratecontrol(ccs_msg::VideoCodec::e_VBR);
        //}

    }
    catch (const std::exception&)
    {
        std::cout << "something error" << std::endl;
    }


}

void heartBreath(WebsocketClient * client)
{
    std::cout << "start breath..." << std::endl;
    while (true) {
        if (running)
        {
            ccs_msg::KeepAliveReq msg;

            vms::ProtobufCodec& protobufCodec = vms::ProtobufCodec::GetInstance();
            std::cout << "heart send message" << msg.DebugString() << std::endl;
            std::string request = protobufCodec.Encode(msg);
            
            client->Send(request);


            DWORD code = WaitForSingleObject(hEvent, 8000);
            if (code == WAIT_TIMEOUT) {

                continue;
            }
            else if (code == WAIT_OBJECT_0)
            {
                break;
            }
        }

    }
    std::cout << "stop HeartBeatStart thread." << std::endl;
}



int main() {
	bool done = false;
	std::string input;
	WebsocketClient endpoint;
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL) {
        std::cout << "Failed to create event object." << std::endl;

    }
    std::shared_ptr<std::thread> m_thread;
	while (!done) {
		std::cout << "Enter Command: ";
		std::getline(std::cin, input);

		if (input == "quit") {
			done = true;
		}
		else if (input == "help") {
			std::cout
				<< "\nCommand List:\n"
				<< "connect <ws uri>\n"
				<< "send <message>\n"
				<< "close [<close code:default=1000>] [<close reason>]\n"
				<< "help: Display this help text\n"
				<< "quit: Exit the program\n"
				<< std::endl;
		}
		else if (input.substr(0, 7) == "connect") {

			endpoint.Connect("ws://172.16.40.139:63342");
            running = true;
            Sleep(1000);
            m_thread = std::make_shared<std::thread>(heartBreath, &endpoint);
		}
		else if (input.substr(0, 4) == "send") {
            ccs_msg::CreateMeetingReq msg;

            creatConferance(msg);
            std::cout << "1111111111111:    " << std::endl;
            std::cout << msg.DebugString() << std::endl;

            vms::ProtobufCodec& protobufCodec = vms::ProtobufCodec::GetInstance();

            std::string request = protobufCodec.Encode(msg);
            std::cout << "send message size : " << request.size() << std::endl;
            std::cout << "send message lenth : " << request.length() << std::endl;

			endpoint.Send(request);
		}
		else if (input.substr(0, 5) == "close") {
			std::stringstream ss(input);

			std::string cmd;
			std::string reason;

			ss >> cmd;
			std::getline(ss, reason);

			endpoint.Close(reason);
		}
		else if (input.substr(0, 4) == "quit") {
			done = true;
		}
		else {
			std::cout << "> Unrecognized Command" << std::endl;
		}
	}
    m_thread->join();
	return 0;
}
