#include "WPILib.h"
class Robot: public IterativeRobot
{
private:
    void RobotInit()
    {
        CameraServer::GetInstance()->StartAutomaticCapture();
    }
};
START_ROBOT_CLASS(Robot)
