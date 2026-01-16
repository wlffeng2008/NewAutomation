///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1CONFIGURATION_H_INCLUDED
#define AUTOMATION1CONFIGURATION_H_INCLUDED

#if defined(_MSC_VER)
	#if defined(AUTOMATION1_CAPI_EXPORT)
		#define AUTOMATION1_CAPI __declspec(dllexport)
	#else
		#define AUTOMATION1_CAPI __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#define AUTOMATION1_CAPI __attribute__((visibility ("default")))
#endif

#include <stdint.h>
#include <stdbool.h>
#include "Automation1Enum.h"
#include "Automation1Controller.h"
#include "Automation1ParameterId.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Represents a collection of configured parameters that you can get from or set to an Automation1 controller.
///		Configured Parameters are different from active parameters in that they persist between controller resets.
/// 	To obtain a handle of this type, see Automation1_ConfiguredParameters_Create().
///		Use the Automation1_Configuration_GetConfiguredParameters() function to get configured parameters from your controller to this handle.
///		Use the Automation1_Configuration_SetConfiguredParameters() function to set the configured parameters on your controller using the values in this handle.
/// 	Use the Automation1_ConfiguredParameters_Get* and Automation1_ConfiguredParameters_Set* functions to get and set values this configured parameters handle.
/// 	Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_ConfiguredParameters_Destroy() function.
typedef struct Automation1ConfiguredParameters_T* Automation1ConfiguredParameters;

/// @brief Represents a calibration file that you can get from or set to an Automation1 controller.
///		To obtain a handle of this type, see Automation1_CalibrationFile_Create().
///		Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_CalibrationFile_Destroy() function.
typedef struct Automation1CalibrationFile_T* Automation1CalibrationFile;

/// @brief Represents a configuration of compiled AeroScript programs, compiled AeroScript libraries, and AeroScript source files that you can get from or set to an Automation1 controller.
///		Compiled AeroScript programs can be configured to automatically load or run on a task whenever the controller starts.
///		Compiled AeroScript libraries can be configured to automatically load and import in other AeroScript programs.
///		AeroScript source files can be configured to be automatically included in other AeroScript programs.
/// 	To obtain a handle of this type, see Automation1_ConfiguredProgramAutomation_Create().
///		Use the Automation1_Configuration_GetConfiguredProgramAutomation() function to get configured program automation from your controller to this handle.
///		Use the Automation1_Configuration_SetConfiguredProgramAutomation() function to set the configured program automation on your controller using the files configured in this handle.
/// 	Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_ConfiguredProgramAutomation_Destroy() function.
typedef struct Automation1ConfiguredProgramAutomation_T* Automation1ConfiguredProgramAutomation;

/// @brief Represents the configuration of Industrial Ethernet connections and mappings that you can get from or set to an Automation1 Controller.
///		To get and set individual Industrial Ethernet mapping values use the Industrial Ethernet Variables API.
///		To obtain a handle of this type, see Automation1_ConfiguredIndustrialEthernet_Create().
///		Use the Automation1_Configuration_GetConfiguredIndustrialEthernet() function to get configured Industrial Ethernet from your controller to this handle.
///		Use the Automation1_Configuration_SetConfiguredIndustrialEthernet() function to set the configured Industrial Ethernet on your controller using the connections and mappings configured in this handle.
///		Make sure to destroy the handle when you are done to avoid leaking memory using the Automation1_ConfiguredIndustrialEthernet_Destroy() function.
typedef struct Automation1ConfiguredIndustrialEthernet_T* Automation1ConfiguredIndustrialEthernet;

/// @brief Gets the configured parameters from an Automation1 controller
///		Configured parameters are different from active parameters in that they persist between controller resets.
///		If configured parameters have not been set, then trying to get them from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsConfiguredParametersSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the configured parameters from.
/// @param[In] configuredParameters The collection of configured parameters to store the controller's configured parameters in.
///		You must first create the handle using Automation1_ConfiguredParameters_Create() before passing it to this function.
///		This function will clear all other configured parameters that are set in this collection and replace them with the configured
///		parameters from the Automation1Controller. 
/// @return Returns true if the configured parameters from the Automation1 controller were retrieved successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetConfiguredParameters(Automation1Controller controller, Automation1ConfiguredParameters configuredParameters);

/// @brief Sets the configured parameters on an Automation1 controller
///		Configured parameters are different from active parameters in that they persist between controller resets.
///		After calling this function to set the configured parameters on your controller, you may have to reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the configured parameters on.
/// @param[In] configuredParameters The collection of configured parameters to set on the Automation1 controller.
/// @return Returns true if the configured parameters from the Automation1 controller were set successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetConfiguredParameters(Automation1Controller controller, Automation1ConfiguredParameters configuredParameters);

/// @brief Gets whether configured parameters on an Automation1 controller have been set.
///		If configured parameters have not been set, then trying to get them from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetConfiguredParameters().
///	@param[In] controller The Automation1 controller to check whether configured parameters have been set on.
/// @param[Out] isConfiguredParametersSetOut Whether configured parameters are set on the specified Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether the configuration was set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsConfiguredParametersSet(Automation1Controller controller, bool* isConfiguredParametersSetOut);

/// @brief Removes the configured parameters that are set on an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configuration from.
/// @return Returns true if the configured parameters were successfully removed from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveConfiguredParameters(Automation1Controller controller);

/// @brief Gets the configured 1D calibration file from an Automation1 controller.
///		If a configured 1D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsCalibration1DFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the 1D calibration file from.
/// @param[In] calibrationFile The 1D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the 1D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the 1D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetCalibration1DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured 2D calibration file from an Automation1 controller.
///		If a configured 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsCalibration2DFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the 2D calibration file from.
/// @param[In] calibrationFile The 2D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the 2D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the 2D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetCalibration2DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured galvo 2D calibration file from an Automation1 controller.
///		If a configured galvo 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsGalvo2DCalibrationFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the galvo 2D calibration file from.
/// @param[In] calibrationFile The galvo 2D calibration file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the galvo 2D calibration file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the galvo 2D calibration file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetGalvo2DCalibrationFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets the configured galvo power correction file from an Automation1 controller.
///		If a configured galvo power correction file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsGalvoPowerCorrectionFileSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the galvo power correction file from.
/// @param[In] calibrationFile The galvo power correction file retrieved from the Automation1 controller.
///		You must first create the handle using Automation1_CalibrationFile_Create() before passing it to this function.
///		This function will overwrite any content that already exists in the specified calibration file, replacing it with
///		the contents of the galvo power correction file retrieved from the Automation1 controller.
///		Only use this if the function call was successful.
/// @return Returns true if the galvo power correction file was successfully retrieved from the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetGalvoPowerCorrectionFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured 1D calibration file on an Automation1 controller.
///		After calling this function to set the configured 1D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the 1D calibration file on.
/// @param[In] calibrationFile The 1D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the 1D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetCalibration1DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured 2D calibration file on an Automation1 controller.
///		After calling this function to set the configured 2D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the 2D calibration file on.
/// @param[In] calibrationFile The 2D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the 2D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetCalibration2DFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured galvo 2D calibration file on an Automation1 controller.
///		After calling this function to set the configured galvo 2D calibration file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the galvo 2D calibration file on.
/// @param[In] calibrationFile The galvo 2D calibration file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the galvo 2D calibration file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetGalvo2DCalibrationFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Sets a configured galvo power correction file on an Automation1 controller.
///		After calling this function to set the configured galvo power correction file on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the galvo power correction file on.
/// @param[In] calibrationFile The galvo power correction file to set on the Automation1 controller.
///		Use the Automation1_CalibrationFile_Create() function to obtain an Automation1CalibrationFile handle.
/// @return Returns true if the galvo power correction file was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetGalvoPowerCorrectionFile(Automation1Controller controller, Automation1CalibrationFile calibrationFile);

