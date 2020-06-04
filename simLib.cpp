#include "../include/simLib.h"
#include <stdio.h>
#include <string>
#include <cstring>
#if defined (__linux) || defined (__APPLE__)
    #include <dlfcn.h>
#endif

#ifndef SIM_LIBRARY

static simInt _simAddLog(const simChar* pluginName,simInt verbosity,const simChar* msg)
{
    std::string m("[");
    if (strcmp(pluginName,"CoppeliaSimClient")!=0)
        m+="simExt";
    m+=pluginName;
    if (verbosity==sim_verbosity_errors)
        m+=":error]   ";
    if (verbosity==sim_verbosity_warnings)
        m+=":warning]   ";
    if (verbosity==sim_verbosity_loadinfos)
        m+=":loadinfo]   ";
    if (verbosity==sim_verbosity_msgs)
        m+=":msg]   ";
    if (verbosity==sim_verbosity_infos)
        m+=":info]   ";
    if (verbosity==sim_verbosity_debug)
        m+=":debug]   ";
    if (verbosity==sim_verbosity_trace)
        m+=":trace]   ";
    if (verbosity==sim_verbosity_tracelua)
        m+=":tracelua]   ";
    if (verbosity==sim_verbosity_traceall)
        m+=":traceall]   ";
    m+=msg;
    printf("%s\n",m.c_str());
    return(1);
}

ptrSimRunSimulator simRunSimulator=nullptr;
ptrSimRunSimulatorEx simRunSimulatorEx=nullptr;
ptrSimGetSimulatorMessage simGetSimulatorMessage=nullptr;
ptrSimGetMainWindow simGetMainWindow=nullptr;
ptrSimGetLastError simGetLastError=nullptr;
ptrSimLoadModule simLoadModule=nullptr;
ptrSimUnloadModule simUnloadModule=nullptr;
ptrSimSendModuleMessage simSendModuleMessage=nullptr;
ptrSimSetBooleanParameter simSetBooleanParameter=nullptr;
ptrSimGetBooleanParameter simGetBooleanParameter=nullptr;
ptrSimSetBoolParameter simSetBoolParameter=nullptr;
ptrSimGetBoolParameter simGetBoolParameter=nullptr;
ptrSimSetIntegerParameter simSetIntegerParameter=nullptr;
ptrSimGetIntegerParameter simGetIntegerParameter=nullptr;
ptrSimSetInt32Parameter simSetInt32Parameter=nullptr;
ptrSimGetInt32Parameter simGetInt32Parameter=nullptr;
ptrSimGetUInt64Parameter simGetUInt64Parameter=nullptr;
ptrSimSetFloatingParameter simSetFloatingParameter=nullptr;
ptrSimGetFloatingParameter simGetFloatingParameter=nullptr;
ptrSimSetFloatParameter simSetFloatParameter=nullptr;
ptrSimGetFloatParameter simGetFloatParameter=nullptr;
ptrSimSetStringParameter simSetStringParameter=nullptr;
ptrSimGetStringParameter simGetStringParameter=nullptr;
ptrSimGetObjectHandle simGetObjectHandle=nullptr;
ptrSimRemoveObject simRemoveObject=nullptr;
ptrSimRemoveModel simRemoveModel=nullptr;
ptrSimGetObjectName simGetObjectName=nullptr;
ptrSimGetObjects simGetObjects=nullptr;
ptrSimSetObjectName simSetObjectName=nullptr;
ptrSimGetCollectionHandle simGetCollectionHandle=nullptr;
ptrSimRemoveCollection simRemoveCollection=nullptr;
ptrSimEmptyCollection simEmptyCollection=nullptr;
ptrSimGetCollectionName simGetCollectionName=nullptr;
ptrSimSetCollectionName simSetCollectionName=nullptr;
ptrSimGetObjectMatrix simGetObjectMatrix=nullptr;
ptrSimSetObjectMatrix simSetObjectMatrix=nullptr;
ptrSimGetObjectPosition simGetObjectPosition=nullptr;
ptrSimSetObjectPosition simSetObjectPosition=nullptr;
ptrSimGetObjectOrientation simGetObjectOrientation=nullptr;
ptrSimSetObjectOrientation simSetObjectOrientation=nullptr;
ptrSimGetJointPosition simGetJointPosition=nullptr;
ptrSimSetJointPosition simSetJointPosition=nullptr;
ptrSimSetJointTargetPosition simSetJointTargetPosition=nullptr;
ptrSimGetJointTargetPosition simGetJointTargetPosition=nullptr;
ptrSimSetJointMaxForce simSetJointMaxForce=nullptr;
ptrSimGetPathPosition simGetPathPosition=nullptr;
ptrSimSetPathPosition simSetPathPosition=nullptr;
ptrSimGetPathLength simGetPathLength=nullptr;
ptrSimGetJointMatrix simGetJointMatrix=nullptr;
ptrSimSetSphericalJointMatrix simSetSphericalJointMatrix=nullptr;
ptrSimGetJointInterval simGetJointInterval=nullptr;
ptrSimSetJointInterval simSetJointInterval=nullptr;
ptrSimGetObjectParent simGetObjectParent=nullptr;
ptrSimGetObjectChild simGetObjectChild=nullptr;
ptrSimSetObjectParent simSetObjectParent=nullptr;
ptrSimGetObjectType simGetObjectType=nullptr;
ptrSimGetJointType simGetJointType=nullptr;
ptrSimBuildIdentityMatrix simBuildIdentityMatrix=nullptr;
ptrSimCopyMatrix simCopyMatrix=nullptr;
ptrSimBuildMatrix simBuildMatrix=nullptr;
ptrSimGetEulerAnglesFromMatrix simGetEulerAnglesFromMatrix=nullptr;
ptrSimInvertMatrix simInvertMatrix=nullptr;
ptrSimMultiplyMatrices simMultiplyMatrices=nullptr;
ptrSimInterpolateMatrices simInterpolateMatrices=nullptr;
ptrSimTransformVector simTransformVector=nullptr;
ptrSimReservedCommand simReservedCommand=nullptr;
ptrSimGetSimulationTime simGetSimulationTime=nullptr;
ptrSimGetSimulationState simGetSimulationState=nullptr;
ptrSimGetSystemTime simGetSystemTime=nullptr;
ptrSimGetSystemTimeInMilliseconds simGetSystemTimeInMilliseconds=nullptr;
ptrSimGetSystemTimeInMs simGetSystemTimeInMs=nullptr;
ptrSimLoadScene simLoadScene=nullptr;
ptrSimCloseScene simCloseScene=nullptr;
ptrSimSaveScene simSaveScene=nullptr;
ptrSimLoadModel simLoadModel=nullptr;
ptrSimSaveModel simSaveModel=nullptr;
ptrSimAddModuleMenuEntry simAddModuleMenuEntry=nullptr;
ptrSimSetModuleMenuItemState simSetModuleMenuItemState=nullptr;
ptrSimDoesFileExist simDoesFileExist=nullptr;
ptrSimIsObjectInSelection simIsObjectInSelection=nullptr;
ptrSimAddObjectToSelection simAddObjectToSelection=nullptr;
ptrSimRemoveObjectFromSelection simRemoveObjectFromSelection=nullptr;
ptrSimGetObjectSelectionSize simGetObjectSelectionSize=nullptr;
ptrSimGetObjectLastSelection simGetObjectLastSelection=nullptr;
ptrSimGetObjectSelection simGetObjectSelection=nullptr;
ptrSimHandleCollision simHandleCollision=nullptr;
ptrSimReadCollision simReadCollision=nullptr;
ptrSimHandleDistance simHandleDistance=nullptr;
ptrSimReadDistance simReadDistance=nullptr;
ptrSimHandleProximitySensor simHandleProximitySensor=nullptr;
ptrSimReadProximitySensor simReadProximitySensor=nullptr;
ptrSimHandleIkGroup simHandleIkGroup=nullptr;
ptrSimCheckIkGroup simCheckIkGroup=nullptr;
ptrSimHandleDynamics simHandleDynamics=nullptr;
ptrSimGetScriptHandle simGetScriptHandle=nullptr;
ptrSimSetScriptText simSetScriptText=nullptr;
ptrSimGetScriptText simGetScriptText=nullptr;
ptrSimGetScriptProperty simGetScriptProperty=nullptr;
ptrSimAssociateScriptWithObject simAssociateScriptWithObject=nullptr;
ptrSimGetScript simGetScript=nullptr;
ptrSimGetScriptAssociatedWithObject simGetScriptAssociatedWithObject=nullptr;
ptrSimGetCustomizationScriptAssociatedWithObject simGetCustomizationScriptAssociatedWithObject=nullptr;
ptrSimGetObjectAssociatedWithScript simGetObjectAssociatedWithScript=nullptr;
ptrSimGetScriptName simGetScriptName=nullptr;
ptrSimHandleMainScript simHandleMainScript=nullptr;
ptrSimResetScript simResetScript=nullptr;
ptrSimAddScript simAddScript=nullptr;
ptrSimRemoveScript simRemoveScript=nullptr;
ptrSimRefreshDialogs simRefreshDialogs=nullptr;
ptrSimGetCollisionHandle simGetCollisionHandle=nullptr;
ptrSimGetDistanceHandle simGetDistanceHandle=nullptr;
ptrSimGetIkGroupHandle simGetIkGroupHandle=nullptr;
ptrSimResetCollision simResetCollision=nullptr;
ptrSimResetDistance simResetDistance=nullptr;
ptrSimResetProximitySensor simResetProximitySensor=nullptr;
ptrSimCheckProximitySensor simCheckProximitySensor=nullptr;
ptrSimCheckProximitySensorEx simCheckProximitySensorEx=nullptr;
ptrSimCheckProximitySensorEx2 simCheckProximitySensorEx2=nullptr;
ptrSimCreateBuffer simCreateBuffer=nullptr;
ptrSimReleaseBuffer simReleaseBuffer=nullptr;
ptrSimCheckCollision simCheckCollision=nullptr;
ptrSimCheckCollisionEx simCheckCollisionEx=nullptr;
ptrSimCheckDistance simCheckDistance=nullptr;
ptrSimGetObjectConfiguration simGetObjectConfiguration=nullptr;
ptrSimSetObjectConfiguration simSetObjectConfiguration=nullptr;
ptrSimGetConfigurationTree simGetConfigurationTree=nullptr;
ptrSimSetConfigurationTree simSetConfigurationTree=nullptr;
ptrSimSetSimulationTimeStep simSetSimulationTimeStep=nullptr;
ptrSimGetSimulationTimeStep simGetSimulationTimeStep=nullptr;
ptrSimGetRealTimeSimulation simGetRealTimeSimulation=nullptr;
ptrSimIsRealTimeSimulationStepNeeded simIsRealTimeSimulationStepNeeded=nullptr;
ptrSimAdjustRealTimeTimer simAdjustRealTimeTimer=nullptr;
ptrSimGetSimulationPassesPerRenderingPass simGetSimulationPassesPerRenderingPass=nullptr;
ptrSimAdvanceSimulationByOneStep simAdvanceSimulationByOneStep=nullptr;
ptrSimStartSimulation simStartSimulation=nullptr;
ptrSimStopSimulation simStopSimulation=nullptr;
ptrSimPauseSimulation simPauseSimulation=nullptr;
ptrSimBroadcastMessage simBroadcastMessage=nullptr;
ptrSimGetModuleName simGetModuleName=nullptr;
ptrSimFloatingViewAdd simFloatingViewAdd=nullptr;
ptrSimFloatingViewRemove simFloatingViewRemove=nullptr;
ptrSimAdjustView simAdjustView=nullptr;
ptrSimSetLastError simSetLastError=nullptr;
ptrSimHandleGraph simHandleGraph=nullptr;
ptrSimResetGraph simResetGraph=nullptr;
ptrSimSetNavigationMode simSetNavigationMode=nullptr;
ptrSimGetNavigationMode simGetNavigationMode=nullptr;
ptrSimSetPage simSetPage=nullptr;
ptrSimGetPage simGetPage=nullptr;
ptrSimDisplayDialog simDisplayDialog=nullptr;
ptrSimGetDialogResult simGetDialogResult=nullptr;
ptrSimGetDialogInput simGetDialogInput=nullptr;
ptrSimEndDialog simEndDialog=nullptr;
ptrSimRegisterScriptCallbackFunction simRegisterScriptCallbackFunction=nullptr;
ptrSimRegisterScriptVariable simRegisterScriptVariable=nullptr;
ptrSimSetJointTargetVelocity simSetJointTargetVelocity=nullptr;
ptrSimGetJointTargetVelocity simGetJointTargetVelocity=nullptr;
ptrSimSetPathTargetNominalVelocity simSetPathTargetNominalVelocity=nullptr;
ptrSimGetScriptRawBuffer simGetScriptRawBuffer=nullptr;
ptrSimSetScriptRawBuffer simSetScriptRawBuffer=nullptr;
ptrSimReleaseScriptRawBuffer simReleaseScriptRawBuffer=nullptr;
ptrSimCopyPasteObjects simCopyPasteObjects=nullptr;
ptrSimScaleSelectedObjects simScaleSelectedObjects=nullptr;
ptrSimScaleObjects simScaleObjects=nullptr;
ptrSimDeleteSelectedObjects simDeleteSelectedObjects=nullptr;
ptrSimGetObjectUniqueIdentifier simGetObjectUniqueIdentifier=nullptr;
ptrSimSendData simSendData=nullptr;
ptrSimReceiveData simReceiveData=nullptr;
ptrSimSetGraphUserData simSetGraphUserData=nullptr;
ptrSimAddDrawingObject simAddDrawingObject=nullptr;
ptrSimRemoveDrawingObject simRemoveDrawingObject=nullptr;
ptrSimAddDrawingObjectItem simAddDrawingObjectItem=nullptr;
ptrSimAddParticleObject simAddParticleObject=nullptr;
ptrSimRemoveParticleObject simRemoveParticleObject=nullptr;
ptrSimAddParticleObjectItem simAddParticleObjectItem=nullptr;
ptrSimGetObjectSizeFactor simGetObjectSizeFactor=nullptr;
ptrSimAnnounceSceneContentChange simAnnounceSceneContentChange=nullptr;
ptrSimSetIntegerSignal simSetIntegerSignal=nullptr;
ptrSimGetIntegerSignal simGetIntegerSignal=nullptr;
ptrSimClearIntegerSignal simClearIntegerSignal=nullptr;
ptrSimSetFloatSignal simSetFloatSignal=nullptr;
ptrSimGetFloatSignal simGetFloatSignal=nullptr;
ptrSimClearFloatSignal simClearFloatSignal=nullptr;
ptrSimSetDoubleSignal simSetDoubleSignal=nullptr;
ptrSimGetDoubleSignal simGetDoubleSignal=nullptr;
ptrSimClearDoubleSignal simClearDoubleSignal=nullptr;
ptrSimSetStringSignal simSetStringSignal=nullptr;
ptrSimGetStringSignal simGetStringSignal=nullptr;
ptrSimClearStringSignal simClearStringSignal=nullptr;
ptrSimGetSignalName simGetSignalName=nullptr;
ptrSimSetObjectProperty simSetObjectProperty=nullptr;
ptrSimGetObjectProperty simGetObjectProperty=nullptr;
ptrSimSetObjectSpecialProperty simSetObjectSpecialProperty=nullptr;
ptrSimGetObjectSpecialProperty simGetObjectSpecialProperty=nullptr;
ptrSimGetPositionOnPath simGetPositionOnPath=nullptr;
ptrSimGetDataOnPath simGetDataOnPath=nullptr;
ptrSimGetOrientationOnPath simGetOrientationOnPath=nullptr;
ptrSimGetClosestPositionOnPath simGetClosestPositionOnPath=nullptr;
ptrSimReadForceSensor simReadForceSensor=nullptr;
ptrSimBreakForceSensor simBreakForceSensor=nullptr;
ptrSimGetShapeVertex simGetShapeVertex=nullptr;
ptrSimGetShapeTriangle simGetShapeTriangle=nullptr;
ptrSimSetLightParameters simSetLightParameters=nullptr;
ptrSimGetLightParameters simGetLightParameters=nullptr;
ptrSimGetVelocity simGetVelocity=nullptr;
ptrSimGetObjectVelocity simGetObjectVelocity=nullptr;
ptrSimAddForceAndTorque simAddForceAndTorque=nullptr;
ptrSimAddForce simAddForce=nullptr;
ptrSimSetExplicitHandling simSetExplicitHandling=nullptr;
ptrSimGetExplicitHandling simGetExplicitHandling=nullptr;
ptrSimGetLinkDummy simGetLinkDummy=nullptr;
ptrSimSetLinkDummy simSetLinkDummy=nullptr;
ptrSimSetModelProperty simSetModelProperty=nullptr;
ptrSimGetModelProperty simGetModelProperty=nullptr;
ptrSimSetShapeColor simSetShapeColor=nullptr;
ptrSimGetShapeColor simGetShapeColor=nullptr;
ptrSimResetDynamicObject simResetDynamicObject=nullptr;
ptrSimSetJointMode simSetJointMode=nullptr;
ptrSimGetJointMode simGetJointMode=nullptr;
ptrSimSerialOpen simSerialOpen=nullptr;
ptrSimSerialClose simSerialClose=nullptr;
ptrSimSerialSend simSerialSend=nullptr;
ptrSimSerialRead simSerialRead=nullptr;
ptrSimSerialCheck simSerialCheck=nullptr;
ptrSimGetContactInfo simGetContactInfo=nullptr;
ptrSimSetThreadIsFree simSetThreadIsFree=nullptr;
ptrSimTubeOpen simTubeOpen=nullptr;
ptrSimTubeClose simTubeClose=nullptr;
ptrSimTubeWrite simTubeWrite=nullptr;
ptrSimTubeRead simTubeRead=nullptr;
ptrSimTubeStatus simTubeStatus=nullptr;
ptrSimAuxiliaryConsoleOpen simAuxiliaryConsoleOpen=nullptr;
ptrSimAuxiliaryConsoleClose simAuxiliaryConsoleClose=nullptr;
ptrSimAuxiliaryConsoleShow simAuxiliaryConsoleShow=nullptr;
ptrSimAuxiliaryConsolePrint simAuxiliaryConsolePrint=nullptr;
ptrSimImportShape simImportShape=nullptr;
ptrSimImportMesh simImportMesh=nullptr;
ptrSimExportMesh simExportMesh=nullptr;
ptrSimCreateMeshShape simCreateMeshShape=nullptr;
ptrSimCreatePureShape simCreatePureShape=nullptr;
ptrSimCreateHeightfieldShape simCreateHeightfieldShape=nullptr;
ptrSimGetShapeMesh simGetShapeMesh=nullptr;
ptrSimAddBanner simAddBanner=nullptr;
ptrSimRemoveBanner simRemoveBanner=nullptr;
ptrSimCreateJoint simCreateJoint=nullptr;
ptrSimCreateDummy simCreateDummy=nullptr;
ptrSimCreateProximitySensor simCreateProximitySensor=nullptr;
ptrSimCreatePath simCreatePath=nullptr;
ptrSimInsertPathCtrlPoints simInsertPathCtrlPoints=nullptr;
ptrSimCutPathCtrlPoints simCutPathCtrlPoints=nullptr;
ptrSimCreateForceSensor simCreateForceSensor=nullptr;
ptrSimCreateVisionSensor simCreateVisionSensor=nullptr;
ptrSimGetObjectIntParameter simGetObjectIntParameter=nullptr;
ptrSimSetObjectIntParameter simSetObjectIntParameter=nullptr;
ptrSimGetObjectInt32Parameter simGetObjectInt32Parameter=nullptr;
ptrSimSetObjectInt32Parameter simSetObjectInt32Parameter=nullptr;
ptrSimGetObjectFloatParameter simGetObjectFloatParameter=nullptr;
ptrSimSetObjectFloatParameter simSetObjectFloatParameter=nullptr;
ptrSimGetObjectStringParameter simGetObjectStringParameter=nullptr;
ptrSimSetObjectStringParameter simSetObjectStringParameter=nullptr;
ptrSimSetSimulationPassesPerRenderingPass simSetSimulationPassesPerRenderingPass=nullptr;
ptrSimGetRotationAxis simGetRotationAxis=nullptr;
ptrSimRotateAroundAxis simRotateAroundAxis=nullptr;
ptrSimGetJointForce simGetJointForce=nullptr;
ptrSimGetJointMaxForce simGetJointMaxForce=nullptr;
ptrSimSetArrayParameter simSetArrayParameter=nullptr;
ptrSimGetArrayParameter simGetArrayParameter=nullptr;
ptrSimSetIkGroupProperties simSetIkGroupProperties=nullptr;
ptrSimSetIkElementProperties simSetIkElementProperties=nullptr;
ptrSimCameraFitToView simCameraFitToView=nullptr;
ptrSimPersistentDataWrite simPersistentDataWrite=nullptr;
ptrSimPersistentDataRead simPersistentDataRead=nullptr;
ptrSimIsHandleValid simIsHandleValid=nullptr;
ptrSimHandleVisionSensor simHandleVisionSensor=nullptr;
ptrSimReadVisionSensor simReadVisionSensor=nullptr;
ptrSimResetVisionSensor simResetVisionSensor=nullptr;
ptrSimCheckVisionSensor simCheckVisionSensor=nullptr;
ptrSimCheckVisionSensorEx simCheckVisionSensorEx=nullptr;
ptrSimGetVisionSensorResolution simGetVisionSensorResolution=nullptr;
ptrSimGetVisionSensorImage simGetVisionSensorImage=nullptr;
ptrSimGetVisionSensorCharImage simGetVisionSensorCharImage=nullptr;
ptrSimSetVisionSensorImage simSetVisionSensorImage=nullptr;
ptrSimSetVisionSensorCharImage simSetVisionSensorCharImage=nullptr;
ptrSimGetVisionSensorDepthBuffer simGetVisionSensorDepthBuffer=nullptr;
ptrSimGetObjectQuaternion simGetObjectQuaternion=nullptr;
ptrSimSetObjectQuaternion simSetObjectQuaternion=nullptr;
ptrSimRMLPosition simRMLPosition=nullptr;
ptrSimRMLVelocity simRMLVelocity=nullptr;
ptrSimRMLPos simRMLPos=nullptr;
ptrSimRMLVel simRMLVel=nullptr;
ptrSimRMLStep simRMLStep=nullptr;
ptrSimRMLRemove simRMLRemove=nullptr;
ptrSimBuildMatrixQ simBuildMatrixQ=nullptr;
ptrSimGetQuaternionFromMatrix simGetQuaternionFromMatrix=nullptr;
ptrSimFileDialog simFileDialog=nullptr;
ptrSimMsgBox simMsgBox=nullptr;
ptrSimSetShapeMassAndInertia simSetShapeMassAndInertia=nullptr;
ptrSimGetShapeMassAndInertia simGetShapeMassAndInertia=nullptr;
ptrSimGroupShapes simGroupShapes=nullptr;
ptrSimUngroupShape simUngroupShape=nullptr;
ptrSimConvexDecompose simConvexDecompose=nullptr;
ptrSimGetIkGroupMatrix simGetIkGroupMatrix=nullptr;
ptrSimAddGhost simAddGhost=nullptr;
ptrSimModifyGhost simModifyGhost=nullptr;
ptrSimQuitSimulator simQuitSimulator=nullptr;
ptrSimGetThreadId simGetThreadId=nullptr;
ptrSimLockResources simLockResources=nullptr;
ptrSimUnlockResources simUnlockResources=nullptr;
ptrSimEnableEventCallback simEnableEventCallback=nullptr;
ptrSimSetShapeMaterial simSetShapeMaterial=nullptr;
ptrSimGetTextureId simGetTextureId=nullptr;
ptrSimReadTexture simReadTexture=nullptr;
ptrSimWriteTexture simWriteTexture=nullptr;
ptrSimCreateTexture simCreateTexture=nullptr;
ptrSimWriteCustomDataBlock simWriteCustomDataBlock=nullptr;
ptrSimReadCustomDataBlock simReadCustomDataBlock=nullptr;
ptrSimReadCustomDataBlockTags simReadCustomDataBlockTags=nullptr;
ptrSimAddPointCloud simAddPointCloud=nullptr;
ptrSimModifyPointCloud simModifyPointCloud=nullptr;
ptrSimGetShapeGeomInfo simGetShapeGeomInfo=nullptr;
ptrSimGetObjectsInTree simGetObjectsInTree=nullptr;
ptrSimSetObjectSizeValues simSetObjectSizeValues=nullptr;
ptrSimGetObjectSizeValues simGetObjectSizeValues=nullptr;
ptrSimScaleObject simScaleObject=nullptr;
ptrSimSetShapeTexture simSetShapeTexture=nullptr;
ptrSimGetShapeTextureId simGetShapeTextureId=nullptr;
ptrSimGetCollectionObjects simGetCollectionObjects=nullptr;
ptrSimSetScriptAttribute simSetScriptAttribute=nullptr;
ptrSimGetScriptAttribute simGetScriptAttribute=nullptr;
ptrSimReorientShapeBoundingBox simReorientShapeBoundingBox=nullptr;
ptrSimSwitchThread simSwitchThread=nullptr;
ptrSimCreateIkGroup simCreateIkGroup=nullptr;
ptrSimRemoveIkGroup simRemoveIkGroup=nullptr;
ptrSimCreateIkElement simCreateIkElement=nullptr;
ptrSimCreateCollection simCreateCollection=nullptr;
ptrSimAddObjectToCollection simAddObjectToCollection=nullptr;
ptrSimSaveImage simSaveImage=nullptr;
ptrSimLoadImage simLoadImage=nullptr;
ptrSimGetScaledImage simGetScaledImage=nullptr;
ptrSimTransformImage simTransformImage=nullptr;
ptrSimGetQHull simGetQHull=nullptr;
ptrSimGetDecimatedMesh simGetDecimatedMesh=nullptr;
ptrSimExportIk simExportIk=nullptr;
ptrSimCallScriptFunctionEx simCallScriptFunctionEx=nullptr;
ptrSimComputeJacobian simComputeJacobian=nullptr;
ptrSimGetConfigForTipPose simGetConfigForTipPose=nullptr;
ptrSimGenerateIkPath simGenerateIkPath=nullptr;
ptrSimGetExtensionString simGetExtensionString=nullptr;
ptrSimComputeMassAndInertia simComputeMassAndInertia=nullptr;
ptrSimCreateStack simCreateStack=nullptr;
ptrSimReleaseStack simReleaseStack=nullptr;
ptrSimCopyStack simCopyStack=nullptr;
ptrSimPushNullOntoStack simPushNullOntoStack=nullptr;
ptrSimPushBoolOntoStack simPushBoolOntoStack=nullptr;
ptrSimPushInt32OntoStack simPushInt32OntoStack=nullptr;
ptrSimPushFloatOntoStack simPushFloatOntoStack=nullptr;
ptrSimPushDoubleOntoStack simPushDoubleOntoStack=nullptr;
ptrSimPushStringOntoStack simPushStringOntoStack=nullptr;
ptrSimPushUInt8TableOntoStack simPushUInt8TableOntoStack=nullptr;
ptrSimPushInt32TableOntoStack simPushInt32TableOntoStack=nullptr;
ptrSimPushFloatTableOntoStack simPushFloatTableOntoStack=nullptr;
ptrSimPushDoubleTableOntoStack simPushDoubleTableOntoStack=nullptr;
ptrSimPushTableOntoStack simPushTableOntoStack=nullptr;
ptrSimInsertDataIntoStackTable simInsertDataIntoStackTable=nullptr;
ptrSimGetStackSize simGetStackSize=nullptr;
ptrSimPopStackItem simPopStackItem=nullptr;
ptrSimMoveStackItemToTop simMoveStackItemToTop=nullptr;
ptrSimIsStackValueNull simIsStackValueNull=nullptr;
ptrSimGetStackBoolValue simGetStackBoolValue=nullptr;
ptrSimGetStackInt32Value simGetStackInt32Value=nullptr;
ptrSimGetStackFloatValue simGetStackFloatValue=nullptr;
ptrSimGetStackDoubleValue simGetStackDoubleValue=nullptr;
ptrSimGetStackStringValue simGetStackStringValue=nullptr;
ptrSimGetStackTableInfo simGetStackTableInfo=nullptr;
ptrSimGetStackUInt8Table simGetStackUInt8Table=nullptr;
ptrSimGetStackInt32Table simGetStackInt32Table=nullptr;
ptrSimGetStackFloatTable simGetStackFloatTable=nullptr;
ptrSimGetStackDoubleTable simGetStackDoubleTable=nullptr;
ptrSimUnfoldStackTable simUnfoldStackTable=nullptr;
ptrSimDebugStack simDebugStack=nullptr;
ptrSimSetScriptVariable simSetScriptVariable=nullptr;
ptrSimGetEngineFloatParameter simGetEngineFloatParameter=nullptr;
ptrSimGetEngineInt32Parameter simGetEngineInt32Parameter=nullptr;
ptrSimGetEngineBoolParameter simGetEngineBoolParameter=nullptr;
ptrSimSetEngineFloatParameter simSetEngineFloatParameter=nullptr;
ptrSimSetEngineInt32Parameter simSetEngineInt32Parameter=nullptr;
ptrSimSetEngineBoolParameter simSetEngineBoolParameter=nullptr;
ptrSimCreateOctree simCreateOctree=nullptr;
ptrSimCreatePointCloud simCreatePointCloud=nullptr;
ptrSimSetPointCloudOptions simSetPointCloudOptions=nullptr;
ptrSimGetPointCloudOptions simGetPointCloudOptions=nullptr;
ptrSimInsertVoxelsIntoOctree simInsertVoxelsIntoOctree=nullptr;
ptrSimRemoveVoxelsFromOctree simRemoveVoxelsFromOctree=nullptr;
ptrSimInsertPointsIntoPointCloud simInsertPointsIntoPointCloud=nullptr;
ptrSimRemovePointsFromPointCloud simRemovePointsFromPointCloud=nullptr;
ptrSimIntersectPointsWithPointCloud simIntersectPointsWithPointCloud=nullptr;
ptrSimGetOctreeVoxels simGetOctreeVoxels=nullptr;
ptrSimGetPointCloudPoints simGetPointCloudPoints=nullptr;
ptrSimInsertObjectIntoOctree simInsertObjectIntoOctree=nullptr;
ptrSimSubtractObjectFromOctree simSubtractObjectFromOctree=nullptr;
ptrSimInsertObjectIntoPointCloud simInsertObjectIntoPointCloud=nullptr;
ptrSimSubtractObjectFromPointCloud simSubtractObjectFromPointCloud=nullptr;
ptrSimCheckOctreePointOccupancy simCheckOctreePointOccupancy=nullptr;
ptrSimOpenTextEditor simOpenTextEditor=nullptr;
ptrSimPackTable simPackTable=nullptr;
ptrSimUnpackTable simUnpackTable=nullptr;
ptrSimSetReferencedHandles simSetReferencedHandles=nullptr;
ptrSimGetReferencedHandles simGetReferencedHandles=nullptr;
ptrSimGetShapeViz simGetShapeViz=nullptr;
ptrSimExecuteScriptString simExecuteScriptString=nullptr;
ptrSimGetApiFunc simGetApiFunc=nullptr;
ptrSimGetApiInfo simGetApiInfo=nullptr;
ptrSimSetModuleInfo simSetModuleInfo=nullptr;
ptrSimGetModuleInfo simGetModuleInfo=nullptr;
ptrSimIsDeprecated simIsDeprecated=nullptr;
ptrSimGetPersistentDataTags simGetPersistentDataTags=nullptr;
ptrSimEventNotification simEventNotification=nullptr;
ptrSimApplyTexture simApplyTexture=nullptr;
ptrSimSetJointDependency simSetJointDependency=nullptr;
ptrSimSetStringNamedParam simSetStringNamedParam=nullptr;
ptrSimGetStringNamedParam simGetStringNamedParam=nullptr;
ptrSimGetUserParameter simGetUserParameter=nullptr;
ptrSimSetUserParameter simSetUserParameter=nullptr;
ptrSimAddLog simAddLog=_simAddLog;


