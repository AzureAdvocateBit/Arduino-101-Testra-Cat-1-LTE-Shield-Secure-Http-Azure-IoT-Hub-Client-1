#ifndef AzureIotHub_h
#define AzureIotHub_h

#include "Arduino.h"
#include "sha256.h"
#include "Base64.h"
//#include <WiFiClientSecure.h>
//#include <ESP8266WiFi.h>
#include <TimeLib.h> // http://playground.arduino.cc/code/time - installed via library manager
#include "connection4g.h"

#define RequestBufferLength 511

class AzureIotHub
{

public:
  AzureIotHub(Connection4G *conn, const char *cs, const char *route);
  String send(String json);
  int sendBegin(int length);
  int sendData(String data);
  int sendData(const char *data, int length);
  int sendData(char *data);
  String sendEnd();

  String requestDeviceBoundMessage();

  time_t sasExpiryPeriodInSeconds = 5 * 60;
  // const char *certificateFingerprint;

protected:
private:
  const char *host;
  char *key;
  const char *deviceId;
  const char *routeId;

  String sasUrl;
  String endPoint;
  String deviceBoundEndPoint;

  const char *fullSas;
  time_t sasExpiryTime = 0;

  void setConnectionString(String cs);

  void initialiseHub();
  int connectToAzure();
  int tcpWrite(char *data, uint16_t length);

  String createSas(char *key, String url);
  bool renewSas();

  void initialiseAzure();
  
  String buildHttpRequest(int length);
  String buildDeviceBoundHttpRequest();
  

  bool azureInitialised = false;
  bool connected4G = false;
  Connection4G *conn;

  char requestBuffer[RequestBufferLength + 1];

  const char *TARGET_URL = "/devices/";
  const char *IOT_HUB_END_POINT = "/messages/events?api-version=2016-11-14";
  const char *IOT_HUB_DEVICE_BOUND = "/messages/devicebound?api-version=2016-11-14";

  String splitStringByIndex(String data, char separator, int index);
  String urlEncode(const char *msg);
  const char *GetStringValue(String value);
};

#endif