/// @brief Gets whether a configured 1D calibration file is set on an Automation1 controller.
///		If a configured 1D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetCalibration1DFile().
/// @param[In] controller The Automation1 controller to get whether a 1D calibration file is set on.
/// @param[Out] isCalibration1DFileSetOut Whether a configured 1D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured 1D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsCalibration1DFileSet(Automation1Controller controller, bool* isCalibration1DFileSetOut);

/// @brief Gets whether a configured 2D calibration file is set on an Automation1 controller.
///		If a configured 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetCalibration2DFile().
/// @param[In] controller The Automation1 controller to get whether a 2D calibration file is set on.
/// @param[Out] isCalibration2DFileSetOut Whether a configured 2D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured 2D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsCalibration2DFileSet(Automation1Controller controller, bool* isCalibration2DFileSetOut);

/// @brief Gets whether a configured galvo 2D calibration file is set on an Automation1 controller.
///		If a configured galvo 2D calibration file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetGalvo2DCalibrationFile().
/// @param[In] controller The Automation1 controller to get whether a galvo 2D calibration file is set on.
/// @param[Out] isGalvo2DCalibrationFileSetOut Whether a configured galvo 2D calibration file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured galvo 2D calibration file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsGalvo2DCalibrationFileSet(Automation1Controller controller, bool* isGalvo2DCalibrationFileSetOut);

/// @brief Gets whether a configured galvo power correction file is set on an Automation1 controller.
///		If a configured galvo power correction file has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetGalvoPowerCorrectionFile().
/// @param[In] controller The Automation1 controller to get whether a galvo power correction file is set on.
/// @param[Out] isGalvoPowerCorrectionFileSetOut Whether a configured galvo power correction file is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether a configured galvo power correction file is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsGalvoPowerCorrectionFileSet(Automation1Controller controller, bool* isGalvoPowerCorrectionFileSetOut);

/// @brief Removes the configured 1D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured 1D calibration file from.
/// @return Returns true if the configured 1D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveCalibration1DFile(Automation1Controller controller);

/// @brief Removes the configured 2D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured 2D calibration file from.
/// @return Returns true if the configured 2D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveCalibration2DFile(Automation1Controller controller);

/// @brief Removes the configured galvo 2D calibration file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured galvo 2D calibration file from.
/// @return Returns true if the configured galvo 2D calibration file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveGalvo2DCalibrationFile(Automation1Controller controller);

/// @brief Removes the configured galvo power correction file from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured galvo power correction file from.
/// @return Returns true if the configured galvo power correction file was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveGalvoPowerCorrectionFile(Automation1Controller controller);

/// @brief Gets the configured program automation from an Automation1 controller
///		If program automation has not been configured, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsConfiguredProgramAutomationSet() before calling this function.
/// @param[In] controller The Automation1 controller to get the configured program automation from.
/// @param[In] configuredProgramAutomation The handle to store the controller's configured program automation files in.
///		You must first create the handle using Automation1_ConfiguredProgramAutomation_Create() before passing it to this function.
///		This function will clear all other configured program automation files that are set in this handle and replace them with the
///		configured program automation files from the Automation1Controller. 
/// @return Returns true if the configured program automation from the Automation1 controller was retrieved successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetConfiguredProgramAutomation(Automation1Controller controller, Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Sets the configured program automation on an Automation1 controller.
///		After calling this function to set the configured program automation on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the configured program automation on.
/// @param[In] configuredProgramAutomation The configured program automation to set on the Automation1 controller.
///		Use the Automation1_ConfiguredProgramAutomation_Create() function to obtain an Automation1ConfiguredProgramAutomation handle.
/// @return Returns true if the configured program automation was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetConfiguredProgramAutomation(Automation1Controller controller, Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Gets whether configured program automation is set on an Automation1 controller.
///		If configured program automation has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetConfiguredProgramAutomation().
/// @param[In] controller The Automation1 controller to get whether configured program automation is set on.
/// @param[Out] isConfigurationSetOut Whether configured program automation is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether configured program automation is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsConfiguredProgramAutomationSet(Automation1Controller controller, bool* isConfigurationSetOut);

/// @brief Removes the configured program automation from an Automation1 controller.
/// @param[In] controller The Automation1 controller to remove the configured program automation from.
/// @return Returns true if the configured program automation was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveConfiguredProgramAutomation(Automation1Controller controller);

/// @brief Creates a new Automation1ConfiguredParameters handle.
///		Make sure to call Automation1_ConfiguredParameters_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] configuredParametersOut The created Automation1ConfiguredParameters handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1ConfiguredParameters handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_Create(Automation1ConfiguredParameters* configuredParametersOut);

/// @brief Destroys the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The Automation1ConfiguredParameters handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_Destroy(Automation1ConfiguredParameters configuredParameters);

/// @brief Gets the string value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the system parameter from.
/// @param[In] parameterId The system parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified system parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetSystemStringValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the system parameter from.
/// @param[In] parameterId The system parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified system parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetSystemValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the system parameter on.
/// @param[In] parameterId The system parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetSystemStringValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured system parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the system parameter on.
/// @param[In] parameterId The system parameter to set the value of.
/// @param[In] value The numeric value to set the specified system parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetSystemValue(Automation1ConfiguredParameters configuredParameters, Automation1SystemParameterId parameterId, double value);

/// @brief Gets the string value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the axis parameter from.
/// @param[In] axisIndex The axis to get the parameter from.
/// @param[In] parameterId The axis parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified axis parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetAxisStringValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the axis parameter from.
/// @param[In] axisIndex The axis to get the parameter from.
/// @param[In] parameterId The axis parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified axis parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetAxisValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the axis parameter on.
/// @param[In] axisIndex The axis to set the parameter on.
/// @param[In] parameterId The axis parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetAxisStringValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured axis parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the axis parameter on.
/// @param[In] axisIndex The axis to set the parameter on.
/// @param[In] parameterId The axis parameter to set the value of.
/// @param[In] value The numeric value to set the specified axis parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetAxisValue(Automation1ConfiguredParameters configuredParameters, int32_t axisIndex, Automation1AxisParameterId parameterId, double value);

