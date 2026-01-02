#include "BallRoller.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MMatrix.h>
#include <maya/MVector.h>
#include <maya/MTransformationMatrix.h>

MTypeId BallRoller::TYPE_ID{ 0x00141B85 };
MString BallRoller::TYPE_NAME{ "ballRoller" };

// INPUT
MObject BallRoller::IN_MATRIX;
MObject BallRoller::RADIUS;
MObject BallRoller::PREVIOUS_POSITION;
MObject BallRoller::PREVIOUS_ROTATION;

// OUTPUT
MObject BallRoller::OUT_MATRIX;

BallRoller::BallRoller() :MPxNode() {}
BallRoller::~BallRoller() {}

void* BallRoller::creator() { return new BallRoller(); }

MStatus BallRoller::initialize()
{
	MFnMatrixAttribute  matrixAttrFn;
	MFnNumericAttribute numericAttrFn;

	BallRoller::IN_MATRIX = matrixAttrFn.create("inMatrix", "inMat", MFnMatrixAttribute::kDouble);
	matrixAttrFn.setReadable(false);
	matrixAttrFn.setStorable(true);
	matrixAttrFn.setKeyable(true);

	BallRoller::RADIUS = numericAttrFn.create("radius", "rad", MFnNumericData::kDouble, 1.0);
	numericAttrFn.setMin(0.0001);
	numericAttrFn.setReadable(false);
	numericAttrFn.setStorable(true);
	numericAttrFn.setKeyable(true);

	BallRoller::PREVIOUS_POSITION = numericAttrFn.create("previousPosition", "pp", MFnNumericData::k3Double);
	numericAttrFn.setReadable(true);
	numericAttrFn.setStorable(true);
	numericAttrFn.setKeyable(false);
	numericAttrFn.setHidden(true);

	BallRoller::PREVIOUS_ROTATION = matrixAttrFn.create("previousRotation", "pr", MFnMatrixAttribute::kDouble);
	matrixAttrFn.setReadable(true);
	matrixAttrFn.setStorable(true);
	matrixAttrFn.setKeyable(false);
	matrixAttrFn.setHidden(true);

	BallRoller::OUT_MATRIX = matrixAttrFn.create("outMatrix", "outMat", MFnMatrixAttribute::kDouble);
	matrixAttrFn.setWritable(false);
	matrixAttrFn.setKeyable(false);

	BallRoller::addAttribute(BallRoller::IN_MATRIX);
	BallRoller::addAttribute(BallRoller::RADIUS);
	BallRoller::addAttribute(BallRoller::PREVIOUS_POSITION);
	BallRoller::addAttribute(BallRoller::PREVIOUS_ROTATION);
	BallRoller::addAttribute(BallRoller::OUT_MATRIX);

	BallRoller::attributeAffects(BallRoller::IN_MATRIX, BallRoller::OUT_MATRIX);
	BallRoller::attributeAffects(BallRoller::RADIUS,    BallRoller::OUT_MATRIX);

	BallRoller::setupUI();
	return MStatus::kSuccess;
	
}

MStatus BallRoller::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	if (plug != BallRoller::OUT_MATRIX)
		return MStatus::kUnknownParameter;

	MMatrix inMatrix    = dataBlock.inputValue(BallRoller::IN_MATRIX).asMatrix();
	MVector	offset      = MVector(inMatrix[3][0], inMatrix[3][1], inMatrix[3][2]);

	MVector previousPosition = dataBlock.inputValue(BallRoller::PREVIOUS_POSITION).asVector();
	MMatrix previousRotation = dataBlock.inputValue(BallRoller::PREVIOUS_ROTATION).asMatrix();

	MVector direction = offset - previousPosition;
	double  distance  = direction.length();
	double  angleRad  = distance / dataBlock.inputValue(BallRoller::RADIUS).asDouble();

	MVector rotationAxis = MVector(inMatrix[1][0], inMatrix[1][1], inMatrix[1][2]) ^ direction;

	MTransformationMatrix tempMatrix{};
	tempMatrix.setToRotationAxis(rotationAxis, angleRad);
	MMatrix newRotMatrix = tempMatrix.asMatrix();

	previousRotation *= newRotMatrix;

	dataBlock.outputValue(BallRoller::OUT_MATRIX).setMMatrix(previousRotation);
	dataBlock.outputValue(BallRoller::PREVIOUS_ROTATION).setMMatrix(previousRotation);
	dataBlock.outputValue(BallRoller::PREVIOUS_POSITION).setMVector(offset);

	dataBlock.setClean(plug);
	return MStatus::kSuccess;
}

void BallRoller::setupUI()
{
	const char* melCommand = R"(
	global proc AEballRollerTemplate(string $nodeName)
	{
		editorTemplate -beginScrollLayout;

			editorTemplate -beginLayout "Main" -collapse 0;
				editorTemplate -addControl "inMatrix";
				editorTemplate -addControl "radius";
			editorTemplate -endLayout;

			editorTemplate -beginLayout "Cached" -collapse 0;
				editorTemplate -addControl "previousPosition";
				editorTemplate -addControl "previousRotation";
			editorTemplate -endLayout;

			editorTemplate -beginLayout "Output" -collapse 1;
				editorTemplate -addControl "outMatrix";
			editorTemplate -endLayout;

			editorTemplate -addExtraControls;
		editorTemplate -endScrollLayout;
	}
		)";

	MGlobal::executeCommandOnIdle(melCommand, false);

}
