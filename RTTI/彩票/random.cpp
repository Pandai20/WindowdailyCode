#pragma once
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

int cnumber = 0;
int pdimax = 0;
int pdCmax = 0;
void showlist(vector<int>example)
{
    std::cout << "������";
    for (unsigned int d = 0; d < example.size(); d++)
    {
        std::cout << example[d] << " ";
    }
    std::cout << endl;
}

//��ȡ�����
int Random(int a, int b)
{
    int c = (rand() % (b - a)) + a;
    return c;
}
//����Ƿ�������Ԫ��
int chack(vector<int>& example)
{
    int read = 0;
    while (true)
    {
        sort(example.begin(), example.end());
        vector<int>::iterator it = unique(example.begin(), example.end());
        if (it != example.end())
        {
            std::cout << "T:" << *it << endl;
            example.erase(it, example.end());

        }
        else
        {
            read = 1;
            break;
        }

    }
    cnumber = example.size();
    std::cout << "1--cnumber��ֵΪ��" << cnumber << endl;
    showlist(example);
    std::cout << "����Ѿ���ɣ��Թ����ظ�����" << endl;
    std::cout << "size:" << example.size() << endl;
    return read;
}
//����Ԫ��Ϊ20�����һ�����ͬ
void Checkanswer(vector<int>& example, int number)
{
    int finish = 0;
    while (1)
    {
        finish = chack(example);
        std::cout << "finish��ֵΪ��" << finish << endl;
        std::cout << "cnumber��ֵΪ��ֵΪ��" << cnumber << endl;
        if (cnumber != number)
        {
            for (;;)
            {
                int huge = Random(1, 80);
                example.push_back(huge);
                cnumber++;
                if (cnumber == number)
                    break;
            }
        }
        finish = chack(example);
        if (finish == 1 && cnumber == number)
            break;
    }
    std::cout << "cnumber��ֵΪ��" << cnumber << endl;
}

void D_value_3(vector<int>& example)
{
    int count = 0;
    vector<int>stilnum;
    for (int i = 0; i < 9; i++)
    {
        if ((example[i + 1] - example[i]) <= 3)
        {
            stilnum.push_back(i);
            count++;
        }
    }
    std::cout << "++++++++++Ԫ�������ڲ�С��3��Ԫ���±�Ϊ��";
    showlist(stilnum);
    std::cout << endl;
    std::cout << "stilnum�Ĵ�СΪ" << stilnum.size() << endl;
    if (count > 2)
    {
        for (int i = 1; i < count; i++)
        {
            int host = Random(0, stilnum.size() - 1);
            example.erase(example.begin() + stilnum[host]);
            cnumber--;
        }
        std::cout << "��������������������������������Cnumber��ֵ��" << cnumber << endl;
    }
    showlist(example);

}


