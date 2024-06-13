#include <mysql/mysql.h>
#include <mysql/errmsg.h>

#include <iostream>
#include <string>
int main()
{
    //1.初始化mysql client
    MYSQL* mysql;
    if (NULL == mysql_init(mysql))
    {
        //说明初始化数据库出错
        return -1;
    }

    //1.2 检测是否存在数据库
    //need to do somthing

    // 2. 连接数据库服务器
    if (!mysql_real_connect(mysql, "172.16.40.139", "root", "itc@996Right", "mysql_test", 0, NULL, 0))
    {
        printf("mysql_real_connect() error\n");
        std::string strErrorMsg = mysql_error(mysql);
        std::cout <<"数据库初始化失败的原因: "<< strErrorMsg << std::endl;
        return -1;
    }
    //获取当前的编码格式
    std::string strType = mysql_character_set_name(mysql);
    std::cout << "defalut 编码格式为 is: " << strType <<std::endl;
    //设置字符集utf8
    mysql_set_character_set(mysql, "utf8");
    std::cout << "设置编码格式为 utf8"  << std::endl;

    //3.创建表
    // do somethings
   

    //4.获取表的数据内容
    int MyQuery = mysql_real_query(mysql,"")


    mysql_close(&mysql);
	return 0;
}