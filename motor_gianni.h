
namespace Gianni
{
  class Motor
  {
    public:

      Motor()
      {
      }

        void setSpeed(int speed, int speed2)
        {
            currSpeed = speed;
                analogWrite(3,speed);
                analogWrite(11,speed2);
        }

        int getSpeed() const
        {
            return currSpeed;
        }

    private:
        int currSpeed;
    };
};