// Following courtesy of Stephen James:
ptrSimExtLaunchUIThread simExtLaunchUIThread=nullptr;
ptrSimExtCanInitSimThread simExtCanInitSimThread=nullptr;
ptrSimExtSimThreadInit simExtSimThreadInit=nullptr;
ptrSimExtSimThreadDestroy simExtSimThreadDestroy=nullptr;
ptrSimExtPostExitRequest simExtPostExitRequest=nullptr;
ptrSimExtGetExitRequest simExtGetExitRequest=nullptr;
ptrSimExtStep simExtStep=nullptr;
ptrSimExtCallScriptFunction simExtCallScriptFunction=nullptr;



ptr_simGetContactCallbackCount _simGetContactCallbackCount=nullptr;
ptr_simGetContactCallback _simGetContactCallback=nullptr;
ptr_simSetDynamicSimulationIconCode _simSetDynamicSimulationIconCode=nullptr;
ptr_simSetDynamicObjectFlagForVisualization _simSetDynamicObjectFlagForVisualization=nullptr;
ptr_simGetObjectListSize _simGetObjectListSize=nullptr;
ptr_simGetObjectFromIndex _simGetObjectFromIndex=nullptr;
ptr_simGetObjectID _simGetObjectID=nullptr;
ptr_simGetObjectType _simGetObjectType=nullptr;
ptr_simGetObjectChildren _simGetObjectChildren=nullptr;
ptr_simGetGeomProxyFromShape _simGetGeomProxyFromShape=nullptr;
ptr_simGetParentObject _simGetParentObject=nullptr;
ptr_simGetObject _simGetObject=nullptr;
ptr_simGetIkGroupObject _simGetIkGroupObject=nullptr;
ptr_simMpHandleIkGroupObject _simMpHandleIkGroupObject=nullptr;
ptr_simGetObjectLocalTransformation _simGetObjectLocalTransformation=nullptr;
ptr_simSetObjectLocalTransformation _simSetObjectLocalTransformation=nullptr;
ptr_simSetObjectCumulativeTransformation _simSetObjectCumulativeTransformation=nullptr;
ptr_simGetObjectCumulativeTransformation _simGetObjectCumulativeTransformation=nullptr;
ptr_simIsShapeDynamicallyStatic _simIsShapeDynamicallyStatic=nullptr;
ptr_simGetTreeDynamicProperty _simGetTreeDynamicProperty=nullptr;
ptr_simGetDummyLinkType _simGetDummyLinkType=nullptr;
ptr_simGetJointMode _simGetJointMode=nullptr;
ptr_simIsJointInHybridOperation _simIsJointInHybridOperation=nullptr;
ptr_simDisableDynamicTreeForManipulation _simDisableDynamicTreeForManipulation=nullptr;
ptr_simIsShapeDynamicallyRespondable _simIsShapeDynamicallyRespondable=nullptr;
ptr_simGetDynamicCollisionMask _simGetDynamicCollisionMask=nullptr;
ptr_simGetLastParentForLocalGlobalCollidable _simGetLastParentForLocalGlobalCollidable=nullptr;
ptr_simSetShapeIsStaticAndNotRespondableButDynamicTag _simSetShapeIsStaticAndNotRespondableButDynamicTag=nullptr;
ptr_simGetShapeIsStaticAndNotRespondableButDynamicTag _simGetShapeIsStaticAndNotRespondableButDynamicTag=nullptr;
ptr_simSetJointPosition _simSetJointPosition=nullptr;
ptr_simGetJointPosition _simGetJointPosition=nullptr;
ptr_simSetDynamicMotorPositionControlTargetPosition _simSetDynamicMotorPositionControlTargetPosition=nullptr;
ptr_simGetInitialDynamicVelocity _simGetInitialDynamicVelocity=nullptr;
ptr_simSetInitialDynamicVelocity _simSetInitialDynamicVelocity=nullptr;
ptr_simGetInitialDynamicAngVelocity _simGetInitialDynamicAngVelocity=nullptr;
ptr_simSetInitialDynamicAngVelocity _simSetInitialDynamicAngVelocity=nullptr;
ptr_simGetStartSleeping _simGetStartSleeping=nullptr;
ptr_simGetWasPutToSleepOnce _simGetWasPutToSleepOnce=nullptr;
ptr_simGetDynamicsFullRefreshFlag _simGetDynamicsFullRefreshFlag=nullptr;
ptr_simSetDynamicsFullRefreshFlag _simSetDynamicsFullRefreshFlag=nullptr;
ptr_simSetGeomProxyDynamicsFullRefreshFlag _simSetGeomProxyDynamicsFullRefreshFlag=nullptr;
ptr_simGetGeomProxyDynamicsFullRefreshFlag _simGetGeomProxyDynamicsFullRefreshFlag=nullptr;
ptr_simSetShapeDynamicVelocity _simSetShapeDynamicVelocity=nullptr;
ptr_simGetAdditionalForceAndTorque _simGetAdditionalForceAndTorque=nullptr;
ptr_simClearAdditionalForceAndTorque _simClearAdditionalForceAndTorque=nullptr;
ptr_simGetJointPositionInterval _simGetJointPositionInterval=nullptr;
ptr_simGetJointType _simGetJointType=nullptr;
ptr_simIsForceSensorBroken _simIsForceSensorBroken=nullptr;
ptr_simGetDynamicForceSensorLocalTransformationPart2 _simGetDynamicForceSensorLocalTransformationPart2=nullptr;
ptr_simIsDynamicMotorEnabled _simIsDynamicMotorEnabled=nullptr;
ptr_simIsDynamicMotorPositionCtrlEnabled _simIsDynamicMotorPositionCtrlEnabled=nullptr;
ptr_simIsDynamicMotorTorqueModulationEnabled _simIsDynamicMotorTorqueModulationEnabled=nullptr;
ptr_simGetMotorPid _simGetMotorPid=nullptr;
ptr_simGetDynamicMotorTargetPosition _simGetDynamicMotorTargetPosition=nullptr;
ptr_simGetDynamicMotorTargetVelocity _simGetDynamicMotorTargetVelocity=nullptr;
ptr_simGetDynamicMotorMaxForce _simGetDynamicMotorMaxForce=nullptr;
ptr_simGetDynamicMotorUpperLimitVelocity _simGetDynamicMotorUpperLimitVelocity=nullptr;
ptr_simSetDynamicMotorReflectedPositionFromDynamicEngine _simSetDynamicMotorReflectedPositionFromDynamicEngine=nullptr;
ptr_simSetJointSphericalTransformation _simSetJointSphericalTransformation=nullptr;
ptr_simAddForceSensorCumulativeForcesAndTorques _simAddForceSensorCumulativeForcesAndTorques=nullptr;
ptr_simAddJointCumulativeForcesOrTorques _simAddJointCumulativeForcesOrTorques=nullptr;
ptr_simSetDynamicJointLocalTransformationPart2 _simSetDynamicJointLocalTransformationPart2=nullptr;
ptr_simSetDynamicForceSensorLocalTransformationPart2 _simSetDynamicForceSensorLocalTransformationPart2=nullptr;
ptr_simSetDynamicJointLocalTransformationPart2IsValid _simSetDynamicJointLocalTransformationPart2IsValid=nullptr;
ptr_simSetDynamicForceSensorLocalTransformationPart2IsValid _simSetDynamicForceSensorLocalTransformationPart2IsValid=nullptr;
ptr_simGetGeomWrapFromGeomProxy _simGetGeomWrapFromGeomProxy=nullptr;
ptr_simGetLocalInertiaFrame _simGetLocalInertiaFrame=nullptr;
ptr_simGetPurePrimitiveType _simGetPurePrimitiveType=nullptr;
ptr_simIsGeomWrapGeometric _simIsGeomWrapGeometric=nullptr;
ptr_simIsGeomWrapConvex _simIsGeomWrapConvex=nullptr;
ptr_simGetGeometricCount _simGetGeometricCount=nullptr;
ptr_simGetAllGeometrics _simGetAllGeometrics=nullptr;
ptr_simGetPurePrimitiveSizes _simGetPurePrimitiveSizes=nullptr;
ptr_simMakeDynamicAnnouncement _simMakeDynamicAnnouncement=nullptr;
ptr_simGetVerticesLocalFrame _simGetVerticesLocalFrame=nullptr;
ptr_simGetHeightfieldData _simGetHeightfieldData=nullptr;
ptr_simGetCumulativeMeshes _simGetCumulativeMeshes=nullptr;
ptr_simGetMass _simGetMass=nullptr;
ptr_simGetPrincipalMomentOfInertia _simGetPrincipalMomentOfInertia=nullptr;
ptr_simGetGravity _simGetGravity=nullptr;
ptr_simGetTimeDiffInMs _simGetTimeDiffInMs=nullptr;
ptr_simDoEntitiesCollide _simDoEntitiesCollide=nullptr;
ptr_simGetDistanceBetweenEntitiesIfSmaller _simGetDistanceBetweenEntitiesIfSmaller=nullptr;
ptr_simHandleJointControl _simHandleJointControl=nullptr;
ptr_simHandleCustomContact _simHandleCustomContact=nullptr;
ptr_simGetPureHollowScaling _simGetPureHollowScaling=nullptr;
ptr_simGetJointCallbackCallOrder _simGetJointCallbackCallOrder=nullptr;
ptr_simDynCallback _simDynCallback=nullptr;


// Deprecated begin
ptrSimGetMaterialId simGetMaterialId=nullptr;
ptrSimGetShapeMaterial simGetShapeMaterial=nullptr;
ptrSimHandleVarious simHandleVarious=nullptr;
ptrSimSerialPortOpen simSerialPortOpen=nullptr;
ptrSimSerialPortClose simSerialPortClose=nullptr;
ptrSimSerialPortSend simSerialPortSend=nullptr;
ptrSimSerialPortRead simSerialPortRead=nullptr;
ptrSimJointGetForce simJointGetForce=nullptr;
ptrSimGetPathPlanningHandle simGetPathPlanningHandle=nullptr;
ptrSimGetMotionPlanningHandle simGetMotionPlanningHandle=nullptr;
ptrSimGetMpConfigForTipPose simGetMpConfigForTipPose=nullptr;
ptrSimFindMpPath simFindMpPath=nullptr;
ptrSimSimplifyMpPath simSimplifyMpPath=nullptr;
ptrSimGetMpConfigTransition simGetMpConfigTransition=nullptr;
ptrSimFindIkPath simFindIkPath=nullptr;
ptrSimCreateMotionPlanning simCreateMotionPlanning=nullptr;
ptrSimRemoveMotionPlanning simRemoveMotionPlanning=nullptr;
ptrSimSearchPath simSearchPath=nullptr;
ptrSimInitializePathSearch simInitializePathSearch=nullptr;
ptrSimPerformPathSearchStep simPerformPathSearchStep=nullptr;
ptrSimLockInterface simLockInterface=nullptr;
ptrSimCopyPasteSelectedObjects simCopyPasteSelectedObjects=nullptr;
ptrSimResetPath simResetPath=nullptr;
ptrSimHandlePath simHandlePath=nullptr;
ptrSimResetJoint simResetJoint=nullptr;
ptrSimHandleJoint simHandleJoint=nullptr;
ptrSimAppendScriptArrayEntry simAppendScriptArrayEntry=nullptr;
ptrSimClearScriptVariable simClearScriptVariable=nullptr;
ptr_simGetJointOdeParameters _simGetJointOdeParameters=nullptr;
ptr_simGetJointBulletParameters _simGetJointBulletParameters=nullptr;
ptr_simGetOdeMaxContactFrictionCFMandERP _simGetOdeMaxContactFrictionCFMandERP=nullptr;
ptr_simGetBulletCollisionMargin _simGetBulletCollisionMargin=nullptr;
ptr_simGetBulletStickyContact _simGetBulletStickyContact=nullptr;
ptr_simGetBulletRestitution _simGetBulletRestitution=nullptr;
ptr_simGetVortexParameters _simGetVortexParameters=nullptr;
ptr_simGetNewtonParameters _simGetNewtonParameters=nullptr;
ptr_simGetDamping _simGetDamping=nullptr;
ptr_simGetFriction _simGetFriction=nullptr;
ptrSimAddSceneCustomData simAddSceneCustomData=nullptr;
ptrSimGetSceneCustomDataLength simGetSceneCustomDataLength=nullptr;
ptrSimGetSceneCustomData simGetSceneCustomData=nullptr;
ptrSimAddObjectCustomData simAddObjectCustomData=nullptr;
ptrSimGetObjectCustomDataLength simGetObjectCustomDataLength=nullptr;
ptrSimGetObjectCustomData simGetObjectCustomData=nullptr;
ptrSimCreateUI simCreateUI=nullptr;
ptrSimCreateUIButton simCreateUIButton=nullptr;
ptrSimGetUIHandle simGetUIHandle=nullptr;
ptrSimGetUIProperty simGetUIProperty=nullptr;
ptrSimGetUIEventButton simGetUIEventButton=nullptr;
ptrSimSetUIProperty simSetUIProperty=nullptr;
ptrSimGetUIButtonProperty simGetUIButtonProperty=nullptr;
ptrSimSetUIButtonProperty simSetUIButtonProperty=nullptr;
ptrSimGetUIButtonSize simGetUIButtonSize=nullptr;
ptrSimSetUIButtonLabel simSetUIButtonLabel=nullptr;
ptrSimGetUIButtonLabel simGetUIButtonLabel=nullptr;
ptrSimSetUISlider simSetUISlider=nullptr;
ptrSimGetUISlider simGetUISlider=nullptr;
ptrSimSetUIButtonColor simSetUIButtonColor=nullptr;
ptrSimSetUIButtonTexture simSetUIButtonTexture=nullptr;
ptrSimCreateUIButtonArray simCreateUIButtonArray=nullptr;
ptrSimSetUIButtonArrayColor simSetUIButtonArrayColor=nullptr;
ptrSimDeleteUIButtonArray simDeleteUIButtonArray=nullptr;
ptrSimRemoveUI simRemoveUI=nullptr;
ptrSimSetUIPosition simSetUIPosition=nullptr;
ptrSimGetUIPosition simGetUIPosition=nullptr;
ptrSimLoadUI simLoadUI=nullptr;
ptrSimSaveUI simSaveUI=nullptr;
ptrSimHandleGeneralCallbackScript simHandleGeneralCallbackScript=nullptr;
ptrSimRegisterCustomLuaFunction simRegisterCustomLuaFunction=nullptr;
ptrSimRegisterCustomLuaVariable simRegisterCustomLuaVariable=nullptr;
ptrSimRegisterContactCallback simRegisterContactCallback=nullptr;
ptrSimGetMechanismHandle simGetMechanismHandle=nullptr;
ptrSimHandleMechanism simHandleMechanism=nullptr;
ptrSimHandleCustomizationScripts simHandleCustomizationScripts=nullptr;
ptrSimCallScriptFunction simCallScriptFunction=nullptr;
ptrSimSetVisionSensorFilter simSetVisionSensorFilter=nullptr;
ptrSimGetVisionSensorFilter simGetVisionSensorFilter=nullptr;
ptrSimGetScriptSimulationParameter simGetScriptSimulationParameter=nullptr;
ptrSimSetScriptSimulationParameter simSetScriptSimulationParameter=nullptr;
ptrSimSetJointForce simSetJointForce=nullptr;
ptrSimHandleMill simHandleMill=nullptr;
ptrSimResetMill simResetMill=nullptr;
ptrSimResetMilling simResetMilling=nullptr;
ptrSimApplyMilling simApplyMilling=nullptr;
ptr_simGetParentFollowsDynamic _simGetParentFollowsDynamic=nullptr;
ptrSimGetNameSuffix simGetNameSuffix=nullptr;
ptrSimSetNameSuffix simSetNameSuffix=nullptr;
ptrSimAddStatusbarMessage simAddStatusbarMessage=nullptr;
// Deprecated end


LIBRARY loadSimLibrary(const char* pathAndFilename)
{
    #ifdef QT_FRAMEWORK
        QLibrary* lib=new QLibrary(pathAndFilename);
        if (!lib->load())
        {
            delete lib;
            lib=NULL;
        }
        return lib;
    #else
        #ifdef _WIN32
            return LoadLibraryA(pathAndFilename);
        #elif defined (__linux) || defined (__APPLE__)
            return dlopen(pathAndFilename,RTLD_LAZY);
        #endif
    #endif // QT_FRAMEWORK
}

void unloadSimLibrary(LIBRARY lib)
{
    #ifdef QT_FRAMEWORK
        if (lib!=0)
        {
            lib->unload();
            delete lib;
        }
    #else
        #ifdef _WIN32
            if (lib!=0)
                FreeLibrary(lib);
        #elif defined (__linux) || defined (__APPLE__)
                dlclose(lib);
        #endif
    #endif // QT_FRAMEWORK
}

FARPROC _getProcAddress(LIBRARY lib,const char* funcName)
{
    #ifdef QT_FRAMEWORK
        return (void*)lib->resolve(funcName);
    #else
        #ifdef _WIN32
            return GetProcAddress(lib,funcName);
        #elif defined (__linux) || defined (__APPLE__)
            return dlsym(lib,funcName);
        #endif
    #endif // QT_FRAMEWORK
}

