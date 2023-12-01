#include <memory>
#include <functional>
#include <iostream>
#include "httplib.h" // ����������� HTTP ��

class CommandCenterResponser {
public:
    virtual ~CommandCenterResponser() = default;
    virtual void onCallback(const Json::Value& body, const HttpParams& httpParams) = 0;
};

class SubCommandCenterResponser : public CommandCenterResponser {
public:
    void onCallback(const Json::Value& body, const HttpParams& httpParams) override {
        // �����ض���ʵ��
        std::cout << "Callback in SubCommandCenterResponser" << std::endl;
    }
};

class CommandCenterHandler {
public:
    // �޸�Ϊ���� CommandCenterResponser ������ָ��
    void response(const httplib::Request& req, httplib::Response& rsp, std::shared_ptr<CommandCenterResponser> responserPtr) {
        if (!checkSign(req, rsp, responserPtr.get()))
            return;

        auto fun = [&](const Json::Value& body, const HttpParams& httpParams) {
            // �����麯����ȷ�����õ����������ʵ��
            responserPtr->onCallback(body, httpParams);
        };
        setContent(req, rsp, fun);
    }

private:
    // ����������� checkSign �� setContent ����
    bool checkSign(const httplib::Request& req, httplib::Response& rsp, CommandCenterResponser* responser) {
        // ʵ�ּ���߼�
        return true;
    }

    void setContent(const httplib::Request& req, httplib::Response& rsp, const std::function<void(const
