#include <vector>
#include<iostream>
using namespace std;

int Sqsort(vector<int>& Sqlist, int left, int right) 
{
    int key = Sqlist[left];
    while (left < right)
    {
        while (left < right && Sqlist[right] >= key)
            right--;
        swap(Sqlist[left], Sqlist[right]);
        while (left < right && Sqlist[left] <= key)
            left++;
        swap(Sqlist[left], Sqlist[right]);
    }
    return left;
};

void q_sort(vector<int>& arr, int left, int right) {

    if (left >= right)
        return;
    int key = Sqsort(arr, left, right);
    q_sort(arr, left, key);
    q_sort(arr, key+1, right);

}

int main()
{
    vector<int> Sqlist = {1,5,4,9,8,4};
    int high = Sqlist.size() - 1;
    q_sort(Sqlist, 0, high);
    for (int i = 0; i < Sqlist.size(); i++)
    {
        cout<< Sqlist[i]<<" ";
    }
    return 0;
}