#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
int main() {
     //����һ�� std::multimap ����
    std::multimap<std::string, std::string> myMultimap;
    myMultimap.insert(std::make_pair("key1", "value1"));
    myMultimap.insert(std::make_pair("key2", "value2"));
    //myMultimap.insert(std::make_pair("key1", "value3"));  // �����ظ��ļ�


    // ת��Ϊ JSON
    Json::Value jsonResult;

    for (const auto& pair : myMultimap) {
        jsonResult[pair.first] = pair.second;
    }

    //// �� JSON ����ת��Ϊ�ַ����������Ҫ��
    //Json::StreamWriterBuilder writer;
    //std::string jsonString = Json::writeString(writer, jsonResult);

    // ������
    std::cout << jsonResult.toStyledString() << std::endl;

    return 0;
}
