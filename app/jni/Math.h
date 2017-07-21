//
// Created by Administrator on 2017/7/20.
//

#ifndef EGLDEMO_MATH_H
#define EGLDEMO_MATH_H

#include <map>

namespace EGLDemo
{


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






}   //namespace EGLDemo







#endif //EGLDEMO_MATH_H
