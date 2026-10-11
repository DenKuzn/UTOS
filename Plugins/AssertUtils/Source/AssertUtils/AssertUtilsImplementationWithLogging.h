#pragma once

#define assertUtilsAssertionFailed(Message, Value) \
	ensureAlwaysMsgf( false, TEXT("%s(). %s. %s"), *FString(__FUNCTION__), *FString(Message), *FString(#Value))

#define assertConditionEndBracketWithReturn(...) \
	return __VA_ARGS__; \
};

#define assertConditionEndBracket() \
};

#define assertConditionEndBracketWithBreak() \
	break; \
};

#define assertConditionEndBracketWithContinue() \
	continue; \
};

#define assertConditionEndReturn(...) \
	return __VA_ARGS__;

#define assertConditionEndBreak() \
	break;

#define assertConditionEndContinue() \
	continue;

#define assertNeverReached_Implementation(...) \
	assertUtilsAssertionFailed("Unexpected code execution: we should not be here", );

#define assertOptionalHasValue_Implementation(optional, ...) \
if (!optional.IsSet()) \
{ \
	assertUtilsAssertionFailed("Optional does not have a value", optional);

#define assertCustomStructIsSet_Implementation(CustomStruct, ...) \
if (!CustomStruct.IsSet()) \
{ \
	assertUtilsAssertionFailed("This Struct Data is Empty", CustomStruct);

#define assertOptionalHasNoValue_Implementation(optional, ...) \
if (optional.IsSet()) \
{ \
	assertUtilsAssertionFailed("Optional has a value", optional);

#define assertDefaultImplementationIsOverriden_Implementation(...) \
	assertUtilsAssertionFailed("Default implementation is not overriden or base class implementation is called in derived class",  );

#define assertUObjectPointerIsValid_Implementation(pointer) \
if (!::IsValid(pointer)) \
{\
	assertUtilsAssertionFailed("UObject pointer is not valid", pointer);

#define assertUObjectPointerIsNotValid_Implementation(pointer) \
if (::IsValid(pointer)) \
{\
	assertUtilsAssertionFailed("UObject pointer is valid", pointer);

#define assertScriptInterfaceIsValid_Implementation(scriptInterface) \
if (!::IsValid(scriptInterface.GetObject()) || !scriptInterface.GetInterface()) \
{ \
	assertUtilsAssertionFailed("Script interface is not valid", scriptInterface);

#define assertScriptInterfaceIsNotValid_Implementation(scriptInterface) \
if (::IsValid(scriptInterface.GetObject()) || scriptInterface.GetInterface()) \
{ \
	assertUtilsAssertionFailed("Script interface is valid", scriptInterface);

#define assertSmartPointerIsValid_Implementation(smartPointer) \
if (!smartPointer.IsValid()) \
{ \
	assertUtilsAssertionFailed("Smart pointer is not valid", smartPointer);

#define assertSmartPointerIsNotValid_Implementation(smartPointer) \
if (smartPointer.IsValid()) \
{ \
	assertUtilsAssertionFailed("Smart pointer is valid", smartPointer);

#define assertSoftPointerIsValid_Implementation(softPointer) \
if (softPointer.IsNull()) \
{\
	assertUtilsAssertionFailed("Soft pointer is not valid", softPointer);

#define assertSoftPointerIsNotValid_Implementation(softPointer) \
if (!softPointer.IsNull()) \
{\
	assertUtilsAssertionFailed("Soft pointer is valid", softPointer);

#define assertIsNull_Implementation(rawPointer) \
if (rawPointer) \
{\
	assertUtilsAssertionFailed("Raw pointer is not null", rawPointer);

#define assertIsNotNull_Implementation(rawPointer) \
if (!rawPointer) \
{\
	assertUtilsAssertionFailed("Raw pointer is null", rawPointer);

#define assertStringIsEmpty_Implementation(value) \
if (!value.IsEmpty()) \
{ \
	assertUtilsAssertionFailed("String is not empty", value);

#define assertStringIsNotEmpty_Implementation(value) \
if (value.IsEmpty()) \
{ \
	assertUtilsAssertionFailed("String is empty", value);

#define assertNameIsAssigned_Implementation(value) \
if (value.IsNone()) \
{ \
	assertUtilsAssertionFailed("Name is not assigned", value);

#define assertGameplayTagIsValid_Implementation(value) \
if (!value.IsValid()) \
{ \
	assertUtilsAssertionFailed("GameplayTag is not valid", value);

#define assertIsEqual_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue != rightHandValue) \
{ \
	assertUtilsAssertionFailed(FString("Values are not equal. ") + FString(#leftHandValue) + FString( " != ") + FString(#rightHandValue),  );

#define assertIsNotEqual_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue == rightHandValue) \
{ \
	assertUtilsAssertionFailed(FString("Values are equal. ") + FString(#leftHandValue) + FString( " == ") + FString(#rightHandValue),  );

#define assertIsGreater_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue <= rightHandValue) \
{ \
	assertUtilsAssertionFailed(FString("Value is not greater. ") + FString(#leftHandValue) + FString( " <= ") + FString(#rightHandValue),  );

#define assertIsGreaterOrEqual_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue < rightHandValue) \
{ \
	assertUtilsAssertionFailed(FString("Value is not greater or equal. ") + FString(#leftHandValue) + FString( " < ") + FString(#rightHandValue),  );

#define assertIsLess_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue >= rightHandValue) \
{ \
	assertUtilsAssertionFailed(FString("Value is not less. ") + FString(#leftHandValue) + FString( " >= ") + FString(#rightHandValue),  );

#define assertIsLessOrEqual_Implementation(leftHandValue, rightHandValue) \
if (leftHandValue > rightHandValue) \
{ \
	assertUtilsAssertionFailed("Value is not less or equal. " + FString(#leftHandValue) + FString( " > ") + FString(#rightHandValue),  );

#define assertIsTrue_Implementation(expression) \
if (!(expression)) \
{ \
	assertUtilsAssertionFailed("Value is not true", expression);

#define assertIsFalse_Implementation(expression) \
if (expression) \
{ \
	assertUtilsAssertionFailed("Value is not false", expression);

#define assertIndexIsInArrayBounds_Implementation(index, arr) \
if (index < 0 \
	|| index > arr.Num() - 1) \
{ \
	assertUtilsAssertionFailed("Index is out of array bounds", index);

#define assertContainerContainsElement_Implementation(container, element) \
if (!container.Contains(element)) \
{ \
	assertUtilsAssertionFailed("Container does not contain element", element);

#define assertContainerDoesNotContainElement_Implementation(container, element) \
if (container.Contains(element)) \
{ \
	assertUtilsAssertionFailed("Container contains element", element);

#define assertContainerIsNotEmpty_Implementation(container) \
if (container.IsEmpty()) \
{ \
	assertUtilsAssertionFailed("Container is empty", container);

#define assertContainerIsEmpty_Implementation(container) \
if (!container.IsEmpty()) \
{ \
	assertUtilsAssertionFailed("Container is not empty", container);

#define assertHasAuthority_Implementation(actor, ...) \
if (!::IsValid(actor)) \
{ \
	assertUtilsAssertionFailed("Actor has no authority. Actor is not valid", actor); \
	return __VA_ARGS__; \
}; \
if (!actor->HasAuthority()) \
{ \
	assertUtilsAssertionFailed("Actor has no authority", actor); \
	return __VA_ARGS__; \
};

#define assertHasAuthority_Implementation_ignore(actor) \
if (!::IsValid(actor)) \
{ \
	assertUtilsAssertionFailed("Actor has no authority. Actor is not valid", actor); \
}; \
if (!actor->HasAuthority()) \
{ \
	assertUtilsAssertionFailed("Actor has no authority", actor); \
};

#define assertHasAuthority_Implementation_break(actor) \
if (!::IsValid(actor)) \
{ \
	assertUtilsAssertionFailed("Actor has no authority. Actor is not valid", actor); \
	break; \
}; \
if (!actor->HasAuthority()) \
{ \
	assertUtilsAssertionFailed("Actor has no authority", actor); \
	break; \
};

#define assertHasAuthority_Implementation_continue(actor) \
if (!::IsValid(actor)) \
{ \
	assertUtilsAssertionFailed("Actor has no authority. Actor is not valid", actor); \
	continue; \
}; \
if (!actor->HasAuthority()) \
{ \
	assertUtilsAssertionFailed("Actor has no authority", actor); \
	continue; \
};

#define assertIsLocallyControlled_Implementation(pawn, ...) \
if (!::IsValid(pawn)) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled. Pawn is not valid", pawn); \
	return __VA_ARGS__; \
}; \
if (!pawn->IsLocallyControlled()) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled", pawn); \
	return __VA_ARGS__; \
}; \

#define assertIsLocallyControlled_Implementation_ignore(pawn) \
if (!::IsValid(pawn)) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled. Pawn is not valid", pawn); \
}; \
if (!pawn->IsLocallyControlled()) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled", pawn); \
};

#define assertIsLocallyControlled_Implementation_break(pawn, ...) \
if (!::IsValid(pawn)) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled. Pawn is not valid", pawn); \
	break; \
}; \
if (!pawn->IsLocallyControlled()) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled", pawn); \
	break; \
}; \

#define assertIsLocallyControlled_Implementation_continue(pawn, ...) \
if (!::IsValid(pawn)) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled. Pawn is not valid", pawn); \
	continue; \
}; \
if (!pawn->IsLocallyControlled()) \
{ \
	assertUtilsAssertionFailed("Pawn is not locally controlled", pawn); \
	continue; \
}; \

#define assertIsLocalController_Implementation(controller, ...) \
if (!::IsValid(controller)) \
{ \
	assertUtilsAssertionFailed("Controller is not local. Controller is not valid", controller); \
	return __VA_ARGS__; \
}; \
if (!controller->IsLocalController()) \
{ \
	assertUtilsAssertionFailed("Controller is not local", controller); \
	return __VA_ARGS__; \
};

#define assertIsLocalController_Implementation_ignore(controller) \
if (!::IsValid(controller)) \
{ \
	assertUtilsAssertionFailed("Controller is not local. Controller is not valid", controller); \
}; \
if (!controller->IsLocalController()) \
{ \
	assertUtilsAssertionFailed("Controller is not local", controller); \
};

#define assertIsLocalController_Implementation_break(controller, ...) \
if (!::IsValid(controller)) \
{ \
	assertUtilsAssertionFailed("Controller is not local. Controller is not valid", controller); \
	break; \
}; \
if (!controller->IsLocalController()) \
{ \
	assertUtilsAssertionFailed("Controller is not local", controller); \
	break; \
};

#define assertIsLocalController_Implementation_continue(controller, ...) \
if (!::IsValid(controller)) \
{ \
	assertUtilsAssertionFailed("Controller is not local. Controller is not valid", controller); \
	continue; \
}; \
if (!controller->IsLocalController()) \
{ \
	assertUtilsAssertionFailed("Controller is not local", controller); \
	continue; \
};

#define assertUnrealInterfaceIsImplemented_Implementation(uObject, TInterface, ...) \
if (!::IsValid(uObject)) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented. UObject is not valid", uObject); \
	return __VA_ARGS__; \
}; \
if (!uObject->GetClass()->ImplementsInterface(TInterface::StaticClass())) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented", uObject); \
	return __VA_ARGS__; \
};

#define assertUnrealInterfaceIsImplemented_Implementation_ignore(uObject, TInterface) \
if (!::IsValid(uObject)) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented. UObject is not valid", uObject); \
}; \
if (!uObject->GetClass()->ImplementsInterface(TInterface::StaticClass())) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented", uObject); \
};

#define assertUnrealInterfaceIsImplemented_Implementation_break(uObject, TInterface, ...) \
if (!::IsValid(uObject)) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented. UObject is not valid", uObject); \
	break; \
}; \
if (!uObject->GetClass()->ImplementsInterface(TInterface::StaticClass())) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented", uObject); \
	break; \
};

#define assertUnrealInterfaceIsImplemented_Implementation_continue(uObject, TInterface, ...) \
if (!::IsValid(uObject)) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented. UObject is not valid", uObject); \
	continue; \
}; \
if (!uObject->GetClass()->ImplementsInterface(TInterface::StaticClass())) \
{ \
	assertUtilsAssertionFailed("Unreal interface is not implemented", uObject); \
	continue; \
};

#define assertNativeInterfaceIsImplemented_Implementation(testObject, TInterface) \
if(!Cast<TInterface>(testObject)) \
{ \
	assertUtilsAssertionFailed("Native interface is not implemented", testObject);

#define assertDataTableRowIsFound_Implementation(dataTable, row, rowName, ...) \
if (!dataTable) \
{ \
	assertUtilsAssertionFailed("DataTable row is not found. DataTable is null", dataTable); \
	return __VA_ARGS__; \
} \
if (!row) \
{\
	assertUtilsAssertionFailed("DataTable row is not found", row); \
	return __VA_ARGS__; \
};

#define assertDataTableRowIsFound_Implementation_ignore(dataTable, row, rowName) \
if (!dataTable) \
{ \
	assertUtilsAssertionFailed("DataTable row is not found. DataTable is null", dataTable); \
} \
if (!row) \
{\
	assertUtilsAssertionFailed("DataTable row is not found", row); \
};

#define assertDataTableRowIsFound_Implementation_break(dataTable, row, rowName, ...) \
if (!dataTable) \
{ \
	assertUtilsAssertionFailed("DataTable row is not found. DataTable is null", dataTable); \
	break; \
} \
if (!row) \
{\
	assertUtilsAssertionFailed("DataTable row is not found", row); \
	break; \
};

#define assertDataTableRowIsFound_Implementation_continue(dataTable, row, rowName, ...) \
if (!dataTable) \
{ \
	assertUtilsAssertionFailed("DataTable row is not found. DataTable is null", dataTable); \
	continue; \
} \
if (!row) \
{\
	assertUtilsAssertionFailed("DataTable row is not found", row); \
	continue; \
};

#define assertBlackboardKeyIsValid_Implementation(blackboard, keyName, ...) \
if (!::IsValid(blackboard)) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Blackboard is not valid", blackboard); \
	return __VA_ARGS__; \
}; \
if (!blackboard->IsValidKey(blackboard->GetKeyID(keyName))) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Key is not valid", keyName); \
	return __VA_ARGS__; \
};

#define assertBlackboardKeyIsValid_Implementation_ignore(blackboard, keyName) \
if (!::IsValid(blackboard)) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Blackboard is not valid", blackboard); \
}; \
if (!blackboard->IsValidKey(blackboard->GetKeyID(keyName))) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Key is not valid", keyName); \
};

#define assertBlackboardKeyIsValid_Implementation_break(blackboard, keyName, ...) \
if (!::IsValid(blackboard)) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Blackboard is not valid", blackboard); \
	break; \
}; \
if (!blackboard->IsValidKey(blackboard->GetKeyID(keyName))) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Key is not valid", keyName); \
	break; \
};

#define assertBlackboardKeyIsValid_Implementation_continue(blackboard, keyName, ...) \
if (!::IsValid(blackboard)) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Blackboard is not valid", blackboard); \
	continue; \
}; \
if (!blackboard->IsValidKey(blackboard->GetKeyID(keyName))) \
{ \
	assertUtilsAssertionFailed("Blackboard key is not valid. Key is not valid", keyName); \
	continue; \
};