/// @brief Gets the string value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the task parameter from.
/// @param[In] taskIndex The task to get the parameter from.
/// @param[In] parameterId The task parameter to get the value of.
/// @param[Out] valueOut The null-terminated string value of the specified task parameter.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] valueMaxLength The maximum number of elements to copy to the valueOut function argument.
/// 	This must not be greater than the length of the valueOut array.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetTaskStringValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, char* valueOut, int32_t valueMaxLength);

/// @brief Gets the numeric value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to get the task parameter from.
/// @param[In] taskIndex The task to get the parameter from.
/// @param[In] parameterId The task parameter to get the value of.
/// @param[Out] valueOut The numeric value of the specified task parameter. Only use this if the function call was successful.
/// @return Returns true if the function successfully got the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_GetTaskValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, double* valueOut);

/// @brief Sets the string value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the task parameter on.
/// @param[In] taskIndex The task to set the parameter on.
/// @param[In] parameterId The task parameter to set the value of.
/// @param[In] value The null-terminated string value to set the specified task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetTaskStringValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, const char* value);

/// @brief Sets the numeric value of a configured task parameter in the Automation1ConfiguredParameters handle.
/// @param[In] configuredParameters The collection of configured parameters to set the task parameter on.
/// @param[In] taskIndex The task to set the parameter on.
/// @param[In] parameterId The task parameter to set the value of.
/// @param[In] value The numeric value to set the specified task parameter to.
/// @return Returns true if the function successfully set the parameter value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredParameters_SetTaskValue(Automation1ConfiguredParameters configuredParameters, int32_t taskIndex, Automation1TaskParameterId parameterId, double value);

/// @brief Creates a new Automation1CalibrationFile handle.
///		Make sure to call Automation1_CalibrationFile_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] calibrationFileOut The created Automation1CalibrationFile handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1CalibrationFile handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_Create(Automation1CalibrationFile* calibrationFileOut);

/// @brief Destroys the Automation1CalibrationFile handle.
/// @param[In] calibrationFile The Automation1CalibrationFile handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_Destroy(Automation1CalibrationFile calibrationFile);

/// @brief Gets the content of a calibration file as an array of bytes.
/// @param[In] calibrationFile The calibration file to get the content from.
/// @param[Out] calibrationFileContentOut The content of the calibration file as an array of bytes.
/// @param[Out] calibrationFileContentLengthOut The length of the calibrationFileContentOut array.
///		This argument will be set to the exact length if the calibrationFileContentOut argument is null.
///		If the calibrationFileContentOut argument is not null, this will be set to the number of bytes that was actually copied into calibrationFileContentOut.
/// @return Returns true if the content was successfully copied to the specified array otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_GetContent(Automation1CalibrationFile calibrationFile, uint8_t* calibrationFileContentOut, int32_t* calibrationFileContentLengthOut);

/// @brief Sets the content of a calibration file from an array of bytes.
/// @param[In] calibrationFile The calibration file to set the content of.
/// @param[In] calibrationFileContent The array of bytes to set as the content of the calibration file.
/// @param[In] calibrationFileContentLength The length of the calibrationFileContent array.
/// @return Returns true if the calibration file's content was successfully set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_CalibrationFile_SetContent(Automation1CalibrationFile calibrationFile, uint8_t* calibrationFileContent, int32_t calibrationFileContentLength);

/// @brief Creates a new Automation1ConfiguredProgramAutomation handle.
///		Make sure to call Automation1_ConfiguredProgramAutomation_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] configuredProgramAutomationOut The created Automation1ConfiguredProgramAutomation handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1ConfiguredProgramAutomation handle was created successfully otherwise false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_Create(Automation1ConfiguredProgramAutomation* configuredProgramAutomationOut);

/// @brief Destroys the Automation1ConfiguredProgramAutomation handle.
/// @param[In] configuredProgramAutomation The Automation1ConfiguredProgramAutomation handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_Destroy(Automation1ConfiguredProgramAutomation configuredProgramAutomation);

/// @brief Adds a compiled AeroScript program to automatically load or run on the specified task whenever the controller starts.
///		Whenever the controller starts, the specified compiled AeroScript program will automatically load or run on the specified task.
///		Only one compiled AeroScript program can be configured to automatically load or run on each task. This function will fail if a compiled
///		AeroScript program is already configured to automatically load or run on the specificied task. To change the compiled AeroScript program that is
///		configured to automatically load or run on a task, first call Automation1_ConfiguredProgramAutomation_RemoveCompiledProgram().
/// @param[In] configuredProgramAutomation The configuration in which to add a compiled AeroScript program to automatically load or run.
/// @param[In] taskIndex The task that the compiled AeroScript program should automatically load or run on.
/// @param[In] shouldRun Whether the compiled AeroScript program should automatically run on the specified task whenever the controller starts.
///		If this argument is set to true, the program will automatically run whenever the controller starts, otherwise the program will only be loaded
///		whenever the controller starts.
/// @param[In] controllerFileName The compiled AeroScript program to automatically load or run whenever the controller starts.
/// @return Returns true if the compiled AeroScript program was successfully added, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddCompiledProgram(Automation1ConfiguredProgramAutomation configuredProgramAutomation, int32_t taskIndex, bool shouldRun, const char* controllerFileName);

/// @brief Removes a compiled AeroScript program from being automatically loaded or run on the specified task whenever the controller starts.
/// @param[In] configuredProgramAutomation The configuration from which to remove a compiled AeroScript program from being automatically loaded or run.
/// @param[In] taskIndex The task from which to remove the compiled AeroScript program from being automatically loaded or run on.
/// @return Returns true if the compiled AeroScript program was successfully removed, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveCompiledProgram(Automation1ConfiguredProgramAutomation configuredProgramAutomation, int32_t taskIndex);

/// @brief Gets the controller file names of all compiled AeroScript programs that are configured to load or run.
///		Since the maximum number of tasks on any Automation1 controller is 32, and only one compiled AeroScript program can be configured to a task at a time, this function will
///		return arrays of length 32.
/// @param[In] configuredProgramAutomation The configuration from which to get the compiled AeroScript programs that are configured to be automatically loaded or run.
/// @param[Out] shouldRunOut An array of length 32 that indicates whether each compiled AeroScript program should automatically run on the corresponding task.
/// @param[Out] controllerFileNamesOut The array to store the controller file names of compiled AeroScript programs that are configured to automatically load or run.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is 32, one corresponding to each task.
///		Set this argument to null to get the exact values for the maxControllerFileNameLengthOut argument.
/// @param[Out] maxControllerFileNameLengthOut The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the compiled AeroScript program was successfully retrieved or no compiled AeroScript program was configured, otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetCompiledPrograms(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool* shouldRunOut, char* controllerFileNamesOut, int32_t* maxControllerFileNameLengthOut);

