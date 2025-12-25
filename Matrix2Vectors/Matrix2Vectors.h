#pragma once
#include <maya/MPxNode.h>

class Matrix2Vectors : public MPxNode
{

private:
	// input port
	static MObject IN_MATRIX;

	// output port
	static MObject V1;
	static MObject V2;
	static MObject V3;
	static MObject OFFSET;

public:
	static MTypeId TYPE_ID;
	static MString TYPE_NAME;

public:
	Matrix2Vectors();
	virtual ~Matrix2Vectors() override;

	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;
	static void* creator();
	static MStatus initialize();


};