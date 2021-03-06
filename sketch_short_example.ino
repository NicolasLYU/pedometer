// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
const g = 9.8;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float Ax,Ay,Az,Gx,Gy,Gz;
float Vx,Vy,Vz;
float angleRoll,anglePitch;
unsigned long time_current, time_last;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  angleRoll = acos(sqrt(AcX*AcX+AcZ*AcZ)/g);
  anglePitch = acos(sqrt(AcY*AcY+AcZ*AcZ)/g);
  Vx=0;
  Vy=0;
  Vz=0;
  time_current = 0;
  time_last = 0;
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);

  Ax=2*9.8*(AcX-700)/32768;   //700
  Ay=2*9.8*(AcY-400)/32768;    //400
  Az=2*9.8*(AcZ+2400)/32768;    //-2400
  time_current = millis();
  Vx=Vx + Ax*0.001*(time_current - time_last);
  Vy=Vy + Ay*0.001*(time_current - time_last);
  Vz=Vz + Az*0.001*(time_current - time_last);
  time_last = time_current;
  Gx=250*GyX/32768;
  Gy=250*GyY/32768;
  Gz=250*GyZ/32768;
  Serial.print("Ax = "); Serial.print(Ax); Serial.print("m/s-2");
  Serial.print(" | Ay = "); Serial.print(Ay); Serial.print("m/s-2");
  Serial.print(" | Az = "); Serial.print(Az); Serial.print("m/s-2");
  Serial.print(" | Gx = "); Serial.print(Gx); Serial.print("rad/s");
  Serial.print(" | Gy = "); Serial.print(Gy); Serial.print("rad/s");
  Serial.print(" | Gz = "); Serial.print(Gz); Serial.print("rad/s");
  Serial.print(" |Vx = "); Serial.print(Vx); Serial.print("m/s");
  Serial.print(" | Vy = "); Serial.print(Vy); Serial.print("m/s");
  Serial.print(" | Vz = "); Serial.print(Vz); Serial.print("m/s");
  Serial.println("---------------------");
  delay(333);
}

