#ifndef __CC_MOSQUITO_CLIENT_H__
#define __CC_MOSQUITO_CLIENT_H__

//WARNING!!! cocos2dx\support\data_support\uthash.h needs a modification change on win32
// change     
//     typedef unsigned int uint32_t;
//          to        
//     #include "stdint.h"
	
#include "cocos2d.h"


class MosquittoClientDelegate
{
public:
	virtual void didConnect(int code){};
	virtual void didDisconnect(){};
	virtual void didPublish(int messageId){};

	virtual void didReceiveMessage(std::string message, std::string topic){};
	virtual void didSubscribe(int messageID, cocos2d::CCArray* grantedQos){};
	virtual void didUnsubscribe(int messageID){};
};

class CCMosquittoClient : public cocos2d::CCNode
{
	CC_SYNTHESIZE(std::string, host, host); 
	CC_SYNTHESIZE(unsigned short, port, port); 
	CC_SYNTHESIZE(std::string, username, username); 
	CC_SYNTHESIZE(std::string, password, password); 
	CC_SYNTHESIZE(unsigned short, keepAlive, keepAlive);
	CC_SYNTHESIZE(bool, cleanSession, cleanSession);
	CC_SYNTHESIZE(MosquittoClientDelegate*, delegateC, delegateC);

private:
	static bool initialized;
	struct mosquitto *mosq;

	CCMosquittoClient(std::string clientId);
public:
	static std::string version();

	virtual ~CCMosquittoClient();
    
    static CCMosquittoClient* initWithClientId(std::string clientId, MosquittoClientDelegate* caller);

	void setLogPriorities(int priorities, int destinations);
	void setMessageRetry(unsigned int seconds);
	void connect();
	void connectToHost(std::string host);
	void reconnect();
	void disconnect();

	void publishString(std::string payload, std::string topic, bool retain);

	void subscribe(std::string topic);
	void subscribe(std::string topic, int qos);
	void unsubscribe(std::string topic);


	// This is called automatically when connected
	void loop(cocos2d::ccTime mTime);
};

#endif  // __CC_MOSQUITO_CLIENT_H__