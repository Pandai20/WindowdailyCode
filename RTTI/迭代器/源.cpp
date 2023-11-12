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
// 定义一个函数，找到两个元素的和等于目标值，并返回它们的索引
std::pair<int, int> findTwoSum(const std::vector<int>& nums, int target) {
    std::map<int, int> numToIndex;
    std::pair<int, int> result;

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        // 查找互补值是否已经在映射中
        std::map<int, int>::iterator it = numToIndex.find(complement);

        if (it != numToIndex.end()) {
            result.first = it->second;
            result.second = i;
            break;
        }

        // 将当前元素添加到映射
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
