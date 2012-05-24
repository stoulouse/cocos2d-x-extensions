/*
 * CCNetwork  - simple way to get json object asynchronously.
 * 
 *
 * Customization of CCNetwork by Steve Kim by
 *
 * Jose Antonio Andujar Clavell, JanduSoft
 * http://www.jandusoft.com 
 * http://www.jandujar.com
 *
 * For details, visit the forum blog:
 * http://www.cocos2d-x.org/boards/6/topics/6944?r=11045#message-11045
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "CCNetwork.h"

using namespace cocos2d;

CCNetwork::CCNetwork()
{
    cJSONResult = NULL;
}

size_t CCNetwork::writer( char *data, size_t size, size_t nmemb, string *writerData )
{
    size_t retValue = 0;

    if(writerData != NULL)
    {
            writerData->append(data, size * nmemb);
            retValue = size * nmemb;
    }

    return retValue;
}

CCNetwork::~CCNetwork()
{
    if( cJSONResult != NULL ){
            freeResultJSON();
    }
}

void * CCNetwork::run( void *arg )
{
    CCNetwork *network = (CCNetwork *)arg;
    CURL *curl;
    CURLcode res;
    int result = 1;
    string buffer;

    network->cJSONResult = NULL;

    curl_global_init( CURL_GLOBAL_ALL );

    curl = curl_easy_init();

    if( curl )
    {
		curl_easy_setopt( curl, CURLOPT_URL, network->url.c_str() );
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, CCNetwork::writer );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &buffer );

        res = curl_easy_perform( curl );

        curl_easy_cleanup( curl );

        if (res == 0)
        {
            network->cJSONResult = cJSON_Parse( buffer.c_str() );

            if( network->cJSONResult != NULL )
                result = 0;
        }
    }

    ((network->target)->*(network->callback))();

    return (void *)result;
}

cJSON *CCNetwork::getResultJSON()
{
    int success;

    if( pthread_join( threadInfo, (void **)&success ) == 0 )
        return cJSONResult;
    else
        return NULL;
}

cJSON *CCNetwork::getResultJSONSynchronous()
{
    return cJSONResult;
}

void CCNetwork::freeResultJSON()
{
    if( cJSONResult != NULL )
    {
        cJSON_Delete( cJSONResult );
        cJSONResult = NULL;
    }
}

CCNetwork * CCNetwork::loadJSON( const char *url, CCObject *target, SEL_CallFunc callback )
{
    CCNetwork *network = new CCNetwork();

    if( network != NULL )
    {
        network->target = target;
        network->callback = callback;
		network->url = std::string(url);

        if( pthread_create( &network->threadInfo, NULL, CCNetwork::run, network ) == 0 )
        {
            network->autorelease();
            return network;
        }

        CC_SAFE_DELETE( network );
    }
    return NULL;
}

CCNetwork * CCNetwork::loadJSONSynchronous( const char *url)
{
    CCNetwork *network = new CCNetwork();

    if( network != NULL )
    {
		network->url = std::string(url);
		CURL *curl;
		CURLcode res;
		int result = 1;
		string buffer;

		network->cJSONResult = NULL;

		curl_global_init( CURL_GLOBAL_ALL );

		curl = curl_easy_init();

		if( curl )
		{
			curl_easy_setopt( curl, CURLOPT_URL, network->url.c_str() );
			curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L );
			curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, CCNetwork::writer );
			curl_easy_setopt( curl, CURLOPT_WRITEDATA, &buffer );

			res = curl_easy_perform( curl );

			curl_easy_cleanup( curl );

			if (res == 0)
			{
				network->cJSONResult = cJSON_Parse( buffer.c_str() );

				if( network->cJSONResult != NULL )
					result = 0;
			}
		}

        if( result == 0 )
        {
            network->autorelease();
            return network;
        }

        CC_SAFE_DELETE( network );
    }
    return NULL;
}