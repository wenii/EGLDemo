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
    MESSAGE_ON_ACTIVITY_STOP
};

enum enMsgParamKey
{
    MSG_CONTENT_ANATIVEWINDOW,
    MSG_CONTENT_SURFACE_WIDTH,
    MSG_CONTENT_SURFACE_HEIGHT
};




class Message
{
public:
    Message(){};
    Message(int type);

public:
    int  GetType(){return Type;}

    bool GetParam(int key, int& param) const;
    void SetParam(int key, const int& param);

    bool GetParam(int key, float& param) const;
    void SetParam(int key, const float& param);

    bool GetParam(int key, void*& param) const;
    void SetParam(int key, const void* param);


private:
	int			            Type;
	DynamicArray            Param;

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
	std::queue<Message>      Messages;
	pthread_mutex_t		     Mutex;
	volatile bool            Enable;

};



#endif //EGLDEMO_MESSAGEQUEUE_H
