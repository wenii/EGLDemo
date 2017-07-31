//
// Created by Administrator on 2017/7/20.
//

#ifndef EGLDEMO_MESSAGEQUEUE_H
#define EGLDEMO_MESSAGEQUEUE_H
#include <queue>
#include <pthread.h>
#include "DynamicArray.h"

enum enMsgType
{
    MESSAGE_ON_SURFACE_CHANGED,
    MESSAGE_ON_SURFACE_DESTROY,
    MESSAGE_ON_ACTIVITY_DESTROY,
    MESSAGE_ON_ACTIVITY_PAUSE,
    MESSAGE_ON_ACTIVITY_STOP,
    MESSAGE_ON_GESTURE_SCROLL,
    MESSAGE_ON_GESTURE_ZOOM
};

enum enMsgParamKey
{
    MSG_CONTENT_ANATIVEWINDOW,
    MSG_CONTENT_SURFACE_WIDTH,
    MSG_CONTENT_SURFACE_HEIGHT,
    MSG_CONTENT_GESTURE_BEGIN_X,
    MSG_CONTENT_GESTURE_BEGIN_Y,
    MSG_CONTENT_GESTURE_END_X,
    MSG_CONTENT_GESTURE_END_Y,
    MSG_CONTENT_GESTURE_DISTANCE_X,
    MSG_CONTENT_GESTURE_DISTANCE_Y,
    MSG_CONTENT_GESTURE_ZOOM_OLD_DISTANCE,
    MSG_CONTENT_GESTURE_ZOOM_NEW_DISTANCE
};




class Message
{
public:
    Message(){};
    Message(int type);

public:
    int  GetType() const {return m_type;}

    bool GetParam(int key, int& param) const;
    void SetParam(int key, const int& param);

    bool GetParam(int key, float& param) const;
    void SetParam(int key, const float& param);

    bool GetParam(int key, void*& param) const;
    void SetParam(int key, const void* param);


private:
	int			            m_type;
	DynamicArray            m_param;

};

class MessageQueue
{
public:
    MessageQueue();
    ~MessageQueue();

    void PostMessage(const Message& message);
    bool GetNextMessage(Message& msg);

    void SetEnable(bool enable);

private:
	std::queue<Message>      m_messages;
	pthread_mutex_t		     m_mutex;
	volatile bool            m_enable;

};



#endif //EGLDEMO_MESSAGEQUEUE_H
