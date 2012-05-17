#include "libmosquito/mosquitto.h"

#include "CCMosquittoClient.h"
#include <sstream>
USING_NS_CC;

bool CCMosquittoClient::initialized = false;

static void on_connect(void *ptr, int rc)
{
    CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		client->getdelegateC()->didConnect(rc);
	}
}

static void on_disconnect(void *ptr)
{
    CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		client->getdelegateC()->didDisconnect();
	}
}

static void on_publish(void *ptr, uint16_t message_id)
{
	CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		client->getdelegateC()->didPublish(message_id);
	}
}

static void on_message(void *ptr, const struct mosquitto_message *message)
{
    CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		std::string topic(message->topic);
		std::string payload((char*)message->payload, message->payloadlen);
		client->getdelegateC()->didReceiveMessage(payload, topic);
	}
}

static void on_subscribe(void *ptr, uint16_t message_id, int qos_count, const uint8_t *granted_qos)
{
	CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		//TODO: implement this
		client->getdelegateC()->didSubscribe(message_id, NULL);
	}
}

static void on_unsubscribe(void *ptr, uint16_t message_id)
{
	CCMosquittoClient* client = (CCMosquittoClient*)ptr;
	if(client->getdelegateC()!=NULL){
		//TODO: implement this
		client->getdelegateC()->didUnsubscribe(message_id);
	}
}


CCMosquittoClient::CCMosquittoClient(std::string clientId){
	if(!CCMosquittoClient::initialized){
		mosquitto_lib_init();
		CCMosquittoClient::initialized=true;
	}

	mosq = mosquitto_new(clientId.c_str(), this);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_publish_callback_set(mosq, on_publish);
    mosquitto_message_callback_set(mosq, on_message);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_unsubscribe_callback_set(mosq, on_unsubscribe);
}

std::string CCMosquittoClient::version() {
    int major, minor, revision;
	std::stringstream out;

    mosquitto_lib_version(&major, &minor, &revision);

	out<<major<<"."<<minor<<"."<<revision;

	return out.str();
}

CCMosquittoClient::~CCMosquittoClient(){
	if (mosq) {
        mosquitto_destroy(mosq);
        mosq = NULL;
    }

	this->unscheduleAllSelectors();

	//[super dealloc]
}

CCMosquittoClient* CCMosquittoClient::initWithClientId(std::string clientId, MosquittoClientDelegate* caller){
	CCMosquittoClient* salida = new CCMosquittoClient(clientId);
	salida->setdelegateC(caller);
	salida->sethost(std::string(""));
	salida->setport(1883);
	salida->setkeepAlive(30);
	salida->setcleanSession(true);
	
	return salida;
}

void CCMosquittoClient::setLogPriorities(int priorities, int destinations){
	mosquitto_log_init(mosq, priorities, destinations);
}

void CCMosquittoClient::connect(){
	//std::string host = gethost();
	char *cstrHost=(char*)malloc(gethost().size());
	strcpy(cstrHost, gethost().c_str());
    //const char *cstrHost = gethost().c_str();
    const char *cstrUsername = NULL, *cstrPassword = NULL;

    if (getusername() != "")
		cstrUsername = getusername().c_str();

    if (getpassword() != "")
        cstrPassword = getpassword().c_str();

    // FIXME: check for errors
	mosquitto_username_pw_set(mosq, cstrUsername, cstrPassword);

    mosquitto_connect(mosq, cstrHost, port, keepAlive, cleanSession);

    // Setup timer to handle network events
    // FIXME: better way to do this - hook into iOS Run Loop select() ?
    // or run in seperate thread?
	this->schedule(schedule_selector(CCMosquittoClient::loop),0.01);
    
}

void CCMosquittoClient::loop(cocos2d::ccTime mTime){
	mosquitto_loop(mosq, 0);
}

void CCMosquittoClient::connectToHost(std::string host) {
	sethost(host);
	connect();
}

void CCMosquittoClient::reconnect() {
    mosquitto_reconnect(mosq);
}

void CCMosquittoClient::disconnect() {
    mosquitto_disconnect(mosq);
}

// FIXME: add QoS parameter?
void CCMosquittoClient::publishString(std::string payload, std::string topic, bool retain){
	mosquitto_publish(mosq, NULL, topic.c_str(), payload.size(), (const uint8_t*)payload.c_str(), 0, retain);
}

void CCMosquittoClient::subscribe(std::string topic){
	subscribe(topic, 0);
}

void CCMosquittoClient::subscribe(std::string topic, int qos){
	mosquitto_subscribe(mosq, NULL, topic.c_str(), qos);
}

void CCMosquittoClient::unsubscribe(std::string topic){
	mosquitto_unsubscribe(mosq, NULL, topic.c_str());
}

void CCMosquittoClient::setMessageRetry(unsigned int seconds){
    mosquitto_message_retry_set(mosq, seconds);
}
