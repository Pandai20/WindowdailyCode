#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
#include <fstream>
#include <list>
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
    //

    //���һ��json����
    std::list<std::string> myWaihao;
    myWaihao.push_back("˧��");
    myWaihao.push_back("����");
    int index = 0;
    for (auto it=myWaihao.begin();it!=myWaihao.end();++it)
    {
        jsonResult["���"][index]["name"] = *it;
        index++;
    }



    // ������
    std::cout << jsonResult.toStyledString() << std::endl;



    // ���ļ�
    std::ofstream outputFile("data.json");

    // �� JSON ����д���ļ�
    outputFile  << jsonResult << std::endl;

    // �ر��ļ�
    outputFile.close();
    
    
    
    // �� JSON �ļ�

    std::ifstream inputFile("data.json");

    // ����ļ��Ƿ�ɹ���
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file 'data.json'." << std::endl;
        return 1;
    }

    // ���ļ��ж�ȡ JSON ����
    Json::Value jsonData;
    inputFile >> jsonData;

    // �ر��ļ�
    inputFile.close();

    // �����ȡ���� JSON ����
    std::cout << "Read JSON data from file 'data.json':" << std::endl;
    std::cout << jsonData.toStyledString().c_str() << std::endl;




    return 0;
}
