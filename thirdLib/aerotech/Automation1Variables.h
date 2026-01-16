///
/// Copyright (c) Aerotech, Inc.
///

#ifndef AUTOMATION1VARIABLES_H_INCLUDED
#define AUTOMATION1VARIABLES_H_INCLUDED

#if defined(_MSC_VER)
	#if defined(AUTOMATION1_CAPI_EXPORT)
		#define AUTOMATION1_CAPI __declspec(dllexport)
	#else
		#define AUTOMATION1_CAPI __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#define AUTOMATION1_CAPI __attribute__((visibility ("default")))
#endif

#include <stdbool.h>
#include <stdint.h>
#include "Automation1Controller.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/// @brief Gets the values of a contiguous segment of integer controller global variables ($iglobal in AeroScript), starting at the specified global integer array index and with the specified number of variables to get.
///		The values are returned as AeroScript integer values (which are 64-bit integers).
/// 	These controller global variables are accessible from every task on the controller and from every API.
/// @param[In] controller The controller to get the variables from.
/// @param[In] startingGlobalIntegerIndex The global integer array index that starts the segment of global variables to get.
/// @param[Out] integerValuesOut The out array that will be populated with integer values that were retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] integerValuesOutMaxLength The maximum number of variables to get from the controller and to copy to the integerValuesOut function argument.
/// 	This must not be greater than the length of the integerValuesOut array.
/// @return Returns true if the function successfully got the variable values otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetGlobalIntegers(Automation1Controller controller, int32_t startingGlobalIntegerIndex, int64_t* integerValuesOut, int32_t integerValuesOutMaxLength);

/// @brief Sets the values of a contiguous segment of integer controller global variables ($iglobal in AeroScript), starting at the specified global integer array index and with the specified number of variables to set.
///		The values to set are AeroScript integer values (which are 64-bit integers).
/// 	These controller global variables are accessible from every task on the controller and from every API.
/// @param[In] controller The controller to set the variables on.
/// @param[In] startingGlobalIntegerIndex The global integer array index that starts the segment of global variables to set.
/// @param[In] integerValues The array of AeroScript integer values (which are 64-bit long integers) to set on the controller.
/// @param[In] integerValuesLength The length of the integerValues function argument.
/// @return Returns true if the function successfully set the variable values otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetGlobalIntegers(Automation1Controller controller, int32_t startingGlobalIntegerIndex, int64_t* integerValues, int32_t integerValuesLength);

/// @brief Gets the values of a contiguous segment of real controller global variables ($rglobal in AeroScript), starting at the specified global real array index and with the specified number of variables to get.
///		The values are returned as AeroScript real values (which are double precision floating point numbers).
/// 	These controller global variables are accessible from every task on the controller and from every API.
/// @param[In] controller The controller to get the variables from.
/// @param[In] startingGlobalRealIndex The global real array index that starts the segment of global variables to get.
/// @param[Out] realValuesOut The out array that will be populated with real values that were retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] realValuesOutMaxLength The maximum number of variables to get from the controller and to copy to the realValuesOut function argument.
/// 	This must not be greater than the length of the realValuesOut array.
/// @return Returns true if the function successfully got the variable values otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetGlobalReals(Automation1Controller controller, int32_t startingGlobalRealIndex, double* realValuesOut, int32_t realValuesOutMaxLength);

/// @brief Sets the values of a contiguous segment of real controller global variables ($rglobal in AeroScript), starting at the specified global real array index and with the specified number of variables to set.
///		The values to set are AeroScript real values (which are double precision floating point numbers).
/// 	These controller global variables are accessible from every task on the controller and from every API.
/// @param[In] controller The controller to set the variables on.
/// @param[In] startingGlobalRealIndex The global real array index that starts the segment of global variables to set.
/// @param[In] realValues The array of AeroScript real values (which are double precision floating point numbers) to set on the controller.
/// @param[In] realValuesLength The length of the realValues function argument.
/// @return Returns true if the function successfully set the variable values otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetGlobalReals(Automation1Controller controller, int32_t startingGlobalRealIndex, double* realValues, int32_t realValuesLength);

