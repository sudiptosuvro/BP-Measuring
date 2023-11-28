#include <mbed.h>
#include <string.h>
#include <USBSerial.h>

USBSerial serial;
I2C i2c(PB_7, PB_6);

const int add_write = 0x30;      // 7 bit I2C address
const int add_read = 0x31; // 8bit I2C address
char data[4];
u_int32_t output_data[4];
int main(){

    char dat[3];
    //float time;
    //Timer t;
    while(1){
        // t.start();  Timer to check how many samples we get per second
        // time = t.read(); 
        dat[0] =0xAA;
        dat[1] =0x00;
        dat[2]= 0x00;

        // I2c Write
        i2c.write(add_write, dat, 3);
        wait_ms(5); // Wait before getting the status byte
        i2c.read(add_read,data,1); // reading the status byte
        wait_ms(5);
        i2c.read(add_read,data,4); // Read the data
        
        output_data[0]= data[0];
        output_data[1]= (u_int32_t)data[1] << 16;
        output_data[2]= (u_int32_t)data[2] << 8;
        output_data[3]= (u_int32_t)data[3];

        // Output taken from bits
        float output = float(output_data[1]|output_data[2]|output_data[3]);
        serial.printf(" %f \r\n", output);
        wait_ms(10);

        // t.stop();
        // time = t.read() - time;
        // serial.printf(" %f \r\n", time); // Timer value is used in Heart-rate Calculation
        // Output data is sent to serial and pressure conversion is done in python
    }
}
