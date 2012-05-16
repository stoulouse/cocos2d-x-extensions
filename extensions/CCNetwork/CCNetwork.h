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

#ifndef __CCNETWORK_H__
#define __CCNETWORK_H__

#include "cocos2d.h" 
#include "stdio.h" 
#include "stdlib.h" 
#include "curl/curl.h" 
#include "pthread/pthread.h" 
#include "CCNetwork/cJSON.h" 


class CCNetwork : public cocos2d::CCObject {
		cocos2d::SEL_CallFunc callback;
		cocos2d::CCObject *target;
		pthread_t threadInfo;
		std::string url;
		cJSON *cJSONResult;

		CCNetwork();
	protected:
		static size_t writer( char *data, size_t size, size_t nmemb, string *writerData );
	public:
		virtual ~CCNetwork();

		static void *run( void *arg );

		cJSON *getResultJSON();
		void freeResultJSON();

		static CCNetwork *loadJSON( const char *url, cocos2d::CCObject *target, cocos2d::SEL_CallFunc callback );
};

#endif