/// @brief Gets the value of a single string controller global variable ($sglobal in AeroScript), at the specified global string array index.
/// 	These controller global variables are accessible from every task on the controller and from every API.
///		Each string global variable has a capacity of 256 characters including the null terminator.
/// @param[In] controller The controller to get the variable from.
/// @param[In] startingGlobalStringIndex The global string array index to get the value of.
/// @param[Out] stringValueOut The null-terminated string value of the specified string controller global variable.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] stringValueMaxLength The maximum number of characters to copy to the stringValueOut function argument.
/// 	This must not be greater than the length of the stringValueOut array.
/// @return Returns true if the function successfully got the variable value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetGlobalString(Automation1Controller controller, int32_t startingGlobalStringIndex, char* stringValueOut, int32_t stringValueMaxLength);

/// @brief Sets the value of a single string controller global variable ($sglobal in AeroScript), at the specified global string array index.
/// 	These controller global variables are accessible from every task on the controller and from every API.
///		Each string global variable has a capacity of 256 characters including the null terminator.
/// @param[In] controller The controller to set the variables on.
/// @param[In] startingGlobalStringIndex The global string array index to set the value of.
/// @param[In] stringValue The null-terminated string value to set for the string controller global variable.
/// @return Returns true if the function successfully set the variable value otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetGlobalString(Automation1Controller controller, int32_t startingGlobalStringIndex, const char* stringValue);

/// @brief Gets the values of a contiguous segment of integer task variables ($itask in AeroScript), starting at the specified task integer array index and with the specified number of variables to get.
///		The values are returned as AeroScript integer values (which are 64-bit long integers).
///		These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
/// @param[In] controller The controller to get the task variables from.
/// @param[In] taskIndex The index of the task to get the integer task variables from.
/// @param[In] taskIntegerArrayStartingIndex The task integer array index that starts the segment of task variables to get.
/// @param[Out] integerValuesOut The out array that will be populated with integer values that were retrieved from the task.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] integerValuesOutMaxLength The maximum number of variables to get from the task and to copy to the integerValuesOut function argument.
/// 	This must not be greater than the length of the integerValuesOut array.
/// @return Returns true if the function successfully got the variable values, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetTaskIntegers(Automation1Controller controller, int32_t taskIndex, int32_t taskIntegerArrayStartingIndex, int64_t* integerValuesOut, int32_t integerValuesOutMaxLength);

/// @brief Sets the values of a contiguous segment of integer task variables ($itask in AeroScript), starting at the specified task integer array index and with the specified number of variables to set.
///		The values to set are AeroScript integer values (which are 64-bit long integers).
///		These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
/// @param[In] controller The controller to set the variables on.
/// @param[In] taskIndex The index of the task on which to set the integer task variables.
/// @param[In] taskIntegerArrayStartingIndex The task integer array index that starts the segment of task variables to set.
/// @param[In] integerValues The array of AeroScript integer values (which are 64-bit long integers) to set on the task.
/// @param[In] integerValuesLength The length of the integerValues function argument.
/// @return Returns true if the function successfully set the variable values, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetTaskIntegers(Automation1Controller controller, int32_t taskIndex, int32_t taskIntegerArrayStartingIndex, int64_t* integerValues, int32_t integerValuesLength);

/// @brief Gets the values of a contiguous segment of real task variables ($rtask in AeroScript), starting at the specified task real array index and with the specified number of variables to get.
///		The values are returned as AeroScript real values (which are double precision floating point numbers).
///		These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
/// @param[In] controller The controller to get the task variables from.
/// @param[In] taskIndex The index of the task to get the real task variables from.
/// @param[In] taskRealArrayStartingIndex The task real array index that starts the segment of task variables to get.
/// @param[Out] realValuesOut The out array that will be populated with real values that were retrieved from the task.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] realValuesOutMaxLength The maximum number of variables to get from the task and to copy to the realValuesOut function argument.
/// 	This must not be greater than the length of the realValuesOut array.
/// @return Returns true if the function successfully got the variable values, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetTaskReals(Automation1Controller controller, int32_t taskIndex, int32_t taskRealArrayStartingIndex, double* realValuesOut, int32_t realValuesOutMaxLength);

