#include <ros/ros.h>
#include "MessageManager.h"
#include <string>

template<typename Message>
struct SignedMessage {
    int id;
    Message msg;
}

ros::Publisher publisher;
ros::Subscriber subscriber;

//template<typename Message>

void MessageManager::PublishSignedMessage(int id){
    publisher = ros_handle.advertise<uint8>("Oliver's Topic", 1, 10);
    publisher.publish(id);
}

template<typename Message>
Message MessageManager::GetMessage(int id, std::string topic){

}

