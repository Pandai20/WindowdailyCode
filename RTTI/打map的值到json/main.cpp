#include <iostream>
#include <json/json.h>
#include <map>
#include <string>
#include <fstream>
#include <list>
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
    //

    //添加一个json数组
    std::list<std::string> myWaihao;
    myWaihao.push_back("帅比");
    myWaihao.push_back("靓仔");
    int index = 0;
    for (auto it=myWaihao.begin();it!=myWaihao.end();++it)
    {
        jsonResult["外号"][index]["name"] = *it;
        index++;
    }



    // 输出结果
    std::cout << jsonResult.toStyledString() << std::endl;



    // 打开文件
    std::ofstream outputFile("data.json");

    // 将 JSON 数据写入文件
    outputFile  << jsonResult << std::endl;

    // 关闭文件
    outputFile.close();
    
    
    
    // 打开 JSON 文件

    std::ifstream inputFile("data.json");

    // 检查文件是否成功打开
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file 'data.json'." << std::endl;
        return 1;
    }

    // 从文件中读取 JSON 数据
    Json::Value jsonData;
    inputFile >> jsonData;

    // 关闭文件
    inputFile.close();

    // 输出读取到的 JSON 数据
    std::cout << "Read JSON data from file 'data.json':" << std::endl;
    std::cout << jsonData.toStyledString().c_str() << std::endl;




    return 0;
}