/// @brief Sets the values of a contiguous segment of real task variables ($rtask in AeroScript), starting at the specified task real array index and with the specified number of variables to set.
///		The values to set are AeroScript real values (which are double precision floating point numbers).
///		These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
/// @param[In] controller The controller to set the task variables on.
/// @param[In] taskIndex The index of the task on which to set the real task variables.
/// @param[In] taskRealArrayStartingIndex The task real array index that starts the segment of task variables to set.
/// @param[In] realValues The array of AeroScript real values (which are double precision floating point numbers) to set on the task.
/// @param[In] realValuesLength The length of the realValues function argument.
/// @return Returns true if the function successfully set the variable values, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetTaskReals(Automation1Controller controller, int32_t taskIndex, int32_t taskRealArrayStartingIndex, double* realValues, int32_t realValuesLength);

/// @brief Gets the value of a single string task variable ($stask in AeroScript), at the specified task string array index.
///		These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
///		Each string task variable has a capacity of 256 characters including the null terminator.
/// @param[In] controller The controller to get the task variable from.
/// @param[In] taskIndex The index of the task to get the string task variable from.
/// @param[In] taskStringArrayIndex The task string array index to get the value of.
/// @param[Out] stringValueOut The null-terminated string value of the specified string task variable.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] stringValueMaxLength The maximum number of characters to copy to the stringValueOut function argument.
/// 	This must not be greater than the length of the stringValueOut array.
/// @return Returns true if the function successfully got the task variable value, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetTaskString(Automation1Controller controller, int32_t taskIndex, int32_t taskStringArrayIndex, char* stringValueOut, int32_t stringValueMaxLength);

/// @brief Sets the value of a single string task variable ($stask in AeroScript), at the specified task string array index.
/// These task variables are accessible from every API and can be used to communicate data between iterations of a program running on the same task. They are not accessible from other tasks.
///		Each string task variable has a capacity of 256 characters including the null terminator.
/// @param[In] controller The controller to set the task variables on.
///	@param[In] The index of the task on which to set the string task variable.
/// @param[In] taskStringArrayIndex The task string array index to set the value of.
/// @param[In] stringValue The null-terminated string value to set for the string task variable.
/// @return Returns true if the function successfully set the variable value, otherwise it returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetTaskString(Automation1Controller controller, int32_t taskIndex, int32_t taskStringArrayIndex, const char* stringValue);

/// @brief Gets the value of an integer Industrial Ethernet mapping.
/// @param[In] controller The controller to get the Industrial Ethernet mapping from.
/// @param[In] industrialEthernetMappingName The name of the Industrial Ethernet mapping to get.
/// @param[Out] integerValueOut The integer value that was retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the function successfully got the Industrial Ethernet mapping otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetIndustrialEthernetInteger(Automation1Controller controller, const char* industrialEthernetMappingName, int64_t* integerValueOut);

/// @brief Gets the values of a contiguous segment of an Industrial Ethernet mapping array, starting at the specified Industrial Ethernet mapping array index and with the specified number of integers to get.
/// @param[In] controller The controller to get the Industrial Ethernet mapping array from.
/// @param[In] industrialEthernetMappingArrayName The name of the Industrial Ethernet mapping array to get.
/// @param[In] industrialEthernetMappingStartingArrayIndex The Industrial Ethernet mapping array index that starts the segment of integers to get.
/// @param[Out] integerValuesOut The out array that will be populated with integer values that were retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] integerValuesOutMaxLength The maximum number of integers to get from the Industrial Ethernet mapping array and to copy to the integerValuesOut function argument.
/// 	This must not be greater than the length of the integerValuesOut array.
/// @return Returns true if the function successfully got the Industrial Ethernet mapping array otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetIndustrialEthernetIntegerArray(Automation1Controller controller, const char* industrialEthernetMappingArrayName, int32_t industrialEthernetMappingStartingArrayIndex, int64_t* integerValuesOut, int32_t integerValuesOutMaxLength);

/// @brief Sets the value of an integer Industrial Ethernet mapping.
/// @param[In] controller The controller to set the Industrial Ethernet mapping on.
/// @param[In] industrialEthernetMappingName The name of the Industrial Ethernet mapping to set.
/// @param[In] integerValue The integer value to set on the controller
/// @return Returns true if the function successfully set the Industrial Ethernet mapping otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetIndustrialEthernetInteger(Automation1Controller controller, const char* industrialEthernetMappingName, int64_t integerValue);

