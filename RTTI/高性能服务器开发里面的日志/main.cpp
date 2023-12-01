#include <memory>
#include <functional>
#include <iostream>
#include "httplib.h" // 假设这是你的 HTTP 库

class CommandCenterResponser {
public:
    virtual ~CommandCenterResponser() = default;
    virtual void onCallback(const Json::Value& body, const HttpParams& httpParams) = 0;
};

class SubCommandCenterResponser : public CommandCenterResponser {
public:
    void onCallback(const Json::Value& body, const HttpParams& httpParams) override {
        // 子类特定的实现
        std::cout << "Callback in SubCommandCenterResponser" << std::endl;
    }
};

class CommandCenterHandler {
public:
    // 修改为接受 CommandCenterResponser 的智能指针
    void response(const httplib::Request& req, httplib::Response& rsp, std::shared_ptr<CommandCenterResponser> responserPtr) {
        if (!checkSign(req, rsp, responserPtr.get()))
            return;

        auto fun = [&](const Json::Value& body, const HttpParams& httpParams) {
            // 调用虚函数，确保调用的是派生类的实现
            responserPtr->onCallback(body, httpParams);
        };
        setContent(req, rsp, fun);
    }

private:
    // 假设这是你的 checkSign 和 setContent 函数
    bool checkSign(const httplib::Request& req, httplib::Response& rsp, CommandCenterResponser* responser) {
        // 实现检查逻辑
        return true;
    }

    void setContent(const httplib::Request& req, httplib::Response& rsp, const std::function<void(const
