#include<iostream>
#include <fstream>
using namespace std;

int main()
{

    //ʹ��fstreamд����

    std::string strFilePath="F:\\share\\allProgram\\WindowdailyCode\\fuckyou\\name.text";
    cout << "666666" << strFilePath << endl;

    fstream fp;
    fp.open(strFilePath, std::ios_base::out);
    if (fp.is_open())
    {
        std::string text = "��ֻ��һ������";
        fp.write(text.data(), text.size());
        cout << "77777" << strFilePath << endl;;
    }
    cout << "8888" << strFilePath << endl;;
}