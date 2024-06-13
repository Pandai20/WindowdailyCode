#include "random.cpp"

//目录
void show_cataloguelist()
{
    cout << "                Welcome to my world" << endl << endl;
    cout << "1.Quit system" << endl;
    cout << "2.View history" << endl;
    cout << "3.Get your lucky numbers" << endl;
    cout << "4.Base pair analysis function" << endl;

}
bool is_number(string str)
{
    string::iterator it = str.begin();
    if (*it == '0' && str.length() > 1)
    {
        cout << "输入错误，非数字" << endl;
        Sleep(1000);
        return 0;
    }

    for (; it < str.end(); it++)
    {
        if (*it < '0' || *it > '9')
        {
            cout << "输入错误，非数字" << endl;
            Sleep(1000);
            return 0;
        }
    }
    cout << "输入数字为：" << str << endl;
    return 1;
}

int main()
{
    string push_num;
    int ret = true;
    char in_put;
    int change_intputnum;
    while (1)
    {
        show_cataloguelist();
        cin >> push_num;
        ret = is_number(push_num);
        if (0 == ret)
        {
            cout << "put error" << endl;
            system("cls");

            continue;
        }

        change_intputnum = atoi(push_num.c_str());
        switch (change_intputnum)
        {
        case 1:
            return 0;
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;

        default:

            break;
        }


        /*    switch ((int)push_num)
            {
            default:
                break;
            }*/

    }