/// @brief Adds an AeroScript source file to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to add the AeroScript source file to.
/// @param[In] controllerFileName The null-terminated name of the AeroScript source file to automatically include.
/// @return Returns true if the AeroScript source file was successfully added, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddProgramSourceFile(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Removes an AeroScript source file that is configured to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to remove the AeroScript source file from.
/// @param[In] controllerFileName The null-terminated name of the AeroScript source file to remove.
/// @return Returns true if the AeroScript source file was successfully removed, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveProgramSourceFile(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Gets the list of AeroScript source file that are configured to be automatically included.
/// @param[In] configuredProgramAutomation The configuration to get the AeroScript source files from.
/// @param controllerFileNamesOut[Out] The array to store the controller file names of AeroScript source files that are configured to be automatically included.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is based on the controllerFileNamesLengthOut argument.
///		Set this argument to null to get the exact values for the controllerFileNamesLengthOut and maxControllerFileNameLengthOut arguments.
/// @param controllerFileNamesLengthOut[Out] The length of the controllerFileNamesOut argument.
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		If controllerFileNamesOut is not null, this will be set to the number of controller file names that were actually copied into controllerFileNamesOut.
/// @param maxControllerFileNameLengthOut[Out] The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the names of the AeroScript source files configured to be automatically included were succesfully retrieved, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetProgramSourceFiles(Automation1ConfiguredProgramAutomation configuredProgramAutomation, char* controllerFileNamesOut, int32_t* controllerFileNamesLengthOut, int32_t* maxControllerFileNameLengthOut);

/// @brief Adds a compiled AeroScript library to be automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to add the compiled AeroScript library to.
/// @param[In] shouldAutoImport Whether the compiled AeroScript library should be automatically imported.
///		If this argument is set to true, AeroScript programs do not need to import the library to make use of any items it exposes.
/// @param[In] controllerFileName The null-terminated name of the compiled AeroScript library to load.
/// @return Returns true if the compiled AeroScript library was successfully added, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_AddCompiledLibrary(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool shouldAutoImport, const char* controllerFileName);

/// @brief Removes a compiled AeroScript library from being automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to remove the compiled AeroScript library from.
/// @param[In] controllerFileName The null-terminated name of the compiled AeroScript library to remove.
/// @return Returns true if the compiled AeroScript library was successfully removed, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_RemoveCompiledLibrary(Automation1ConfiguredProgramAutomation configuredProgramAutomation, const char* controllerFileName);

/// @brief Gets the list of compiled AeroScript libraries that are configured to be automatically loaded.
/// @param[In] configuredProgramAutomation The configuration to get the compiled AeroScript libraries from.
/// @param[Out] shouldAutoImportOut An array that indicates whether each compiled AeroScript library should be automatically imported.
///		The length of this array will be the same as the number of controller file names copied into the controllerFileNamesOut argument.
///		This argument must have memory preallocated before passing it to this function. The length of this array must be greater than or
///		equal to the controllerFileNamesLengthOut argument.
/// @param[Out] controllerFileNamesOut The array to store the controller file names of compiled AeroScript libraries that are configured to be loaded.
///		The controller file names will be null-terminated and will be stored in succession based on the maxControllerFileNameLengthOut argument. 
///		The number of controller file names that will be copied is based on the controllerFileNamesLengthOut argument.
///		Set this argument to null to get the exact values for the controllerFileNamesLengthOut and maxControllerFileNameLengthOut arguments.
/// @param[Out] controllerFileNamesLengthOut The length of the controllerFileNamesOut argument.
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		If controllerFileNamesOut is not null, this will be set to the number of controller file names that were actually copied into controllerFileNamesOut.
/// @param[Out] maxControllerFileNameLengthOut The maximum length of the controller file name (including the null-terminator).
///		This argument will be set to the exact length if the controllerFileNamesOut argument is null.
///		To avoid calling this function twice to get the exact size, set this parameter to 1000 characters.
///		If controllerFileNamesOut is not null, this will be set to the actual max controller file name length that was used to copy file names into controllerFileNamesOut.
/// @return Returns true if the names of the compiled AeroScript libraries configured to be loaded were succesfully retrieved, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredProgramAutomation_GetCompiledLibraries(Automation1ConfiguredProgramAutomation configuredProgramAutomation, bool* shouldAutoImportOut, char* controllerFileNamesOut, int32_t* controllerFileNamesLengthOut, int32_t* maxControllerFileNameLengthOut);

/// @brief Creates a new Automation1ConfiguredIndustrialEthernet handle.
///		Make sure to call Automation1_ConfiguredIndustrialEthernet_Destroy() to avoid leaking memory when you are done using this handle.
/// @param[Out] configuredIndustrialEthernetOut The created Automation1ConfiguredIndustrialEthernet handle. Only use this if the function call was successful.
/// @return Returns true if the Automation1ConfiguredIndustrialEthernet handle was created successfully otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_Create(Automation1ConfiguredIndustrialEthernet* configuredIndustrialEthernetOut);

/// @brief Destroys the Automation1ConfiguredIndustrialEthernet handle.
/// @param[In] configuredIndustrialEthernet The Automation1ConfiguredIndustrialEthernet handle to destroy.
/// @return Returns true if the handle was successfully destroyed otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_Destroy(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet);

/// @brief Gets the configured Industrial Ethernet from an Automation1 controller.
///		If Industrial Ethernet has not been configured, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call Automation1_Configuration_IsConfiguredIndustrialEthernetSet() before calling this function.
/// @param[In] controller The Automation1 controller from which to get the configured Industrial Ethernet.
/// @param[In] configuredIndustrialEthernet The handle to store the controller's configured Industrial Ethernet connections and mappings in.
///		You must first create the handle using Automation1_ConfiguredIndustrialEthernet_Create() before passing it to this function.
///		This function will clear all other configured Industrial Ethernet connections and mappings that are set in this handle and replace them with the
///		configured Industrial Ethernet connections and mappings from the Automation1Controller.
/// @return Returns true if the configured Industrial Ethernet from the Automation1 controller was retrieved successfully otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_GetConfiguredIndustrialEthernet(Automation1Controller controller, Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet);

/// @brief Sets the configured Industrial Ethernet on an Automation1 controller.
///		After calling this function to set the configured Industrial Ethernet on your controller, you must reset your controller to apply the changes.
/// @param[In] controller The Automation1 controller to set the configured Industrial Ethernet on.
/// @param[In] configuredIndustrialEthernet The configured Industrial Ethernet to set on the Automation1 controller.
///		Use the Automation1_ConfiguredIndustrialEthernet_Create() function to obtain an Automation1ConfiguredIndustrialEthernet handle.
/// @return Returns true if the configured Industrial Ethernet was successfully set on the Automation1 controller otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_SetConfiguredIndustrialEthernet(Automation1Controller controller, Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet);

