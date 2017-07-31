//
// Created by Administrator on 2017/7/26.
//

#ifndef EGLDEMO_DYNAMICARRAY_H
#define EGLDEMO_DYNAMICARRAY_H

#include <map>


class DynamicArray
{
public:
    DynamicArray();

    bool GetValue(int key, int& value) const;
    void SetValue(int key, const int& value);

    bool GetValue(int key, float& value) const;
    void SetValue(int key, const float& value);

    bool GetValue(int key, void*& value) const;
    void SetValue(int key, const void* value);

private:
    std::map<int, int> intMap;
    std::map<int, float> floatMap;
    std::map<int, long long > voidPtrMap;
};



#endif //EGLDEMO_DYNAMICARRAY_H
