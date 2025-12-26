#include "Matrix2Vectors.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>

MTypeId Matrix2Vectors::TYPE_ID{ 0x00141B81 };
MString Matrix2Vectors::TYPE_NAME{ "matrix2Vectors" };

MObject Matrix2Vectors::IN_MATRIX;
MObject Matrix2Vectors::V1;
MObject Matrix2Vectors::V2;
MObject Matrix2Vectors::V3;
MObject Matrix2Vectors::OFFSET;

Matrix2Vectors::Matrix2Vectors() :MPxNode() {}
Matrix2Vectors::~Matrix2Vectors() {}

void* Matrix2Vectors::creator() 
{
	return new Matrix2Vectors();
}

MStatus Matrix2Vectors::initialize() 
{
	MFnMatrixAttribute  matrixAttr;
	MFnNumericAttribute numericAttr;

	Matrix2Vectors::IN_MATRIX = matrixAttr.create("inMatrix", "inMat", MFnMatrixAttribute::kDouble);
	matrixAttr.setKeyable(true);
	matrixAttr.setStorable(true);

	Matrix2Vectors::V1 = numericAttr.create("vec1", "v1", MFnNumericData::k3Double);
	numericAttr.setStorable(false);
	numericAttr.setKeyable(false);

	Matrix2Vectors::V2 = numericAttr.create("vec2", "v2", MFnNumericData::k3Double);
	numericAttr.setStorable(false);
	numericAttr.setKeyable(false);

	Matrix2Vectors::V3 = numericAttr.create("vec3", "v3", MFnNumericData::k3Double);
	numericAttr.setStorable(false);
	numericAttr.setKeyable(false);

	Matrix2Vectors::OFFSET = numericAttr.create("offset", "off", MFnNumericData::k3Double);
	numericAttr.setStorable(false);
	numericAttr.setKeyable(false);

	Matrix2Vectors::addAttribute(Matrix2Vectors::IN_MATRIX);
	Matrix2Vectors::addAttribute(Matrix2Vectors::V1);
	Matrix2Vectors::addAttribute(Matrix2Vectors::V2);
	Matrix2Vectors::addAttribute(Matrix2Vectors::V3);
	Matrix2Vectors::addAttribute(Matrix2Vectors::OFFSET);

	Matrix2Vectors::attributeAffects(Matrix2Vectors::IN_MATRIX, Matrix2Vectors::V1);
	Matrix2Vectors::attributeAffects(Matrix2Vectors::IN_MATRIX, Matrix2Vectors::V2);
	Matrix2Vectors::attributeAffects(Matrix2Vectors::IN_MATRIX, Matrix2Vectors::V3);
	Matrix2Vectors::attributeAffects(Matrix2Vectors::IN_MATRIX, Matrix2Vectors::OFFSET);

	return MS::kSuccess;
}

MStatus Matrix2Vectors::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	MPlug outPlug{ plug.isChild() ? plug.parent() : plug };
	
	if (outPlug == Matrix2Vectors::V1 or
		outPlug == Matrix2Vectors::V2 or
		outPlug == Matrix2Vectors::V3 or
		outPlug == Matrix2Vectors::OFFSET)
	{
		const MMatrix& inMatrix = dataBlock.inputValue(Matrix2Vectors::IN_MATRIX).asMatrix();

		MDataHandle hV1  = dataBlock.outputValue(V1);
		MDataHandle hV2  = dataBlock.outputValue(V2);
		MDataHandle hV3  = dataBlock.outputValue(V3);
		MDataHandle hOff = dataBlock.outputValue(OFFSET);
		
		hV1 .set3Double(inMatrix[0][0], inMatrix[0][1], inMatrix[0][2]);
		hV2 .set3Double(inMatrix[1][0], inMatrix[1][1], inMatrix[1][2]);
		hV3 .set3Double(inMatrix[2][0], inMatrix[2][1], inMatrix[2][2]);
		hOff.set3Double(inMatrix[3][0], inMatrix[3][1], inMatrix[3][2]);

		hV1	.setClean();
		hV2	.setClean();
		hV3	.setClean();
		hOff.setClean();

		dataBlock.setClean(outPlug);
	}

	return MS::kSuccess;

};







