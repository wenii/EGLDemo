//
// Created by Administrator on 2017/7/20.
//
#include "Math.h"
namespace EGLDemo
{

DynamicArray::DynamicArray()
{
}

bool DynamicArray::GetValue(int key, int& value)    const
{
    std::map<int, int>::const_iterator it = intMap.find(key);
    if(it != intMap.end())
    {
        value = it->second;
        return true;
    }
    return false;
}

void DynamicArray::SetValue(int key, const int& value)
{
    intMap[key] = value;
}

bool DynamicArray::GetValue(int key, float& value)  const
{
    std::map<int, float>::const_iterator it = floatMap.find(key);
    if(it != floatMap.end())
    {
        value = it->second;
        return true;
    }
    return false;
}

void DynamicArray::SetValue(int key, const float& value)
{
    floatMap[key] = value;
}

bool DynamicArray::GetValue(int key, void*& value)  const
{
    std::map<int, long long >::const_iterator it = voidPtrMap.find(key);
    if(it != voidPtrMap.end())
    {
        value = *(void **)&(it->second);
        return true;
    }
    return false;
}
void DynamicArray::SetValue(int key, const void* value)
{
    *(void **)&voidPtrMap[key] = const_cast<void*>(value);
}

}   //namespace EGLDemo