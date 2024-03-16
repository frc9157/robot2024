// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  frc::PWMSparkMax m_frontLeftMotor{0};
  frc::PWMSparkMax m_rearLeftMotor{1};
  frc::PWMSparkMax m_rearRightMotor{2};
  frc::PWMSparkMax m_frontRightMotor{3};
  frc::PWMSparkMax m_shooter1{4};
  frc::MotorControllerGroup m_leftMotor{m_frontLeftMotor, m_rearLeftMotor};
  frc::MotorControllerGroup m_rightMotor{m_frontRightMotor, m_rearRightMotor};  
  frc::DifferentialDrive m_robotDrive{
      [&](double output) { m_leftMotor.Set(output); },
      [&](double output) { m_rightMotor.Set(output); }};
  frc::Joystick m_stick{0};

 public:
  Robot() {
    wpi::SendableRegistry::AddChild(&m_robotDrive, &m_leftMotor);
    wpi::SendableRegistry::AddChild(&m_robotDrive, &m_rightMotor);
  }

  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightMotor.SetInverted(true);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    if(m_stick.GetY() <=0 )
      m_robotDrive.ArcadeDrive((m_stick.GetY()*m_stick.GetY()), (m_stick.GetX()*m_stick.GetX()));
    else{
      m_robotDrive.ArcadeDrive(-(m_stick.GetY()*m_stick.GetY()), -(m_stick.GetX()*m_stick.GetX())); 
    }
    if(m_stick.GetRawButtonPressed(1)){
      m_shooter1.Set(1);
    }else{
      m_shooter1.Set(0);
    }
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
