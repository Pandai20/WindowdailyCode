#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
int main() {
    Json::Value jsonResult;
    jsonResult["123"] = 123;
    jsonResult["456"] = 123;
    jsonResult["780"] = 123;
    jsonResult["888"] = 123;
    std::string mmp = jsonResult.asCString();
    std::cout << mmp << std::endl;
    // 创建一个 std::multimap 对象
    //std::multimap<std::string, std::string> myMultimap;
    //myMultimap.insert(std::make_pair("key1", "value1"));
    //myMultimap.insert(std::make_pair("key2", "value2"));
    //myMultimap.insert(std::make_pair("key1", "value3"));  // 允许重复的键

    //Json::Value jsonResult;
    //for (const auto& pair : myMultimap) {
    //    jsonResult[pair.first].append(pair.second);
    //}


    //// 转换为 JSON
    //Json::Value jsonResult;

    //for (const auto& pair : myMultimap) {
    //    jsonResult[pair.first].append(pair.second);
    //}

    //// 将 JSON 对象转换为字符串（如果需要）
    //Json::StreamWriterBuilder writer;
    //std::string jsonString = Json::writeString(writer, jsonResult);

    //// 输出结果
    //std::cout << jsonString << std::endl;

    return 0;
}