/// @brief Removes the configured Industrial Ethernet from an Automation1 controller.
/// @param[In] controller The Automation1 controller from which to remove the configured Industrial Ethernet.
/// @return Returns true if the configured Industrial Ethernet was successfully removed otherwise false.
AUTOMATION1_CAPI bool Automation1_Configuration_RemoveConfiguredIndustrialEthernet(Automation1Controller controller);

/// @brief Gets whether configured Industrial Ethernet is set on an Automation1 controller.
///		If configured Industrial Ethernet has not been set, then trying to get it from an Automation1 controller will fail. Thus, you should typically
///		call this function before calling Automation1_Configuration_GetConfiguredIndustrialEthernet().
/// @param[In] controller The Automation1 controller to get whether configured Industrial Ethernet is set on.
/// @param[Out] isConfigurationSetOut Whether configured Industrial Ethernet is set on the Automation1 controller.
///		Only use this value if the function call was successful.
/// @return Returns true if this function successfully got whether configured Industrial Ethernet is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Configuration_IsConfiguredIndustrialEthernetSet(Automation1Controller controller, bool* isConfiguredIndustrialEthernetOut);

/// @brief Sets the Modbus Server connection.
///		Only one Modbus Server can be configured at a time. If you call this function again on the same Industrial Ethernet configuration,
///		it will replace the Modbus Server configured previously.
///		To add a Modbus Register to the Modbus Server, call the Automation1_ConfiguredIndustrialEthernet_AddRegisterToModbusServer() function after this call succeeds.
/// @param[In] configuredIndustrialEthernet The configuration in which to set the Modbus Server.
/// @param[In] name The null-terminated name of the Modbus Server. This name is informational only and is used to differentiate between Industrial Ethernet connections within Automation1.
/// @param[In] id The identifier for the Modbus Server.
/// @return Returns true if the Modbus Server was set successfully otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_SetModbusServer(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* name, int32_t id);

/// @brief Adds a Modbus Register to the configured Modbus Server. A Modbus Register maps a memory region of the Modbus Server.
///		In order for this function to succeed, the Modbus Server must already be configured. To configure the Modbus Server,
///		call the Automation1_ConfiguredIndustrialEthernet_SetModbusServer() function.
///		You can call this function repeatedly to add multiple Modbus Registers to the configured Modbus Server.
/// @param[In] configuredIndustrialEthernet The configuration in which to add the register.
/// @param[In] registerName The null-terminated name of the register to add. This name will be automatically converted into an AeroScript variable by the controller that can be interacted with via programs or libraries.
/// @param[In] type The type of the register to add. Automation1ModbusRegisterType_OutputWordsStatus and Automation1ModbusRegisterType_OutputBitsStatus are not valid for Modbus Servers.
/// @param[In] bitAddress The bit address which is the bit offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress. Non-bit data types must be 8-bit byte aligned.
/// @param[In] byteAddress The byte address which is the byte offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[In] count The count to set for the register. This determines how many variables this register can hold.
/// @param[In] comment The null-terminated comment to set for the register. This can be used to provide some information about the register.
/// @param[In] dataType The data type of the register to add.
/// @return Returns true if the register was successfully added to the configured Modbus Server otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_AddRegisterToModbusServer(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1ModbusRegisterType type, int32_t bitAddress, int32_t byteAddress, int32_t count, const char* comment, Automation1ModbusRegisterDataType dataType);

/// @brief Gets whether or not the Modbus Server is set.
///		If the Modbus Server is not set, getting the Modbus Server will fail. Thus, you should typically call this function before
///		calling Automation1_ConfiguredIndustrialEthernet_GetModbusServer().
/// @param[In] configuredIndustrialEthernet The configuration from which to get whether or not the Modbus Server is set.
/// @param[Out] isModbusServerSetOut Whether the Modbus Server is set on the controller.
/// @return Returns true if this function successfully got whether the Modbus Server is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_IsModbusServerSet(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, bool* isModbusServerSetOut);

/// @brief Gets the configured Modbus Server connection.
///		If the Modbus Server is not set, getting the Modbus Server will fail. Thus, you should typically call
///		Automation1_ConfiguredIndustrialEthernet_IsModbusServerSet() before calling this function.
///		To get the registers of the configured Modbus Server, you must call the Automation1_ConfiguredIndustrialEthernet_GetModbusServerRegister()
///		function after this one multiple times based on the value of the numberOfRegistersOut argument that this function returns.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Server.
/// @param[Out] nameOut The null-terminated name of the Modbus Server. This name is informational only and is used to differentiate between Industrial Ethernet connections within Automation1.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] nameMaxLength The maximum number of elements to copy to the nameOut function argument.
///		This must not be greater than the length of the nameOut array.
/// @param[Out] idOut The identifier of the Modbus Server.
/// @param[Out] numberOfRegistersOut The number of registers that the configured Modbus server has. Modbus Registers map to different memory regions on the configured Modbus Server.
///		Use the value returned in this argument to determine how many times to call the Automation1_ConfiguredIndustrialEthernet_GetModbusServerRegister() function
///		to actually get each register of the configured Modbus Server.
/// @return Returns true if the Modbus Server was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusServer(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, char* nameOut, int32_t nameMaxLength, int32_t* idOut, int32_t* numberOfRegistersOut);

/// @brief Gets a Modbus Register from the configured Modbus Server. A Modbus Register maps a memory region of the Modbus Server.
///		To use this function, first call the Automation1_ConfiguredIndustrialEthernet_GetModbusServer() function to determine the number of Modbus Registers
///		the configured Modbus Server has. Then call this function passing in the index of the register you want to retrieve for the registerIndex argument.
///		To get all registers of the Modbus Server, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for the registerIndex argument.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Server register.
/// @param[In] registerIndex The index of the register to get.
///		To determine what indices are valid, first call the Automation1_ConfiguredIndustrialEthernet_GetModbusServer() function to get the number
///		of Modbus Registers that the configured Modbus Server has.
///		To get all registers of the Modbus Server, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for this argument.
/// @param[Out] registerNameOut The null-terminated name of the register. This name is treated as an AeroScript variable by the controller that can be interacted with via programs or libraries.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] registerNameMaxLength The maximum number of elements to copy to the registerNameOut function argument.
///		This must not be greater than the length of the registerNameOut array.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusServerRegister(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, int32_t registerIndex, char* registerNameOut, int32_t registerNameMaxLength, Automation1ModbusRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1ModbusRegisterDataType* dataTypeOut);

/// @brief Gets the Modbus Register from the configured Modbus Server with the specified name. A Modbus Register maps a memory region of the Modbus Server.
///		If the Modbus Server does not have a register with the specified name, this function will fail.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Server register.
/// @param[In] registerName The name of the register to get.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusServerRegisterByName(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1ModbusRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1ModbusRegisterDataType* dataTypeOut);

