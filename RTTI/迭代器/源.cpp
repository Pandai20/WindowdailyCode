#include <iostream>
#include <vector>
#include <map>
class MyClass
{
public:
    MyClass();
    ~MyClass();

:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}


using namespace std;
// ����һ���������ҵ�����Ԫ�صĺ͵���Ŀ��ֵ�����������ǵ�����
std::pair<int, int> findTwoSum(const std::vector<int>& nums, int target) {
    std::map<int, int> numToIndex;
    std::pair<int, int> result;

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        // ���һ���ֵ�Ƿ��Ѿ���ӳ����
        std::map<int, int>::iterator it = numToIndex.find(complement);

        if (it != numToIndex.end()) {
            result.first = it->second;
            result.second = i;
            break;
        }

        // ����ǰԪ����ӵ�ӳ��
        numToIndex[nums[i]] = i;
    }

    return result;
}

int main() {
    std::vector<int> nums;
    cout << "vector capacity :" << nums.capacity() << endl;
    cout << "vector size :" << nums.size() << endl;
    nums.push_back(2);
    cout << "vector capacity :" << nums.capacity() << endl;
    cout << "vector size :" << nums.size() << endl;
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);
    cout << "vector capacity :" << nums.capacity() << endl;

    int target = 9;
    std::pair<int, int> result = findTwoSum(nums, target);

    std::cout << "Indices: " << result.first << " " << result.second << std::endl;
    return 0;
}
