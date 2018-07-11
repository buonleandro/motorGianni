//#include <NewPing.h>
#include "motor_gianni.h"
#include "remote.h"

/*#include "moving_average.h"

#define TRIGGER_PIN 14
#define ECHO_PIN 15*/


//NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, 200);

namespace Gianni
{
  class Core
  {
    public:
    Gianni::Motor motor;

    Core()
        : remoteControl()
    {
      initialize();
    }

    void initialize()
    {
      remote();
    }

    void runG()
   {
    
    RemoteControlDriver::command_t remoteCmd;
    bool haveRemoteCmd = remoteControl.getRemoteCommand(remoteCmd);

    if (haveRemoteCmd) {
                    switch (remoteCmd.key) {
                    case RemoteControlDriver::command_t::keyNone:
                        // this is a directional command
                        motor.setSpeed(remoteCmd.right,remoteCmd.left);
                        break;
                    default:
                        break;
                    }
                  }
    }

  protected:
        void remote()
        {
            motor.setSpeed(0,0);
        }
       
    
  private:
    RemoteControl remoteControl; 
    //MovingAverage<unsigned int, 3> distanceAverage;
    unsigned long endStateTime;
  };
};
Gianni::Core core;

void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
}

void loop()
{
  //Serial.print(DistanceSensor.ping_cm());
  core.runG();
}
