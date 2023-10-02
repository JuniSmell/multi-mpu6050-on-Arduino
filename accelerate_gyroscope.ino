/*
嘗試將accelerate_gyroscope_8的程式優化
*/


#include<Adafruit_MPU6050.h>
#include<Adafruit_Sensor.h>
#include<Wire.h>

Adafruit_MPU6050 mpu0;
Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;
Adafruit_MPU6050 mpu3;
Adafruit_MPU6050 mpu4;
Adafruit_MPU6050 mpu5;
Adafruit_MPU6050 mpu6;
Adafruit_MPU6050 mpu7;
Adafruit_MPU6050 mpu8;
Adafruit_MPU6050 mpu9;
Adafruit_MPU6050 mpu10;
Adafruit_MPU6050 mpu11;

void setup(){
    Serial.begin(9600);
    Wire.begin();

    Serial.println("Setting......");
    tcaSwitch(0x70, 0);
    tcaSwitch(0x71, 7);
    mpuSetup(&mpu0, 0x68);
    mpuSetup(&mpu1, 0x69);
    tcaSwitch(0x70, 1);
    mpuSetup(&mpu2, 0x68);
    mpuSetup(&mpu3, 0x69);
    tcaSwitch(0x70, 2);
    mpuSetup(&mpu4, 0x68);
    mpuSetup(&mpu5, 0x69);
    tcaSwitch(0x70, 3);
    mpuSetup(&mpu6, 0x68);
    mpuSetup(&mpu7, 0x69);
    tcaSwitch(0x70, 4);
    mpuSetup(&mpu8, 0x68);
    mpuSetup(&mpu9, 0x69);
    tcaSwitch(0x70, 7);
    tcaSwitch(0x71, 0);
    mpuSetup(&mpu10, 0x68);
    tcaSwitch(0x71, 1);
    mpuSetup(&mpu11, 0x68);
    Serial.print("Finish setting");
}

void loop(){
    sensors_event_t a_0, a_1, a_2, a_3, a_4, a_5, a_6, a_7, a_8, a_9, a_10, a_11;
    sensors_event_t g_0, g_1, g_2, g_3, g_4, g_5, g_6, g_7, g_8, g_9, g_10, g_11;
    sensors_event_t t_0, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9, t_10, t_11;

    tcaSwitch(0x70, 0);
    tcaSwitch(0x71, 7);
    mpu0.getEvent(&a_0, &g_0, &t_0);
    mpu1.getEvent(&a_1, &g_1, &t_1);
    tcaSwitch(0x70, 1);
    mpu2.getEvent(&a_2, &g_2, &t_2);
    mpu3.getEvent(&a_3, &g_3, &t_3);
    tcaSwitch(0x70, 2);
    mpu4.getEvent(&a_4, &g_4, &t_4);
    mpu5.getEvent(&a_5, &g_5, &t_5);
    tcaSwitch(0x70, 3);
    mpu6.getEvent(&a_6, &g_6, &t_6);
    mpu7.getEvent(&a_7, &g_7, &t_7);
    tcaSwitch(0x70, 4);
    mpu8.getEvent(&a_8, &g_8, &t_8);
    mpu9.getEvent(&a_9, &g_9, &t_9);
    tcaSwitch(0x70, 7);
    tcaSwitch(0x71, 0);
    mpu10.getEvent(&a_10, &g_10, &t_10);
    tcaSwitch(0x71, 1);
    mpu11.getEvent(&a_11, &g_11, &t_11);

    printAccGyo(&a_0, &g_0, &t_0);
    printAccGyo(&a_1, &g_1, &t_1);
    printAccGyo(&a_2, &g_2, &t_2);
    printAccGyo(&a_3, &g_3, &t_3);
    printAccGyo(&a_4, &g_4, &t_4);
    printAccGyo(&a_5, &g_5, &t_5);
    printAccGyo(&a_6, &g_6, &t_6);
    printAccGyo(&a_7, &g_7, &t_7);
    printAccGyo(&a_8, &g_8, &t_8);
    printAccGyo(&a_9, &g_9, &t_9);
    printAccGyo(&a_10, &g_10, &t_10);
    printAccGyo(&a_11, &g_11, &t_11); 
}

void tcaSwitch(int tca_num, uint8_t tca_slave){
    if(tca_slave > 7){
        return;
    }
    Wire.beginTransmission(tca_num);
    Wire.write(1 << tca_slave);
    Wire.endTransmission();
    return;
}

void mpuSetup(Adafruit_MPU6050 *mpu, uint8_t i2c_addr){
    if((mpu->begin(i2c_addr)) == false){  
    Serial.println("Failed to setup mpu");
    while(1){
        delay(10);
      }
   }
    mpu->setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu->setGyroRange(MPU6050_RANGE_250_DEG);
    mpu->setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void printAccGyo(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t){
    Serial.print(a->acceleration.x);
    Serial.print("\t");
    Serial.print(a->acceleration.y);
    Serial.print("\t");
    Serial.print(a->acceleration.z);
    Serial.print("\t");
    Serial.print(g->gyro.x);
    Serial.print("\t");
    Serial.print(g->gyro.y);
    Serial.print("\t");
    Serial.print(g->gyro.z);
    Serial.print("\t");
    Serial.println(t->temperature);
}