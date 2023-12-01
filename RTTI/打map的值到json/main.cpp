#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
int main() {
     //创建一个 std::multimap 对象
    std::multimap<std::string, std::string> myMultimap;
    myMultimap.insert(std::make_pair("key1", "value1"));
    myMultimap.insert(std::make_pair("key2", "value2"));
    //myMultimap.insert(std::make_pair("key1", "value3"));  // 允许重复的键


    // 转换为 JSON
    Json::Value jsonResult;

    for (const auto& pair : myMultimap) {
        jsonResult[pair.first] = pair.second;
    }

    //// 将 JSON 对象转换为字符串（如果需要）
    //Json::StreamWriterBuilder writer;
    //std::string jsonString = Json::writeString(writer, jsonResult);

    // 输出结果
    std::cout << jsonResult.toStyledString() << std::endl;

    return 0;
}