//��Ԫ�ؽ���ɾ��
void oooooooooooooo(vector<int>& example)
{
    int Ret = 0;
    int hostnumber0 = 0;
    int hostnumber1 = 0;
    int hostnumber2 = 0;
    int hostnumber3 = 0;
    int hostnumber4 = 0;
    int hostnumber5 = 0;
    int hostnumber6 = 0;
    int hostnumber7 = 0;
    int hostnumber8 = 0;
    vector<int>host[9];
    cout << "000--cnumber" << cnumber << endl;
    do
    {
        if (cnumber != 10)
        {
            Checkanswer(example, 10);
        }
        for (int i = 0; i < 10; i++)
        {
            int a = (example[i] / 10);
            std::cout << "____a:" << a << endl;
            switch (a)
            {
            case 0:
                hostnumber0++;
                host[a].push_back(i);
                break;
            case 1:
                hostnumber1++;
                host[a].push_back(i);
                break;
            case 2:
                hostnumber2++;
                host[a].push_back(i);
                break;
            case 3:
                hostnumber3++;
                host[a].push_back(i);
                break;
            case 4:
                hostnumber4++;
                host[a].push_back(i);
                break;
            case 5:
                hostnumber5++;
                host[a].push_back(i);
                break;
            case 6:
                hostnumber6++;
                host[a].push_back(i);
                break;
            case 7:
                hostnumber7++;
                host[a].push_back(i);
            }
            /*if (example[i] == 80)
            {
                example.erase(example.begin() + i);
                cnumber--;
                break;

            }*/
        }
        for (int c = 0; c < 8; c++)
        {
            if (host[c].size() >= 2)
            {
                cout << "+++++++++c>2+++++++++" << endl;
                cout << "��ͬʮλ�ĸ�����" << host[c].size() << endl;
                if (host[c].size() >= pdimax)
                {
                    pdimax = host[c].size();
                    pdCmax = c;
                }
                cout << "��Ӧ��ʮλ�ǣ�" << c << endl;
                for (int i = 0; i < host[c].size() - 1; i++)
                {

                    int a = Random(0, host[c].size() - 1);
                    cout << "a��ֵ��" << a << endl;
                    cout << "host[c][a]��" << host[c][a] << endl;
                    Ret = host[c][a];
                    cout << "exapple.host[c][a]��" << example[Ret + 1] << endl;
                    while (1)
                    {
                        int a = Random(0, host[c].size() - 1);
                        Ret = host[c][a];
                        cout << "��������example[Ret + 1]��" << example[Ret + 1] << endl;
                        if (example[Ret + 1] != 99)
                        {
                            example[Ret + 1] = 99;
                            break;
                        }

                    }
                    //example.erase(example.begin() + ((host[c][a])));//�ж����ֵ�ǲ�������Ժ�������ֵ�����һ����Խ��
                    example[Ret + 1] = 99;

                    showlist(example);
                }
                cout << "+++++++++c>2+++++++++" << endl;

            }
            Ret = 0;
            if (host[c].size() == 0)
            {
                cout << "û�д棺" << host[c].size() << endl;
                cout << "c��ֵ��" << c << endl;
                if (c != 0)
                {
                    cout << "***********c!=0*************" << endl;
                    int b = Random((c * 10), ((c * 10) + 9));
                    cout << "b��ֵ��" << b << endl;
                    example.push_back(b);
                    showlist(example);

                    cnumber++;
                    cout << "***********c!=0*************" << endl;
                }
                else
                {
                    cout << "__________c=0___________" << endl;
                    int b = Random(1, 9);
                    cout << "b��ֵ��" << b << endl;
                    example.push_back(b);
                    showlist(example);
                    cnumber++;
                    cout << "__________c=0___________" << endl;
                }
            }
        }


    } while (false);

    std::cout << "�����ÿ���������ѡ" << endl;
    cout << "+++++cnumber:" << cnumber << endl;
    //������8����
    sort(example.begin(), example.end());
    std::cout << "+++++++++++++++++++++++++++++���Ͻ����ȷ+++++++++++++++++++++++++++++++" << endl;
    showlist(example);
    for (int i = 0; i < example.size(); i++)
    {
        if (example[i] == 99)
            example.erase(example.begin() + i, example.end());
    }
    showlist(example);
    cnumber = example.size();
    cout << "��������ʮλ��pdCmax��" << pdCmax << endl;
    vector<int>::iterator ret;
    if (pdCmax != 0)
    {
        do
        {
            int r = Random(pdCmax * 10, (pdCmax * 10 + 9));
            ret = std::find(example.begin(), example.end(), r);
            if (ret == example.end())
            {
                example.push_back(r);
                cnumber++;
            }

            else
                continue;
        } while (false);
    }
    else
    {
        do
        {
            int r = Random(1, 9);
            ret = std::find(example.begin(), example.end(), r);
            if (ret == example.end())
            {
                example.push_back(r);
                cnumber++;
            }
            else
                continue;
        } while (false);
    }
    std::cout << "+++++++++++++++++++++++++�õ�������9������+++++++++++++++++++++++++++++++" << endl;
    cnumber = example.size();
    sort(example.begin(), example.end());
    showlist(example);
}

void demo(vector<int>& example)
{

    for (int i = 0; i < 10; i++)
    {

        int a = Random(1, 80);
        cnumber++;
        example.push_back(a);
        std::cout << i << endl;
    }
    std::cout << "2--cnumber��ֵΪ��" << cnumber << endl;
    sort(example.begin(), example.end());

    showlist(example);
    //sort(panda.begin(),panda.end());
    Checkanswer(example, 10);//20������ͬ
    sort(example.begin(), example.end());
    showlist(example);

    std::cout << "������" << cnumber << endl << "++++++++++�Խ������ɸѡ++++++++++" << endl;
    D_value_3(example);
    oooooooooooooo(example);
    //��εõ�һ��������10�����֣�

    vector<int>::iterator it;
    do
    {
        int r = Random(1, 80);
        it = find(example.begin(), example.end(), r);
        if (it == example.end())
        {
            example.push_back(r);
            cnumber++;
            break;
        }
    } while (true);

    cout << "++++++++++����10����++++++++++" << endl;
    sort(example.begin(), example.end());
    showlist(example);


}
bool changelife(vector<int>& txt1, vector<int>& txt2)
{
    bool ret = true;
    vector<int>::iterator pofir;
    vector<int>::iterator posec;
    pofir = txt1.begin();
    posec = txt2.begin();
    for (; pofir != txt1.end(); )
    {
        if (*pofir == *posec)
            ret = false;
        pofir++;
        posec++;
    }
    return ret;
}