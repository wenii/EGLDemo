//
// Created by Administrator on 2017/7/20.
//

#include "MessageQueue.h"
#include "unistd.h"

using namespace EGLDemo;
Message::Message(int type) :
    Type(type)
{
}


bool Message::GetParam(int key, int& param) const
{
    return Param.GetValue(key, param);
}

void Message::SetParam(int key, const int& param)
{
    Param.SetValue(key, param);
}

bool Message::GetParam(int key, float& param) const
{
    return Param.GetValue(key, param);
}

void Message::SetParam(int key, const float& param)
{
    Param.SetValue(key, param);
}

bool Message::GetParam(int key, void*& param) const
{
    return Param.GetValue(key, param);
}

void Message::SetParam(int key, const void* param)
{
    Param.SetValue(key, param);
}


//-------------------------------------------------------------------------
MessageQueue::MessageQueue()
{
    Enable = true;
    pthread_mutex_init( &Mutex, NULL );
}

MessageQueue::~MessageQueue()
{
    pthread_mutex_destroy(&Mutex);
}

void MessageQueue::SetEnable(bool enable)
{
    pthread_mutex_lock(&Mutex);
    Enable = enable;
    pthread_mutex_unlock(&Mutex);
}

void MessageQueue::PostMessage(const Message& message)
{
    pthread_mutex_lock(&Mutex);
    if(!Enable)
    {
        pthread_mutex_unlock(&Mutex);
        return;
    }
    Messages.push(message);
    pthread_mutex_unlock(&Mutex);
}

bool MessageQueue::GetNextMessage(Message& msg)
{
    pthread_mutex_lock(&Mutex);
    if(!Messages.empty())
    {
        msg = Messages.front();
        Messages.pop();
        pthread_mutex_unlock(&Mutex);
        return true;
    }
    pthread_mutex_unlock(&Mutex);
    return false;

}



