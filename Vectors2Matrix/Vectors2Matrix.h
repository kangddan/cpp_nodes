#pragma once
#include <maya/MPxNode.h>

class Vectors2Matrix : public MPxNode
{

private:
	// input port
	static MObject V1;
	static MObject V2;
	static MObject V3;
	static MObject OFFSET;

	// output port
	static MObject OUT_MATRIX;

public:
	static MTypeId TYPE_ID;
	static MString TYPE_NAME;

public:
	Vectors2Matrix();
	virtual ~Vectors2Matrix() override;

	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;
	static void* creator();
	static MStatus initialize();


};