/// @brief Adds a Modbus Client connection.
///		Depending on your license, multiple Modbus Clients can be added to the configuration by calling this function repeatedly.
///		To add a Modbus Register to a Modbus Client, call the Automation1_ConfiguredIndustrialEthernet_AddRegisterToModbusClient()
///		function after this call succeeds.
/// @param[In] configuredIndustrialEthernet The configuration in which to add the Modbus Client.
/// @param[In] name The null-terminated name of the Modbus Client to add. This name is informational only and is used to differentiate between Industrial Ethernet connections within Automation1.
/// @param[In] serverId The identifier of the server to which this Modbus Client connects.
/// @param[In] serverIpAddress The null-terminated IP address of the server to which this Modbus Client connects.
/// @param[In] serverPort The port of the server to which this Modbus Client connects.
/// @return Returns true if the Modbus Client was successfully added otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_AddModbusClient(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* name, int32_t serverId, const char* serverIpAddress, int32_t serverPort);

/// @brief Adds a Modbus Register to the specified configured Modbus Client. A Modbus Register maps a memory region of a Modbus Client.
///		In order for this function to succeed, the specified Modbus Client must already be configured. To configure a Modbus Client,
///		call the Automation1_ConfiguredIndustrialEthernet_AddModbusClient() function.
///		You can call this function repeatedly to add multiple Modbus Registers to the configured Modbus Client.
/// @param[In] configuredIndustrialEthernet The configuration in which to add the register.
/// @param[In] registerName The null-terminated name of the register to add. This name will be automatically converted into an AeroScript variable by the controller that can be interacted with via programs or libraries.
/// @param[In] type The type of the register to add.
/// @param[In] bitAddress The bit address which is the bit offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress. Non-bit data types must be 8-bit byte aligned.
/// @param[In] byteAddress The byte address which is the byte offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[In] count The count to set for the register. This determines how many variables this register can hold.
/// @param[In] comment The null-terminated comment to set for the register. This can be used to provide some additional information about the register.
/// @param[In] dataType The data type of the register to add.
/// @return Returns true if the register was successfully added to the Modbus Client otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_AddRegisterToModbusClient(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* modbusClientName, const char* registerName, Automation1ModbusRegisterType type, int32_t bitAddress, int32_t byteAddress, int32_t count, const char* comment, Automation1ModbusRegisterDataType dataType);

/// @brief Gets the number of Modbus Clients that are configured.
///		Use the value retrieved in the numberOfModbusClientsOut argument to determine the number of times to call the
///		Automation1_ConfiguredIndustrialEthernet_GetModbusClient() function to get each configured Modbus Client.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the number of Modbus Clients.
/// @param[Out] numberOfModbusClientsOut[Out] The number of Modbus Clients that are configured.
///		Use the value retrieved in this argument to determine the number of times to call the Automation1_ConfiguredIndustrialEthernet_GetModbusClient()
///		function to get each configured Modbus Client.
/// @return Returns true if the number of Modbus Client was successfully retrieved, otherwise returns false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetNumberOfModbusClients(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, int32_t* numberOfModbusClientsOut);

/// @brief Gets the Modbus Client connection based on the given index.
///		To use this function, first call the Automation1_ConfiguredIndustrialEthernet_GetNumberOfModbusClients() function to determine what indicies are valid.
///		Then call this function passing in the index of the ModbusClient you want to retrieve for the modbusClientIndex argument.
///		To get all ModbusClients call this function repeatedly passing in 0 ... numberOfModbusClients - 1 for the modbusClientIndex argument.
///		To get the registers of this Modbus Client, you must call the Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegister()
///		function passing in the name of this Modbus Client multiple times based on the value of the numberOfRegistersOut argument that this function returns.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Client.
/// @param[In] modbusClientIndex The index of the Modbus Client to get.
/// @param[Out] nameOut The null-terminated name of the Modbus Client. This name is informational only and is used to differentiate between Industrial Ethernet connections within Automation1.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] nameMaxLength The maximum number of elements to copy to the nameOut function argument.
///		This must not be greater than the length of the nameOut array.
/// @param[Out] serverIdOut The identifier of the server to which this Modbus Client connects.
/// @param[Out] serverIpAddressOut The null-terminated IP address of the server to which this Modbus Client connects.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] serverIpAddressMaxLength The maximum number of elements to copy to the serverIpAddressOut function argument.
///		This must not be greater than the length of the serverIpAddressOut array.
/// @param[Out] serverPortOut The port of the server to which this Modbus Client connects.
/// @param[Out] numberOfRegistersOut The number of registers that this Modbus Client has. Modbus Registers map to different memory regions on the configured Modbus Client.
///		Use the value returned in this argument to determine how many times to call the Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegister()
///		function to actually get each register of this Modbus Client.
/// @return Returns true if the Modbus Client was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusClient(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, int32_t modbusClientIndex, char* nameOut, int32_t nameMaxLength, int32_t* serverIdOut, char* serverIpAddressOut, int32_t serverIpAddressMaxLength, int32_t* serverPortOut, int32_t* numberOfRegistersOut);

/// @brief Gets the Modbus Client connection with the given name.
///		To get the registers of this Modbus Client, you must call the Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegister()
///		function passing in the name of this Modbus Client multiple times based on the value of the numberOfRegistersOut argument that this function returns.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Client.
/// @param[In] name The null-terminated name of the Modbus Client to get.
/// @param[Out] serverIdOut The identifier of the server to which this Modbus Client connects.
/// @param[Out] serverIpAddressOut The null-terminated IP address of the server to which this Modbus Client connects.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] serverIpAddressMaxLength The maximum number of elements to copy to the serverIpAddressOut function argument.
///		This must not be greater than the length of the serverIpAddressOut array.
/// @param[Out] serverPortOut The port of the server to which this Modbus Client connects.
/// @param[Out] numberOfRegistersOut The number of registers that this Modbus Client has. Modbus Registers map to different memory regions on the configured Modbus Client.
///		Use the value returned in this argument to determine how many times to call the Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegister()
///		function to actually get each register of this Modbus Client.
/// @return Returns true if the Modbus Client was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusClientByName(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* name, int32_t* serverIdOut, char* serverIpAddressOut, int32_t serverIpAddressMaxLength, int32_t* serverPortOut, int32_t* numberOfRegistersOut);

