#ifndef SHIFTOUT_H
#define SHIFTOUT_H

#include <mbed.h>

class ShiftOut {

    public :
    
        ShiftOut(PinName clk, PinName data, PinName latch, int8_t registerCount = 8) {
            clkout = new DigitalOut(clk);
            dataout = new DigitalOut(data);
            latchout = new DigitalOut(latch);
            this->registerCount = registerCount;
        }
        
        ~ShiftOut() {
            delete clkout;
            delete dataout;
            delete latchout;
        }
        
        void write(int data) {
            *latchout = 0;
            for(int i = registerCount - 1; i >=  0; i--){
                *clkout = 0;
                *dataout = (data & (1 << i)) != 0;
                *clkout = 1;
            }
            *latchout = 1;
        }
         
    private :
        DigitalOut *clkout;
        DigitalOut *dataout;
        DigitalOut *latchout;
        int8_t registerCount;     
};

#endif