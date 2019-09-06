#include "BLEDevice.h"
#include <M5Stack.h>
#include <string.h>
#include "NoraBLE.h"

CNoraBLE noraBLE;
static bool scan_end = false;

// BLEスキャン成功時のコールバック
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks{
  void onResult(BLEAdvertisedDevice advertisedDevice){
    int num = 0;  
      
    // 野良バッジを検出したらLEDデバイスとして1件クラスに追加する
    if(strcmp(advertisedDevice.getName().c_str(), BLE_DEVICE_NAME) == 0){
      num = noraBLE.AddDevice(advertisedDevice);
      M5.Lcd.printf("LED [%d] %s\n", num, advertisedDevice.getAddress().toString().c_str());
      if(num >= DEVICENUM_MAX){
        advertisedDevice.getScan()->stop();
      }
    }
  }
};

void setup(){
  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Start Application...\n Please Wait 30sec\n");

  // BLE init
  BLEDevice::init("");
  // 30秒間Scan
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);
}

void loop() {
  M5.update();
  if(scan_end == false){
    M5.Lcd.println("LED Scan End!!\n");
    scan_end = true;    
  }
  if (M5.BtnA.wasReleased()) {  // 
    M5.Lcd.println("Press A");
    noraBLE.SetSpeed(3);
    noraBLE.SetMode(0);
    noraBLE.SetString("おはよう");
    noraBLE.WriteBLE(0);
  } else if (M5.BtnB.wasReleased()) {
    M5.Lcd.println("Press B");
    noraBLE.SetSpeed(7);
    noraBLE.SetMode(1);
    noraBLE.SetString("こんにちは");
    noraBLE.WriteBLE(0);
  } else if (M5.BtnC.wasReleased()) {
    M5.Lcd.println("Press C");
    noraBLE.SetSpeed(6);
    noraBLE.SetMode(4);
    noraBLE.SetString("イイネ！");
    noraBLE.WriteBLE(0);
  }
}