/// @brief Gets a Modbus Register from the specified Modbus Client. A Modbus Register maps a memory region of a Modbus Client.
///		To use this function, first call the Automation1_ConfiguredIndustrialEthernet_GetModbusClient() function to determine the number of Modbus Registers the configured
///		the Modbus Client has. Then call this function passing in the index of the register you want to retrieve for the registerIndex argument.
///		To get all registers of the Modbus Client call this function repeatedly passing in 0 ... numberOfRegisters - 1 for the registerIndex argument.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Client register.
/// @param[In] modbusClientName The null-terminated name of the Modbus Client whose register to get.
/// @param[In] registerIndex The index of the register to get.
///		To determine what indices are valid, first call the Automation1_ConfiguredIndustrialEthernet_GetModbusClient() function to get the number
///		of Modbus Registers the Modbus Client has.
///		To get all registers of the Modbus Client call this function repeatedly passing in 0 ... numberOfRegisters - 1 for this argument.
/// @param[Out] registerNameOut The null-terminated name of the register. This name is treated as an AeroScript variable by the controller that can be interacted with via programs or libraries.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] registerNameMaxLength The maximum number of elements to copy to the registerNameOut function argument.
///		This must not be greater than the length of the registerNameOut array.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegister(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* modbusClientName, int32_t registerIndex, char* registerNameOut, int32_t registerNameMaxLength, Automation1ModbusRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1ModbusRegisterDataType* dataTypeOut);

/// @brief Gets the Modbus Register from the specified Modbus Client with the specified register name. A Modbus Register maps a memory region of a Modbus Client.
///		If the specified Modbus Client does not have a register with the specified register name, this function will fail.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the Modbus Client register.
/// @param[In] modbusClientName The null-terminated name of the Modbus Client whose register to get.
/// @param[In] registerName The name of the register to get. This name is treated as an AeroScript variable by the controller that can be interacted with via programs or libraries.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetModbusClientRegisterByName(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* modbusClientName, const char* registerName, Automation1ModbusRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1ModbusRegisterDataType* dataTypeOut);

/// @brief Sets the EtherCAT connection.
///		Only one EtherCAT connection can be configured at a time. If you call this function again on the same Industrial Ethernet configuration,
///		it will replace the EtherCAT connection configured previously.
///		To add an EtherCAT register to the EtherCAT connection, call the Automation1_ConfiguredIndustrialEthernet_AddRegisterToEthercat() function after this call succeeds.
/// @param[In] configuredIndustrialEthernet The configuration in which to set the EtherCAT connection.
/// @param[In] name The null-terminated name of the EtherCAT connection.
/// @return Returns true if the EtherCAT connection was set successfully otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_SetEthercat(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* name);

/// @brief Adds an EtherCAT register to the configured EtherCAT connection. An EtherCAT Register maps a memory region of the EtherCAT.
///		In order for this function to succeed, the EtherCAT connection must already be configured. To configure the EtherCAT connection,
///		call the Automation1_ConfiguredIndustrialEthernet_SetEthercat() function.
///		You can call this function repeatedly to add multiple registers to the configured EtherCAT connection.
/// @param[In] configuredIndustrialEthernet The configuration in which to add the register.
/// @param[In] registerName The null-terminated name of the register to add. This name will be automatically converted into an AeroScript variable by the controller that can be interacted with via programs or libraries.
/// @param[In] type The type of the register to add which represents its access level to the EtherCAT PDO space.
/// @param[In] bitAddress The bit address which is the bit offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress. Non-bit data types must be 8-bit byte aligned.
/// @param[In] byteAddress The byte address which is the byte offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[In] count The count to set for the register. This determines how many variables this register can hold.
/// @param[In] comment The null-terminated comment to set for the register. This can be used to provide some additional information about the register.
/// @param[In] dataType The data type of the register to add.
/// @return Returns true if the register was successfully added to the configured EtherCAT connection otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_AddRegisterToEthercat(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1EthercatRegisterType type, int32_t bitAddress, int32_t byteAddress, int32_t count, const char* comment, Automation1EthercatRegisterDataType dataType);

/// @brief Gets whether or not the EtherCAT connection is set.
///		If the EtherCAT connection is not set, getting EtherCAT will fail. Thus, you should typically call this function before
///		calling Automation1_ConfiguredIndustrialEthernet_GetEthercat().
/// @param[In] configuredIndustrialEthernet The configuration from which to get whether or not the EtherCAT connection is set.
/// @param[Out] isEthercatSetOut Whether the EtherCAT connection is set on the controller.
/// @return Returns true if this function successfully got whether the EtherCAT connection is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_IsEthercatSet(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, bool* isEthercatSetOut);

/// @brief Gets the configured EtherCAT connection.
///		If the EtherCAT connection is not set, getting EtherCAT will fail. Thus, you should typically call
///		Automation1_ConfiguredIndustrialEthernet_IsEthercatSet() before calling this function.
///		To get the registers of the configured EtherCAT connection, you must call the Automation1_ConfiguredIndustrialEthernet_GetEthercatRegister()
///		function after this one multiple times based on the value of the numberOfRegistersOut argument that this function returns.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherCAT connection.
/// @param[Out] nameOut The null-terminated name of the EtherCAT connection.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] nameMaxLength The maximum number of elements to copy to the nameOut function argument.
///		This must not be greater than the length of the nameOut array.
/// @param[Out] numberOfRegistersOut The number of registers that the configured EtherCAT connection has. An EtherCAT register maps a memory region of the EtherCAT.
///		Use the value returned in this argument to determine how many times to call the Automation1_ConfiguredIndustrialEthernet_GetEthercatRegister() function
///		to actually get each register of the configured EtherCAT connection.
/// @return Returns true if the EtherCAT connection was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEthercat(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, char* nameOut, int32_t nameMaxLength, int32_t* numberOfRegistersOut);

/// @brief Gets an EtherCAT register from the configured EtherCAT connection. An EtherCAT Register maps a memory region of the EtherCAT.
///		To use this function, first call the Automation1_ConfiguredIndustrialEthernet_GetEthercat() function to determine the number of registers the configured
///		EtherCAT connection has. Then call this function passing in the index of the register you want to retrieve for the registerIndex argument.
///		To get all registers of the EtherCAT connection, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for the registerIndex argument.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherCAT register.
/// @param[In] registerIndex The index of the register to get.
///		To determine what indices are valid, first call the Automation1_ConfiguredIndustrialEthernet_GetEthercat() function to get the number
///		of registers the configured EtherCAT connection has.
///		To get all registers of the EtherCAT connection, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for this argument.
/// @param[Out] registerNameOut The null-terminated name of the register. This name is treated as an AeroScript variable by the controller that can be interacted with via programs or libraries.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] registerNameMaxLength The maximum number of elements to copy to the registerNameOut function argument.
///		This must not be greater than the length of the registerNameOut array.
/// @param[Out] typeOut The type of the register which represents its access level to the EtherCAT PDO space.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEthercatRegister(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, int32_t registerIndex, char* registerNameOut, int32_t registerNameMaxLength, Automation1EthercatRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1EthercatRegisterDataType* dataTypeOut);

/// @brief Gets the EtherCAT register from the configured EtherCAT connection with the specified name.
///		If a register with the specified name does not exist, this function will fail.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherCAT register.
/// @param[In] registerName The name of the register to get.
/// @param[Out] typeOut The type of the register which represents its access level to the EtherCAT PDO space.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEthercatRegisterByName(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1EthercatRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1EthercatRegisterDataType* dataTypeOut);

