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
    // ����һ�� std::multimap ����
    //std::multimap<std::string, std::string> myMultimap;
    //myMultimap.insert(std::make_pair("key1", "value1"));
    //myMultimap.insert(std::make_pair("key2", "value2"));
    //myMultimap.insert(std::make_pair("key1", "value3"));  // �����ظ��ļ�

    //Json::Value jsonResult;
    //for (const auto& pair : myMultimap) {
    //    jsonResult[pair.first].append(pair.second);
    //}


    //// ת��Ϊ JSON
    //Json::Value jsonResult;

    //for (const auto& pair : myMultimap) {
    //    jsonResult[pair.first].append(pair.second);
    //}

    //// �� JSON ����ת��Ϊ�ַ����������Ҫ��
    //Json::StreamWriterBuilder writer;
    //std::string jsonString = Json::writeString(writer, jsonResult);

    //// ������
    //std::cout << jsonString << std::endl;

    return 0;
}
