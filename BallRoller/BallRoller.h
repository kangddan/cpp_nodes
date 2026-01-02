#pragma once
#include <maya/MPxNode.h>

class BallRoller : public MPxNode
{

private:
	// INPUT
	static MObject IN_MATRIX;
	static MObject RADIUS;

	static MObject PREVIOUS_POSITION;
	static MObject PREVIOUS_ROTATION;

	// OUTPUT
	static MObject OUT_MATRIX;

public:
	static MTypeId TYPE_ID;
	static MString TYPE_NAME;

public:
	BallRoller();
	virtual ~BallRoller() override;

	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;
	static void* creator();
	static MStatus initialize();
	static void setupUI();


};