/// @brief Sets the values of a contiguous segment of an integer Industrial Ethernet mapping array, starting at the specified Industrial Ethernet mapping array index and with the specified number of integers to set.
/// @param[In] controller The controller to set the Industrial Ethernet mapping array on.
/// @param[In] industrialEthernetMappingArrayName The name of the Industrial Ethernet mapping array to set.
/// @param[In] industrialEthernetMappingStartingArrayIndex The Industrial Ethernet mapping array index that starts the segment of integers to set.
/// @param[In] integerValues The array of integer values to set on the controller.
/// @param[In] integerValuesLength The length of the integerValues function argument.
/// @return Returns true if the function successfully set the Industrial Ethernet mapping array otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetIndustrialEthernetIntegerArray(Automation1Controller controller, const char* industrialEthernetMappingArrayName, int32_t industrialEthernetMappingStartingArrayIndex, int64_t* integerValues, int32_t integerValuesLength);

/// @brief Gets the value of a real Industrial Ethernet mapping.
/// @param[In] controller The controller to get the Industrial Ethernet mapping from.
/// @param[In] industrialEthernetMappingName The name of the Industrial Ethernet mapping to get.
/// @param[Out] realValueOut The real value that was retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @return Returns true if the function successfully got the Industrial Ethernet mapping otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetIndustrialEthernetReal(Automation1Controller controller, const char* industrialEthernetMappingName, double* realValueOut);

/// @brief Gets the values of a contiguous segment of an Industrial Ethernet mapping array, starting at the specified Industrial Ethernet mapping array index and with the specified number of reals to get.
/// @param[In] controller The controller to get the Industrial Ethernet mapping array from.
/// @param[In] industrialEthernetMappingArrayName The name of the Industrial Ethernet mapping array to get.
/// @param[In] industrialEthernetMappingStartingArrayIndex The Industrial Ethernet mapping array index that starts the segment of reals to get.
/// @param[Out] realValuesOut The out array that will be populated with real values that were retrieved from the controller.
/// 	Only use this if the function call was successful. This argument must have memory preallocated before passing it into this function.
/// @param[In] realValuesOutMaxLength The maximum number of reals to get from the Industrial Ethernet mapping array and to copy to the realValuesOut function argument.
/// 	This must not be greater than the length of the integerValuesOut array.
/// @return Returns true if the function successfully got the Industrial Ethernet mapping array otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_GetIndustrialEthernetRealArray(Automation1Controller controller, const char* industrialEthernetMappingArrayName, int32_t industrialEthernetMappingStartingArrayIndex, double* realValuesOut, int32_t realValuesOutMaxLength);

/// @brief Sets the value of a real Industrial Ethernet mapping.
/// @param[In] controller The controller to set the Industrial Ethernet mapping on.
/// @param[In] industrialEthernetMappingName The name of the Industrial Ethernet mapping to set.
/// @param[In] realValue The real value to set on the controller
/// @return Returns true if the function successfully set the Industrial Ethernet mapping otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetIndustrialEthernetReal(Automation1Controller controller, const char* industrialEthernetMappingName, double realValue);

/// @brief Sets the values of a contiguous segment of a real Industrial Ethernet mapping array, starting at the specified Industrial Ethernet mapping array index and with the specified number of reals to set.
/// @param[In] controller The controller to set the Industrial Ethernet mapping array on.
/// @param[In] industrialEthernetMappingArrayName The name of the Industrial Ethernet mapping array to set.
/// @param[In] industrialEthernetMappingStartingArrayIndex The Industrial Ethernet mapping array index that starts the segment of reals to set.
/// @param[In] realValues The array of real values to set on the controller.
/// @param[In] realValuesLength The length of the realValues function argument.
/// @return Returns true if the function successfully set the Industrial Ethernet mapping array otherwise returns false.
/// 	See Automation1_GetLastError() and Automation1_GetLastErrorMessage() for more information.
AUTOMATION1_CAPI bool Automation1_Variables_SetIndustrialEthernetRealArray(Automation1Controller controller, const char* industrialEthernetMappingArrayName, int32_t industrialEthernetMappingStartingArrayIndex, double* realValues, int32_t realValuesLength);

#if defined(__cplusplus)
}
#endif

#endif // AUTOMATION1VARIABLES_H_INCLUDED