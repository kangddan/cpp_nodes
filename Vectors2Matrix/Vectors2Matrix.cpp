#include "Vectors2Matrix.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>


MTypeId Vectors2Matrix::TYPE_ID{ 0x00141B82 };
MString Vectors2Matrix::TYPE_NAME{ "vectors2Matrix" };

MObject Vectors2Matrix::OUT_MATRIX;

MObject Vectors2Matrix::V1;
MObject Vectors2Matrix::V2;
MObject Vectors2Matrix::V3;
MObject Vectors2Matrix::OFFSET;

Vectors2Matrix::Vectors2Matrix() :MPxNode() {}
Vectors2Matrix::~Vectors2Matrix() {}

void* Vectors2Matrix::creator()
{
	return new Vectors2Matrix();
}

MStatus Vectors2Matrix::initialize()
{
	MFnMatrixAttribute  matrixAttr;
	MFnNumericAttribute numericAttr;

	Vectors2Matrix::OUT_MATRIX = matrixAttr.create("output Matrix", "outMat", MFnMatrixAttribute::kDouble);
	matrixAttr.setStorable(false);
	matrixAttr.setKeyable(false);
	matrixAttr.setWritable(false);
	matrixAttr.setReadable(true);

	Vectors2Matrix::V1 = numericAttr.create("vec1", "v1", MFnNumericData::k3Double);
	numericAttr.setKeyable(true);
	numericAttr.setStorable(true);
	numericAttr.setWritable(true);

	Vectors2Matrix::V2 = numericAttr.create("vec2", "v2", MFnNumericData::k3Double);
	numericAttr.setKeyable(true);
	numericAttr.setStorable(true);
	numericAttr.setWritable(true);

	Vectors2Matrix::V3 = numericAttr.create("vec3", "v3", MFnNumericData::k3Double);
	numericAttr.setKeyable(true);
	numericAttr.setStorable(true);
	numericAttr.setWritable(true);

	Vectors2Matrix::OFFSET = numericAttr.create("offset", "off", MFnNumericData::k3Double);
	numericAttr.setKeyable(true);
	numericAttr.setStorable(true);
	numericAttr.setWritable(true);

	Vectors2Matrix::addAttribute(Vectors2Matrix::OUT_MATRIX);
	Vectors2Matrix::addAttribute(Vectors2Matrix::V1);
	Vectors2Matrix::addAttribute(Vectors2Matrix::V2);
	Vectors2Matrix::addAttribute(Vectors2Matrix::V3);
	Vectors2Matrix::addAttribute(Vectors2Matrix::OFFSET);

	Vectors2Matrix::attributeAffects(Vectors2Matrix::V1,     Vectors2Matrix::OUT_MATRIX);
	Vectors2Matrix::attributeAffects(Vectors2Matrix::V2,     Vectors2Matrix::OUT_MATRIX);
	Vectors2Matrix::attributeAffects(Vectors2Matrix::V3,     Vectors2Matrix::OUT_MATRIX);
	Vectors2Matrix::attributeAffects(Vectors2Matrix::OFFSET, Vectors2Matrix::OUT_MATRIX);

	return MS::kSuccess;
}

MStatus Vectors2Matrix::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	if (plug == Vectors2Matrix::OUT_MATRIX)
	{
		const double* v1  = dataBlock.inputValue(Vectors2Matrix::V1).asDouble3();
		const double* v2  = dataBlock.inputValue(Vectors2Matrix::V2).asDouble3();
		const double* v3  = dataBlock.inputValue(Vectors2Matrix::V3).asDouble3();
		const double* off = dataBlock.inputValue(Vectors2Matrix::OFFSET).asDouble3();

		double _m[4][4] = {{  v1[0],   v1[1],  v1[2],  0.0 },
					   	   {  v2[0],   v2[1],  v2[2],  0.0 },
						   {  v3[0],   v3[1],  v3[2],  0.0 },
						   { off[0],  off[1], off[2],  1.0 }};

		MMatrix outMatrix{ _m };

		dataBlock.outputValue(Vectors2Matrix::OUT_MATRIX).setMMatrix(outMatrix);
		dataBlock.setClean(plug);
	}

	return MS::kSuccess;

};



