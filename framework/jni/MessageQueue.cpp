//
// Created by Administrator on 2017/7/20.
//

#include "MessageQueue.h"
#include "unistd.h"

Message::Message(int type) :
    m_type(type)
{
}


bool Message::GetParam(int key, int& param) const
{
    return m_param.GetValue(key, param);
}

void Message::SetParam(int key, const int& param)
{
    m_param.SetValue(key, param);
}

bool Message::GetParam(int key, float& param) const
{
    return m_param.GetValue(key, param);
}

void Message::SetParam(int key, const float& param)
{
    m_param.SetValue(key, param);
}

bool Message::GetParam(int key, void*& param) const
{
    return m_param.GetValue(key, param);
}

void Message::SetParam(int key, const void* param)
{
    m_param.SetValue(key, param);
}


//-------------------------------------------------------------------------
MessageQueue::MessageQueue() :
    m_enable(true)
{
    pthread_mutex_init( &m_mutex, NULL );
}

MessageQueue::~MessageQueue()
{
    pthread_mutex_destroy(&m_mutex);
}

void MessageQueue::SetEnable(bool enable)
{
    pthread_mutex_lock(&m_mutex);
    m_enable = enable;
    pthread_mutex_unlock(&m_mutex);
}

void MessageQueue::PostMessage(const Message& message)
{
    pthread_mutex_lock(&m_mutex);
    if(!m_enable)
    {
        pthread_mutex_unlock(&m_mutex);
        return;
    }
    m_messages.push(message);
    pthread_mutex_unlock(&m_mutex);
}

bool MessageQueue::GetNextMessage(Message& msg)
{
    pthread_mutex_lock(&m_mutex);
    if(!m_messages.empty())
    {
        msg = m_messages.front();
        m_messages.pop();
        pthread_mutex_unlock(&m_mutex);
        return true;
    }
    pthread_mutex_unlock(&m_mutex);
    return false;

}



