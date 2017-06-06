//Adaptation of example found here: https://playground.arduino.cc/Main/MPU-6050
#include<Wire.h>

const int MPU_6050_addr = 0x68;  // I2C address of the MPU-6050
int16_t acceleration_X, acceleration_Y, acceleration_Z, temperature, Gyro_X, Gyro_Y, Gyro_Z;

void setup(){
    Wire.begin();
    Wire.beginTransmission(MPU_6050_addr);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // wake up 6050
    Wire.endTransmission(true);
    Serial.begin(9600);
}

void read_and_print(){
    acceleration_X = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
    acceleration_Y = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    acceleration_Z = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    Gyro_X = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    Gyro_Y = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    Gyro_Z = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    
    Serial.print("acceleration_X = "); Serial.print(acceleration_X);
    Serial.print(" | acceleration_Y = "); Serial.print(acceleration_Y);
    Serial.print(" | acceleration_Z = "); Serial.print(acceleration_Z);
    Serial.print(" | temperature = "); Serial.print(temperature/340.00+36.53);  //equation for temperature in degrees C from datasheet
    Serial.print(" | Gyro_X = "); Serial.print(Gyro_X);
    Serial.print(" | Gyro_Y = "); Serial.print(Gyro_Y);
    Serial.print(" | Gyro_Z = "); Serial.println(Gyro_Z);
}

void loop(){
    
    Wire.beginTransmission(MPU_6050_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    
    Wire.requestFrom(MPU_6050_addr, 14, true);  // request a total of 14 registers

    read_and_print();

    delay(1000);
}