/// @brief Sets the EtherNet/IP connection.
///		Only one EtherNet/IP connection can be configured at a time. If you call this function again on the same Industrial Ethernet configuration,
///		it will replace the EtherNet/IP connection configured previously.
///		To add an EtherNet/IP register to the EtherNet/IP connection, call the Automation1_ConfiguredIndustrialEthernet_AddRegisterToEtherNetIp() function after this call succeeds.
/// @param[In] configuredIndustrialEthernet The configuration in which to set the EtherNet/IP connection.
/// @param[In] name The null-terminated name of the EtherNet/IP connection.
/// @return Returns true if the EtherNet/IP connection was set successfully otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_SetEtherNetIp(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* name);

/// @brief Adds an EtherNet/IP register to the configured EtherNet/IP connection. An EtherNet/IP Register maps a memory region of the EtherNet/IP connection.
///		In order for this function to succeed, the EtherNet/IP connection must already be configured. To configure the EtherNet/IP connection,
///		call the Automation1_ConfiguredIndustrialEthernet_SetEtherNetIp() function.
///		You can call this function repeatedly to add multiple registers to the configured EtherNet/IP connection.
/// @param[In] configuredIndustrialEthernet The configuration in which to add the register.
/// @param[In] registerName The null-terminated name of the register to add. This name will be automatically converted into an AeroScript variable by the controller that can be interacted with via programs or libraries.
/// @param[In] type The type of the register to add.
/// @param[In] bitAddress The bit address which is the bit offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress. Non-bit data types must be 8-bit byte aligned.
/// @param[In] byteAddress The byte address which is the byte offset to set for the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[In] count The count to set for the register. This determines how many variables this register can hold.
/// @param[In] comment The null-terminated comment to set for the register. This can be used to provide some additional information about the register.
/// @param[In] dataType The data type of the register to add.
/// @return Returns true if the register was successfully added to the configured EtherNet/IP connection otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_AddRegisterToEtherNetIp(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1EtherNetIpRegisterType type, int32_t bitAddress, int32_t byteAddress, int32_t count, const char* comment, Automation1EtherNetIpRegisterDataType dataType);

/// @brief Gets whether or not the EtherNet/IP connection is set.
///		If the EtherNet/IP connection is not set, getting the EtherNet/IP connection will fail. Thus, you should typically call this function before
///		calling Automation1_ConfiguredIndustrialEthernet_GetEtherNetIp().
/// @param[In] configuredIndustrialEthernet The configuration from which to get whether or not the EtherNet/IP connection is set.
/// @param[Out] isEtherNetIpSetOut Whether the EtherNet/IP connection is set on the controller.
/// @return Returns true if this function successfully got whether the EtherNet/IP connection is set otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_IsEtherNetIpSet(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, bool* isEtherNetIpSetOut);

/// @brief Gets the configured EtherNet/IP connection.
///		If the EtherNet/IP connection is not set, getting the EtherNet/IP connection will fail. Thus, you should typically call
///		Automation1_ConfiguredIndustrialEthernet_IsEtherNetIpSet() before calling this function.
///		To get the registers of the configured EtherNet/IP connection, you must call the Automation1_ConfiguredIndustrialEthernet_GetEtherNetIpRegister()
///		function after this one multiple times based on the value of the numberOfRegistersOut argument that this function returns.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherNet/IP connection.
/// @param[Out] nameOut The null-terminated name of the EtherNet/IP connection.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] nameMaxLength The maximum number of elements to copy to the nameOut function argument.
///		This must not be greater than the length of the nameOut array.
/// @param[Out] numberOfRegistersOut The number of registers that the configured EtherNet/IP connection has. An EtherNet/IP register maps a memory region of the EtherNet/IP connection.
///		Use the value returned in this argument to determine how many times to call the Automation1_ConfiguredIndustrialEthernet_GetEtherNetIpRegister() function
///		to actually get each register of the configured EtherNet/IP connection.
/// @return Returns true if the EtherNet/IP connection was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEtherNetIp(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, char* nameOut, int32_t nameMaxLength, int32_t* numberOfRegistersOut);

/// @brief Gets an EtherNet/IP register from the configured EtherNet/IP connection. An EtherNet/IP Register maps a memory region of the EtherNet/IP connection.
///		To use this function, first call the Automation1_ConfiguredIndustrialEthernet_GetEtherNetIp() function to determine the number of registers the configured
///		EtherNet/IP connection has. Then call this function passing in the index of the register you want to retrieve for the registerIndex argument.
///		To get all registers of the EtherNet/IP connection, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for the registerIndex argument.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherNet/IP register.
/// @param[In] registerIndex The index of the register to get.
///		To determine what indices are valid, first call the Automation1_ConfiguredIndustrialEthernet_GetEtherNetIp() function to get the number
///		of registers the configured EtherNet/IP connection has.
///		To get all registers of the EtherNet/IP connection, call this function repeatedly passing in 0 ... numberOfRegisters - 1 for this argument.
/// @param[Out] registerNameOut The null-terminated name of the register. This name is treated as an AeroScript variable by the controller that can be interacted with via programs or libraries.
///		Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] registerNameMaxLength The maximum number of elements to copy to the registerNameOut function argument.
///		This must not be greater than the length of the registerNameOut array.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEtherNetIpRegister(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, int32_t registerIndex, char* registerNameOut, int32_t registerNameMaxLength, Automation1EtherNetIpRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1EtherNetIpRegisterDataType* dataTypeOut);

/// @brief Gets the EtherNet/IP register from the configured EtherNet/IP connection with the specified name.
///		If a register with the specified name does not exist, this function will fail.
/// @param[In] configuredIndustrialEthernet The configuration from which to get the EtherNet/IP register.
/// @param[In] registerName The name of the register to get.
/// @param[Out] typeOut The type of the register.
/// @param[Out] bitAddressOut The bit address which is the bit offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] byteAddressOut The byte address which is the byte offset of the register. The final address is the sum of byteAddress * 8 + bitAddress.
/// @param[Out] countOut The count of the register which is the number of variables the register can have.
/// @param[Out] commentOut The null-terminated comment of the register which may contain some additional information about the register.
/// @param[Out] dataTypeOut The data type of the register.
/// @return Returns true if the register was successfully retrieved otherwise false.
///		See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_ConfiguredIndustrialEthernet_GetEtherNetIpRegisterByName(Automation1ConfiguredIndustrialEthernet configuredIndustrialEthernet, const char* registerName, Automation1EtherNetIpRegisterType* typeOut, int32_t* bitAddressOut, int32_t* byteAddressOut, int32_t* countOut, char* commentOut, int32_t commentMaxLength, Automation1EtherNetIpRegisterDataType* dataTypeOut);


#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1CONFIGURATION_H_INCLUDED
