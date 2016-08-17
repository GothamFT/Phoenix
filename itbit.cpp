
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include "base64.h"
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <jansson.h>
#include "itbit.h"
#include "curl_fun.h"
  
namespace ItBit {

double getQuote(CURL *curl, bool isBid) {
  json_t *root = getJsonFromUrl(curl, "https://api.itbit.com/v1/markets/XBTUSD/ticker", "");
  const char *quote;
  double quoteValue;
  if (isBid) {
    quote = json_string_value(json_object_get(root, "bid"));  
  } else {
    quote = json_string_value(json_object_get(root, "ask")); 
  }
  if (quote != NULL) {
    quoteValue = atof(quote);
  } else {
    quoteValue = 0.0;
  }
  json_decref(root);
  return quoteValue;
}


double getAvail(CURL *curl, Parameters params, std::string currency) {
  // TODOfaf
  
  return 0.0;
}
json_t* authRequest(CURL *curl, Parameters params, std::string url, std::string options) {
  // get milliseconds since epoch
  struct timeval tv;
  gettimeofday(&tv, NULL);

  unsigned long long millisecondsSinceEpoch =(unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
  std::cout<<"EPOCH SECONDS: " <<millisecondsSinceEpoch<<endl;
  // nonce 		
  std::string nonce = std::to_string(millisecondsSinceEpoch + 0.5);
  std::string epochTime = std::to_string(millisecondsSinceEpoch);
  
  json_t *req_array(void);
  
  if(options == "GET") {
    string request[5] = {options,url,"",nonce,epochTime}
  }
  else if(options == "POST") {
    string	
  }
  for(int = 0; i < 5; i++) {
	json_t *json_string(static_cast<char *>request[i]);
	
    req_array.append(json_string);
	}
	cout<<"JSON ARRAY: "<<req_array<<endl;	
   
  
  // Using sha256 hash engine
  unsigned char* digest;
  digest = HMAC(EVP_sha1(), key, strlen(array), (unsigned char*)array, strlen(array), NULL, NULL);    
  digest = HMAC(EVP_sha256(),);

  char mdString[SHA256_DIGEST_LENGTH+100];  // FIXME +100
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    sprintf(&mdString[i*2], "%02X", (unsigned int)digest[i]);
  }

  oss.clear();
  oss.str("");

  oss << "key=" << params.bitstampApi << "&signature=" << mdString << "&nonce=" << nonce << "&" << options;
  std::string postParams = oss.str().c_str();

  CURLcode resCurl;  // cURL request
  // curl = curl_easy_init();
  if (curl) {
    std::string readBuffer;
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_POST,1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    resCurl = curl_easy_perform(curl);
    json_t *root;
    json_error_t error;

    while (resCurl != CURLE_OK) {
      std::cout << "<Bitstamp> Error with cURL. Retry in 2 sec...\n" << std::endl;
      sleep(2.0);
      readBuffer = "";
      resCurl = curl_easy_perform(curl);
    }
    root = json_loads(readBuffer.c_str(), 0, &error);

    while (!root) {
      std::cout << "<Bitstamp> Error with JSON in authRequest:\n" << "Error: : " << error.text << ".  Retrying..." << std::endl;
      readBuffer = "";
      resCurl = curl_easy_perform(curl);
      while (resCurl != CURLE_OK) {
        std::cout << "<Bitstamp> Error with cURL. Retry in 2 sec...\n" << std::endl;
        sleep(2.0);
        readBuffer = "";
        resCurl = curl_easy_perform(curl);
      }
      root = json_loads(readBuffer.c_str(), 0, &error);
    }
    curl_easy_reset(curl);
    return root;
  }
  else {
    std::cout << "<Bitstamp> Error with cURL init." << std::endl;
    return NULL;
  }
}
  
double getActivePos(CURL *curl, Parameters params) {
  // TODO
  return 0.0;
}

double getLimitPrice(CURL *curl, double volume, bool isBid) {
  // TODO
  return 0.0;
}

}
