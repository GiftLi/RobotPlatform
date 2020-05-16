#pragma once


class AgentFunc
{
public:
	AgentFunc();
	~AgentFunc();

public:
	/* init Robot Func Interface */
	int startMaster(void);
	int closeMaster(void);
	int robotEnable(void);
	int robotDisable(void);
	int robotReset(void);


	/* Config Robot Func Interface */
	int setSlaveType();
	int setEndIOType();
	int setEncodeType();
	int setEncodeRadio();
	int setGearRatio();
	
	int setOverride();
	int setHomePosition();
	int setAcsSafetySpaceLimit();
	int setPcsSafetySpaceLimit();
	int setToolCoord();
	int setUserCoord();
	int setMoveJointLimits();
	int setMovePosLimits();
	int setStopJointLimits();
	int setStopPcsLimits();

	int setTorqueFeedMode();
	int setVelocityFeedMode();
	int setFeedForwardParam();
	int setConveyorScale();
	int setConveyorParam();
	int setToolCoordConfirm();

	/* Cooperation Set */
	int setVelocityThresholds();
	int setDampConstant();
	int setFrictionCompensationFactor();
	int setMaxEfficiency();
	int setTorqueConstant();
	int setKinematicsParam();
	int setDynamicsParam();
	int setInitRobotDynamic();
	int setGravityParam();
	int setMotorCurScales();
	int setMaxActutorCur();
	int setBaseMountingAngle();
	int setCollideStopPayload();
	int setCollideStopThresholds();
	int setCollisionMomentumThresholds();
	int setAssistveModeCollideStopThresholds();
	int setCollisionStopMode();
	int SetCollideStopLevel();
	int setFreeDriveMode();
	int setMaxPowerAndMomentum();
	
	
	

	/* Move Control Robot Func Interface */
	int robotContinueMove(void);
	int robotInterruptMove(void);
	int robotStopMove(void);
	
	int robotShortJogJ();
	int robotShortJogL();
	
	int robotLongJogJ();
	int robotLongJogL();
	
	int robotMoveRelJ();
	int robotMoveRelL();
	
	int robotMoveJ();
	int robotMoveL();
	int robotMoveC();
	
	int robotMoveToAcs();
	int robotMoveToPcs();
	
	int robotStartPushBlending();
	int robotPushBlendingPoint();
	int robotStartBlendingMotion();	
    int robotWayPoint();

public:
	
	
};



