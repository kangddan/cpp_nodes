#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include "CurveNaturalWeight.h"


MStatus initializePlugin(MObject pluginObj)
{
    const char* vendor = "LinkRigger";
    const char* version = "1.0.0";
    const char* requiredApiVersion = "Any";

    MStatus status;

    MFnPlugin pluginFn(pluginObj, vendor, version, requiredApiVersion, &status);
    if (not status)
    {
        MGlobal::displayError("Failed to initialize plugin: " + status.errorString());
        return status;
    }

    status = pluginFn.registerNode(CurveNaturalWeight::TYPE_NAME,
        CurveNaturalWeight::TYPE_ID,
        CurveNaturalWeight::creator,
        CurveNaturalWeight::initialize,
        CurveNaturalWeight::kDependNode);
    if (not status)
    {
        MGlobal::displayError("Failed to register node: " + CurveNaturalWeight::TYPE_NAME);
        return status;
    }

    return status;
}

MStatus uninitializePlugin(MObject pluginObj)
{
    MStatus status;

    MFnPlugin pluginFn(pluginObj);

    status = pluginFn.deregisterNode(CurveNaturalWeight::TYPE_ID);
    if (not status)
    {
        MGlobal::displayError("Failed to deregister node: " + CurveNaturalWeight::TYPE_NAME);
        return status;
    }

    return(status);

}