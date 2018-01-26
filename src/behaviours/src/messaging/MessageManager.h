#include <ros/ros.h>
#include "MessageManager.cpp"
#include <string>

template<typename Message>
struct SignedMessage;

//template<typename Message>
void PublishSignedMessage(int id);

template<typename Message>
Message GetMessage(int id, std::string topic);