int getSimProcAddresses(LIBRARY lib)
{
    simRunSimulator=(ptrSimRunSimulator)(_getProcAddress(lib,"simRunSimulator"));
    simRunSimulatorEx=(ptrSimRunSimulatorEx)(_getProcAddress(lib,"simRunSimulatorEx"));
    simGetSimulatorMessage=(ptrSimGetSimulatorMessage)(_getProcAddress(lib,"simGetSimulatorMessage"));
    simGetMainWindow=(ptrSimGetMainWindow)(_getProcAddress(lib,"simGetMainWindow"));
    simGetLastError=(ptrSimGetLastError)(_getProcAddress(lib,"simGetLastError"));
    simLoadModule=(ptrSimLoadModule)(_getProcAddress(lib,"simLoadModule"));
    simUnloadModule=(ptrSimUnloadModule)(_getProcAddress(lib,"simUnloadModule"));
    simSendModuleMessage=(ptrSimSendModuleMessage)(_getProcAddress(lib,"simSendModuleMessage"));
    simSetBooleanParameter=(ptrSimSetBooleanParameter)(_getProcAddress(lib,"simSetBooleanParameter"));
    simGetBooleanParameter=(ptrSimGetBooleanParameter)(_getProcAddress(lib,"simGetBooleanParameter"));
    simSetBoolParameter=(ptrSimSetBoolParameter)(_getProcAddress(lib,"simSetBoolParameter"));
    simGetBoolParameter=(ptrSimGetBoolParameter)(_getProcAddress(lib,"simGetBoolParameter"));
    simSetIntegerParameter=(ptrSimSetIntegerParameter)(_getProcAddress(lib,"simSetIntegerParameter"));
    simGetIntegerParameter=(ptrSimGetIntegerParameter)(_getProcAddress(lib,"simGetIntegerParameter"));
    simSetInt32Parameter=(ptrSimSetInt32Parameter)(_getProcAddress(lib,"simSetInt32Parameter"));
    simGetInt32Parameter=(ptrSimGetInt32Parameter)(_getProcAddress(lib,"simGetInt32Parameter"));
    simGetUInt64Parameter=(ptrSimGetUInt64Parameter)(_getProcAddress(lib,"simGetUInt64Parameter"));
    simSetFloatingParameter=(ptrSimSetFloatingParameter)(_getProcAddress(lib,"simSetFloatingParameter"));
    simGetFloatingParameter=(ptrSimGetFloatingParameter)(_getProcAddress(lib,"simGetFloatingParameter"));
    simSetFloatParameter=(ptrSimSetFloatParameter)(_getProcAddress(lib,"simSetFloatParameter"));
    simGetFloatParameter=(ptrSimGetFloatParameter)(_getProcAddress(lib,"simGetFloatParameter"));
    simSetStringParameter=(ptrSimSetStringParameter)(_getProcAddress(lib,"simSetStringParameter"));
    simGetStringParameter=(ptrSimGetStringParameter)(_getProcAddress(lib,"simGetStringParameter"));
    simGetObjectHandle=(ptrSimGetObjectHandle)(_getProcAddress(lib,"simGetObjectHandle"));
    simRemoveObject=(ptrSimRemoveObject)(_getProcAddress(lib,"simRemoveObject"));
    simRemoveModel=(ptrSimRemoveModel)(_getProcAddress(lib,"simRemoveModel"));
    simGetObjectName=(ptrSimGetObjectName)(_getProcAddress(lib,"simGetObjectName"));
    simGetObjects=(ptrSimGetObjects)(_getProcAddress(lib,"simGetObjects"));
    simSetObjectName=(ptrSimSetObjectName)(_getProcAddress(lib,"simSetObjectName"));
    simGetCollectionHandle=(ptrSimGetCollectionHandle)(_getProcAddress(lib,"simGetCollectionHandle"));
    simRemoveCollection=(ptrSimRemoveCollection)(_getProcAddress(lib,"simRemoveCollection"));
    simEmptyCollection=(ptrSimEmptyCollection)(_getProcAddress(lib,"simEmptyCollection"));
    simGetCollectionName=(ptrSimGetCollectionName)(_getProcAddress(lib,"simGetCollectionName"));
    simSetCollectionName=(ptrSimSetCollectionName)(_getProcAddress(lib,"simSetCollectionName"));
    simGetObjectMatrix=(ptrSimGetObjectMatrix)(_getProcAddress(lib,"simGetObjectMatrix"));
    simSetObjectMatrix=(ptrSimSetObjectMatrix)(_getProcAddress(lib,"simSetObjectMatrix"));
    simGetObjectPosition=(ptrSimGetObjectPosition)(_getProcAddress(lib,"simGetObjectPosition"));
    simSetObjectPosition=(ptrSimSetObjectPosition)(_getProcAddress(lib,"simSetObjectPosition"));
    simGetObjectOrientation=(ptrSimGetObjectOrientation)(_getProcAddress(lib,"simGetObjectOrientation"));
    simSetObjectOrientation=(ptrSimSetObjectOrientation)(_getProcAddress(lib,"simSetObjectOrientation"));
    simGetJointPosition=(ptrSimGetJointPosition)(_getProcAddress(lib,"simGetJointPosition"));
    simSetJointPosition=(ptrSimSetJointPosition)(_getProcAddress(lib,"simSetJointPosition"));
    simSetJointTargetPosition=(ptrSimSetJointTargetPosition)(_getProcAddress(lib,"simSetJointTargetPosition"));
    simGetJointTargetPosition=(ptrSimGetJointTargetPosition)(_getProcAddress(lib,"simGetJointTargetPosition"));
    simSetJointMaxForce=(ptrSimSetJointMaxForce)(_getProcAddress(lib,"simSetJointMaxForce"));
    simGetPathPosition=(ptrSimGetPathPosition)(_getProcAddress(lib,"simGetPathPosition"));
    simSetPathPosition=(ptrSimSetPathPosition)(_getProcAddress(lib,"simSetPathPosition"));
    simGetPathLength=(ptrSimGetPathLength)(_getProcAddress(lib,"simGetPathLength"));
    simGetJointMatrix=(ptrSimGetJointMatrix)(_getProcAddress(lib,"simGetJointMatrix"));
    simSetSphericalJointMatrix=(ptrSimSetSphericalJointMatrix)(_getProcAddress(lib,"simSetSphericalJointMatrix"));
    simGetJointInterval=(ptrSimGetJointInterval)(_getProcAddress(lib,"simGetJointInterval"));
    simSetJointInterval=(ptrSimSetJointInterval)(_getProcAddress(lib,"simSetJointInterval"));
    simGetObjectParent=(ptrSimGetObjectParent)(_getProcAddress(lib,"simGetObjectParent"));
    simGetObjectChild=(ptrSimGetObjectChild)(_getProcAddress(lib,"simGetObjectChild"));
    simSetObjectParent=(ptrSimSetObjectParent)(_getProcAddress(lib,"simSetObjectParent"));
    simGetObjectType=(ptrSimGetObjectType)(_getProcAddress(lib,"simGetObjectType"));
    simGetJointType=(ptrSimGetJointType)(_getProcAddress(lib,"simGetJointType"));
    simBuildIdentityMatrix=(ptrSimBuildIdentityMatrix)(_getProcAddress(lib,"simBuildIdentityMatrix"));
    simCopyMatrix=(ptrSimCopyMatrix)(_getProcAddress(lib,"simCopyMatrix"));
    simBuildMatrix=(ptrSimBuildMatrix)(_getProcAddress(lib,"simBuildMatrix"));
    simGetEulerAnglesFromMatrix=(ptrSimGetEulerAnglesFromMatrix)(_getProcAddress(lib,"simGetEulerAnglesFromMatrix"));
    simInvertMatrix=(ptrSimInvertMatrix)(_getProcAddress(lib,"simInvertMatrix"));
    simMultiplyMatrices=(ptrSimMultiplyMatrices)(_getProcAddress(lib,"simMultiplyMatrices"));
    simInterpolateMatrices=(ptrSimInterpolateMatrices)(_getProcAddress(lib,"simInterpolateMatrices"));
    simTransformVector=(ptrSimTransformVector)(_getProcAddress(lib,"simTransformVector"));
    simReservedCommand=(ptrSimReservedCommand)(_getProcAddress(lib,"simReservedCommand"));
    simGetSimulationTime=(ptrSimGetSimulationTime)(_getProcAddress(lib,"simGetSimulationTime"));
    simGetSimulationState=(ptrSimGetSimulationState)(_getProcAddress(lib,"simGetSimulationState"));
    simGetSystemTime=(ptrSimGetSystemTime)(_getProcAddress(lib,"simGetSystemTime"));
    simGetSystemTimeInMilliseconds=(ptrSimGetSystemTimeInMilliseconds)(_getProcAddress(lib,"simGetSystemTimeInMilliseconds"));
    simGetSystemTimeInMs=(ptrSimGetSystemTimeInMs)(_getProcAddress(lib,"simGetSystemTimeInMs"));
    simLoadScene=(ptrSimLoadScene)(_getProcAddress(lib,"simLoadScene"));
    simCloseScene=(ptrSimCloseScene)(_getProcAddress(lib,"simCloseScene"));
    simSaveScene=(ptrSimSaveScene)(_getProcAddress(lib,"simSaveScene"));
    simLoadModel=(ptrSimLoadModel)(_getProcAddress(lib,"simLoadModel"));
    simSaveModel=(ptrSimSaveModel)(_getProcAddress(lib,"simSaveModel"));
    simAddModuleMenuEntry=(ptrSimAddModuleMenuEntry)(_getProcAddress(lib,"simAddModuleMenuEntry"));
    simSetModuleMenuItemState=(ptrSimSetModuleMenuItemState)(_getProcAddress(lib,"simSetModuleMenuItemState"));
    simDoesFileExist=(ptrSimDoesFileExist)(_getProcAddress(lib,"simDoesFileExist"));
    simIsObjectInSelection=(ptrSimIsObjectInSelection)(_getProcAddress(lib,"simIsObjectInSelection"));
    simAddObjectToSelection=(ptrSimAddObjectToSelection)(_getProcAddress(lib,"simAddObjectToSelection"));
    simRemoveObjectFromSelection=(ptrSimRemoveObjectFromSelection)(_getProcAddress(lib,"simRemoveObjectFromSelection"));
    simGetObjectSelectionSize=(ptrSimGetObjectSelectionSize)(_getProcAddress(lib,"simGetObjectSelectionSize"));
    simGetObjectLastSelection=(ptrSimGetObjectLastSelection)(_getProcAddress(lib,"simGetObjectLastSelection"));
    simGetObjectSelection=(ptrSimGetObjectSelection)(_getProcAddress(lib,"simGetObjectSelection"));
    simHandleCollision=(ptrSimHandleCollision)(_getProcAddress(lib,"simHandleCollision"));
    simReadCollision=(ptrSimReadCollision)(_getProcAddress(lib,"simReadCollision"));
    simHandleDistance=(ptrSimHandleDistance)(_getProcAddress(lib,"simHandleDistance"));
    simReadDistance=(ptrSimReadDistance)(_getProcAddress(lib,"simReadDistance"));
    simHandleProximitySensor=(ptrSimHandleProximitySensor)(_getProcAddress(lib,"simHandleProximitySensor"));
    simReadProximitySensor=(ptrSimReadProximitySensor)(_getProcAddress(lib,"simReadProximitySensor"));
    simHandleIkGroup=(ptrSimHandleIkGroup)(_getProcAddress(lib,"simHandleIkGroup"));
    simCheckIkGroup=(ptrSimCheckIkGroup)(_getProcAddress(lib,"simCheckIkGroup"));
    simHandleDynamics=(ptrSimHandleDynamics)(_getProcAddress(lib,"simHandleDynamics"));
    simGetScriptHandle=(ptrSimGetScriptHandle)(_getProcAddress(lib,"simGetScriptHandle"));
    simSetScriptText=(ptrSimSetScriptText)(_getProcAddress(lib,"simSetScriptText"));
    simGetScriptText=(ptrSimGetScriptText)(_getProcAddress(lib,"simGetScriptText"));
    simGetScriptProperty=(ptrSimGetScriptProperty)(_getProcAddress(lib,"simGetScriptProperty"));
    simAssociateScriptWithObject=(ptrSimAssociateScriptWithObject)(_getProcAddress(lib,"simAssociateScriptWithObject"));
    simGetScript=(ptrSimGetScript)(_getProcAddress(lib,"simGetScript"));
    simGetScriptAssociatedWithObject=(ptrSimGetScriptAssociatedWithObject)(_getProcAddress(lib,"simGetScriptAssociatedWithObject"));
    simGetCustomizationScriptAssociatedWithObject=(ptrSimGetCustomizationScriptAssociatedWithObject)(_getProcAddress(lib,"simGetCustomizationScriptAssociatedWithObject"));
    simGetObjectAssociatedWithScript=(ptrSimGetObjectAssociatedWithScript)(_getProcAddress(lib,"simGetObjectAssociatedWithScript"));
    simGetScriptName=(ptrSimGetScriptName)(_getProcAddress(lib,"simGetScriptName"));
    simHandleMainScript=(ptrSimHandleMainScript)(_getProcAddress(lib,"simHandleMainScript"));
    simResetScript=(ptrSimResetScript)(_getProcAddress(lib,"simResetScript"));
    simAddScript=(ptrSimAddScript)(_getProcAddress(lib,"simAddScript"));
    simRemoveScript=(ptrSimRemoveScript)(_getProcAddress(lib,"simRemoveScript"));
    simRefreshDialogs=(ptrSimRefreshDialogs)(_getProcAddress(lib,"simRefreshDialogs"));
    simGetCollisionHandle=(ptrSimGetCollisionHandle)(_getProcAddress(lib,"simGetCollisionHandle"));
    simGetDistanceHandle=(ptrSimGetDistanceHandle)(_getProcAddress(lib,"simGetDistanceHandle"));
    simGetIkGroupHandle=(ptrSimGetIkGroupHandle)(_getProcAddress(lib,"simGetIkGroupHandle"));
    simResetCollision=(ptrSimResetCollision)(_getProcAddress(lib,"simResetCollision"));
    simResetDistance=(ptrSimResetDistance)(_getProcAddress(lib,"simResetDistance"));
    simResetProximitySensor=(ptrSimResetProximitySensor)(_getProcAddress(lib,"simResetProximitySensor"));
    simCheckProximitySensor=(ptrSimCheckProximitySensor)(_getProcAddress(lib,"simCheckProximitySensor"));
    simCheckProximitySensorEx=(ptrSimCheckProximitySensorEx)(_getProcAddress(lib,"simCheckProximitySensorEx"));
    simCheckProximitySensorEx2=(ptrSimCheckProximitySensorEx2)(_getProcAddress(lib,"simCheckProximitySensorEx2"));
    simCreateBuffer=(ptrSimCreateBuffer)(_getProcAddress(lib,"simCreateBuffer"));
    simReleaseBuffer=(ptrSimReleaseBuffer)(_getProcAddress(lib,"simReleaseBuffer"));
    simCheckCollision=(ptrSimCheckCollision)(_getProcAddress(lib,"simCheckCollision"));
    simCheckCollisionEx=(ptrSimCheckCollisionEx)(_getProcAddress(lib,"simCheckCollisionEx"));
    simCheckDistance=(ptrSimCheckDistance)(_getProcAddress(lib,"simCheckDistance"));
    simGetObjectConfiguration=(ptrSimGetObjectConfiguration)(_getProcAddress(lib,"simGetObjectConfiguration"));
    simSetObjectConfiguration=(ptrSimSetObjectConfiguration)(_getProcAddress(lib,"simSetObjectConfiguration"));
    simGetConfigurationTree=(ptrSimGetConfigurationTree)(_getProcAddress(lib,"simGetConfigurationTree"));
    simSetConfigurationTree=(ptrSimSetConfigurationTree)(_getProcAddress(lib,"simSetConfigurationTree"));
    simSetSimulationTimeStep=(ptrSimSetSimulationTimeStep)(_getProcAddress(lib,"simSetSimulationTimeStep"));
    simGetSimulationTimeStep=(ptrSimGetSimulationTimeStep)(_getProcAddress(lib,"simGetSimulationTimeStep"));
    simGetRealTimeSimulation=(ptrSimGetRealTimeSimulation)(_getProcAddress(lib,"simGetRealTimeSimulation"));
    simIsRealTimeSimulationStepNeeded=(ptrSimIsRealTimeSimulationStepNeeded)(_getProcAddress(lib,"simIsRealTimeSimulationStepNeeded"));
    simAdjustRealTimeTimer=(ptrSimAdjustRealTimeTimer)(_getProcAddress(lib,"simAdjustRealTimeTimer"));
    simGetSimulationPassesPerRenderingPass=(ptrSimGetSimulationPassesPerRenderingPass)(_getProcAddress(lib,"simGetSimulationPassesPerRenderingPass"));
    simAdvanceSimulationByOneStep=(ptrSimAdvanceSimulationByOneStep)(_getProcAddress(lib,"simAdvanceSimulationByOneStep"));
    simStartSimulation=(ptrSimStartSimulation)(_getProcAddress(lib,"simStartSimulation"));
    simStopSimulation=(ptrSimStopSimulation)(_getProcAddress(lib,"simStopSimulation"));
    simPauseSimulation=(ptrSimPauseSimulation)(_getProcAddress(lib,"simPauseSimulation"));
    simBroadcastMessage=(ptrSimBroadcastMessage)(_getProcAddress(lib,"simBroadcastMessage"));
    simGetModuleName=(ptrSimGetModuleName)(_getProcAddress(lib,"simGetModuleName"));
    simFloatingViewAdd=(ptrSimFloatingViewAdd)(_getProcAddress(lib,"simFloatingViewAdd"));
    simFloatingViewRemove=(ptrSimFloatingViewRemove)(_getProcAddress(lib,"simFloatingViewRemove"));
    simAdjustView=(ptrSimAdjustView)(_getProcAddress(lib,"simAdjustView"));
    simSetLastError=(ptrSimSetLastError)(_getProcAddress(lib,"simSetLastError"));
    simHandleGraph=(ptrSimHandleGraph)(_getProcAddress(lib,"simHandleGraph"));
    simResetGraph=(ptrSimResetGraph)(_getProcAddress(lib,"simResetGraph"));
    simSetNavigationMode=(ptrSimSetNavigationMode)(_getProcAddress(lib,"simSetNavigationMode"));
    simGetNavigationMode=(ptrSimGetNavigationMode)(_getProcAddress(lib,"simGetNavigationMode"));
    simSetPage=(ptrSimSetPage)(_getProcAddress(lib,"simSetPage"));
    simGetPage=(ptrSimGetPage)(_getProcAddress(lib,"simGetPage"));
    simDisplayDialog=(ptrSimDisplayDialog)(_getProcAddress(lib,"simDisplayDialog"));
    simGetDialogResult=(ptrSimGetDialogResult)(_getProcAddress(lib,"simGetDialogResult"));
    simGetDialogInput=(ptrSimGetDialogInput)(_getProcAddress(lib,"simGetDialogInput"));
    simEndDialog=(ptrSimEndDialog)(_getProcAddress(lib,"simEndDialog"));
    simRegisterScriptCallbackFunction=(ptrSimRegisterScriptCallbackFunction)(_getProcAddress(lib,"simRegisterScriptCallbackFunction"));
    simRegisterScriptVariable=(ptrSimRegisterScriptVariable)(_getProcAddress(lib,"simRegisterScriptVariable"));
    simSetJointTargetVelocity=(ptrSimSetJointTargetVelocity)(_getProcAddress(lib,"simSetJointTargetVelocity"));
    simGetJointTargetVelocity=(ptrSimGetJointTargetVelocity)(_getProcAddress(lib,"simGetJointTargetVelocity"));
    simSetPathTargetNominalVelocity=(ptrSimSetPathTargetNominalVelocity)(_getProcAddress(lib,"simSetPathTargetNominalVelocity"));
    simGetScriptRawBuffer=(ptrSimGetScriptRawBuffer)(_getProcAddress(lib,"simGetScriptRawBuffer"));
    simSetScriptRawBuffer=(ptrSimSetScriptRawBuffer)(_getProcAddress(lib,"simSetScriptRawBuffer"));
    simReleaseScriptRawBuffer=(ptrSimReleaseScriptRawBuffer)(_getProcAddress(lib,"simReleaseScriptRawBuffer"));
    simCopyPasteObjects=(ptrSimCopyPasteObjects)(_getProcAddress(lib,"simCopyPasteObjects"));
    simScaleSelectedObjects=(ptrSimScaleSelectedObjects)(_getProcAddress(lib,"simScaleSelectedObjects"));
    simScaleObjects=(ptrSimScaleObjects)(_getProcAddress(lib,"simScaleObjects"));
    simDeleteSelectedObjects=(ptrSimDeleteSelectedObjects)(_getProcAddress(lib,"simDeleteSelectedObjects"));
    simGetObjectUniqueIdentifier=(ptrSimGetObjectUniqueIdentifier)(_getProcAddress(lib,"simGetObjectUniqueIdentifier"));
    simSendData=(ptrSimSendData)(_getProcAddress(lib,"simSendData"));
    simReceiveData=(ptrSimReceiveData)(_getProcAddress(lib,"simReceiveData"));
    simSetGraphUserData=(ptrSimSetGraphUserData)(_getProcAddress(lib,"simSetGraphUserData"));
    simAddDrawingObject=(ptrSimAddDrawingObject)(_getProcAddress(lib,"simAddDrawingObject"));
    simRemoveDrawingObject=(ptrSimRemoveDrawingObject)(_getProcAddress(lib,"simRemoveDrawingObject"));
    simAddDrawingObjectItem=(ptrSimAddDrawingObjectItem)(_getProcAddress(lib,"simAddDrawingObjectItem"));
    simAddParticleObject=(ptrSimAddParticleObject)(_getProcAddress(lib,"simAddParticleObject"));
    simRemoveParticleObject=(ptrSimRemoveParticleObject)(_getProcAddress(lib,"simRemoveParticleObject"));
    simAddParticleObjectItem=(ptrSimAddParticleObjectItem)(_getProcAddress(lib,"simAddParticleObjectItem"));
    simGetObjectSizeFactor=(ptrSimGetObjectSizeFactor)(_getProcAddress(lib,"simGetObjectSizeFactor"));
    simAnnounceSceneContentChange=(ptrSimAnnounceSceneContentChange)(_getProcAddress(lib,"simAnnounceSceneContentChange"));
    simSetIntegerSignal=(ptrSimSetIntegerSignal)(_getProcAddress(lib,"simSetIntegerSignal"));
    simGetIntegerSignal=(ptrSimGetIntegerSignal)(_getProcAddress(lib,"simGetIntegerSignal"));
    simClearIntegerSignal=(ptrSimClearIntegerSignal)(_getProcAddress(lib,"simClearIntegerSignal"));
    simSetFloatSignal=(ptrSimSetFloatSignal)(_getProcAddress(lib,"simSetFloatSignal"));
    simGetFloatSignal=(ptrSimGetFloatSignal)(_getProcAddress(lib,"simGetFloatSignal"));
    simClearFloatSignal=(ptrSimClearFloatSignal)(_getProcAddress(lib,"simClearFloatSignal"));
    simSetDoubleSignal=(ptrSimSetDoubleSignal)(_getProcAddress(lib,"simSetDoubleSignal"));
    simGetDoubleSignal=(ptrSimGetDoubleSignal)(_getProcAddress(lib,"simGetDoubleSignal"));
    simClearDoubleSignal=(ptrSimClearDoubleSignal)(_getProcAddress(lib,"simClearDoubleSignal"));
    simSetStringSignal=(ptrSimSetStringSignal)(_getProcAddress(lib,"simSetStringSignal"));
    simGetStringSignal=(ptrSimGetStringSignal)(_getProcAddress(lib,"simGetStringSignal"));
    simClearStringSignal=(ptrSimClearStringSignal)(_getProcAddress(lib,"simClearStringSignal"));
    simGetSignalName=(ptrSimGetSignalName)(_getProcAddress(lib,"simGetSignalName"));
    simSetObjectProperty=(ptrSimSetObjectProperty)(_getProcAddress(lib,"simSetObjectProperty"));
    simGetObjectProperty=(ptrSimGetObjectProperty)(_getProcAddress(lib,"simGetObjectProperty"));
    simSetObjectSpecialProperty=(ptrSimSetObjectSpecialProperty)(_getProcAddress(lib,"simSetObjectSpecialProperty"));
    simGetObjectSpecialProperty=(ptrSimGetObjectSpecialProperty)(_getProcAddress(lib,"simGetObjectSpecialProperty"));
    simGetPositionOnPath=(ptrSimGetPositionOnPath)(_getProcAddress(lib,"simGetPositionOnPath"));
    simGetDataOnPath=(ptrSimGetDataOnPath)(_getProcAddress(lib,"simGetDataOnPath"));
    simGetOrientationOnPath=(ptrSimGetOrientationOnPath)(_getProcAddress(lib,"simGetOrientationOnPath"));
    simGetClosestPositionOnPath=(ptrSimGetClosestPositionOnPath)(_getProcAddress(lib,"simGetClosestPositionOnPath"));
    simReadForceSensor=(ptrSimReadForceSensor)(_getProcAddress(lib,"simReadForceSensor"));
    simBreakForceSensor=(ptrSimBreakForceSensor)(_getProcAddress(lib,"simBreakForceSensor"));
    simGetShapeVertex=(ptrSimGetShapeVertex)(_getProcAddress(lib,"simGetShapeVertex"));
    simGetShapeTriangle=(ptrSimGetShapeTriangle)(_getProcAddress(lib,"simGetShapeTriangle"));
    simSetLightParameters=(ptrSimSetLightParameters)(_getProcAddress(lib,"simSetLightParameters"));
    simGetLightParameters=(ptrSimGetLightParameters)(_getProcAddress(lib,"simGetLightParameters"));
    simGetVelocity=(ptrSimGetVelocity)(_getProcAddress(lib,"simGetVelocity"));
    simGetObjectVelocity=(ptrSimGetObjectVelocity)(_getProcAddress(lib,"simGetObjectVelocity"));
    simAddForceAndTorque=(ptrSimAddForceAndTorque)(_getProcAddress(lib,"simAddForceAndTorque"));
    simAddForce=(ptrSimAddForce)(_getProcAddress(lib,"simAddForce"));
    simSetExplicitHandling=(ptrSimSetExplicitHandling)(_getProcAddress(lib,"simSetExplicitHandling"));
    simGetExplicitHandling=(ptrSimGetExplicitHandling)(_getProcAddress(lib,"simGetExplicitHandling"));
    simGetLinkDummy=(ptrSimGetLinkDummy)(_getProcAddress(lib,"simGetLinkDummy"));
    simSetLinkDummy=(ptrSimSetLinkDummy)(_getProcAddress(lib,"simSetLinkDummy"));
    simSetModelProperty=(ptrSimSetModelProperty)(_getProcAddress(lib,"simSetModelProperty"));
    simGetModelProperty=(ptrSimGetModelProperty)(_getProcAddress(lib,"simGetModelProperty"));
    simSetShapeColor=(ptrSimSetShapeColor)(_getProcAddress(lib,"simSetShapeColor"));
    simGetShapeColor=(ptrSimGetShapeColor)(_getProcAddress(lib,"simGetShapeColor"));
    simResetDynamicObject=(ptrSimResetDynamicObject)(_getProcAddress(lib,"simResetDynamicObject"));
    simSetJointMode=(ptrSimSetJointMode)(_getProcAddress(lib,"simSetJointMode"));
    simGetJointMode=(ptrSimGetJointMode)(_getProcAddress(lib,"simGetJointMode"));
    simSerialOpen=(ptrSimSerialOpen)(_getProcAddress(lib,"simSerialOpen"));
    simSerialClose=(ptrSimSerialClose)(_getProcAddress(lib,"simSerialClose"));
    simSerialSend=(ptrSimSerialSend)(_getProcAddress(lib,"simSerialSend"));
    simSerialRead=(ptrSimSerialRead)(_getProcAddress(lib,"simSerialRead"));
    simSerialCheck=(ptrSimSerialCheck)(_getProcAddress(lib,"simSerialCheck"));
    simGetContactInfo=(ptrSimGetContactInfo)(_getProcAddress(lib,"simGetContactInfo"));
    simSetThreadIsFree=(ptrSimSetThreadIsFree)(_getProcAddress(lib,"simSetThreadIsFree"));
    simTubeOpen=(ptrSimTubeOpen)(_getProcAddress(lib,"simTubeOpen"));
    simTubeClose=(ptrSimTubeClose)(_getProcAddress(lib,"simTubeClose"));
    simTubeWrite=(ptrSimTubeWrite)(_getProcAddress(lib,"simTubeWrite"));
    simTubeRead=(ptrSimTubeRead)(_getProcAddress(lib,"simTubeRead"));
    simTubeStatus=(ptrSimTubeStatus)(_getProcAddress(lib,"simTubeStatus"));
    simAuxiliaryConsoleOpen=(ptrSimAuxiliaryConsoleOpen)(_getProcAddress(lib,"simAuxiliaryConsoleOpen"));
    simAuxiliaryConsoleClose=(ptrSimAuxiliaryConsoleClose)(_getProcAddress(lib,"simAuxiliaryConsoleClose"));
    simAuxiliaryConsoleShow=(ptrSimAuxiliaryConsoleShow)(_getProcAddress(lib,"simAuxiliaryConsoleShow"));
    simAuxiliaryConsolePrint=(ptrSimAuxiliaryConsolePrint)(_getProcAddress(lib,"simAuxiliaryConsolePrint"));
    simImportShape=(ptrSimImportShape)(_getProcAddress(lib,"simImportShape"));
    simImportMesh=(ptrSimImportMesh)(_getProcAddress(lib,"simImportMesh"));
    simExportMesh=(ptrSimExportMesh)(_getProcAddress(lib,"simExportMesh"));
    simCreateMeshShape=(ptrSimCreateMeshShape)(_getProcAddress(lib,"simCreateMeshShape"));
    simCreatePureShape=(ptrSimCreatePureShape)(_getProcAddress(lib,"simCreatePureShape"));
    simCreateHeightfieldShape=(ptrSimCreateHeightfieldShape)(_getProcAddress(lib,"simCreateHeightfieldShape"));
    simGetShapeMesh=(ptrSimGetShapeMesh)(_getProcAddress(lib,"simGetShapeMesh"));
    simAddBanner=(ptrSimAddBanner)(_getProcAddress(lib,"simAddBanner"));
    simRemoveBanner=(ptrSimRemoveBanner)(_getProcAddress(lib,"simRemoveBanner"));
    simCreateJoint=(ptrSimCreateJoint)(_getProcAddress(lib,"simCreateJoint"));
    simCreateDummy=(ptrSimCreateDummy)(_getProcAddress(lib,"simCreateDummy"));
    simCreateProximitySensor=(ptrSimCreateProximitySensor)(_getProcAddress(lib,"simCreateProximitySensor"));
    simCreatePath=(ptrSimCreatePath)(_getProcAddress(lib,"simCreatePath"));
    simInsertPathCtrlPoints=(ptrSimInsertPathCtrlPoints)(_getProcAddress(lib,"simInsertPathCtrlPoints"));
    simCutPathCtrlPoints=(ptrSimCutPathCtrlPoints)(_getProcAddress(lib,"simCutPathCtrlPoints"));
    simCreateForceSensor=(ptrSimCreateForceSensor)(_getProcAddress(lib,"simCreateForceSensor"));
    simCreateVisionSensor=(ptrSimCreateVisionSensor)(_getProcAddress(lib,"simCreateVisionSensor"));
    simGetObjectIntParameter=(ptrSimGetObjectIntParameter)(_getProcAddress(lib,"simGetObjectIntParameter"));
    simSetObjectIntParameter=(ptrSimSetObjectIntParameter)(_getProcAddress(lib,"simSetObjectIntParameter"));
    simGetObjectInt32Parameter=(ptrSimGetObjectInt32Parameter)(_getProcAddress(lib,"simGetObjectInt32Parameter"));
    simSetObjectInt32Parameter=(ptrSimSetObjectInt32Parameter)(_getProcAddress(lib,"simSetObjectInt32Parameter"));
    simGetObjectFloatParameter=(ptrSimGetObjectFloatParameter)(_getProcAddress(lib,"simGetObjectFloatParameter"));
    simSetObjectFloatParameter=(ptrSimSetObjectFloatParameter)(_getProcAddress(lib,"simSetObjectFloatParameter"));
    simGetObjectStringParameter=(ptrSimGetObjectStringParameter)(_getProcAddress(lib,"simGetObjectStringParameter"));
    simSetObjectStringParameter=(ptrSimSetObjectStringParameter)(_getProcAddress(lib,"simSetObjectStringParameter"));
    simSetSimulationPassesPerRenderingPass=(ptrSimSetSimulationPassesPerRenderingPass)(_getProcAddress(lib,"simSetSimulationPassesPerRenderingPass"));
    simGetRotationAxis=(ptrSimGetRotationAxis)(_getProcAddress(lib,"simGetRotationAxis"));
    simRotateAroundAxis=(ptrSimRotateAroundAxis)(_getProcAddress(lib,"simRotateAroundAxis"));
    simGetJointForce=(ptrSimGetJointForce)(_getProcAddress(lib,"simGetJointForce"));
    simGetJointMaxForce=(ptrSimGetJointMaxForce)(_getProcAddress(lib,"simGetJointMaxForce"));
    simSetArrayParameter=(ptrSimSetArrayParameter)(_getProcAddress(lib,"simSetArrayParameter"));
    simGetArrayParameter=(ptrSimGetArrayParameter)(_getProcAddress(lib,"simGetArrayParameter"));
    simSetIkGroupProperties=(ptrSimSetIkGroupProperties)(_getProcAddress(lib,"simSetIkGroupProperties"));
    simSetIkElementProperties=(ptrSimSetIkElementProperties)(_getProcAddress(lib,"simSetIkElementProperties"));
    simCameraFitToView=(ptrSimCameraFitToView)(_getProcAddress(lib,"simCameraFitToView"));
    simPersistentDataWrite=(ptrSimPersistentDataWrite)(_getProcAddress(lib,"simPersistentDataWrite"));
    simPersistentDataRead=(ptrSimPersistentDataRead)(_getProcAddress(lib,"simPersistentDataRead"));
    simIsHandleValid=(ptrSimIsHandleValid)(_getProcAddress(lib,"simIsHandleValid"));
    simHandleVisionSensor=(ptrSimHandleVisionSensor)(_getProcAddress(lib,"simHandleVisionSensor"));
    simReadVisionSensor=(ptrSimReadVisionSensor)(_getProcAddress(lib,"simReadVisionSensor"));
    simResetVisionSensor=(ptrSimResetVisionSensor)(_getProcAddress(lib,"simResetVisionSensor"));
    simCheckVisionSensor=(ptrSimCheckVisionSensor)(_getProcAddress(lib,"simCheckVisionSensor"));
    simCheckVisionSensorEx=(ptrSimCheckVisionSensorEx)(_getProcAddress(lib,"simCheckVisionSensorEx"));
    simGetVisionSensorResolution=(ptrSimGetVisionSensorResolution)(_getProcAddress(lib,"simGetVisionSensorResolution"));
    simGetVisionSensorImage=(ptrSimGetVisionSensorImage)(_getProcAddress(lib,"simGetVisionSensorImage"));
    simGetVisionSensorCharImage=(ptrSimGetVisionSensorCharImage)(_getProcAddress(lib,"simGetVisionSensorCharImage"));
    simSetVisionSensorImage=(ptrSimSetVisionSensorImage)(_getProcAddress(lib,"simSetVisionSensorImage"));
    simSetVisionSensorCharImage=(ptrSimSetVisionSensorCharImage)(_getProcAddress(lib,"simSetVisionSensorCharImage"));
    simGetVisionSensorDepthBuffer=(ptrSimGetVisionSensorDepthBuffer)(_getProcAddress(lib,"simGetVisionSensorDepthBuffer"));
    simGetObjectQuaternion=(ptrSimGetObjectQuaternion)(_getProcAddress(lib,"simGetObjectQuaternion"));
    simSetObjectQuaternion=(ptrSimSetObjectQuaternion)(_getProcAddress(lib,"simSetObjectQuaternion"));
    simRMLPosition=(ptrSimRMLPosition)(_getProcAddress(lib,"simRMLPosition"));
    simRMLVelocity=(ptrSimRMLVelocity)(_getProcAddress(lib,"simRMLVelocity"));
    simRMLPos=(ptrSimRMLPos)(_getProcAddress(lib,"simRMLPos"));
    simRMLVel=(ptrSimRMLVel)(_getProcAddress(lib,"simRMLVel"));
    simRMLStep=(ptrSimRMLStep)(_getProcAddress(lib,"simRMLStep"));
    simRMLRemove=(ptrSimRMLRemove)(_getProcAddress(lib,"simRMLRemove"));
    simBuildMatrixQ=(ptrSimBuildMatrixQ)(_getProcAddress(lib,"simBuildMatrixQ"));
    simGetQuaternionFromMatrix=(ptrSimGetQuaternionFromMatrix)(_getProcAddress(lib,"simGetQuaternionFromMatrix"));
    simFileDialog=(ptrSimFileDialog)(_getProcAddress(lib,"simFileDialog"));
    simMsgBox=(ptrSimMsgBox)(_getProcAddress(lib,"simMsgBox"));
    simSetShapeMassAndInertia=(ptrSimSetShapeMassAndInertia)(_getProcAddress(lib,"simSetShapeMassAndInertia"));
    simGetShapeMassAndInertia=(ptrSimGetShapeMassAndInertia)(_getProcAddress(lib,"simGetShapeMassAndInertia"));
    simGroupShapes=(ptrSimGroupShapes)(_getProcAddress(lib,"simGroupShapes"));
    simUngroupShape=(ptrSimUngroupShape)(_getProcAddress(lib,"simUngroupShape"));
    simConvexDecompose=(ptrSimConvexDecompose)(_getProcAddress(lib,"simConvexDecompose"));
    simGetIkGroupMatrix=(ptrSimGetIkGroupMatrix)(_getProcAddress(lib,"simGetIkGroupMatrix"));
    simAddGhost=(ptrSimAddGhost)(_getProcAddress(lib,"simAddGhost"));
    simModifyGhost=(ptrSimModifyGhost)(_getProcAddress(lib,"simModifyGhost"));
    simQuitSimulator=(ptrSimQuitSimulator)(_getProcAddress(lib,"simQuitSimulator"));
    simGetThreadId=(ptrSimGetThreadId)(_getProcAddress(lib,"simGetThreadId"));
    simLockResources=(ptrSimLockResources)(_getProcAddress(lib,"simLockResources"));
    simUnlockResources=(ptrSimUnlockResources)(_getProcAddress(lib,"simUnlockResources"));
    simEnableEventCallback=(ptrSimEnableEventCallback)(_getProcAddress(lib,"simEnableEventCallback"));
    simSetShapeMaterial=(ptrSimSetShapeMaterial)(_getProcAddress(lib,"simSetShapeMaterial"));
    simGetTextureId=(ptrSimGetTextureId)(_getProcAddress(lib,"simGetTextureId"));
    simReadTexture=(ptrSimReadTexture)(_getProcAddress(lib,"simReadTexture"));
    simWriteTexture=(ptrSimWriteTexture)(_getProcAddress(lib,"simWriteTexture"));
    simCreateTexture=(ptrSimCreateTexture)(_getProcAddress(lib,"simCreateTexture"));
    simWriteCustomDataBlock=(ptrSimWriteCustomDataBlock)(_getProcAddress(lib,"simWriteCustomDataBlock"));
    simReadCustomDataBlock=(ptrSimReadCustomDataBlock)(_getProcAddress(lib,"simReadCustomDataBlock"));
    simReadCustomDataBlockTags=(ptrSimReadCustomDataBlockTags)(_getProcAddress(lib,"simReadCustomDataBlockTags"));
    simAddPointCloud=(ptrSimAddPointCloud)(_getProcAddress(lib,"simAddPointCloud"));
    simModifyPointCloud=(ptrSimModifyPointCloud)(_getProcAddress(lib,"simModifyPointCloud"));
    simGetShapeGeomInfo=(ptrSimGetShapeGeomInfo)(_getProcAddress(lib,"simGetShapeGeomInfo"));
    simGetObjectsInTree=(ptrSimGetObjectsInTree)(_getProcAddress(lib,"simGetObjectsInTree"));
    simSetObjectSizeValues=(ptrSimSetObjectSizeValues)(_getProcAddress(lib,"simSetObjectSizeValues"));
    simGetObjectSizeValues=(ptrSimGetObjectSizeValues)(_getProcAddress(lib,"simGetObjectSizeValues"));
    simScaleObject=(ptrSimScaleObject)(_getProcAddress(lib,"simScaleObject"));
    simSetShapeTexture=(ptrSimSetShapeTexture)(_getProcAddress(lib,"simSetShapeTexture"));
    simGetShapeTextureId=(ptrSimGetShapeTextureId)(_getProcAddress(lib,"simGetShapeTextureId"));
    simGetCollectionObjects=(ptrSimGetCollectionObjects)(_getProcAddress(lib,"simGetCollectionObjects"));
    simSetScriptAttribute=(ptrSimSetScriptAttribute)(_getProcAddress(lib,"simSetScriptAttribute"));
    simGetScriptAttribute=(ptrSimGetScriptAttribute)(_getProcAddress(lib,"simGetScriptAttribute"));
    simReorientShapeBoundingBox=(ptrSimReorientShapeBoundingBox)(_getProcAddress(lib,"simReorientShapeBoundingBox"));
    simSwitchThread=(ptrSimSwitchThread)(_getProcAddress(lib,"simSwitchThread"));
    simCreateIkGroup=(ptrSimCreateIkGroup)(_getProcAddress(lib,"simCreateIkGroup"));
    simRemoveIkGroup=(ptrSimRemoveIkGroup)(_getProcAddress(lib,"simRemoveIkGroup"));
    simCreateIkElement=(ptrSimCreateIkElement)(_getProcAddress(lib,"simCreateIkElement"));
    simCreateCollection=(ptrSimCreateCollection)(_getProcAddress(lib,"simCreateCollection"));
    simAddObjectToCollection=(ptrSimAddObjectToCollection)(_getProcAddress(lib,"simAddObjectToCollection"));
    simSaveImage=(ptrSimSaveImage)(_getProcAddress(lib,"simSaveImage"));
    simLoadImage=(ptrSimLoadImage)(_getProcAddress(lib,"simLoadImage"));
    simGetScaledImage=(ptrSimGetScaledImage)(_getProcAddress(lib,"simGetScaledImage"));
    simTransformImage=(ptrSimTransformImage)(_getProcAddress(lib,"simTransformImage"));
    simGetQHull=(ptrSimGetQHull)(_getProcAddress(lib,"simGetQHull"));
    simGetDecimatedMesh=(ptrSimGetDecimatedMesh)(_getProcAddress(lib,"simGetDecimatedMesh"));
    simExportIk=(ptrSimExportIk)(_getProcAddress(lib,"simExportIk"));
    simCallScriptFunctionEx=(ptrSimCallScriptFunctionEx)(_getProcAddress(lib,"simCallScriptFunctionEx"));
    simComputeJacobian=(ptrSimComputeJacobian)(_getProcAddress(lib,"simComputeJacobian"));
    simGetConfigForTipPose=(ptrSimGetConfigForTipPose)(_getProcAddress(lib,"simGetConfigForTipPose"));
    simGenerateIkPath=(ptrSimGenerateIkPath)(_getProcAddress(lib,"simGenerateIkPath"));
    simGetExtensionString=(ptrSimGetExtensionString)(_getProcAddress(lib,"simGetExtensionString"));
    simComputeMassAndInertia=(ptrSimComputeMassAndInertia)(_getProcAddress(lib,"simComputeMassAndInertia"));
    simCreateStack=(ptrSimCreateStack)(_getProcAddress(lib,"simCreateStack"));
    simReleaseStack=(ptrSimReleaseStack)(_getProcAddress(lib,"simReleaseStack"));
    simCopyStack=(ptrSimCopyStack)(_getProcAddress(lib,"simCopyStack"));
    simPushNullOntoStack=(ptrSimPushNullOntoStack)(_getProcAddress(lib,"simPushNullOntoStack"));
    simPushBoolOntoStack=(ptrSimPushBoolOntoStack)(_getProcAddress(lib,"simPushBoolOntoStack"));
    simPushInt32OntoStack=(ptrSimPushInt32OntoStack)(_getProcAddress(lib,"simPushInt32OntoStack"));
    simPushFloatOntoStack=(ptrSimPushFloatOntoStack)(_getProcAddress(lib,"simPushFloatOntoStack"));
    simPushDoubleOntoStack=(ptrSimPushDoubleOntoStack)(_getProcAddress(lib,"simPushDoubleOntoStack"));
    simPushStringOntoStack=(ptrSimPushStringOntoStack)(_getProcAddress(lib,"simPushStringOntoStack"));
    simPushUInt8TableOntoStack=(ptrSimPushUInt8TableOntoStack)(_getProcAddress(lib,"simPushUInt8TableOntoStack"));
    simPushInt32TableOntoStack=(ptrSimPushInt32TableOntoStack)(_getProcAddress(lib,"simPushInt32TableOntoStack"));
    simPushFloatTableOntoStack=(ptrSimPushFloatTableOntoStack)(_getProcAddress(lib,"simPushFloatTableOntoStack"));
    simPushDoubleTableOntoStack=(ptrSimPushDoubleTableOntoStack)(_getProcAddress(lib,"simPushDoubleTableOntoStack"));
    simPushTableOntoStack=(ptrSimPushTableOntoStack)(_getProcAddress(lib,"simPushTableOntoStack"));
    simInsertDataIntoStackTable=(ptrSimInsertDataIntoStackTable)(_getProcAddress(lib,"simInsertDataIntoStackTable"));
    simGetStackSize=(ptrSimGetStackSize)(_getProcAddress(lib,"simGetStackSize"));
    simPopStackItem=(ptrSimPopStackItem)(_getProcAddress(lib,"simPopStackItem"));
    simMoveStackItemToTop=(ptrSimMoveStackItemToTop)(_getProcAddress(lib,"simMoveStackItemToTop"));
    simIsStackValueNull=(ptrSimIsStackValueNull)(_getProcAddress(lib,"simIsStackValueNull"));
    simGetStackBoolValue=(ptrSimGetStackBoolValue)(_getProcAddress(lib,"simGetStackBoolValue"));
    simGetStackInt32Value=(ptrSimGetStackInt32Value)(_getProcAddress(lib,"simGetStackInt32Value"));
    simGetStackFloatValue=(ptrSimGetStackFloatValue)(_getProcAddress(lib,"simGetStackFloatValue"));
    simGetStackDoubleValue=(ptrSimGetStackDoubleValue)(_getProcAddress(lib,"simGetStackDoubleValue"));
    simGetStackStringValue=(ptrSimGetStackStringValue)(_getProcAddress(lib,"simGetStackStringValue"));
    simGetStackTableInfo=(ptrSimGetStackTableInfo)(_getProcAddress(lib,"simGetStackTableInfo"));
    simGetStackUInt8Table=(ptrSimGetStackUInt8Table)(_getProcAddress(lib,"simGetStackUInt8Table"));
    simGetStackInt32Table=(ptrSimGetStackInt32Table)(_getProcAddress(lib,"simGetStackInt32Table"));
    simGetStackFloatTable=(ptrSimGetStackFloatTable)(_getProcAddress(lib,"simGetStackFloatTable"));
    simGetStackDoubleTable=(ptrSimGetStackDoubleTable)(_getProcAddress(lib,"simGetStackDoubleTable"));
    simUnfoldStackTable=(ptrSimUnfoldStackTable)(_getProcAddress(lib,"simUnfoldStackTable"));
    simDebugStack=(ptrSimDebugStack)(_getProcAddress(lib,"simDebugStack"));
    simSetScriptVariable=(ptrSimSetScriptVariable)(_getProcAddress(lib,"simSetScriptVariable"));
    simGetEngineFloatParameter=(ptrSimGetEngineFloatParameter)(_getProcAddress(lib,"simGetEngineFloatParameter"));
    simGetEngineInt32Parameter=(ptrSimGetEngineInt32Parameter)(_getProcAddress(lib,"simGetEngineInt32Parameter"));
    simGetEngineBoolParameter=(ptrSimGetEngineBoolParameter)(_getProcAddress(lib,"simGetEngineBoolParameter"));
    simSetEngineFloatParameter=(ptrSimSetEngineFloatParameter)(_getProcAddress(lib,"simSetEngineFloatParameter"));
    simSetEngineInt32Parameter=(ptrSimSetEngineInt32Parameter)(_getProcAddress(lib,"simSetEngineInt32Parameter"));
    simSetEngineBoolParameter=(ptrSimSetEngineBoolParameter)(_getProcAddress(lib,"simSetEngineBoolParameter"));
    simCreateOctree=(ptrSimCreateOctree)(_getProcAddress(lib,"simCreateOctree"));
    simCreatePointCloud=(ptrSimCreatePointCloud)(_getProcAddress(lib,"simCreatePointCloud"));
    simSetPointCloudOptions=(ptrSimSetPointCloudOptions)(_getProcAddress(lib,"simSetPointCloudOptions"));
    simGetPointCloudOptions=(ptrSimGetPointCloudOptions)(_getProcAddress(lib,"simGetPointCloudOptions"));
    simInsertVoxelsIntoOctree=(ptrSimInsertVoxelsIntoOctree)(_getProcAddress(lib,"simInsertVoxelsIntoOctree"));
    simRemoveVoxelsFromOctree=(ptrSimRemoveVoxelsFromOctree)(_getProcAddress(lib,"simRemoveVoxelsFromOctree"));
    simInsertPointsIntoPointCloud=(ptrSimInsertPointsIntoPointCloud)(_getProcAddress(lib,"simInsertPointsIntoPointCloud"));
    simRemovePointsFromPointCloud=(ptrSimRemovePointsFromPointCloud)(_getProcAddress(lib,"simRemovePointsFromPointCloud"));
    simIntersectPointsWithPointCloud=(ptrSimIntersectPointsWithPointCloud)(_getProcAddress(lib,"simIntersectPointsWithPointCloud"));
    simGetOctreeVoxels=(ptrSimGetOctreeVoxels)(_getProcAddress(lib,"simGetOctreeVoxels"));
    simGetPointCloudPoints=(ptrSimGetPointCloudPoints)(_getProcAddress(lib,"simGetPointCloudPoints"));
    simInsertObjectIntoOctree=(ptrSimInsertObjectIntoOctree)(_getProcAddress(lib,"simInsertObjectIntoOctree"));
    simSubtractObjectFromOctree=(ptrSimSubtractObjectFromOctree)(_getProcAddress(lib,"simSubtractObjectFromOctree"));
    simInsertObjectIntoPointCloud=(ptrSimInsertObjectIntoPointCloud)(_getProcAddress(lib,"simInsertObjectIntoPointCloud"));
    simSubtractObjectFromPointCloud=(ptrSimSubtractObjectFromPointCloud)(_getProcAddress(lib,"simSubtractObjectFromPointCloud"));
    simCheckOctreePointOccupancy=(ptrSimCheckOctreePointOccupancy)(_getProcAddress(lib,"simCheckOctreePointOccupancy"));
    simOpenTextEditor=(ptrSimOpenTextEditor)(_getProcAddress(lib,"simOpenTextEditor"));
    simPackTable=(ptrSimPackTable)(_getProcAddress(lib,"simPackTable"));
    simUnpackTable=(ptrSimUnpackTable)(_getProcAddress(lib,"simUnpackTable"));
    simSetReferencedHandles=(ptrSimSetReferencedHandles)(_getProcAddress(lib,"simSetReferencedHandles"));
    simGetReferencedHandles=(ptrSimGetReferencedHandles)(_getProcAddress(lib,"simGetReferencedHandles"));
    simGetShapeViz=(ptrSimGetShapeViz)(_getProcAddress(lib,"simGetShapeViz"));
    simExecuteScriptString=(ptrSimExecuteScriptString)(_getProcAddress(lib,"simExecuteScriptString"));
    simGetApiFunc=(ptrSimGetApiFunc)(_getProcAddress(lib,"simGetApiFunc"));
    simGetApiInfo=(ptrSimGetApiInfo)(_getProcAddress(lib,"simGetApiInfo"));
    simSetModuleInfo=(ptrSimSetModuleInfo)(_getProcAddress(lib,"simSetModuleInfo"));
    simGetModuleInfo=(ptrSimGetModuleInfo)(_getProcAddress(lib,"simGetModuleInfo"));
    simIsDeprecated=(ptrSimIsDeprecated)(_getProcAddress(lib,"simIsDeprecated"));
    simGetPersistentDataTags=(ptrSimGetPersistentDataTags)(_getProcAddress(lib,"simGetPersistentDataTags"));
    simEventNotification=(ptrSimEventNotification)(_getProcAddress(lib,"simEventNotification"));
    simApplyTexture=(ptrSimApplyTexture)(_getProcAddress(lib,"simApplyTexture"));
    simSetJointDependency=(ptrSimSetJointDependency)(_getProcAddress(lib,"simSetJointDependency"));
    simSetStringNamedParam=(ptrSimSetStringNamedParam)(_getProcAddress(lib,"simSetStringNamedParam"));
    simGetStringNamedParam=(ptrSimGetStringNamedParam)(_getProcAddress(lib,"simGetStringNamedParam"));
    simGetUserParameter=(ptrSimGetUserParameter)(_getProcAddress(lib,"simGetUserParameter"));
    simSetUserParameter=(ptrSimSetUserParameter)(_getProcAddress(lib,"simSetUserParameter"));
    simAddLog=(ptrSimAddLog)(_getProcAddress(lib,"simAddLog"));


    // Following courtesy of Stephen James:
    simExtLaunchUIThread=(ptrSimExtLaunchUIThread)(_getProcAddress(lib,"simExtLaunchUIThread"));
    simExtCanInitSimThread=(ptrSimExtCanInitSimThread)(_getProcAddress(lib,"simExtCanInitSimThread"));
    simExtSimThreadInit=(ptrSimExtSimThreadInit)(_getProcAddress(lib,"simExtSimThreadInit"));
    simExtSimThreadDestroy=(ptrSimExtSimThreadDestroy)(_getProcAddress(lib,"simExtSimThreadDestroy"));
    simExtPostExitRequest=(ptrSimExtPostExitRequest)(_getProcAddress(lib,"simExtPostExitRequest"));
    simExtGetExitRequest=(ptrSimExtGetExitRequest)(_getProcAddress(lib,"simExtGetExitRequest"));
    simExtStep=(ptrSimExtStep)(_getProcAddress(lib,"simExtStep"));
    simExtCallScriptFunction=(ptrSimExtCallScriptFunction)(_getProcAddress(lib,"simExtCallScriptFunction"));

    _simGetContactCallbackCount=(ptr_simGetContactCallbackCount)(_getProcAddress(lib,"_simGetContactCallbackCount"));
    _simGetContactCallback=(ptr_simGetContactCallback)(_getProcAddress(lib,"_simGetContactCallback"));
    _simSetDynamicSimulationIconCode=(ptr_simSetDynamicSimulationIconCode)(_getProcAddress(lib,"_simSetDynamicSimulationIconCode"));
    _simSetDynamicObjectFlagForVisualization=(ptr_simSetDynamicObjectFlagForVisualization)(_getProcAddress(lib,"_simSetDynamicObjectFlagForVisualization"));
    _simGetObjectListSize=(ptr_simGetObjectListSize)(_getProcAddress(lib,"_simGetObjectListSize"));
    _simGetObjectFromIndex=(ptr_simGetObjectFromIndex)(_getProcAddress(lib,"_simGetObjectFromIndex"));
    _simGetObjectID=(ptr_simGetObjectID)(_getProcAddress(lib,"_simGetObjectID"));
    _simGetObjectType=(ptr_simGetObjectType)(_getProcAddress(lib,"_simGetObjectType"));
    _simGetObjectChildren=(ptr_simGetObjectChildren)(_getProcAddress(lib,"_simGetObjectChildren"));
    _simGetGeomProxyFromShape=(ptr_simGetGeomProxyFromShape)(_getProcAddress(lib,"_simGetGeomProxyFromShape"));
    _simGetParentObject=(ptr_simGetParentObject)(_getProcAddress(lib,"_simGetParentObject"));
    _simGetObject=(ptr_simGetObject)(_getProcAddress(lib,"_simGetObject"));
    _simGetIkGroupObject=(ptr_simGetIkGroupObject)(_getProcAddress(lib,"_simGetIkGroupObject"));
    _simMpHandleIkGroupObject=(ptr_simMpHandleIkGroupObject)(_getProcAddress(lib,"_simMpHandleIkGroupObject"));
    _simGetObjectLocalTransformation=(ptr_simGetObjectLocalTransformation)(_getProcAddress(lib,"_simGetObjectLocalTransformation"));
    _simSetObjectLocalTransformation=(ptr_simSetObjectLocalTransformation)(_getProcAddress(lib,"_simSetObjectLocalTransformation"));
    _simSetObjectCumulativeTransformation=(ptr_simSetObjectCumulativeTransformation)(_getProcAddress(lib,"_simSetObjectCumulativeTransformation"));
    _simGetObjectCumulativeTransformation=(ptr_simGetObjectCumulativeTransformation)(_getProcAddress(lib,"_simGetObjectCumulativeTransformation"));
    _simIsShapeDynamicallyStatic=(ptr_simIsShapeDynamicallyStatic)(_getProcAddress(lib,"_simIsShapeDynamicallyStatic"));
    _simGetTreeDynamicProperty=(ptr_simGetTreeDynamicProperty)(_getProcAddress(lib,"_simGetTreeDynamicProperty"));
    _simGetDummyLinkType=(ptr_simGetDummyLinkType)(_getProcAddress(lib,"_simGetDummyLinkType"));
    _simGetJointMode=(ptr_simGetJointMode)(_getProcAddress(lib,"_simGetJointMode"));
    _simIsJointInHybridOperation=(ptr_simIsJointInHybridOperation)(_getProcAddress(lib,"_simIsJointInHybridOperation"));
    _simDisableDynamicTreeForManipulation=(ptr_simDisableDynamicTreeForManipulation)(_getProcAddress(lib,"_simDisableDynamicTreeForManipulation"));
    _simIsShapeDynamicallyRespondable=(ptr_simIsShapeDynamicallyRespondable)(_getProcAddress(lib,"_simIsShapeDynamicallyRespondable"));
    _simGetDynamicCollisionMask=(ptr_simGetDynamicCollisionMask)(_getProcAddress(lib,"_simGetDynamicCollisionMask"));
    _simGetLastParentForLocalGlobalCollidable=(ptr_simGetLastParentForLocalGlobalCollidable)(_getProcAddress(lib,"_simGetLastParentForLocalGlobalCollidable"));
    _simSetShapeIsStaticAndNotRespondableButDynamicTag=(ptr_simSetShapeIsStaticAndNotRespondableButDynamicTag)(_getProcAddress(lib,"_simSetShapeIsStaticAndNotRespondableButDynamicTag"));
    _simGetShapeIsStaticAndNotRespondableButDynamicTag=(ptr_simGetShapeIsStaticAndNotRespondableButDynamicTag)(_getProcAddress(lib,"_simGetShapeIsStaticAndNotRespondableButDynamicTag"));
    _simSetJointPosition=(ptr_simSetJointPosition)(_getProcAddress(lib,"_simSetJointPosition"));
    _simGetJointPosition=(ptr_simGetJointPosition)(_getProcAddress(lib,"_simGetJointPosition"));
    _simSetDynamicMotorPositionControlTargetPosition=(ptr_simSetDynamicMotorPositionControlTargetPosition)(_getProcAddress(lib,"_simSetDynamicMotorPositionControlTargetPosition"));
    _simGetInitialDynamicVelocity=(ptr_simGetInitialDynamicVelocity)(_getProcAddress(lib,"_simGetInitialDynamicVelocity"));
    _simSetInitialDynamicVelocity=(ptr_simSetInitialDynamicVelocity)(_getProcAddress(lib,"_simSetInitialDynamicVelocity"));
    _simGetInitialDynamicAngVelocity=(ptr_simGetInitialDynamicAngVelocity)(_getProcAddress(lib,"_simGetInitialDynamicAngVelocity"));
    _simSetInitialDynamicAngVelocity=(ptr_simSetInitialDynamicAngVelocity)(_getProcAddress(lib,"_simSetInitialDynamicAngVelocity"));
    _simGetStartSleeping=(ptr_simGetStartSleeping)(_getProcAddress(lib,"_simGetStartSleeping"));
    _simGetWasPutToSleepOnce=(ptr_simGetWasPutToSleepOnce)(_getProcAddress(lib,"_simGetWasPutToSleepOnce"));
    _simGetDynamicsFullRefreshFlag=(ptr_simGetDynamicsFullRefreshFlag)(_getProcAddress(lib,"_simGetDynamicsFullRefreshFlag"));
    _simSetDynamicsFullRefreshFlag=(ptr_simSetDynamicsFullRefreshFlag)(_getProcAddress(lib,"_simSetDynamicsFullRefreshFlag"));
    _simSetGeomProxyDynamicsFullRefreshFlag=(ptr_simSetGeomProxyDynamicsFullRefreshFlag)(_getProcAddress(lib,"_simSetGeomProxyDynamicsFullRefreshFlag"));
    _simGetGeomProxyDynamicsFullRefreshFlag=(ptr_simGetGeomProxyDynamicsFullRefreshFlag)(_getProcAddress(lib,"_simGetGeomProxyDynamicsFullRefreshFlag"));
    _simSetShapeDynamicVelocity=(ptr_simSetShapeDynamicVelocity)(_getProcAddress(lib,"_simSetShapeDynamicVelocity"));
    _simGetAdditionalForceAndTorque=(ptr_simGetAdditionalForceAndTorque)(_getProcAddress(lib,"_simGetAdditionalForceAndTorque"));
    _simClearAdditionalForceAndTorque=(ptr_simClearAdditionalForceAndTorque)(_getProcAddress(lib,"_simClearAdditionalForceAndTorque"));
    _simGetJointPositionInterval=(ptr_simGetJointPositionInterval)(_getProcAddress(lib,"_simGetJointPositionInterval"));
    _simGetJointType=(ptr_simGetJointType)(_getProcAddress(lib,"_simGetJointType"));
    _simIsForceSensorBroken=(ptr_simIsForceSensorBroken)(_getProcAddress(lib,"_simIsForceSensorBroken"));
    _simGetDynamicForceSensorLocalTransformationPart2=(ptr_simGetDynamicForceSensorLocalTransformationPart2)(_getProcAddress(lib,"_simGetDynamicForceSensorLocalTransformationPart2"));
    _simIsDynamicMotorEnabled=(ptr_simIsDynamicMotorEnabled)(_getProcAddress(lib,"_simIsDynamicMotorEnabled"));
    _simIsDynamicMotorPositionCtrlEnabled=(ptr_simIsDynamicMotorPositionCtrlEnabled)(_getProcAddress(lib,"_simIsDynamicMotorPositionCtrlEnabled"));
    _simIsDynamicMotorTorqueModulationEnabled=(ptr_simIsDynamicMotorTorqueModulationEnabled)(_getProcAddress(lib,"_simIsDynamicMotorTorqueModulationEnabled"));
    _simGetMotorPid=(ptr_simGetMotorPid)(_getProcAddress(lib,"_simGetMotorPid"));
    _simGetDynamicMotorTargetPosition=(ptr_simGetDynamicMotorTargetPosition)(_getProcAddress(lib,"_simGetDynamicMotorTargetPosition"));
    _simGetDynamicMotorTargetVelocity=(ptr_simGetDynamicMotorTargetVelocity)(_getProcAddress(lib,"_simGetDynamicMotorTargetVelocity"));
    _simGetDynamicMotorMaxForce=(ptr_simGetDynamicMotorMaxForce)(_getProcAddress(lib,"_simGetDynamicMotorMaxForce"));
    _simGetDynamicMotorUpperLimitVelocity=(ptr_simGetDynamicMotorUpperLimitVelocity)(_getProcAddress(lib,"_simGetDynamicMotorUpperLimitVelocity"));
    _simSetDynamicMotorReflectedPositionFromDynamicEngine=(ptr_simSetDynamicMotorReflectedPositionFromDynamicEngine)(_getProcAddress(lib,"_simSetDynamicMotorReflectedPositionFromDynamicEngine"));
    _simSetJointSphericalTransformation=(ptr_simSetJointSphericalTransformation)(_getProcAddress(lib,"_simSetJointSphericalTransformation"));
    _simAddForceSensorCumulativeForcesAndTorques=(ptr_simAddForceSensorCumulativeForcesAndTorques)(_getProcAddress(lib,"_simAddForceSensorCumulativeForcesAndTorques"));
    _simAddJointCumulativeForcesOrTorques=(ptr_simAddJointCumulativeForcesOrTorques)(_getProcAddress(lib,"_simAddJointCumulativeForcesOrTorques"));
    _simSetDynamicJointLocalTransformationPart2=(ptr_simSetDynamicJointLocalTransformationPart2)(_getProcAddress(lib,"_simSetDynamicJointLocalTransformationPart2"));
    _simSetDynamicForceSensorLocalTransformationPart2=(ptr_simSetDynamicForceSensorLocalTransformationPart2)(_getProcAddress(lib,"_simSetDynamicForceSensorLocalTransformationPart2"));
    _simSetDynamicJointLocalTransformationPart2IsValid=(ptr_simSetDynamicJointLocalTransformationPart2IsValid)(_getProcAddress(lib,"_simSetDynamicJointLocalTransformationPart2IsValid"));
    _simSetDynamicForceSensorLocalTransformationPart2IsValid=(ptr_simSetDynamicForceSensorLocalTransformationPart2IsValid)(_getProcAddress(lib,"_simSetDynamicForceSensorLocalTransformationPart2IsValid"));
    _simGetGeomWrapFromGeomProxy=(ptr_simGetGeomWrapFromGeomProxy)(_getProcAddress(lib,"_simGetGeomWrapFromGeomProxy"));
    _simGetLocalInertiaFrame=(ptr_simGetLocalInertiaFrame)(_getProcAddress(lib,"_simGetLocalInertiaFrame"));
    _simGetPurePrimitiveType=(ptr_simGetPurePrimitiveType)(_getProcAddress(lib,"_simGetPurePrimitiveType"));
    _simIsGeomWrapGeometric=(ptr_simIsGeomWrapGeometric)(_getProcAddress(lib,"_simIsGeomWrapGeometric"));
    _simIsGeomWrapConvex=(ptr_simIsGeomWrapConvex)(_getProcAddress(lib,"_simIsGeomWrapConvex"));
    _simGetGeometricCount=(ptr_simGetGeometricCount)(_getProcAddress(lib,"_simGetGeometricCount"));
    _simGetAllGeometrics=(ptr_simGetAllGeometrics)(_getProcAddress(lib,"_simGetAllGeometrics"));
    _simGetPurePrimitiveSizes=(ptr_simGetPurePrimitiveSizes)(_getProcAddress(lib,"_simGetPurePrimitiveSizes"));
    _simMakeDynamicAnnouncement=(ptr_simMakeDynamicAnnouncement)(_getProcAddress(lib,"_simMakeDynamicAnnouncement"));
    _simGetVerticesLocalFrame=(ptr_simGetVerticesLocalFrame)(_getProcAddress(lib,"_simGetVerticesLocalFrame"));
    _simGetHeightfieldData=(ptr_simGetHeightfieldData)(_getProcAddress(lib,"_simGetHeightfieldData"));
    _simGetCumulativeMeshes=(ptr_simGetCumulativeMeshes)(_getProcAddress(lib,"_simGetCumulativeMeshes"));
    _simGetMass=(ptr_simGetMass)(_getProcAddress(lib,"_simGetMass"));
    _simGetPrincipalMomentOfInertia=(ptr_simGetPrincipalMomentOfInertia)(_getProcAddress(lib,"_simGetPrincipalMomentOfInertia"));
    _simGetGravity=(ptr_simGetGravity)(_getProcAddress(lib,"_simGetGravity"));
    _simGetTimeDiffInMs=(ptr_simGetTimeDiffInMs)(_getProcAddress(lib,"_simGetTimeDiffInMs"));
    _simDoEntitiesCollide=(ptr_simDoEntitiesCollide)(_getProcAddress(lib,"_simDoEntitiesCollide"));
    _simGetDistanceBetweenEntitiesIfSmaller=(ptr_simGetDistanceBetweenEntitiesIfSmaller)(_getProcAddress(lib,"_simGetDistanceBetweenEntitiesIfSmaller"));
    _simHandleJointControl=(ptr_simHandleJointControl)(_getProcAddress(lib,"_simHandleJointControl"));
    _simHandleCustomContact=(ptr_simHandleCustomContact)(_getProcAddress(lib,"_simHandleCustomContact"));
    _simGetPureHollowScaling=(ptr_simGetPureHollowScaling)(_getProcAddress(lib,"_simGetPureHollowScaling"));
    _simGetJointCallbackCallOrder=(ptr_simGetJointCallbackCallOrder)(_getProcAddress(lib,"_simGetJointCallbackCallOrder"));
    _simDynCallback=(ptr_simDynCallback)(_getProcAddress(lib,"_simDynCallback"));



    // Deprecated begin
    simGetMaterialId=(ptrSimGetMaterialId)(_getProcAddress(lib,"simGetMaterialId"));
    simGetShapeMaterial=(ptrSimGetShapeMaterial)(_getProcAddress(lib,"simGetShapeMaterial"));
    simHandleVarious=(ptrSimHandleVarious)(_getProcAddress(lib,"simHandleVarious"));
    simSerialPortOpen=(ptrSimSerialPortOpen)(_getProcAddress(lib,"simSerialPortOpen"));
    simSerialPortClose=(ptrSimSerialPortClose)(_getProcAddress(lib,"simSerialPortClose"));
    simSerialPortSend=(ptrSimSerialPortSend)(_getProcAddress(lib,"simSerialPortSend"));
    simSerialPortRead=(ptrSimSerialPortRead)(_getProcAddress(lib,"simSerialPortRead"));
    simJointGetForce=(ptrSimJointGetForce)(_getProcAddress(lib,"simJointGetForce"));
    simGetPathPlanningHandle=(ptrSimGetPathPlanningHandle)(_getProcAddress(lib,"simGetPathPlanningHandle"));
    simGetMotionPlanningHandle=(ptrSimGetMotionPlanningHandle)(_getProcAddress(lib,"simGetMotionPlanningHandle"));
    simGetMpConfigForTipPose=(ptrSimGetMpConfigForTipPose)(_getProcAddress(lib,"simGetMpConfigForTipPose"));
    simFindMpPath=(ptrSimFindMpPath)(_getProcAddress(lib,"simFindMpPath"));
    simSimplifyMpPath=(ptrSimSimplifyMpPath)(_getProcAddress(lib,"simSimplifyMpPath"));
    simGetMpConfigTransition=(ptrSimGetMpConfigTransition)(_getProcAddress(lib,"simGetMpConfigTransition"));
    simFindIkPath=(ptrSimFindIkPath)(_getProcAddress(lib,"simFindIkPath"));
    simCreateMotionPlanning=(ptrSimCreateMotionPlanning)(_getProcAddress(lib,"simCreateMotionPlanning"));
    simRemoveMotionPlanning=(ptrSimRemoveMotionPlanning)(_getProcAddress(lib,"simRemoveMotionPlanning"));
    simSearchPath=(ptrSimSearchPath)(_getProcAddress(lib,"simSearchPath"));
    simInitializePathSearch=(ptrSimInitializePathSearch)(_getProcAddress(lib,"simInitializePathSearch"));
    simPerformPathSearchStep=(ptrSimPerformPathSearchStep)(_getProcAddress(lib,"simPerformPathSearchStep"));
    simLockInterface=(ptrSimLockInterface)(_getProcAddress(lib,"simLockInterface"));
    simCopyPasteSelectedObjects=(ptrSimCopyPasteSelectedObjects)(_getProcAddress(lib,"simCopyPasteSelectedObjects"));
    simResetPath=(ptrSimResetPath)(_getProcAddress(lib,"simResetPath"));
    simHandlePath=(ptrSimHandlePath)(_getProcAddress(lib,"simHandlePath"));
    simResetJoint=(ptrSimResetJoint)(_getProcAddress(lib,"simResetJoint"));
    simHandleJoint=(ptrSimHandleJoint)(_getProcAddress(lib,"simHandleJoint"));
    simAppendScriptArrayEntry=(ptrSimAppendScriptArrayEntry)(_getProcAddress(lib,"simAppendScriptArrayEntry"));
    simClearScriptVariable=(ptrSimClearScriptVariable)(_getProcAddress(lib,"simClearScriptVariable"));
    _simGetJointOdeParameters=(ptr_simGetJointOdeParameters)(_getProcAddress(lib,"_simGetJointOdeParameters"));
    _simGetJointBulletParameters=(ptr_simGetJointBulletParameters)(_getProcAddress(lib,"_simGetJointBulletParameters"));
    _simGetOdeMaxContactFrictionCFMandERP=(ptr_simGetOdeMaxContactFrictionCFMandERP)(_getProcAddress(lib,"_simGetOdeMaxContactFrictionCFMandERP"));
    _simGetBulletCollisionMargin=(ptr_simGetBulletCollisionMargin)(_getProcAddress(lib,"_simGetBulletCollisionMargin"));
    _simGetBulletStickyContact=(ptr_simGetBulletStickyContact)(_getProcAddress(lib,"_simGetBulletStickyContact"));
    _simGetBulletRestitution=(ptr_simGetBulletRestitution)(_getProcAddress(lib,"_simGetBulletRestitution"));
    _simGetVortexParameters=(ptr_simGetVortexParameters)(_getProcAddress(lib,"_simGetVortexParameters"));
    _simGetNewtonParameters=(ptr_simGetNewtonParameters)(_getProcAddress(lib,"_simGetNewtonParameters"));
    _simGetDamping=(ptr_simGetDamping)(_getProcAddress(lib,"_simGetDamping"));
    _simGetFriction=(ptr_simGetFriction)(_getProcAddress(lib,"_simGetFriction"));
    simAddSceneCustomData=(ptrSimAddSceneCustomData)(_getProcAddress(lib,"simAddSceneCustomData"));
    simGetSceneCustomDataLength=(ptrSimGetSceneCustomDataLength)(_getProcAddress(lib,"simGetSceneCustomDataLength"));
    simGetSceneCustomData=(ptrSimGetSceneCustomData)(_getProcAddress(lib,"simGetSceneCustomData"));
    simAddObjectCustomData=(ptrSimAddObjectCustomData)(_getProcAddress(lib,"simAddObjectCustomData"));
    simGetObjectCustomDataLength=(ptrSimGetObjectCustomDataLength)(_getProcAddress(lib,"simGetObjectCustomDataLength"));
    simGetObjectCustomData=(ptrSimGetObjectCustomData)(_getProcAddress(lib,"simGetObjectCustomData"));
    simCreateUI=(ptrSimCreateUI)(_getProcAddress(lib,"simCreateUI"));
    simCreateUIButton=(ptrSimCreateUIButton)(_getProcAddress(lib,"simCreateUIButton"));
    simGetUIHandle=(ptrSimGetUIHandle)(_getProcAddress(lib,"simGetUIHandle"));
    simGetUIProperty=(ptrSimGetUIProperty)(_getProcAddress(lib,"simGetUIProperty"));
    simGetUIEventButton=(ptrSimGetUIEventButton)(_getProcAddress(lib,"simGetUIEventButton"));
    simSetUIProperty=(ptrSimSetUIProperty)(_getProcAddress(lib,"simSetUIProperty"));
    simGetUIButtonProperty=(ptrSimGetUIButtonProperty)(_getProcAddress(lib,"simGetUIButtonProperty"));
    simSetUIButtonProperty=(ptrSimSetUIButtonProperty)(_getProcAddress(lib,"simSetUIButtonProperty"));
    simGetUIButtonSize=(ptrSimGetUIButtonSize)(_getProcAddress(lib,"simGetUIButtonSize"));
    simSetUIButtonLabel=(ptrSimSetUIButtonLabel)(_getProcAddress(lib,"simSetUIButtonLabel"));
    simGetUIButtonLabel=(ptrSimGetUIButtonLabel)(_getProcAddress(lib,"simGetUIButtonLabel"));
    simSetUISlider=(ptrSimSetUISlider)(_getProcAddress(lib,"simSetUISlider"));
    simGetUISlider=(ptrSimGetUISlider)(_getProcAddress(lib,"simGetUISlider"));
    simSetUIButtonColor=(ptrSimSetUIButtonColor)(_getProcAddress(lib,"simSetUIButtonColor"));
    simSetUIButtonTexture=(ptrSimSetUIButtonTexture)(_getProcAddress(lib,"simSetUIButtonTexture"));
    simCreateUIButtonArray=(ptrSimCreateUIButtonArray)(_getProcAddress(lib,"simCreateUIButtonArray"));
    simSetUIButtonArrayColor=(ptrSimSetUIButtonArrayColor)(_getProcAddress(lib,"simSetUIButtonArrayColor"));
    simDeleteUIButtonArray=(ptrSimDeleteUIButtonArray)(_getProcAddress(lib,"simDeleteUIButtonArray"));
    simRemoveUI=(ptrSimRemoveUI)(_getProcAddress(lib,"simRemoveUI"));
    simSetUIPosition=(ptrSimSetUIPosition)(_getProcAddress(lib,"simSetUIPosition"));
    simGetUIPosition=(ptrSimGetUIPosition)(_getProcAddress(lib,"simGetUIPosition"));
    simLoadUI=(ptrSimLoadUI)(_getProcAddress(lib,"simLoadUI"));
    simSaveUI=(ptrSimSaveUI)(_getProcAddress(lib,"simSaveUI"));
    simHandleGeneralCallbackScript=(ptrSimHandleGeneralCallbackScript)(_getProcAddress(lib,"simHandleGeneralCallbackScript"));
    simRegisterCustomLuaFunction=(ptrSimRegisterCustomLuaFunction)(_getProcAddress(lib,"simRegisterCustomLuaFunction"));
    simRegisterCustomLuaVariable=(ptrSimRegisterCustomLuaVariable)(_getProcAddress(lib,"simRegisterCustomLuaVariable"));
    simRegisterContactCallback=(ptrSimRegisterContactCallback)(_getProcAddress(lib,"simRegisterContactCallback"));
    simGetMechanismHandle=(ptrSimGetMechanismHandle)(_getProcAddress(lib,"simGetMechanismHandle"));
    simHandleMechanism=(ptrSimHandleMechanism)(_getProcAddress(lib,"simHandleMechanism"));
    simHandleCustomizationScripts=(ptrSimHandleCustomizationScripts)(_getProcAddress(lib,"simHandleCustomizationScripts"));
    simCallScriptFunction=(ptrSimCallScriptFunction)(_getProcAddress(lib,"simCallScriptFunction"));
    simSetVisionSensorFilter=(ptrSimSetVisionSensorFilter)(_getProcAddress(lib,"simSetVisionSensorFilter"));
    simGetVisionSensorFilter=(ptrSimGetVisionSensorFilter)(_getProcAddress(lib,"simGetVisionSensorFilter"));
    simGetScriptSimulationParameter=(ptrSimGetScriptSimulationParameter)(_getProcAddress(lib,"simGetScriptSimulationParameter"));
    simSetScriptSimulationParameter=(ptrSimSetScriptSimulationParameter)(_getProcAddress(lib,"simSetScriptSimulationParameter"));
    simSetJointForce=(ptrSimSetJointForce)(_getProcAddress(lib,"simSetJointForce"));
    simHandleMill=(ptrSimHandleMill)(_getProcAddress(lib,"simHandleMill"));
    simResetMill=(ptrSimResetMill)(_getProcAddress(lib,"simResetMill"));
    simResetMilling=(ptrSimResetMilling)(_getProcAddress(lib,"simResetMilling"));
    simApplyMilling=(ptrSimApplyMilling)(_getProcAddress(lib,"simApplyMilling"));
    _simGetParentFollowsDynamic=(ptr_simGetParentFollowsDynamic)(_getProcAddress(lib,"_simGetParentFollowsDynamic"));
    simGetNameSuffix=(ptrSimGetNameSuffix)(_getProcAddress(lib,"simGetNameSuffix"));
    simSetNameSuffix=(ptrSimSetNameSuffix)(_getProcAddress(lib,"simSetNameSuffix"));
    simAddStatusbarMessage=(ptrSimAddStatusbarMessage)(_getProcAddress(lib,"simAddStatusbarMessage"));
    // Deprecated end


    char couldNotFind[]="Could not find function";
    if (simRunSimulator==nullptr)
    {
        printf("%s simRunSimulator\n",couldNotFind);
        return 0;
    }
    if (simRunSimulatorEx==nullptr)
    {
        printf("%s simRunSimulatorEx\n",couldNotFind);
        return 0;
    }
    if (simGetSimulatorMessage==nullptr)
    {
        printf("%s simGetSimulatorMessage\n",couldNotFind);
        return 0;
    }
    if (simGetMainWindow==nullptr)
    {
        printf("%s simGetMainWindow\n",couldNotFind);
        return 0;
    }
    if (simGetLastError==nullptr)
    {
        printf("%s simGetLastError\n",couldNotFind);
        return 0;
    }
    if (simLoadModule==nullptr)
    {
        printf("%s simLoadModule\n",couldNotFind);
        return 0;
    }
    if (simUnloadModule==nullptr)
    {
        printf("%s simUnloadModule\n",couldNotFind);
        return 0;
    }
    if (simSendModuleMessage==nullptr)
    {
        printf("%s simSendModuleMessage\n",couldNotFind);
        return 0;
    }
    if (simSetBooleanParameter==nullptr)
    {
        printf("%s simSetBooleanParameter\n",couldNotFind);
        return 0;
    }
    if (simGetBooleanParameter==nullptr)
    {
        printf("%s simGetBooleanParameter\n",couldNotFind);
        return 0;
    }
    if (simSetBoolParameter==nullptr)
    {
        printf("%s simSetBoolParameter\n",couldNotFind);
        return 0;
    }
    if (simGetBoolParameter==nullptr)
    {
        printf("%s simGetBoolParameter\n",couldNotFind);
        return 0;
    }
    if (simSetIntegerParameter==nullptr)
    {
        printf("%s simSetIntegerParameter\n",couldNotFind);
        return 0;
    }
    if (simGetIntegerParameter==nullptr)
    {
        printf("%s simGetIntegerParameter\n",couldNotFind);
        return 0;
    }
    if (simSetInt32Parameter==nullptr)
    {
        printf("%s simSetInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simGetInt32Parameter==nullptr)
    {
        printf("%s simGetInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simGetUInt64Parameter==nullptr)
    {
        printf("%s simGetUInt64Parameter\n",couldNotFind);
        return 0;
    }
    if (simSetFloatingParameter==nullptr)
    {
        printf("%s simSetFloatingParameter\n",couldNotFind);
        return 0;
    }
    if (simGetFloatingParameter==nullptr)
    {
        printf("%s simGetFloatingParameter\n",couldNotFind);
        return 0;
    }
    if (simSetFloatParameter==nullptr)
    {
        printf("%s simSetFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simGetFloatParameter==nullptr)
    {
        printf("%s simGetFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simSetStringParameter==nullptr)
    {
        printf("%s simSetStringParameter\n",couldNotFind);
        return 0;
    }
    if (simGetStringParameter==nullptr)
    {
        printf("%s simGetStringParameter\n",couldNotFind);
        return 0;
    }
    if (simGetObjectHandle==nullptr)
    {
        printf("%s simGetObjectHandle\n",couldNotFind);
        return 0;
    }
    if (simRemoveObject==nullptr)
    {
        printf("%s simRemoveObject\n",couldNotFind);
        return 0;
    }
    if (simRemoveModel==nullptr)
    {
        printf("%s simRemoveModel\n",couldNotFind);
        return 0;
    }
    if (simGetObjectName==nullptr)
    {
        printf("%s simGetObjectName\n",couldNotFind);
        return 0;
    }
    if (simGetObjects==nullptr)
    {
        printf("%s simGetObjects\n",couldNotFind);
        return 0;
    }
    if (simSetObjectName==nullptr)
    {
        printf("%s simSetObjectName\n",couldNotFind);
        return 0;
    }
    if (simGetCollectionHandle==nullptr)
    {
        printf("%s simGetCollectionHandle\n",couldNotFind);
        return 0;
    }
    if (simRemoveCollection==nullptr)
    {
        printf("%s simRemoveCollection\n",couldNotFind);
        return 0;
    }
    if (simEmptyCollection==nullptr)
    {
        printf("%s simEmptyCollection\n",couldNotFind);
        return 0;
    }
    if (simGetCollectionName==nullptr)
    {
        printf("%s simGetCollectionName\n",couldNotFind);
        return 0;
    }
    if (simSetCollectionName==nullptr)
    {
        printf("%s simSetCollectionName\n",couldNotFind);
        return 0;
    }
    if (simGetObjectMatrix==nullptr)
    {
        printf("%s simGetObjectMatrix\n",couldNotFind);
        return 0;
    }
    if (simSetObjectMatrix==nullptr)
    {
        printf("%s simSetObjectMatrix\n",couldNotFind);
        return 0;
    }
    if (simGetObjectPosition==nullptr)
    {
        printf("%s simGetObjectPosition\n",couldNotFind);
        return 0;
    }
    if (simSetObjectPosition==nullptr)
    {
        printf("%s simSetObjectPosition\n",couldNotFind);
        return 0;
    }
    if (simGetObjectOrientation==nullptr)
    {
        printf("%s simGetObjectOrientation\n",couldNotFind);
        return 0;
    }
    if (simSetObjectOrientation==nullptr)
    {
        printf("%s simSetObjectOrientation\n",couldNotFind);
        return 0;
    }
    if (simGetJointPosition==nullptr)
    {
        printf("%s simGetJointPosition\n",couldNotFind);
        return 0;
    }
    if (simSetJointPosition==nullptr)
    {
        printf("%s simSetJointPosition\n",couldNotFind);
        return 0;
    }
    if (simSetJointTargetPosition==nullptr)
    {
        printf("%s simSetJointTargetPosition\n",couldNotFind);
        return 0;
    }
    if (simGetJointTargetPosition==nullptr)
    {
        printf("%s simGetJointTargetPosition\n",couldNotFind);
        return 0;
    }
    if (simSetJointMaxForce==nullptr)
    {
        printf("%s simSetJointMaxForce\n",couldNotFind);
        return 0;
    }
    if (simGetPathPosition==nullptr)
    {
        printf("%s simGetPathPosition\n",couldNotFind);
        return 0;
    }
    if (simSetPathPosition==nullptr)
    {
        printf("%s simSetPathPosition\n",couldNotFind);
        return 0;
    }
    if (simGetPathLength==nullptr)
    {
        printf("%s simGetPathLength\n",couldNotFind);
        return 0;
    }
    if (simGetJointMatrix==nullptr)
    {
        printf("%s simGetJointMatrix\n",couldNotFind);
        return 0;
    }
    if (simSetSphericalJointMatrix==nullptr)
    {
        printf("%s simSetSphericalJointMatrix\n",couldNotFind);
        return 0;
    }
    if (simGetJointInterval==nullptr)
    {
        printf("%s simGetJointInterval\n",couldNotFind);
        return 0;
    }
    if (simSetJointInterval==nullptr)
    {
        printf("%s simSetJointInterval\n",couldNotFind);
        return 0;
    }
    if (simGetObjectParent==nullptr)
    {
        printf("%s simGetObjectParent\n",couldNotFind);
        return 0;
    }
    if (simGetObjectChild==nullptr)
    {
        printf("%s simGetObjectChild\n",couldNotFind);
        return 0;
    }
    if (simSetObjectParent==nullptr)
    {
        printf("%s simSetObjectParent\n",couldNotFind);
        return 0;
    }
    if (simGetObjectType==nullptr)
    {
        printf("%s simGetObjectType\n",couldNotFind);
        return 0;
    }
    if (simGetJointType==nullptr)
    {
        printf("%s simGetJointType\n",couldNotFind);
        return 0;
    }
    if (simBuildIdentityMatrix==nullptr)
    {
        printf("%s simBuildIdentityMatrix\n",couldNotFind);
        return 0;
    }
    if (simCopyMatrix==nullptr)
    {
        printf("%s simCopyMatrix\n",couldNotFind);
        return 0;
    }
    if (simBuildMatrix==nullptr)
    {
        printf("%s simBuildMatrix\n",couldNotFind);
        return 0;
    }
    if (simGetEulerAnglesFromMatrix==nullptr)
    {
        printf("%s simGetEulerAnglesFromMatrix\n",couldNotFind);
        return 0;
    }
    if (simInvertMatrix==nullptr)
    {
        printf("%s simInvertMatrix\n",couldNotFind);
        return 0;
    }
    if (simMultiplyMatrices==nullptr)
    {
        printf("%s simMultiplyMatrices\n",couldNotFind);
        return 0;
    }
    if (simInterpolateMatrices==nullptr)
    {
        printf("%s simInterpolateMatrices\n",couldNotFind);
        return 0;
    }
    if (simTransformVector==nullptr)
    {
        printf("%s simTransformVector\n",couldNotFind);
        return 0;
    }
    if (simReservedCommand==nullptr)
    {
        printf("%s simReservedCommand\n",couldNotFind);
        return 0;
    }
    if (simGetSimulationTime==nullptr)
    {
        printf("%s simGetSimulationTime\n",couldNotFind);
        return 0;
    }
    if (simGetSimulationState==nullptr)
    {
        printf("%s simGetSimulationState\n",couldNotFind);
        return 0;
    }
    if (simGetSystemTime==nullptr)
    {
        printf("%s simGetSystemTime\n",couldNotFind);
        return 0;
    }
    if (simGetSystemTimeInMilliseconds==nullptr)
    {
        printf("%s simGetSystemTimeInMilliseconds\n",couldNotFind);
        return 0;
    }
    if (simGetSystemTimeInMs==nullptr)
    {
        printf("%s simGetSystemTimeInMs\n",couldNotFind);
        return 0;
    }
    if (simLoadScene==nullptr)
    {
        printf("%s simLoadScene\n",couldNotFind);
        return 0;
    }
    if (simCloseScene==nullptr)
    {
        printf("%s simCloseScene\n",couldNotFind);
        return 0;
    }
    if (simSaveScene==nullptr)
    {
        printf("%s simSaveScene\n",couldNotFind);
        return 0;
    }
    if (simLoadModel==nullptr)
    {
        printf("%s simLoadModel\n",couldNotFind);
        return 0;
    }
    if (simSaveModel==nullptr)
    {
        printf("%s simSaveModel\n",couldNotFind);
        return 0;
    }
    if (simAddModuleMenuEntry==nullptr)
    {
        printf("%s simAddModuleMenuEntry\n",couldNotFind);
        return 0;
    }
    if (simSetModuleMenuItemState==nullptr)
    {
        printf("%s simSetModuleMenuItemState\n",couldNotFind);
        return 0;
    }
    if (simDoesFileExist==nullptr)
    {
        printf("%s simDoesFileExist\n",couldNotFind);
        return 0;
    }
    if (simIsObjectInSelection==nullptr)
    {
        printf("%s simIsObjectInSelection\n",couldNotFind);
        return 0;
    }
    if (simAddObjectToSelection==nullptr)
    {
        printf("%s simAddObjectToSelection\n",couldNotFind);
        return 0;
    }
    if (simRemoveObjectFromSelection==nullptr)
    {
        printf("%s simRemoveObjectFromSelection\n",couldNotFind);
        return 0;
    }
    if (simGetObjectSelectionSize==nullptr)
    {
        printf("%s simGetObjectSelectionSize\n",couldNotFind);
        return 0;
    }
    if (simGetObjectLastSelection==nullptr)
    {
        printf("%s simGetObjectLastSelection\n",couldNotFind);
        return 0;
    }
    if (simGetObjectSelection==nullptr)
    {
        printf("%s simGetObjectSelection\n",couldNotFind);
        return 0;
    }
    if (simHandleCollision==nullptr)
    {
        printf("%s simHandleCollision\n",couldNotFind);
        return 0;
    }
    if (simReadCollision==nullptr)
    {
        printf("%s simReadCollision\n",couldNotFind);
        return 0;
    }
    if (simHandleDistance==nullptr)
    {
        printf("%s simHandleDistance\n",couldNotFind);
        return 0;
    }
    if (simReadDistance==nullptr)
    {
        printf("%s simReadDistance\n",couldNotFind);
        return 0;
    }
    if (simHandleProximitySensor==nullptr)
    {
        printf("%s simHandleProximitySensor\n",couldNotFind);
        return 0;
    }
    if (simReadProximitySensor==nullptr)
    {
        printf("%s simReadProximitySensor\n",couldNotFind);
        return 0;
    }
    if (simHandleIkGroup==nullptr)
    {
        printf("%s simHandleIkGroup\n",couldNotFind);
        return 0;
    }
    if (simCheckIkGroup==nullptr)
    {
        printf("%s simCheckIkGroup\n",couldNotFind);
        return 0;
    }
    if (simHandleDynamics==nullptr)
    {
        printf("%s simHandleDynamics\n",couldNotFind);
        return 0;
    }
    if (simGetScriptHandle==nullptr)
    {
        printf("%s simGetScriptHandle\n",couldNotFind);
        return 0;
    }
    if (simSetScriptText==nullptr)
    {
        printf("%s simSetScriptText\n",couldNotFind);
        return 0;
    }
    if (simGetScriptText==nullptr)
    {
        printf("%s simGetScriptText\n",couldNotFind);
        return 0;
    }
    if (simGetScriptProperty==nullptr)
    {
        printf("%s simGetScriptProperty\n",couldNotFind);
        return 0;
    }
    if (simAssociateScriptWithObject==nullptr)
    {
        printf("%s simAssociateScriptWithObject\n",couldNotFind);
        return 0;
    }
    if (simGetScript==nullptr)
    {
        printf("%s simGetScript\n",couldNotFind);
        return 0;
    }
    if (simGetScriptAssociatedWithObject==nullptr)
    {
        printf("%s simGetScriptAssociatedWithObject\n",couldNotFind);
        return 0;
    }
    if (simGetCustomizationScriptAssociatedWithObject==nullptr)
    {
        printf("%s simGetCustomizationScriptAssociatedWithObject\n",couldNotFind);
        return 0;
    }
    if (simGetObjectAssociatedWithScript==nullptr)
    {
        printf("%s simGetObjectAssociatedWithScript\n",couldNotFind);
        return 0;
    }
    if (simGetScriptName==nullptr)
    {
        printf("%s simGetScriptName\n",couldNotFind);
        return 0;
    }
    if (simHandleMainScript==nullptr)
    {
        printf("%s simHandleMainScript\n",couldNotFind);
        return 0;
    }
    if (simResetScript==nullptr)
    {
        printf("%s simResetScript\n",couldNotFind);
        return 0;
    }
    if (simAddScript==nullptr)
    {
        printf("%s simAddScript\n",couldNotFind);
        return 0;
    }
    if (simRemoveScript==nullptr)
    {
        printf("%s simRemoveScript\n",couldNotFind);
        return 0;
    }
    if (simRefreshDialogs==nullptr)
    {
        printf("%s simRefreshDialogs\n",couldNotFind);
        return 0;
    }
    if (simGetCollisionHandle==nullptr)
    {
        printf("%s simGetCollisionHandle\n",couldNotFind);
        return 0;
    }
    if (simGetDistanceHandle==nullptr)
    {
        printf("%s simGetDistanceHandle\n",couldNotFind);
        return 0;
    }
    if (simGetIkGroupHandle==nullptr)
    {
        printf("%s simGetIkGroupHandle\n",couldNotFind);
        return 0;
    }
    if (simResetCollision==nullptr)
    {
        printf("%s simResetCollision\n",couldNotFind);
        return 0;
    }
    if (simResetDistance==nullptr)
    {
        printf("%s simResetDistance\n",couldNotFind);
        return 0;
    }
    if (simResetProximitySensor==nullptr)
    {
        printf("%s simResetProximitySensor\n",couldNotFind);
        return 0;
    }
    if (simCheckProximitySensor==nullptr)
    {
        printf("%s simCheckProximitySensor\n",couldNotFind);
        return 0;
    }
    if (simCheckProximitySensorEx==nullptr)
    {
        printf("%s simCheckProximitySensorEx\n",couldNotFind);
        return 0;
    }
    if (simCheckProximitySensorEx2==nullptr)
    {
        printf("%s simCheckProximitySensorEx2\n",couldNotFind);
        return 0;
    }
    if (simCreateBuffer==nullptr)
    {
        printf("%s simCreateBuffer\n",couldNotFind);
        return 0;
    }
    if (simReleaseBuffer==nullptr)
    {
        printf("%s simReleaseBuffer\n",couldNotFind);
        return 0;
    }
    if (simCheckCollision==nullptr)
    {
        printf("%s simCheckCollision\n",couldNotFind);
        return 0;
    }
    if (simCheckCollisionEx==nullptr)
    {
        printf("%s simCheckCollisionEx\n",couldNotFind);
        return 0;
    }
    if (simCheckDistance==nullptr)
    {
        printf("%s simCheckDistance\n",couldNotFind);
        return 0;
    }
    if (simGetObjectConfiguration==nullptr)
    {
        printf("%s simGetObjectConfiguration\n",couldNotFind);
        return 0;
    }
    if (simSetObjectConfiguration==nullptr)
    {
        printf("%s simSetObjectConfiguration\n",couldNotFind);
        return 0;
    }
    if (simGetConfigurationTree==nullptr)
    {
        printf("%s simGetConfigurationTree\n",couldNotFind);
        return 0;
    }
    if (simSetConfigurationTree==nullptr)
    {
        printf("%s simSetConfigurationTree\n",couldNotFind);
        return 0;
    }
    if (simSetSimulationTimeStep==nullptr)
    {
        printf("%s simSetSimulationTimeStep\n",couldNotFind);
        return 0;
    }
    if (simGetSimulationTimeStep==nullptr)
    {
        printf("%s simGetSimulationTimeStep\n",couldNotFind);
        return 0;
    }
    if (simGetRealTimeSimulation==nullptr)
    {
        printf("%s simGetRealTimeSimulation\n",couldNotFind);
        return 0;
    }
    if (simIsRealTimeSimulationStepNeeded==nullptr)
    {
        printf("%s simIsRealTimeSimulationStepNeeded\n",couldNotFind);
        return 0;
    }
    if (simAdjustRealTimeTimer==nullptr)
    {
        printf("%s simAdjustRealTimeTimer\n",couldNotFind);
        return 0;
    }
    if (simGetSimulationPassesPerRenderingPass==nullptr)
    {
        printf("%s simGetSimulationPassesPerRenderingPass\n",couldNotFind);
        return 0;
    }
    if (simAdvanceSimulationByOneStep==nullptr)
    {
        printf("%s simAdvanceSimulationByOneStep\n",couldNotFind);
        return 0;
    }
    if (simStartSimulation==nullptr)
    {
        printf("%s simStartSimulation\n",couldNotFind);
        return 0;
    }
    if (simStopSimulation==nullptr)
    {
        printf("%s simStopSimulation\n",couldNotFind);
        return 0;
    }
    if (simPauseSimulation==nullptr)
    {
        printf("%s simPauseSimulation\n",couldNotFind);
        return 0;
    }
    if (simBroadcastMessage==nullptr)
    {
        printf("%s simBroadcastMessage\n",couldNotFind);
        return 0;
    }
    if (simGetModuleName==nullptr)
    {
        printf("%s simGetModuleName\n",couldNotFind);
        return 0;
    }
    if (simFloatingViewAdd==nullptr)
    {
        printf("%s simFloatingViewAdd\n",couldNotFind);
        return 0;
    }
    if (simFloatingViewRemove==nullptr)
    {
        printf("%s simFloatingViewRemove\n",couldNotFind);
        return 0;
    }
    if (simAdjustView==nullptr)
    {
        printf("%s simAdjustView\n",couldNotFind);
        return 0;
    }
    if (simSetLastError==nullptr)
    {
        printf("%s simSetLastError\n",couldNotFind);
        return 0;
    }
    if (simHandleGraph==nullptr)
    {
        printf("%s simHandleGraph\n",couldNotFind);
        return 0;
    }
    if (simResetGraph==nullptr)
    {
        printf("%s simResetGraph\n",couldNotFind);
        return 0;
    }
    if (simSetNavigationMode==nullptr)
    {
        printf("%s simSetNavigationMode\n",couldNotFind);
        return 0;
    }
    if (simGetNavigationMode==nullptr)
    {
        printf("%s simGetNavigationMode\n",couldNotFind);
        return 0;
    }
    if (simSetPage==nullptr)
    {
        printf("%s simSetPage\n",couldNotFind);
        return 0;
    }
    if (simGetPage==nullptr)
    {
        printf("%s simGetPage\n",couldNotFind);
        return 0;
    }
    if (simDisplayDialog==nullptr)
    {
        printf("%s simDisplayDialog\n",couldNotFind);
        return 0;
    }
    if (simGetDialogResult==nullptr)
    {
        printf("%s simGetDialogResult\n",couldNotFind);
        return 0;
    }
    if (simGetDialogInput==nullptr)
    {
        printf("%s simGetDialogInput\n",couldNotFind);
        return 0;
    }
    if (simEndDialog==nullptr)
    {
        printf("%s simEndDialog\n",couldNotFind);
        return 0;
    }
    if (simRegisterScriptCallbackFunction==nullptr)
    {
        printf("%s simRegisterScriptCallbackFunction\n",couldNotFind);
        return 0;
    }
    if (simRegisterScriptVariable==nullptr)
    {
        printf("%s simRegisterScriptVariable\n",couldNotFind);
        return 0;
    }
    if (simSetJointTargetVelocity==nullptr)
    {
        printf("%s simSetJointTargetVelocity\n",couldNotFind);
        return 0;
    }
    if (simGetJointTargetVelocity==nullptr)
    {
        printf("%s simGetJointTargetVelocity\n",couldNotFind);
        return 0;
    }
    if (simSetPathTargetNominalVelocity==nullptr)
    {
        printf("%s simSetPathTargetNominalVelocity\n",couldNotFind);
        return 0;
    }
    if (simGetScriptRawBuffer==nullptr)
    {
        printf("%s simGetScriptRawBuffer\n",couldNotFind);
        return 0;
    }
    if (simSetScriptRawBuffer==nullptr)
    {
        printf("%s simSetScriptRawBuffer\n",couldNotFind);
        return 0;
    }
    if (simReleaseScriptRawBuffer==nullptr)
    {
        printf("%s simReleaseScriptRawBuffer\n",couldNotFind);
        return 0;
    }
    if (simCopyPasteObjects==nullptr)
    {
        printf("%s simCopyPasteObjects\n",couldNotFind);
        return 0;
    }
    if (simScaleSelectedObjects==nullptr)
    {
        printf("%s simScaleSelectedObjects\n",couldNotFind);
        return 0;
    }
    if (simScaleObjects==nullptr)
    {
        printf("%s simScaleObjects\n",couldNotFind);
        return 0;
    }
    if (simDeleteSelectedObjects==nullptr)
    {
        printf("%s simDeleteSelectedObjects\n",couldNotFind);
        return 0;
    }
    if (simGetObjectUniqueIdentifier==nullptr)
    {
        printf("%s simGetObjectUniqueIdentifier\n",couldNotFind);
        return 0;
    }
    if (simSendData==nullptr)
    {
        printf("%s simSendData\n",couldNotFind);
        return 0;
    }
    if (simReceiveData==nullptr)
    {
        printf("%s simReceiveData\n",couldNotFind);
        return 0;
    }
    if (simSetGraphUserData==nullptr)
    {
        printf("%s simSetGraphUserData\n",couldNotFind);
        return 0;
    }
    if (simAddDrawingObject==nullptr)
    {
        printf("%s simAddDrawingObject\n",couldNotFind);
        return 0;
    }
    if (simRemoveDrawingObject==nullptr)
    {
        printf("%s simRemoveDrawingObject\n",couldNotFind);
        return 0;
    }
    if (simAddDrawingObjectItem==nullptr)
    {
        printf("%s simAddDrawingObjectItem\n",couldNotFind);
        return 0;
    }
    if (simAddParticleObject==nullptr)
    {
        printf("%s simAddParticleObject\n",couldNotFind);
        return 0;
    }
    if (simRemoveParticleObject==nullptr)
    {
        printf("%s simRemoveParticleObject\n",couldNotFind);
        return 0;
    }
    if (simAddParticleObjectItem==nullptr)
    {
        printf("%s simAddParticleObjectItem\n",couldNotFind);
        return 0;
    }
    if (simGetObjectSizeFactor==nullptr)
    {
        printf("%s simGetObjectSizeFactor\n",couldNotFind);
        return 0;
    }
    if (simAnnounceSceneContentChange==nullptr)
    {
        printf("%s simAnnounceSceneContentChange\n",couldNotFind);
        return 0;
    }
    if (simSetIntegerSignal==nullptr)
    {
        printf("%s simSetIntegerSignal\n",couldNotFind);
        return 0;
    }
    if (simGetIntegerSignal==nullptr)
    {
        printf("%s simGetIntegerSignal\n",couldNotFind);
        return 0;
    }
    if (simClearIntegerSignal==nullptr)
    {
        printf("%s simClearIntegerSignal\n",couldNotFind);
        return 0;
    }
    if (simSetFloatSignal==nullptr)
    {
        printf("%s simSetFloatSignal\n",couldNotFind);
        return 0;
    }
    if (simGetFloatSignal==nullptr)
    {
        printf("%s simGetFloatSignal\n",couldNotFind);
        return 0;
    }
    if (simClearFloatSignal==nullptr)
    {
        printf("%s simClearFloatSignal\n",couldNotFind);
        return 0;
    }
    if (simSetDoubleSignal==nullptr)
    {
        printf("%s simSetDoubleSignal\n",couldNotFind);
        return 0;
    }
    if (simGetDoubleSignal==nullptr)
    {
        printf("%s simGetDoubleSignal\n",couldNotFind);
        return 0;
    }
    if (simClearDoubleSignal==nullptr)
    {
        printf("%s simClearDoubleSignal\n",couldNotFind);
        return 0;
    }
    if (simSetStringSignal==nullptr)
    {
        printf("%s simSetStringSignal\n",couldNotFind);
        return 0;
    }
    if (simGetStringSignal==nullptr)
    {
        printf("%s simGetStringSignal\n",couldNotFind);
        return 0;
    }
    if (simClearStringSignal==nullptr)
    {
        printf("%s simClearStringSignal\n",couldNotFind);
        return 0;
    }
    if (simGetSignalName==nullptr)
    {
        printf("%s simGetSignalName\n",couldNotFind);
        return 0;
    }
    if (simSetObjectProperty==nullptr)
    {
        printf("%s simSetObjectProperty\n",couldNotFind);
        return 0;
    }
    if (simGetObjectProperty==nullptr)
    {
        printf("%s simGetObjectProperty\n",couldNotFind);
        return 0;
    }
    if (simSetObjectSpecialProperty==nullptr)
    {
        printf("%s simSetObjectSpecialProperty\n",couldNotFind);
        return 0;
    }
    if (simGetObjectSpecialProperty==nullptr)
    {
        printf("%s simGetObjectSpecialProperty\n",couldNotFind);
        return 0;
    }
    if (simGetPositionOnPath==nullptr)
    {
        printf("%s simGetPositionOnPath\n",couldNotFind);
        return 0;
    }
    if (simGetDataOnPath==nullptr)
    {
        printf("%s simGetDataOnPath\n",couldNotFind);
        return 0;
    }
    if (simGetOrientationOnPath==nullptr)
    {
        printf("%s simGetOrientationOnPath\n",couldNotFind);
        return 0;
    }
    if (simGetClosestPositionOnPath==nullptr)
    {
        printf("%s simGetClosestPositionOnPath\n",couldNotFind);
        return 0;
    }
    if (simReadForceSensor==nullptr)
    {
        printf("%s simReadForceSensor\n",couldNotFind);
        return 0;
    }
    if (simBreakForceSensor==nullptr)
    {
        printf("%s simBreakForceSensor\n",couldNotFind);
        return 0;
    }
    if (simGetShapeVertex==nullptr)
    {
        printf("%s simGetShapeVertex\n",couldNotFind);
        return 0;
    }
    if (simGetShapeTriangle==nullptr)
    {
        printf("%s simGetShapeTriangle\n",couldNotFind);
        return 0;
    }
    if (simSetLightParameters==nullptr)
    {
        printf("%s simSetLightParameters\n",couldNotFind);
        return 0;
    }
    if (simGetLightParameters==nullptr)
    {
        printf("%s simGetLightParameters\n",couldNotFind);
        return 0;
    }
    if (simGetVelocity==nullptr)
    {
        printf("%s simGetVelocity\n",couldNotFind);
        return 0;
    }
    if (simGetObjectVelocity==nullptr)
    {
        printf("%s simGetObjectVelocity\n",couldNotFind);
        return 0;
    }
    if (simAddForceAndTorque==nullptr)
    {
        printf("%s simAddForceAndTorque\n",couldNotFind);
        return 0;
    }
    if (simAddForce==nullptr)
    {
        printf("%s simAddForce\n",couldNotFind);
        return 0;
    }
    if (simSetExplicitHandling==nullptr)
    {
        printf("%s simSetExplicitHandling\n",couldNotFind);
        return 0;
    }
    if (simGetExplicitHandling==nullptr)
    {
        printf("%s simGetExplicitHandling\n",couldNotFind);
        return 0;
    }
    if (simGetLinkDummy==nullptr)
    {
        printf("%s simGetLinkDummy\n",couldNotFind);
        return 0;
    }
    if (simSetLinkDummy==nullptr)
    {
        printf("%s simSetLinkDummy\n",couldNotFind);
        return 0;
    }
    if (simSetModelProperty==nullptr)
    {
        printf("%s simSetModelProperty\n",couldNotFind);
        return 0;
    }
    if (simGetModelProperty==nullptr)
    {
        printf("%s simGetModelProperty\n",couldNotFind);
        return 0;
    }
    if (simSetShapeColor==nullptr)
    {
        printf("%s simSetShapeColor\n",couldNotFind);
        return 0;
    }
    if (simGetShapeColor==nullptr)
    {
        printf("%s simGetShapeColor\n",couldNotFind);
        return 0;
    }
    if (simResetDynamicObject==nullptr)
    {
        printf("%s simResetDynamicObject\n",couldNotFind);
        return 0;
    }
    if (simSetJointMode==nullptr)
    {
        printf("%s simSetJointMode\n",couldNotFind);
        return 0;
    }
    if (simGetJointMode==nullptr)
    {
        printf("%s simGetJointMode\n",couldNotFind);
        return 0;
    }
    if (simSerialOpen==nullptr)
    {
        printf("%s simSerialOpen\n",couldNotFind);
        return 0;
    }
    if (simSerialClose==nullptr)
    {
        printf("%s simSerialClose\n",couldNotFind);
        return 0;
    }
    if (simSerialSend==nullptr)
    {
        printf("%s simSerialSend\n",couldNotFind);
        return 0;
    }
    if (simSerialRead==nullptr)
    {
        printf("%s simSerialRead\n",couldNotFind);
        return 0;
    }
    if (simSerialCheck==nullptr)
    {
        printf("%s simSerialCheck\n",couldNotFind);
        return 0;
    }
    if (simGetContactInfo==nullptr)
    {
        printf("%s simGetContactInfo\n",couldNotFind);
        return 0;
    }
    if (simSetThreadIsFree==nullptr)
    {
        printf("%s simSetThreadIsFree\n",couldNotFind);
        return 0;
    }
    if (simTubeOpen==nullptr)
    {
        printf("%s simTubeOpen\n",couldNotFind);
        return 0;
    }
    if (simTubeClose==nullptr)
    {
        printf("%s simTubeClose\n",couldNotFind);
        return 0;
    }
    if (simTubeWrite==nullptr)
    {
        printf("%s simTubeWrite\n",couldNotFind);
        return 0;
    }
    if (simTubeRead==nullptr)
    {
        printf("%s simTubeRead\n",couldNotFind);
        return 0;
    }
    if (simTubeStatus==nullptr)
    {
        printf("%s simTubeStatus\n",couldNotFind);
        return 0;
    }
    if (simAuxiliaryConsoleOpen==nullptr)
    {
        printf("%s simAuxiliaryConsoleOpen\n",couldNotFind);
        return 0;
    }
    if (simAuxiliaryConsoleClose==nullptr)
    {
        printf("%s simAuxiliaryConsoleClose\n",couldNotFind);
        return 0;
    }
    if (simAuxiliaryConsoleShow==nullptr)
    {
        printf("%s simAuxiliaryConsoleShow\n",couldNotFind);
        return 0;
    }
    if (simAuxiliaryConsolePrint==nullptr)
    {
        printf("%s simAuxiliaryConsolePrint\n",couldNotFind);
        return 0;
    }
    if (simImportShape==nullptr)
    {
        printf("%s simImportShape\n",couldNotFind);
        return 0;
    }
    if (simImportMesh==nullptr)
    {
        printf("%s simImportMesh\n",couldNotFind);
        return 0;
    }
    if (simExportMesh==nullptr)
    {
        printf("%s simExportMesh\n",couldNotFind);
        return 0;
    }
    if (simCreateMeshShape==nullptr)
    {
        printf("%s simCreateMeshShape\n",couldNotFind);
        return 0;
    }
    if (simCreatePureShape==nullptr)
    {
        printf("%s simCreatePureShape\n",couldNotFind);
        return 0;
    }
    if (simCreateHeightfieldShape==nullptr)
    {
        printf("%s simCreateHeightfieldShape\n",couldNotFind);
        return 0;
    }
    if (simGetShapeMesh==nullptr)
    {
        printf("%s simGetShapeMesh\n",couldNotFind);
        return 0;
    }
    if (simAddBanner==nullptr)
    {
        printf("%s simAddBanner\n",couldNotFind);
        return 0;
    }
    if (simRemoveBanner==nullptr)
    {
        printf("%s simRemoveBanner\n",couldNotFind);
        return 0;
    }
    if (simCreateJoint==nullptr)
    {
        printf("%s simCreateJoint\n",couldNotFind);
        return 0;
    }
    if (simCreateDummy==nullptr)
    {
        printf("%s simCreateDummy\n",couldNotFind);
        return 0;
    }
    if (simCreateProximitySensor==nullptr)
    {
        printf("%s simCreateProximitySensor\n",couldNotFind);
        return 0;
    }
    if (simCreatePath==nullptr)
    {
        printf("%s simCreatePath\n",couldNotFind);
        return 0;
    }
    if (simInsertPathCtrlPoints==nullptr)
    {
        printf("%s simInsertPathCtrlPoints\n",couldNotFind);
        return 0;
    }
    if (simCutPathCtrlPoints==nullptr)
    {
        printf("%s simCutPathCtrlPoints\n",couldNotFind);
        return 0;
    }
    if (simCreateVisionSensor==nullptr)
    {
        printf("%s simCreateVisionSensor\n",couldNotFind);
        return 0;
    }
    if (simCreateForceSensor==nullptr)
    {
        printf("%s simCreateForceSensor\n",couldNotFind);
        return 0;
    }
    if (simGetObjectIntParameter==nullptr)
    {
        printf("%s simGetObjectIntParameter\n",couldNotFind);
        return 0;
    }
    if (simSetObjectIntParameter==nullptr)
    {
        printf("%s simSetObjectIntParameter\n",couldNotFind);
        return 0;
    }
    if (simGetObjectInt32Parameter==nullptr)
    {
        printf("%s simGetObjectInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simSetObjectInt32Parameter==nullptr)
    {
        printf("%s simSetObjectInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simGetObjectFloatParameter==nullptr)
    {
        printf("%s simGetObjectFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simSetObjectFloatParameter==nullptr)
    {
        printf("%s simSetObjectFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simGetObjectStringParameter==nullptr)
    {
        printf("%s simGetObjectStringParameter\n",couldNotFind);
        return 0;
    }
    if (simSetObjectStringParameter==nullptr)
    {
        printf("%s simSetObjectStringParameter\n",couldNotFind);
        return 0;
    }
    if (simSetSimulationPassesPerRenderingPass==nullptr)
    {
        printf("%s simSetSimulationPassesPerRenderingPass\n",couldNotFind);
        return 0;
    }
    if (simGetRotationAxis==nullptr)
    {
        printf("%s simGetRotationAxis\n",couldNotFind);
        return 0;
    }
    if (simRotateAroundAxis==nullptr)
    {
        printf("%s simRotateAroundAxis\n",couldNotFind);
        return 0;
    }
    if (simGetJointForce==nullptr)
    {
        printf("%s simGetJointForce\n",couldNotFind);
        return 0;
    }
    if (simGetJointMaxForce==nullptr)
    {
        printf("%s simGetJointMaxForce\n",couldNotFind);
        return 0;
    }
    if (simSetArrayParameter==nullptr)
    {
        printf("%s simSetArrayParameter\n",couldNotFind);
        return 0;
    }
    if (simGetArrayParameter==nullptr)
    {
        printf("%s simGetArrayParameter\n",couldNotFind);
        return 0;
    }
    if (simSetIkGroupProperties==nullptr)
    {
        printf("%s simSetIkGroupProperties\n",couldNotFind);
        return 0;
    }
    if (simSetIkElementProperties==nullptr)
    {
        printf("%s simSetIkElementProperties\n",couldNotFind);
        return 0;
    }
    if (simCameraFitToView==nullptr)
    {
        printf("%s simCameraFitToView\n",couldNotFind);
        return 0;
    }
    if (simPersistentDataWrite==nullptr)
    {
        printf("%s simPersistentDataWrite\n",couldNotFind);
        return 0;
    }
    if (simPersistentDataRead==nullptr)
    {
        printf("%s simPersistentDataRead\n",couldNotFind);
        return 0;
    }
    if (simIsHandleValid==nullptr)
    {
        printf("%s simIsHandleValid\n",couldNotFind);
        return 0;
    }
    if (simHandleVisionSensor==nullptr)
    {
        printf("%s simHandleVisionSensor\n",couldNotFind);
        return 0;
    }
    if (simReadVisionSensor==nullptr)
    {
        printf("%s simReadVisionSensor\n",couldNotFind);
        return 0;
    }
    if (simResetVisionSensor==nullptr)
    {
        printf("%s simResetVisionSensor\n",couldNotFind);
        return 0;
    }
    if (simCheckVisionSensor==nullptr)
    {
        printf("%s simCheckVisionSensor\n",couldNotFind);
        return 0;
    }
    if (simCheckVisionSensorEx==nullptr)
    {
        printf("%s simCheckVisionSensorEx\n",couldNotFind);
        return 0;
    }
    if (simGetVisionSensorResolution==nullptr)
    {
        printf("%s simGetVisionSensorResolution\n",couldNotFind);
        return 0;
    }
    if (simGetVisionSensorImage==nullptr)
    {
        printf("%s simGetVisionSensorImage\n",couldNotFind);
        return 0;
    }
    if (simGetVisionSensorCharImage==nullptr)
    {
        printf("%s simGetVisionSensorCharImage\n",couldNotFind);
        return 0;
    }
    if (simSetVisionSensorImage==nullptr)
    {
        printf("%s simSetVisionSensorImage\n",couldNotFind);
        return 0;
    }
    if (simSetVisionSensorCharImage==nullptr)
    {
        printf("%s simSetVisionSensorCharImage\n",couldNotFind);
        return 0;
    }
    if (simGetVisionSensorDepthBuffer==nullptr)
    {
        printf("%s simGetVisionSensorDepthBuffer\n",couldNotFind);
        return 0;
    }
    if (simGetObjectQuaternion==nullptr)
    {
        printf("%s simGetObjectQuaternion\n",couldNotFind);
        return 0;
    }
    if (simSetObjectQuaternion==nullptr)
    {
        printf("%s simSetObjectQuaternion\n",couldNotFind);
        return 0;
    }
    if (simRMLPosition==nullptr)
    {
        printf("%s simRMLPosition\n",couldNotFind);
        return 0;
    }
    if (simRMLVelocity==nullptr)
    {
        printf("%s simRMLVelocity\n",couldNotFind);
        return 0;
    }
    if (simRMLPos==nullptr)
    {
        printf("%s simRMLPos\n",couldNotFind);
        return 0;
    }
    if (simRMLVel==nullptr)
    {
        printf("%s simRMLVel\n",couldNotFind);
        return 0;
    }
    if (simRMLStep==nullptr)
    {
        printf("%s simRMLStep\n",couldNotFind);
        return 0;
    }
    if (simRMLRemove==nullptr)
    {
        printf("%s simRMLRemove\n",couldNotFind);
        return 0;
    }
    if (simBuildMatrixQ==nullptr)
    {
        printf("%s simBuildMatrixQ\n",couldNotFind);
        return 0;
    }
    if (simGetQuaternionFromMatrix==nullptr)
    {
        printf("%s simGetQuaternionFromMatrix\n",couldNotFind);
        return 0;
    }
    if (simFileDialog==nullptr)
    {
        printf("%s simFileDialog\n",couldNotFind);
        return 0;
    }
    if (simMsgBox==nullptr)
    {
        printf("%s simMsgBox\n",couldNotFind);
        return 0;
    }
    if (simSetShapeMassAndInertia==nullptr)
    {
        printf("%s simSetShapeMassAndInertia\n",couldNotFind);
        return 0;
    }
    if (simGetShapeMassAndInertia==nullptr)
    {
        printf("%s simGetShapeMassAndInertia\n",couldNotFind);
        return 0;
    }
    if (simGroupShapes==nullptr)
    {
        printf("%s simGroupShapes\n",couldNotFind);
        return 0;
    }
    if (simUngroupShape==nullptr)
    {
        printf("%s simUngroupShape\n",couldNotFind);
        return 0;
    }
    if (simConvexDecompose==nullptr)
    {
        printf("%s simConvexDecompose\n",couldNotFind);
        return 0;
    }
    if (simGetIkGroupMatrix==nullptr)
    {
        printf("%s simGetIkGroupMatrix\n",couldNotFind);
        return 0;
    }
    if (simAddGhost==nullptr)
    {
        printf("%s simAddGhost\n",couldNotFind);
        return 0;
    }
    if (simModifyGhost==nullptr)
    {
        printf("%s simModifyGhost\n",couldNotFind);
        return 0;
    }
    if (simQuitSimulator==nullptr)
    {
        printf("%s simQuitSimulator\n",couldNotFind);
        return 0;
    }
    if (simGetThreadId==nullptr)
    {
        printf("%s simGetThreadId\n",couldNotFind);
        return 0;
    }
    if (simLockResources==nullptr)
    {
        printf("%s simLockResources\n",couldNotFind);
        return 0;
    }
    if (simUnlockResources==nullptr)
    {
        printf("%s simUnlockResources\n",couldNotFind);
        return 0;
    }
    if (simEnableEventCallback==nullptr)
    {
        printf("%s simEnableEventCallback\n",couldNotFind);
        return 0;
    }
    if (simSetShapeMaterial==nullptr)
    {
        printf("%s simSetShapeMaterial\n",couldNotFind);
        return 0;
    }
    if (simGetTextureId==nullptr)
    {
        printf("%s simGetTextureId\n",couldNotFind);
        return 0;
    }
    if (simReadTexture==nullptr)
    {
        printf("%s simReadTexture\n",couldNotFind);
        return 0;
    }
    if (simWriteTexture==nullptr)
    {
        printf("%s simWriteTexture\n",couldNotFind);
        return 0;
    }
    if (simCreateTexture==nullptr)
    {
        printf("%s simCreateTexture\n",couldNotFind);
        return 0;
    }
    if (simWriteCustomDataBlock==nullptr)
    {
        printf("%s simWriteCustomDataBlock\n",couldNotFind);
        return 0;
    }
    if (simReadCustomDataBlock==nullptr)
    {
        printf("%s simReadCustomDataBlock\n",couldNotFind);
        return 0;
    }
    if (simReadCustomDataBlockTags==nullptr)
    {
        printf("%s simReadCustomDataBlockTags\n",couldNotFind);
        return 0;
    }
    if (simAddPointCloud==nullptr)
    {
        printf("%s simAddPointCloud\n",couldNotFind);
        return 0;
    }
    if (simModifyPointCloud==nullptr)
    {
        printf("%s simModifyPointCloud\n",couldNotFind);
        return 0;
    }
    if (simGetShapeGeomInfo==nullptr)
    {
        printf("%s simGetShapeGeomInfo\n",couldNotFind);
        return 0;
    }
    if (simGetObjectsInTree==nullptr)
    {
        printf("%s simGetObjectsInTree\n",couldNotFind);
        return 0;
    }
    if (simSetObjectSizeValues==nullptr)
    {
        printf("%s simSetObjectSizeValues\n",couldNotFind);
        return 0;
    }
    if (simGetObjectSizeValues==nullptr)
    {
        printf("%s simGetObjectSizeValues\n",couldNotFind);
        return 0;
    }
    if (simScaleObject==nullptr)
    {
        printf("%s simScaleObject\n",couldNotFind);
        return 0;
    }
    if (simSetShapeTexture==nullptr)
    {
        printf("%s simSetShapeTexture\n",couldNotFind);
        return 0;
    }
    if (simGetShapeTextureId==nullptr)
    {
        printf("%s simGetShapeTextureId\n",couldNotFind);
        return 0;
    }
    if (simGetCollectionObjects==nullptr)
    {
        printf("%s simGetCollectionObjects\n",couldNotFind);
        return 0;
    }
    if (simSetScriptAttribute==nullptr)
    {
        printf("%s simSetScriptAttribute\n",couldNotFind);
        return 0;
    }
    if (simGetScriptAttribute==nullptr)
    {
        printf("%s simGetScriptAttribute\n",couldNotFind);
        return 0;
    }
    if (simReorientShapeBoundingBox==nullptr)
    {
        printf("%s simReorientShapeBoundingBox\n",couldNotFind);
        return 0;
    }
    if (simSwitchThread==nullptr)
    {
        printf("%s simSwitchThread\n",couldNotFind);
        return 0;
    }
    if (simCreateIkGroup==nullptr)
    {
        printf("%s simCreateIkGroup\n",couldNotFind);
        return 0;
    }
    if (simRemoveIkGroup==nullptr)
    {
        printf("%s simRemoveIkGroup\n",couldNotFind);
        return 0;
    }
    if (simCreateIkElement==nullptr)
    {
        printf("%s simCreateIkElement\n",couldNotFind);
        return 0;
    }
    if (simCreateCollection==nullptr)
    {
        printf("%s simCreateCollection\n",couldNotFind);
        return 0;
    }
    if (simAddObjectToCollection==nullptr)
    {
        printf("%s simAddObjectToCollection\n",couldNotFind);
        return 0;
    }
    if (simSaveImage==nullptr)
    {
        printf("%s simSaveImage\n",couldNotFind);
        return 0;
    }
    if (simLoadImage==nullptr)
    {
        printf("%s simLoadImage\n",couldNotFind);
        return 0;
    }
    if (simGetScaledImage==nullptr)
    {
        printf("%s simGetScaledImage\n",couldNotFind);
        return 0;
    }
    if (simTransformImage==nullptr)
    {
        printf("%s simTransformImage\n",couldNotFind);
        return 0;
    }
    if (simGetQHull==nullptr)
    {
        printf("%s simGetQHull\n",couldNotFind);
        return 0;
    }
    if (simGetDecimatedMesh==nullptr)
    {
        printf("%s simGetDecimatedMesh\n",couldNotFind);
        return 0;
    }
    if (simExportIk==nullptr)
    {
        printf("%s simExportIk\n",couldNotFind);
        return 0;
    }
    if (simCallScriptFunctionEx==nullptr)
    {
        printf("%s simCallScriptFunctionEx\n",couldNotFind);
        return 0;
    }
    if (simComputeJacobian==nullptr)
    {
        printf("%s simComputeJacobian\n",couldNotFind);
        return 0;
    }
    if (simGetConfigForTipPose==nullptr)
    {
        printf("%s simGetConfigForTipPose\n",couldNotFind);
        return 0;
    }
    if (simGenerateIkPath==nullptr)
    {
        printf("%s simGenerateIkPath\n",couldNotFind);
        return 0;
    }
    if (simGetExtensionString==nullptr)
    {
        printf("%s simGetExtensionString\n",couldNotFind);
        return 0;
    }
    if (simComputeMassAndInertia==nullptr)
    {
        printf("%s simComputeMassAndInertia\n",couldNotFind);
        return 0;
    }
    if (simCreateStack==nullptr)
    {
        printf("%s simCreateStack\n",couldNotFind);
        return 0;
    }
    if (simReleaseStack==nullptr)
    {
        printf("%s simReleaseStack\n",couldNotFind);
        return 0;
    }
    if (simCopyStack==nullptr)
    {
        printf("%s simCopyStack\n",couldNotFind);
        return 0;
    }
    if (simPushNullOntoStack==nullptr)
    {
        printf("%s simPushNullOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushBoolOntoStack==nullptr)
    {
        printf("%s simPushBoolOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushInt32OntoStack==nullptr)
    {
        printf("%s simPushInt32OntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushFloatOntoStack==nullptr)
    {
        printf("%s simPushFloatOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushDoubleOntoStack==nullptr)
    {
        printf("%s simPushDoubleOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushStringOntoStack==nullptr)
    {
        printf("%s simPushStringOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushUInt8TableOntoStack==nullptr)
    {
        printf("%s simPushUInt8TableOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushInt32TableOntoStack==nullptr)
    {
        printf("%s simPushInt32TableOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushFloatTableOntoStack==nullptr)
    {
        printf("%s simPushFloatTableOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushDoubleTableOntoStack==nullptr)
    {
        printf("%s simPushDoubleTableOntoStack\n",couldNotFind);
        return 0;
    }
    if (simPushTableOntoStack==nullptr)
    {
        printf("%s simPushTableOntoStack\n",couldNotFind);
        return 0;
    }
    if (simInsertDataIntoStackTable==nullptr)
    {
        printf("%s simInsertDataIntoStackTable\n",couldNotFind);
        return 0;
    }
    if (simGetStackSize==nullptr)
    {
        printf("%s simGetStackSize\n",couldNotFind);
        return 0;
    }
    if (simPopStackItem==nullptr)
    {
        printf("%s simPopStackItem\n",couldNotFind);
        return 0;
    }
    if (simMoveStackItemToTop==nullptr)
    {
        printf("%s simMoveStackItemToTop\n",couldNotFind);
        return 0;
    }
    if (simIsStackValueNull==nullptr)
    {
        printf("%s simIsStackValueNull\n",couldNotFind);
        return 0;
    }
    if (simGetStackBoolValue==nullptr)
    {
        printf("%s simGetStackBoolValue\n",couldNotFind);
        return 0;
    }
    if (simGetStackInt32Value==nullptr)
    {
        printf("%s simGetStackInt32Value\n",couldNotFind);
        return 0;
    }
    if (simGetStackFloatValue==nullptr)
    {
        printf("%s simGetStackFloatValue\n",couldNotFind);
        return 0;
    }
    if (simGetStackDoubleValue==nullptr)
    {
        printf("%s simGetStackDoubleValue\n",couldNotFind);
        return 0;
    }
    if (simGetStackStringValue==nullptr)
    {
        printf("%s simGetStackStringValue\n",couldNotFind);
        return 0;
    }
    if (simGetStackTableInfo==nullptr)
    {
        printf("%s simGetStackTableInfo\n",couldNotFind);
        return 0;
    }
    if (simGetStackUInt8Table==nullptr)
    {
        printf("%s simGetStackUInt8Table\n",couldNotFind);
        return 0;
    }
    if (simGetStackInt32Table==nullptr)
    {
        printf("%s simGetStackInt32Table\n",couldNotFind);
        return 0;
    }
    if (simGetStackFloatTable==nullptr)
    {
        printf("%s simGetStackFloatTable\n",couldNotFind);
        return 0;
    }
    if (simGetStackDoubleTable==nullptr)
    {
        printf("%s simGetStackDoubleTable\n",couldNotFind);
        return 0;
    }
    if (simUnfoldStackTable==nullptr)
    {
        printf("%s simUnfoldStackTable\n",couldNotFind);
        return 0;
    }
    if (simDebugStack==nullptr)
    {
        printf("%s simDebugStack\n",couldNotFind);
        return 0;
    }
    if (simSetScriptVariable==nullptr)
    {
        printf("%s simSetScriptVariable\n",couldNotFind);
        return 0;
    }
    if (simGetEngineFloatParameter==nullptr)
    {
        printf("%s simGetEngineFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simGetEngineInt32Parameter==nullptr)
    {
        printf("%s simGetEngineInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simGetEngineBoolParameter==nullptr)
    {
        printf("%s simGetEngineBoolParameter\n",couldNotFind);
        return 0;
    }
    if (simSetEngineFloatParameter==nullptr)
    {
        printf("%s simSetEngineFloatParameter\n",couldNotFind);
        return 0;
    }
    if (simSetEngineInt32Parameter==nullptr)
    {
        printf("%s simSetEngineInt32Parameter\n",couldNotFind);
        return 0;
    }
    if (simSetEngineBoolParameter==nullptr)
    {
        printf("%s simSetEngineBoolParameter\n",couldNotFind);
        return 0;
    }
    if (simCreateOctree==nullptr)
    {
        printf("%s simCreateOctree\n",couldNotFind);
        return 0;
    }
    if (simCreatePointCloud==nullptr)
    {
        printf("%s simCreatePointCloud\n",couldNotFind);
        return 0;
    }
    if (simSetPointCloudOptions==nullptr)
    {
        printf("%s simSetPointCloudOptions\n",couldNotFind);
        return 0;
    }
    if (simGetPointCloudOptions==nullptr)
    {
        printf("%s simGetPointCloudOptions\n",couldNotFind);
        return 0;
    }
    if (simInsertVoxelsIntoOctree==nullptr)
    {
        printf("%s simInsertVoxelsIntoOctree\n",couldNotFind);
        return 0;
    }
    if (simRemoveVoxelsFromOctree==nullptr)
    {
        printf("%s simRemoveVoxelsFromOctree\n",couldNotFind);
        return 0;
    }
    if (simInsertPointsIntoPointCloud==nullptr)
    {
        printf("%s simInsertPointsIntoPointCloud\n",couldNotFind);
        return 0;
    }
    if (simRemovePointsFromPointCloud==nullptr)
    {
        printf("%s simRemovePointsFromPointCloud\n",couldNotFind);
        return 0;
    }
    if (simIntersectPointsWithPointCloud==nullptr)
    {
        printf("%s simIntersectPointsWithPointCloud\n",couldNotFind);
        return 0;
    }
    if (simGetOctreeVoxels==nullptr)
    {
        printf("%s simGetOctreeVoxels\n",couldNotFind);
        return 0;
    }
    if (simGetPointCloudPoints==nullptr)
    {
        printf("%s simGetPointCloudPoints\n",couldNotFind);
        return 0;
    }
    if (simInsertObjectIntoOctree==nullptr)
    {
        printf("%s simInsertObjectIntoOctree\n",couldNotFind);
        return 0;
    }
    if (simSubtractObjectFromOctree==nullptr)
    {
        printf("%s simSubtractObjectFromOctree\n",couldNotFind);
        return 0;
    }
    if (simInsertObjectIntoPointCloud==nullptr)
    {
        printf("%s simInsertObjectIntoPointCloud\n",couldNotFind);
        return 0;
    }
    if (simSubtractObjectFromPointCloud==nullptr)
    {
        printf("%s simSubtractObjectFromPointCloud\n",couldNotFind);
        return 0;
    }
    if (simCheckOctreePointOccupancy==nullptr)
    {
        printf("%s simCheckOctreePointOccupancy\n",couldNotFind);
        return 0;
    }
    if (simOpenTextEditor==nullptr)
    {
        printf("%s simOpenTextEditor\n",couldNotFind);
        return 0;
    }
    if (simPackTable==nullptr)
    {
        printf("%s simPackTable\n",couldNotFind);
        return 0;
    }
    if (simUnpackTable==nullptr)
    {
        printf("%s simUnpackTable\n",couldNotFind);
        return 0;
    }
    if (simSetReferencedHandles==nullptr)
    {
        printf("%s simSetReferencedHandles\n",couldNotFind);
        return 0;
    }
    if (simGetReferencedHandles==nullptr)
    {
        printf("%s simGetReferencedHandles\n",couldNotFind);
        return 0;
    }
    if (simGetShapeViz==nullptr)
    {
        printf("%s simGetShapeViz\n",couldNotFind);
        return 0;
    }
    if (simExecuteScriptString==nullptr)
    {
        printf("%s simExecuteScriptString\n",couldNotFind);
        return 0;
    }
    if (simGetApiFunc==nullptr)
    {
        printf("%s simGetApiFunc\n",couldNotFind);
        return 0;
    }
    if (simGetApiInfo==nullptr)
    {
        printf("%s simGetApiInfo\n",couldNotFind);
        return 0;
    }
    if (simSetModuleInfo==nullptr)
    {
        printf("%s simSetModuleInfo\n",couldNotFind);
        return 0;
    }
    if (simGetModuleInfo==nullptr)
    {
        printf("%s simGetModuleInfo\n",couldNotFind);
        return 0;
    }
    if (simIsDeprecated==nullptr)
    {
        printf("%s simIsDeprecated\n",couldNotFind);
        return 0;
    }
    if (simGetPersistentDataTags==nullptr)
    {
        printf("%s simGetPersistentDataTags\n",couldNotFind);
        return 0;
    }
    if (simEventNotification==nullptr)
    {
        printf("%s simEventNotification\n",couldNotFind);
        return 0;
    }
    if (simApplyTexture==nullptr)
    {
        printf("%s simApplyTexture\n",couldNotFind);
        return 0;
    }
    if (simSetJointDependency==nullptr)
    {
        printf("%s simSetJointDependency\n",couldNotFind);
        return 0;
    }
    if (simSetStringNamedParam==nullptr)
    {
        printf("%s simSetStringNamedParam\n",couldNotFind);
        return 0;
    }
    if (simGetStringNamedParam==nullptr)
    {
        printf("%s simGetStringNamedParam\n",couldNotFind);
        return 0;
    }
    if (simGetUserParameter==nullptr)
    {
        printf("%s simGetUserParameter\n",couldNotFind);
        return 0;
    }
    if (simSetUserParameter==nullptr)
    {
        printf("%s simSetUserParameter\n",couldNotFind);
        return 0;
    }


    // Following courtesy of Stephen James:
    if (simExtLaunchUIThread==nullptr)
    {
        printf("%s simExtLaunchUIThread\n",couldNotFind);
        return 0;
    }
    if (simExtCanInitSimThread==nullptr)
    {
        printf("%s simExtCanInitSimThread\n",couldNotFind);
        return 0;
    }
    if (simExtSimThreadInit==nullptr)
    {
        printf("%s simExtSimThreadInit\n",couldNotFind);
        return 0;
    }
    if (simExtSimThreadDestroy==nullptr)
    {
        printf("%s simExtSimThreadDestroy\n",couldNotFind);
        return 0;
    }
    if (simExtPostExitRequest==nullptr)
    {
        printf("%s simExtPostExitRequest\n",couldNotFind);
        return 0;
    }
    if (simExtGetExitRequest==nullptr)
    {
        printf("%s simExtGetExitRequest\n",couldNotFind);
        return 0;
    }
    if (simExtStep==nullptr)
    {
        printf("%s simExtStep\n",couldNotFind);
        return 0;
    }
    if (simExtCallScriptFunction==nullptr)
    {
        printf("%s simExtCallScriptFunction\n",couldNotFind);
        return 0;
    }


    if (_simGetContactCallbackCount==nullptr)
    {
        printf("%s _simGetContactCallbackCount\n",couldNotFind);
        return 0;
    }
    if (_simGetContactCallback==nullptr)
    {
        printf("%s _simGetContactCallback\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicSimulationIconCode==nullptr)
    {
        printf("%s _simSetDynamicSimulationIconCode\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicObjectFlagForVisualization==nullptr)
    {
        printf("%s _simSetDynamicObjectFlagForVisualization\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectListSize==nullptr)
    {
        printf("%s _simGetObjectListSize\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectFromIndex==nullptr)
    {
        printf("%s _simGetObjectFromIndex\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectID==nullptr)
    {
        printf("%s _simGetObjectID\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectType==nullptr)
    {
        printf("%s _simGetObjectType\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectChildren==nullptr)
    {
        printf("%s _simGetObjectChildren\n",couldNotFind);
        return 0;
    }
    if (_simGetGeomProxyFromShape==nullptr)
    {
        printf("%s _simGetGeomProxyFromShape\n",couldNotFind);
        return 0;
    }
    if (_simGetParentObject==nullptr)
    {
        printf("%s _simGetParentObject\n",couldNotFind);
        return 0;
    }
    if (_simGetObject==nullptr)
    {
        printf("%s _simGetObject\n",couldNotFind);
        return 0;
    }
    if (_simGetIkGroupObject==nullptr)
    {
        printf("%s _simGetIkGroupObject\n",couldNotFind);
        return 0;
    }
    if (_simMpHandleIkGroupObject==nullptr)
    {
        printf("%s _simMpHandleIkGroupObject\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectLocalTransformation==nullptr)
    {
        printf("%s _simGetObjectLocalTransformation\n",couldNotFind);
        return 0;
    }
    if (_simSetObjectLocalTransformation==nullptr)
    {
        printf("%s _simSetObjectLocalTransformation\n",couldNotFind);
        return 0;
    }
    if (_simSetObjectCumulativeTransformation==nullptr)
    {
        printf("%s _simSetObjectCumulativeTransformation\n",couldNotFind);
        return 0;
    }
    if (_simGetObjectCumulativeTransformation==nullptr)
    {
        printf("%s _simGetObjectCumulativeTransformation\n",couldNotFind);
        return 0;
    }
    if (_simIsShapeDynamicallyStatic==nullptr)
    {
        printf("%s _simIsShapeDynamicallyStatic\n",couldNotFind);
        return 0;
    }
    if (_simGetTreeDynamicProperty==nullptr)
    {
        printf("%s _simGetTreeDynamicProperty\n",couldNotFind);
        return 0;
    }
    if (_simGetDummyLinkType==nullptr)
    {
        printf("%s _simGetDummyLinkType\n",couldNotFind);
        return 0;
    }
    if (_simGetJointMode==nullptr)
    {
        printf("%s _simGetJointMode\n",couldNotFind);
        return 0;
    }
    if (_simIsJointInHybridOperation==nullptr)
    {
        printf("%s _simIsJointInHybridOperation\n",couldNotFind);
        return 0;
    }
    if (_simDisableDynamicTreeForManipulation==nullptr)
    {
        printf("%s _simDisableDynamicTreeForManipulation\n",couldNotFind);
        return 0;
    }
    if (_simIsShapeDynamicallyRespondable==nullptr)
    {
        printf("%s _simIsShapeDynamicallyRespondable\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicCollisionMask==nullptr)
    {
        printf("%s _simGetDynamicCollisionMask\n",couldNotFind);
        return 0;
    }
    if (_simGetLastParentForLocalGlobalCollidable==nullptr)
    {
        printf("%s _simGetLastParentForLocalGlobalCollidable\n",couldNotFind);
        return 0;
    }
    if (_simSetShapeIsStaticAndNotRespondableButDynamicTag==nullptr)
    {
        printf("%s _simSetShapeIsStaticAndNotRespondableButDynamicTag\n",couldNotFind);
        return 0;
    }
    if (_simGetShapeIsStaticAndNotRespondableButDynamicTag==nullptr)
    {
        printf("%s _simGetShapeIsStaticAndNotRespondableButDynamicTag\n",couldNotFind);
        return 0;
    }
    if (_simSetJointPosition==nullptr)
    {
        printf("%s _simSetJointPosition\n",couldNotFind);
        return 0;
    }
    if (_simGetJointPosition==nullptr)
    {
        printf("%s _simGetJointPosition\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicMotorPositionControlTargetPosition==nullptr)
    {
        printf("%s _simSetDynamicMotorPositionControlTargetPosition\n",couldNotFind);
        return 0;
    }
    if (_simGetInitialDynamicVelocity==nullptr)
    {
        printf("%s _simGetInitialDynamicVelocity\n",couldNotFind);
        return 0;
    }
    if (_simSetInitialDynamicVelocity==nullptr)
    {
        printf("%s _simSetInitialDynamicVelocity\n",couldNotFind);
        return 0;
    }
    if (_simGetInitialDynamicAngVelocity==nullptr)
    {
        printf("%s _simGetInitialDynamicAngVelocity\n",couldNotFind);
        return 0;
    }
    if (_simSetInitialDynamicAngVelocity==nullptr)
    {
        printf("%s _simSetInitialDynamicAngVelocity\n",couldNotFind);
        return 0;
    }
    if (_simGetStartSleeping==nullptr)
    {
        printf("%s _simGetStartSleeping\n",couldNotFind);
        return 0;
    }
    if (_simGetWasPutToSleepOnce==nullptr)
    {
        printf("%s _simGetWasPutToSleepOnce\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicsFullRefreshFlag==nullptr)
    {
        printf("%s _simGetDynamicsFullRefreshFlag\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicsFullRefreshFlag==nullptr)
    {
        printf("%s _simSetDynamicsFullRefreshFlag\n",couldNotFind);
        return 0;
    }
    if (_simSetGeomProxyDynamicsFullRefreshFlag==nullptr)
    {
        printf("%s _simSetGeomProxyDynamicsFullRefreshFlag\n",couldNotFind);
        return 0;
    }
    if (_simGetGeomProxyDynamicsFullRefreshFlag==nullptr)
    {
        printf("%s _simGetGeomProxyDynamicsFullRefreshFlag\n",couldNotFind);
        return 0;
    }
    if (_simSetShapeDynamicVelocity==nullptr)
    {
        printf("%s _simSetShapeDynamicVelocity\n",couldNotFind);
        return 0;
    }
    if (_simGetAdditionalForceAndTorque==nullptr)
    {
        printf("%s _simGetAdditionalForceAndTorque\n",couldNotFind);
        return 0;
    }
    if (_simClearAdditionalForceAndTorque==nullptr)
    {
        printf("%s _simClearAdditionalForceAndTorque\n",couldNotFind);
        return 0;
    }
    if (_simGetJointPositionInterval==nullptr)
    {
        printf("%s _simGetJointPositionInterval\n",couldNotFind);
        return 0;
    }
    if (_simGetJointType==nullptr)
    {
        printf("%s _simGetJointType\n",couldNotFind);
        return 0;
    }
    if (_simIsForceSensorBroken==nullptr)
    {
        printf("%s _simIsForceSensorBroken\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicForceSensorLocalTransformationPart2==nullptr)
    {
        printf("%s _simGetDynamicForceSensorLocalTransformationPart2\n",couldNotFind);
        return 0;
    }
    if (_simIsDynamicMotorEnabled==nullptr)
    {
        printf("%s _simIsDynamicMotorEnabled\n",couldNotFind);
        return 0;
    }
    if (_simIsDynamicMotorPositionCtrlEnabled==nullptr)
    {
        printf("%s _simIsDynamicMotorPositionCtrlEnabled\n",couldNotFind);
        return 0;
    }
    if (_simIsDynamicMotorTorqueModulationEnabled==nullptr)
    {
        printf("%s _simIsDynamicMotorTorqueModulationEnabled\n",couldNotFind);
        return 0;
    }
    if (_simGetMotorPid==nullptr)
    {
        printf("%s _simGetMotorPid\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicMotorTargetPosition==nullptr)
    {
        printf("%s _simGetDynamicMotorTargetPosition\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicMotorTargetVelocity==nullptr)
    {
        printf("%s _simGetDynamicMotorTargetVelocity\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicMotorMaxForce==nullptr)
    {
        printf("%s _simGetDynamicMotorMaxForce\n",couldNotFind);
        return 0;
    }
    if (_simGetDynamicMotorUpperLimitVelocity==nullptr)
    {
        printf("%s _simGetDynamicMotorUpperLimitVelocity\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicMotorReflectedPositionFromDynamicEngine==nullptr)
    {
        printf("%s _simSetDynamicMotorReflectedPositionFromDynamicEngine\n",couldNotFind);
        return 0;
    }
    if (_simSetJointSphericalTransformation==nullptr)
    {
        printf("%s _simSetJointSphericalTransformation\n",couldNotFind);
        return 0;
    }
    if (_simAddForceSensorCumulativeForcesAndTorques==nullptr)
    {
        printf("%s _simAddForceSensorCumulativeForcesAndTorques\n",couldNotFind);
        return 0;
    }
    if (_simAddJointCumulativeForcesOrTorques==nullptr)
    {
        printf("%s _simAddJointCumulativeForcesOrTorques\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicJointLocalTransformationPart2==nullptr)
    {
        printf("%s _simSetDynamicJointLocalTransformationPart2\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicForceSensorLocalTransformationPart2==nullptr)
    {
        printf("%s _simSetDynamicForceSensorLocalTransformationPart2\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicJointLocalTransformationPart2IsValid==nullptr)
    {
        printf("%s _simSetDynamicJointLocalTransformationPart2IsValid\n",couldNotFind);
        return 0;
    }
    if (_simSetDynamicForceSensorLocalTransformationPart2IsValid==nullptr)
    {
        printf("%s _simSetDynamicForceSensorLocalTransformationPart2IsValid\n",couldNotFind);
        return 0;
    }
    if (_simGetGeomWrapFromGeomProxy==nullptr)
    {
        printf("%s _simGetGeomWrapFromGeomProxy\n",couldNotFind);
        return 0;
    }
    if (_simGetLocalInertiaFrame==nullptr)
    {
        printf("%s _simGetLocalInertiaFrame\n",couldNotFind);
        return 0;
    }
    if (_simGetPurePrimitiveType==nullptr)
    {
        printf("%s _simGetPurePrimitiveType\n",couldNotFind);
        return 0;
    }
    if (_simIsGeomWrapGeometric==nullptr)
    {
        printf("%s _simIsGeomWrapGeometric\n",couldNotFind);
        return 0;
    }
    if (_simIsGeomWrapConvex==nullptr)
    {
        printf("%s _simIsGeomWrapConvex\n",couldNotFind);
        return 0;
    }
    if (_simGetGeometricCount==nullptr)
    {
        printf("%s _simGetGeometricCount\n",couldNotFind);
        return 0;
    }
    if (_simGetAllGeometrics==nullptr)
    {
        printf("%s _simGetAllGeometrics\n",couldNotFind);
        return 0;
    }
    if (_simGetPurePrimitiveSizes==nullptr)
    {
        printf("%s _simGetPurePrimitiveSizes\n",couldNotFind);
        return 0;
    }
    if (_simMakeDynamicAnnouncement==nullptr)
    {
        printf("%s _simMakeDynamicAnnouncement\n",couldNotFind);
        return 0;
    }
    if (_simGetVerticesLocalFrame==nullptr)
    {
        printf("%s _simGetVerticesLocalFrame\n",couldNotFind);
        return 0;
    }
    if (_simGetHeightfieldData==nullptr)
    {
        printf("%s _simGetHeightfieldData\n",couldNotFind);
        return 0;
    }
    if (_simGetCumulativeMeshes==nullptr)
    {
        printf("%s _simGetCumulativeMeshes\n",couldNotFind);
        return 0;
    }
    if (_simGetMass==nullptr)
    {
        printf("%s _simGetMass\n",couldNotFind);
        return 0;
    }
    if (_simGetPrincipalMomentOfInertia==nullptr)
    {
        printf("%s _simGetPrincipalMomentOfInertia\n",couldNotFind);
        return 0;
    }
    if (_simGetGravity==nullptr)
    {
        printf("%s _simGetGravity\n",couldNotFind);
        return 0;
    }
    if (_simGetTimeDiffInMs==nullptr)
    {
        printf("%s _simGetTimeDiffInMs\n",couldNotFind);
        return 0;
    }
    if (_simDoEntitiesCollide==nullptr)
    {
        printf("%s _simDoEntitiesCollide\n",couldNotFind);
        return 0;
    }
    if (_simGetDistanceBetweenEntitiesIfSmaller==nullptr)
    {
        printf("%s _simGetDistanceBetweenEntitiesIfSmaller\n",couldNotFind);
        return 0;
    }
    if (_simHandleJointControl==nullptr)
    {
        printf("%s _simHandleJointControl\n",couldNotFind);
        return 0;
    }
    if (_simHandleCustomContact==nullptr)
    {
        printf("%s _simHandleCustomContact\n",couldNotFind);
        return 0;
    }
    if (_simGetPureHollowScaling==nullptr)
    {
        printf("%s _simGetPureHollowScaling\n",couldNotFind);
        return 0;
    }
    if (_simGetJointCallbackCallOrder==nullptr)
    {
        printf("%s _simGetJointCallbackCallOrder\n",couldNotFind);
        return 0;
    }
    if (_simDynCallback==nullptr)
    {
        printf("%s _simDynCallback\n",couldNotFind);
        return 0;
    }




    // Deprecated begin
    if (simGetMaterialId==nullptr)
    {
        printf("%s simGetMaterialId\n",couldNotFind);
        return 0;
    }
    if (simGetShapeMaterial==nullptr)
    {
        printf("%s simGetShapeMaterial\n",couldNotFind);
        return 0;
    }
    if (simHandleVarious==nullptr)
    {
        printf("%s simHandleVarious\n",couldNotFind);
        return 0;
    }
    if (simSerialPortOpen==nullptr)
    {
        printf("%s simSerialPortOpen\n",couldNotFind);
        return 0;
    }
    if (simSerialPortClose==nullptr)
    {
        printf("%s simSerialPortClose\n",couldNotFind);
        return 0;
    }
    if (simSerialPortSend==nullptr)
    {
        printf("%s simSerialPortSend\n",couldNotFind);
        return 0;
    }
    if (simSerialPortRead==nullptr)
    {
        printf("%s simSerialPortRead\n",couldNotFind);
        return 0;
    }
    if (simJointGetForce==nullptr)
    {
        printf("%s simJointGetForce\n",couldNotFind);
        return 0;
    }
    if (simGetPathPlanningHandle==nullptr)
    {
        printf("%s simGetPathPlanningHandle\n",couldNotFind);
        return 0;
    }
    if (simGetMotionPlanningHandle==nullptr)
    {
        printf("%s simGetMotionPlanningHandle\n",couldNotFind);
        return 0;
    }
    if (simGetMpConfigForTipPose==nullptr)
    {
        printf("%s simGetMpConfigForTipPose\n",couldNotFind);
        return 0;
    }
    if (simFindMpPath==nullptr)
    {
        printf("%s simFindMpPath\n",couldNotFind);
        return 0;
    }
    if (simSimplifyMpPath==nullptr)
    {
        printf("%s simSimplifyMpPath\n",couldNotFind);
        return 0;
    }
    if (simGetMpConfigTransition==nullptr)
    {
        printf("%s simGetMpConfigTransition\n",couldNotFind);
        return 0;
    }
    if (simFindIkPath==nullptr)
    {
        printf("%s simFindIkPath\n",couldNotFind);
        return 0;
    }
    if (simCreateMotionPlanning==nullptr)
    {
        printf("%s simCreateMotionPlanning\n",couldNotFind);
        return 0;
    }
    if (simRemoveMotionPlanning==nullptr)
    {
        printf("%s simRemoveMotionPlanning\n",couldNotFind);
        return 0;
    }
    if (simSearchPath==nullptr)
    {
        printf("%s simSearchPath\n",couldNotFind);
        return 0;
    }
    if (simInitializePathSearch==nullptr)
    {
        printf("%s simInitializePathSearch\n",couldNotFind);
        return 0;
    }
    if (simPerformPathSearchStep==nullptr)
    {
        printf("%s simPerformPathSearchStep\n",couldNotFind);
        return 0;
    }
    if (simLockInterface==nullptr)
    {
        printf("%s simLockInterface\n",couldNotFind);
        return 0;
    }
    if (simCopyPasteSelectedObjects==nullptr)
    {
        printf("%s simCopyPasteSelectedObjects\n",couldNotFind);
        return 0;
    }
    if (simResetPath==nullptr)
    {
        printf("%s simResetPath\n",couldNotFind);
        return 0;
    }
    if (simHandlePath==nullptr)
    {
        printf("%s simHandlePath\n",couldNotFind);
        return 0;
    }
    if (simResetJoint==nullptr)
    {
        printf("%s simResetJoint\n",couldNotFind);
        return 0;
    }
    if (simHandleJoint==nullptr)
    {
        printf("%s simHandleJoint\n",couldNotFind);
        return 0;
    }
    if (simAppendScriptArrayEntry==nullptr)
    {
        printf("%s simAppendScriptArrayEntry\n",couldNotFind);
        return 0;
    }
    if (simClearScriptVariable==nullptr)
    {
        printf("%s simClearScriptVariable\n",couldNotFind);
        return 0;
    }
    if (_simGetJointOdeParameters==nullptr)
    {
        printf("%s _simGetJointOdeParameters\n",couldNotFind);
        return 0;
    }
    if (_simGetJointBulletParameters==nullptr)
    {
        printf("%s _simGetJointBulletParameters\n",couldNotFind);
        return 0;
    }
    if (_simGetOdeMaxContactFrictionCFMandERP==nullptr)
    {
        printf("%s _simGetOdeMaxContactFrictionCFMandERP\n",couldNotFind);
        return 0;
    }
    if (_simGetBulletCollisionMargin==nullptr)
    {
        printf("%s _simGetBulletCollisionMargin\n",couldNotFind);
        return 0;
    }
    if (_simGetBulletStickyContact==nullptr)
    {
        printf("%s _simGetBulletStickyContact\n",couldNotFind);
        return 0;
    }
    if (_simGetBulletRestitution==nullptr)
    {
        printf("%s _simGetBulletRestitution\n",couldNotFind);
        return 0;
    }
    if (_simGetVortexParameters==nullptr)
    {
        printf("%s _simGetVortexParameters\n",couldNotFind);
        return 0;
    }
    if (_simGetNewtonParameters==nullptr)
    {
        printf("%s _simGetNewtonParameters\n",couldNotFind);
        return 0;
    }
    if (_simGetDamping==nullptr)
    {
        printf("%s _simGetDamping\n",couldNotFind);
        return 0;
    }
    if (_simGetFriction==nullptr)
    {
        printf("%s _simGetFriction\n",couldNotFind);
        return 0;
    }
    if (simAddSceneCustomData==nullptr)
    {
        printf("%s simAddSceneCustomData\n",couldNotFind);
        return 0;
    }
    if (simGetSceneCustomDataLength==nullptr)
    {
        printf("%s simGetSceneCustomDataLength\n",couldNotFind);
        return 0;
    }
    if (simGetSceneCustomData==nullptr)
    {
        printf("%s simGetSceneCustomData\n",couldNotFind);
        return 0;
    }
    if (simAddObjectCustomData==nullptr)
    {
        printf("%s simAddObjectCustomData\n",couldNotFind);
        return 0;
    }
    if (simGetObjectCustomDataLength==nullptr)
    {
        printf("%s simGetObjectCustomDataLength\n",couldNotFind);
        return 0;
    }
    if (simGetObjectCustomData==nullptr)
    {
        printf("%s simGetObjectCustomData\n",couldNotFind);
        return 0;
    }
    if (simCreateUI==nullptr)
    {
        printf("%s simCreateUI\n",couldNotFind);
        return 0;
    }
    if (simCreateUIButton==nullptr)
    {
        printf("%s simCreateUIButton\n",couldNotFind);
        return 0;
    }
    if (simGetUIHandle==nullptr)
    {
        printf("%s simGetUIHandle\n",couldNotFind);
        return 0;
    }
    if (simGetUIProperty==nullptr)
    {
        printf("%s simGetUIProperty\n",couldNotFind);
        return 0;
    }
    if (simGetUIEventButton==nullptr)
    {
        printf("%s simGetUIEventButton\n",couldNotFind);
        return 0;
    }
    if (simSetUIProperty==nullptr)
    {
        printf("%s simSetUIProperty\n",couldNotFind);
        return 0;
    }
    if (simGetUIButtonProperty==nullptr)
    {
        printf("%s simGetUIButtonProperty\n",couldNotFind);
        return 0;
    }
    if (simSetUIButtonProperty==nullptr)
    {
        printf("%s simSetUIButtonProperty\n",couldNotFind);
        return 0;
    }
    if (simGetUIButtonSize==nullptr)
    {
        printf("%s simGetUIButtonSize\n",couldNotFind);
        return 0;
    }
    if (simSetUIButtonLabel==nullptr)
    {
        printf("%s simSetUIButtonLabel\n",couldNotFind);
        return 0;
    }
    if (simGetUIButtonLabel==nullptr)
    {
        printf("%s simGetUIButtonLabel\n",couldNotFind);
        return 0;
    }
    if (simSetUISlider==nullptr)
    {
        printf("%s simSetUISlider\n",couldNotFind);
        return 0;
    }
    if (simGetUISlider==nullptr)
    {
        printf("%s simGetUISlider\n",couldNotFind);
        return 0;
    }
    if (simSetUIButtonColor==nullptr)
    {
        printf("%s simSetUIButtonColor\n",couldNotFind);
        return 0;
    }
    if (simSetUIButtonTexture==nullptr)
    {
        printf("%s simSetUIButtonTexture\n",couldNotFind);
        return 0;
    }
    if (simCreateUIButtonArray==nullptr)
    {
        printf("%s simCreateUIButtonArray\n",couldNotFind);
        return 0;
    }
    if (simSetUIButtonArrayColor==nullptr)
    {
        printf("%s simSetUIButtonArrayColor\n",couldNotFind);
        return 0;
    }
    if (simDeleteUIButtonArray==nullptr)
    {
        printf("%s simDeleteUIButtonArray\n",couldNotFind);
        return 0;
    }
    if (simRemoveUI==nullptr)
    {
        printf("%s simRemoveUI\n",couldNotFind);
        return 0;
    }
    if (simSetUIPosition==nullptr)
    {
        printf("%s simSetUIPosition\n",couldNotFind);
        return 0;
    }
    if (simGetUIPosition==nullptr)
    {
        printf("%s simGetUIPosition\n",couldNotFind);
        return 0;
    }
    if (simLoadUI==nullptr)
    {
        printf("%s simLoadUI\n",couldNotFind);
        return 0;
    }
    if (simSaveUI==nullptr)
    {
        printf("%s simSaveUI\n",couldNotFind);
        return 0;
    }
    if (simHandleGeneralCallbackScript==nullptr)
    {
        printf("%s simHandleGeneralCallbackScript\n",couldNotFind);
        return 0;
    }
    if (simRegisterCustomLuaFunction==nullptr)
    {
        printf("%s simRegisterCustomLuaFunction\n",couldNotFind);
        return 0;
    }
    if (simRegisterCustomLuaVariable==nullptr)
    {
        printf("%s simRegisterCustomLuaVariable\n",couldNotFind);
        return 0;
    }
    if (simRegisterContactCallback==nullptr)
    {
        printf("%s simRegisterContactCallback\n",couldNotFind);
        return 0;
    }
    if (simGetMechanismHandle==nullptr)
    {
        printf("%s simGetMechanismHandle\n",couldNotFind);
        return 0;
    }
    if (simHandleMechanism==nullptr)
    {
        printf("%s simHandleMechanism\n",couldNotFind);
        return 0;
    }
    if (simHandleCustomizationScripts==nullptr)
    {
        printf("%s simHandleCustomizationScripts\n",couldNotFind);
        return 0;
    }
    if (simCallScriptFunction==nullptr)
    {
        printf("%s simCallScriptFunction\n",couldNotFind);
        return 0;
    }
    if (simSetVisionSensorFilter==nullptr)
    {
        printf("%s simSetVisionSensorFilter\n",couldNotFind);
        return 0;
    }
    if (simGetVisionSensorFilter==nullptr)
    {
        printf("%s simGetVisionSensorFilter\n",couldNotFind);
        return 0;
    }
    if (simGetScriptSimulationParameter==nullptr)
    {
        printf("%s simGetScriptSimulationParameter\n",couldNotFind);
        return 0;
    }
    if (simSetScriptSimulationParameter==nullptr)
    {
        printf("%s simSetScriptSimulationParameter\n",couldNotFind);
        return 0;
    }
    if (simSetJointForce==nullptr)
    {
        printf("%s simSetJointForce\n",couldNotFind);
        return 0;
    }
    if (simHandleMill==nullptr)
    {
        printf("%s simHandleMill\n",couldNotFind);
        return 0;
    }
    if (simResetMill==nullptr)
    {
        printf("%s simResetMill\n",couldNotFind);
        return 0;
    }
    if (simResetMilling==nullptr)
    {
        printf("%s simResetMilling\n",couldNotFind);
        return 0;
    }
    if (simApplyMilling==nullptr)
    {
        printf("%s simApplyMilling\n",couldNotFind);
        return 0;
    }
    if (_simGetParentFollowsDynamic==nullptr)
    {
        printf("%s _simGetParentFollowsDynamic\n",couldNotFind);
        return 0;
    }
    if (simGetNameSuffix==nullptr)
    {
        printf("%s simGetNameSuffix\n",couldNotFind);
        return 0;
    }
    if (simSetNameSuffix==nullptr)
    {
        printf("%s simSetNameSuffix\n",couldNotFind);
        return 0;
    }
    if (simAddStatusbarMessage==nullptr)
    {
        printf("%s simAddStatusbarMessage\n",couldNotFind);
        return 0;
    }
    // Deprecated end

    return 1;
}

#endif // SIM_LIBRARY
