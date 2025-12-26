#pragma once
#include <maya/MPxNode.h>

class CatenarySolver : public MPxNode
{

private:
	// input port
	static MObject ITEM_COUNT;
	static MObject LENGTH;
	static MObject INPUT1;
	static MObject INPUT2;

	// output port
	static MObject OUTPUTS;

public:
	static MTypeId TYPE_ID;
	static MString TYPE_NAME;
	static double  MAIN_EPS;
	static int	   MAX_ITER;

public:
	CatenarySolver();
	virtual ~CatenarySolver() override;

	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;
	static void* creator();
	static MStatus initialize();
};