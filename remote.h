#include "bluetooth.h"
#include <SoftwareSerial.h>
#define BT_RX_PIN 16                    
#define BT_TX_PIN 17
SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN);

namespace Gianni
{
    class RemoteControl : public RemoteControlDriver
    {
    public:
        
        RemoteControl() : RemoteControlDriver(), lastKey(command_t::keyNone) {}

        virtual bool getRemoteCommand(command_t& cmd)
        {
            cmd.stop();
            cmd.key = command_t::keyNone;
            
            if (BTSerial.available() <= 0)
                return false; 
            char ch = BTSerial.read();
            switch (ch) {
                case '8': // su
                    cmd.goForward();
                    Serial.println("Avanti");
                    break;
                case '2': // giu
                    cmd.goBack();
                    Serial.println("Indietro");
                    break;
                case '4': // sx
                    cmd.turnLeft();
                    Serial.println("Sinistra");
                    break;
                case '6': // dx
                    cmd.turnRight();
                    Serial.println("Destra");
                    break;
                case 'A': // function key #1
                case 'C':
                    cmd.key = command_t::keyF1;
                    break;
                case 'B': // function key #2
                case 'D':
                    cmd.key = command_t::keyF2;
                    break;
                case 'E': // function key #3
                    cmd.key = command_t::keyF3;
                    break;
                case 'F': // function key #4
                    cmd.key = command_t::keyF4;
                    break;
                default:
                    break;
            }
            if (cmd.key != command_t::keyNone && cmd.key == lastKey) {
                // repeated key, ignore it
                return false; 
            }
            lastKey = cmd.key;
            return true;
        }
    
    private:
        command_t::key_t lastKey;
        
    };
};
