#pragma once

#include "AssertUtilsImplementationWithLogging.h"

// assertNeverReached
#define assertNeverReached_return(...)\
		assertNeverReached_Implementation()\
		assertConditionEndReturn(__VA_ARGS__)

#define assertNeverReached_ignore()\
		assertNeverReached_Implementation()

#define assertNeverReached_withBreak()\
		assertNeverReached_Implementation()\
		assertConditionEndBreak()

#define assertNeverReached_withContinue()\
		assertNeverReached_Implementation()\
		assertConditionEndContinue()

// assertCustomStructIsNotEmpty
#define assertCustomStructIsSet_return(CustomStruct, ...)\
		assertCustomStructIsSet_Implementation(CustomStruct)\
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertCustomStructIsSet_ignore(CustomStruct)\
		assertCustomStructIsSet_Implementation(CustomStruct)\
		assertConditionEndBracket()

#define assertCustomStructIsSet_withBreak(CustomStruct)\
		assertCustomStructIsSet_Implementation(CustomStruct)\
		assertConditionEndBracketWithBreak()

#define assertCustomStructIsSet_withContinue(CustomStruct)\
		assertCustomStructIsSet_Implementation(CustomStruct)\
		assertConditionEndBracketWithContinue()

// assertOptionalHasValue
#define assertOptionalHasValue_return(optional, ...)\
		assertOptionalHasValue_Implementation(optional)\
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertOptionalHasValue_ignore(optional)\
		assertOptionalHasValue_Implementation(optional)\
		assertConditionEndBracket()

#define assertOptionalHasValue_withBreak(optional)\
		assertOptionalHasValue_Implementation(optional)\
		assertConditionEndBracketWithBreak()

#define assertOptionalHasValue_withContinue(optional)\
		assertOptionalHasValue_Implementation(optional)\
		assertConditionEndBracketWithContinue()

// assertOptionalHasNoValue
#define assertOptionalHasNoValue_return(optional, ...)\
		assertOptionalHasNoValue_Implementation(optional)\
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertOptionalHasNoValue_ignore(optional)\
		assertOptionalHasNoValue_Implementation(optional)\
		assertConditionEndBracket()

#define assertOptionalHasNoValue_withBreak(optional)\
		assertOptionalHasNoValue_Implementation(optional)\
		assertConditionEndBracketWithBreak()

#define assertOptionalHasNoValue_withContinue(optional)\
		assertOptionalHasNoValue_Implementation(optional)\
		assertConditionEndBracketWithContinue()

// assertDefaultImplementationIsOverriden
#define assertDefaultImplementationIsOverriden_return(...)\
		assertDefaultImplementationIsOverriden_Implementation()\
		assertConditionEndReturn(__VA_ARGS__)

#define assertDefaultImplementationIsOverriden_ignore()\
		assertDefaultImplementationIsOverriden_Implementation()

#define assertDefaultImplementationIsOverriden_withBreak()\
		assertDefaultImplementationIsOverriden_Implementation()\
		assertConditionEndBreak()

#define assertDefaultImplementationIsOverriden_withContinue()\
		assertDefaultImplementationIsOverriden_Implementation()\
		assertConditionEndContinue()

// assertUObjectPointerIsValid
#define assertUObjectPointerIsValid_return(pointer, ...)\
		assertUObjectPointerIsValid_Implementation(pointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertUObjectPointerIsValid_ignore(pointer)\
		assertUObjectPointerIsValid_Implementation(pointer) \
		assertConditionEndBracket()

#define assertUObjectPointerIsValid_withBreak(pointer)\
		assertUObjectPointerIsValid_Implementation(pointer) \
		assertConditionEndBracketWithBreak()

#define assertUObjectPointerIsValid_withContinue(pointer)\
		assertUObjectPointerIsValid_Implementation(pointer) \
		assertConditionEndBracketWithContinue()

// assertUObjectPointerIsNotValid
#define assertUObjectPointerIsNotValid_return(pointer, ...)\
		assertUObjectPointerIsNotValid_Implementation(pointer)\
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertUObjectPointerIsNotValid_ignore(pointer)\
		assertUObjectPointerIsNotValid_Implementation(pointer) \
		assertConditionEndBracket()

#define assertUObjectPointerIsNotValid_withBreak(pointer)\
		assertUObjectPointerIsNotValid_Implementation(pointer) \
		assertConditionEndBracketWithBreak()

#define assertUObjectPointerIsNotValid_withContinue(pointer)\
		assertUObjectPointerIsNotValid_Implementation(pointer) \
		assertConditionEndBracketWithContinue()

// assertScriptInterfaceIsValid
#define assertScriptInterfaceIsValid_return(scriptInterface, ...)\
		assertScriptInterfaceIsValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertScriptInterfaceIsValid_ignore(scriptInterface)\
		assertScriptInterfaceIsValid_Implementation(scriptInterface) \
		assertConditionEndBracket()

#define assertScriptInterfaceIsValid_withBreak(scriptInterface)\
		assertScriptInterfaceIsValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithBreak()

#define assertScriptInterfaceIsValid_withContinue(scriptInterface)\
		assertScriptInterfaceIsValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithContinue()

// assertScriptInterfaceIsNotValid
#define assertScriptInterfaceIsNotValid_return(scriptInterface, ...)\
		assertScriptInterfaceIsNotValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertScriptInterfaceIsNotValid_ignore(scriptInterface)\
		assertScriptInterfaceIsNotValid_Implementation(scriptInterface) \
		assertConditionEndBracket()

#define assertScriptInterfaceIsNotValid_withBreak(scriptInterface)\
		assertScriptInterfaceIsNotValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithBreak()

#define assertScriptInterfaceIsNotValid_withContinue(scriptInterface)\
		assertScriptInterfaceIsNotValid_Implementation(scriptInterface) \
		assertConditionEndBracketWithContinue()

// assertSmartPointerIsValid
#define assertSmartPointerIsValid_return(smartPointer, ...)\
		assertSmartPointerIsValid_Implementation(smartPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertSmartPointerIsValid_ignore(smartPointer)\
		assertSmartPointerIsValid_Implementation(smartPointer) \
		assertConditionEndBracket()

#define assertSmartPointerIsValid_withBreak(smartPointer)\
		assertSmartPointerIsValid_Implementation(smartPointer) \
		assertConditionEndBracketWithBreak()

#define assertSmartPointerIsValid_withContinue(smartPointer)\
		assertSmartPointerIsValid_Implementation(smartPointer) \
		assertConditionEndBracketWithContinue()

// assertSmartPointerIsNotValid
#define assertSmartPointerIsNotValid_return(smartPointer, ...)\
		assertSmartPointerIsNotValid_Implementation(smartPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertSmartPointerIsNotValid_ignore(smartPointer)\
		assertSmartPointerIsNotValid_Implementation(smartPointer) \
		assertConditionEndBracket()

#define assertSmartPointerIsNotValid_withBreak(smartPointer)\
		assertSmartPointerIsNotValid_Implementation(smartPointer) \
		assertConditionEndBracketWithBreak()

#define assertSmartPointerIsNotValid_withContinue(smartPointer)\
		assertSmartPointerIsNotValid_Implementation(smartPointer) \
		assertConditionEndBracketWithContinue()

// assertSoftPointerIsValid
#define assertSoftPointerIsValid_return(softPointer, ...)\
		assertSoftPointerIsValid_Implementation(softPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertSoftPointerIsValid_ignore(softPointer)\
		assertSoftPointerIsValid_Implementation(softPointer) \
		assertConditionEndBracket()

#define assertSoftPointerIsValid_withBreak(softPointer)\
		assertSoftPointerIsValid_Implementation(softPointer) \
		assertConditionEndBracketWithBreak()

#define assertSoftPointerIsValid_withContinue(softPointer)\
		assertSoftPointerIsValid_Implementation(softPointer) \
		assertConditionEndBracketWithContinue()

// assertSoftPointerIsNotValid
#define assertSoftPointerIsNotValid_return(softPointer, ...)\
		assertSoftPointerIsNotValid_Implementation(softPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertSoftPointerIsNotValid_ignore(softPointer)\
		assertSoftPointerIsNotValid_Implementation(softPointer) \
		assertConditionEndBracket()

#define assertSoftPointerIsNotValid_withBreak(softPointer)\
		assertSoftPointerIsNotValid_Implementation(softPointer) \
		assertConditionEndBracketWithBreak()

#define assertSoftPointerIsNotValid_withContinue(softPointer)\
		assertSoftPointerIsNotValid_Implementation(softPointer) \
		assertConditionEndBracketWithContinue()

// assertIsNull
#define assertIsNull_return(rawPointer, ...)\
		assertIsNull_Implementation(rawPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsNull_ignore(rawPointer)\
		assertIsNull_Implementation(rawPointer) \
		assertConditionEndBracket()

#define assertIsNull_withBreak(rawPointer)\
		assertIsNull_Implementation(rawPointer) \
		assertConditionEndBracketWithBreak()

#define assertIsNull_withContinue(rawPointer)\
		assertIsNull_Implementation(rawPointer) \
		assertConditionEndBracketWithContinue()

// assertIsNotNull
#define assertIsNotNull_return(rawPointer, ...)\
		assertIsNotNull_Implementation(rawPointer) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsNotNull_ignore(rawPointer)\
		assertIsNotNull_Implementation(rawPointer) \
		assertConditionEndBracket()

#define assertIsNotNull_withBreak(rawPointer)\
		assertIsNotNull_Implementation(rawPointer) \
		assertConditionEndBracketWithBreak()

#define assertIsNotNull_withContinue(rawPointer)\
		assertIsNotNull_Implementation(rawPointer) \
		assertConditionEndBracketWithContinue()

// assertStringIsEmpty
#define assertStringIsEmpty_return(value, ...)\
		assertStringIsEmpty_Implementation(value) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertStringIsEmpty_ignore(value)\
		assertStringIsEmpty_Implementation(value) \
		assertConditionEndBracket()

#define assertStringIsEmpty_withBreak(value)\
		assertStringIsEmpty_Implementation(value) \
		assertConditionEndBracketWithBreak()

#define assertStringIsEmpty_withContinue(value)\
		assertStringIsEmpty_Implementation(value) \
		assertConditionEndBracketWithContinue()

// assertStringIsNotEmpty
#define assertStringIsNotEmpty_return(value, ...)\
		assertStringIsNotEmpty_Implementation(value) \
		assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertStringIsNotEmpty_ignore(value)\
		assertStringIsNotEmpty_Implementation(value) \
		assertConditionEndBracket()

#define assertStringIsNotEmpty_withBreak(value)\
		assertStringIsNotEmpty_Implementation(value) \
		assertConditionEndBracketWithBreak()

#define assertStringIsNotEmpty_withContinue(value)\
		assertStringIsNotEmpty_Implementation(value) \
		assertConditionEndBracketWithContinue()

// assertNameIsAssigned
#define assertNameIsAssigned_return(value, ...)\
        assertNameIsAssigned_Implementation(value) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertNameIsAssigned_ignore(value)\
        assertNameIsAssigned_Implementation(value) \
        assertConditionEndBracket()

#define assertNameIsAssigned_withBreak(value)\
        assertNameIsAssigned_Implementation(value) \
        assertConditionEndBracketWithBreak()

#define assertNameIsAssigned_withContinue(value)\
        assertNameIsAssigned_Implementation(value) \
        assertConditionEndBracketWithContinue()

// assertGameplayTagIsValid
#define assertGameplayTagIsValid_return(value, ...)\
        assertGameplayTagIsValid_Implementation(value) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertGameplayTagIsValid_ignore(value)\
        assertGameplayTagIsValid_Implementation(value) \
        assertConditionEndBracket()

#define assertGameplayTagIsValid_withBreak(value)\
        assertGameplayTagIsValid_Implementation(value) \
        assertConditionEndBracketWithBreak()

#define assertGameplayTagIsValid_withContinue(value)\
        assertGameplayTagIsValid_Implementation(value) \
        assertConditionEndBracketWithContinue()

// assertIsEqual
#define assertIsEqual_return(leftHandValue, rightHandValue, ...)\
        assertIsEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsEqual_ignore(leftHandValue, rightHandValue)\
        assertIsEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsEqual_withBreak(leftHandValue, rightHandValue)\
        assertIsEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsEqual_withContinue(leftHandValue, rightHandValue)\
        assertIsEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsNotEqual
#define assertIsNotEqual_return(leftHandValue, rightHandValue, ...)\
        assertIsNotEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsNotEqual_ignore(leftHandValue, rightHandValue)\
        assertIsNotEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsNotEqual_withBreak(leftHandValue, rightHandValue)\
        assertIsNotEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsNotEqual_withContinue(leftHandValue, rightHandValue)\
        assertIsNotEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsGreater
#define assertIsGreater_return(leftHandValue, rightHandValue, ...)\
        assertIsGreater_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsGreater_ignore(leftHandValue, rightHandValue)\
        assertIsGreater_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsGreater_withBreak(leftHandValue, rightHandValue)\
        assertIsGreater_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsGreater_withContinue(leftHandValue, rightHandValue)\
        assertIsGreater_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsGreaterOrEqual
#define assertIsGreaterOrEqual_return(leftHandValue, rightHandValue, ...)\
        assertIsGreaterOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsGreaterOrEqual_ignore(leftHandValue, rightHandValue)\
        assertIsGreaterOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsGreaterOrEqual_withBreak(leftHandValue, rightHandValue)\
        assertIsGreaterOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsGreaterOrEqual_withContinue(leftHandValue, rightHandValue)\
        assertIsGreaterOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsLess
#define assertIsLess_return(leftHandValue, rightHandValue, ...)\
        assertIsLess_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsLess_ignore(leftHandValue, rightHandValue)\
        assertIsLess_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsLess_withBreak(leftHandValue, rightHandValue)\
        assertIsLess_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsLess_withContinue(leftHandValue, rightHandValue)\
        assertIsLess_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsLessOrEqual
#define assertIsLessOrEqual_return(leftHandValue, rightHandValue, ...)\
        assertIsLessOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsLessOrEqual_ignore(leftHandValue, rightHandValue)\
        assertIsLessOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracket()

#define assertIsLessOrEqual_withBreak(leftHandValue, rightHandValue)\
        assertIsLessOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithBreak()

#define assertIsLessOrEqual_withContinue(leftHandValue, rightHandValue)\
        assertIsLessOrEqual_Implementation(leftHandValue, rightHandValue) \
        assertConditionEndBracketWithContinue()

// assertIsTrue
#define assertIsTrue_return(value, ...)\
        assertIsTrue_Implementation(value) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsTrue_ignore(value)\
        assertIsTrue_Implementation(value) \
        assertConditionEndBracket()

#define assertIsTrue_withBreak(value)\
        assertIsTrue_Implementation(value) \
        assertConditionEndBracketWithBreak()

#define assertIsTrue_withContinue(value)\
        assertIsTrue_Implementation(value) \
        assertConditionEndBracketWithContinue()

// assertIsFalse
#define assertIsFalse_return(value, ...)\
        assertIsFalse_Implementation(value) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIsFalse_ignore(value)\
        assertIsFalse_Implementation(value) \
        assertConditionEndBracket()

#define assertIsFalse_withBreak(value)\
        assertIsFalse_Implementation(value) \
        assertConditionEndBracketWithBreak()

#define assertIsFalse_withContinue(value)\
        assertIsFalse_Implementation(value) \
        assertConditionEndBracketWithContinue()

// assertIndexIsInArrayBounds
#define assertIndexIsInArrayBounds_return(index, arr, ...)\
        assertIndexIsInArrayBounds_Implementation(index, arr) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertIndexIsInArrayBounds_ignore(index, arr)\
        assertIndexIsInArrayBounds_Implementation(index, arr) \
        assertConditionEndBracket()

#define assertIndexIsInArrayBounds_withBreak(index, arr)\
        assertIndexIsInArrayBounds_Implementation(index, arr) \
        assertConditionEndBracketWithBreak()

#define assertIndexIsInArrayBounds_withContinue(index, arr)\
        assertIndexIsInArrayBounds_Implementation(index, arr) \
        assertConditionEndBracketWithContinue()

// assertContainerContainsElement
#define assertContainerContainsElement_return(container, element, ...)\
        assertContainerContainsElement_Implementation(container, element) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertContainerContainsElement_ignore(container, element)\
        assertContainerContainsElement_Implementation(container, element) \
        assertConditionEndBracket()

#define assertContainerContainsElement_withBreak(container, element)\
        assertContainerContainsElement_Implementation(container, element) \
        assertConditionEndBracketWithBreak()

#define assertContainerContainsElement_withContinue(container, element)\
        assertContainerContainsElement_Implementation(container, element) \
        assertConditionEndBracketWithContinue()

// assertContainerDoesNotContainElement
#define assertContainerDoesNotContainElement_return(container, element, ...)\
        assertContainerDoesNotContainElement_Implementation(container, element) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertContainerDoesNotContainElement_ignore(container, element)\
        assertContainerDoesNotContainElement_Implementation(container, element) \
        assertConditionEndBracket()

#define assertContainerDoesNotContainElement_withBreak(container, element)\
        assertContainerDoesNotContainElement_Implementation(container, element) \
        assertConditionEndBracketWithBreak()

#define assertContainerDoesNotContainElement_withContinue(container, element)\
        assertContainerDoesNotContainElement_Implementation(container, element) \
        assertConditionEndBracketWithContinue()

// assertContainerIsNotEmpty
#define assertContainerIsNotEmpty_return(container, ...)\
        assertContainerIsNotEmpty_Implementation(container) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertContainerIsNotEmpty_ignore(container)\
        assertContainerIsNotEmpty_Implementation(container) \
        assertConditionEndBracket()

#define assertContainerIsNotEmpty_withBreak(container)\
        assertContainerIsNotEmpty_Implementation(container) \
        assertConditionEndBracketWithBreak()

#define assertContainerIsNotEmpty_withContinue(container)\
        assertContainerIsNotEmpty_Implementation(container) \
        assertConditionEndBracketWithContinue()

// assertContainerIsEmpty
#define assertContainerIsEmpty_return(container, ...)\
        assertContainerIsEmpty_Implementation(container) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertContainerIsEmpty_ignore(container)\
        assertContainerIsEmpty_Implementation(container) \
        assertConditionEndBracket()

#define assertContainerIsEmpty_withBreak(container)\
        assertContainerIsEmpty_Implementation(container) \
        assertConditionEndBracketWithBreak()

#define assertContainerIsEmpty_withContinue(container)\
        assertContainerIsEmpty_Implementation(container) \
        assertConditionEndBracketWithContinue()

// assertHasAuthority
#define assertHasAuthority_return(actor, ...)\
		assertHasAuthority_Implementation(actor)

#define assertHasAuthority_ignore(actor)\
		assertHasAuthority_Implementation_ignore(actor)

#define assertHasAuthority_withBreak(actor)\
		assertHasAuthority_Implementation_break(actor)

#define assertHasAuthority_withContinue(actor)\
		assertHasAuthority_Implementation_continue(actor)

// assertIsLocallyControlled
#define assertIsLocallyControlled_return(pawn, ...)\
		assertIsLocallyControlled_Implementation(pawn)

#define assertIsLocallyControlled_ignore(pawn)\
		assertIsLocallyControlled_Implementation_ignore(pawn)

#define assertIsLocallyControlled_withBreak(pawn)\
		assertIsLocallyControlled_Implementation_break(pawn)

#define assertIsLocallyControlled_withContinue(pawn)\
		assertIsLocallyControlled_Implementation_continue(pawn)

// assertIsLocalController
#define assertIsLocalController_return(controller, ...)\
		assertIsLocalController_Implementation(controller)

#define assertIsLocalController_ignore(controller)\
		assertIsLocalController_Implementation_ignore(controller)

#define assertIsLocalController_withBreak(controller)\
		assertIsLocalController_Implementation_break(controller)

#define assertIsLocalController_withContinue(controller)\
		assertIsLocalController_Implementation_continue(controller)

// assertUnrealInterfaceIsImplemented
#define assertUnrealInterfaceIsImplemented_return(uObject, TInterface, ...) \
		assertUnrealInterfaceIsImplemented_Implementation(uObject, TInterface)

#define assertUnrealInterfaceIsImplemented_ignore(uObject, TInterface) \
		assertUnrealInterfaceIsImplemented_Implementation_ignore(uObject, TInterface)

#define assertUnrealInterfaceIsImplemented_withBreak(uObject, TInterface) \
		assertUnrealInterfaceIsImplemented_Implementation_break(uObject, TInterface)

#define assertUnrealInterfaceIsImplemented_withContinue(uObject, TInterface) \
		assertUnrealInterfaceIsImplemented_Implementation_continue(uObject, TInterface)

// assertNativeInterfaceIsImplemented
#define assertNativeInterfaceIsImplemented_return(uObject, TInterface, ...) \
        assertNativeInterfaceIsImplemented_Implementation(uObject, TInterface) \
        assertConditionEndBracketWithReturn(__VA_ARGS__)

#define assertNativeInterfaceIsImplemented_ignore(uObject, TInterface) \
        assertNativeInterfaceIsImplemented_Implementation(uObject, TInterface) \
        assertConditionEndBracket()

#define assertNativeInterfaceIsImplemented_withBreak(uObject, TInterface) \
        assertNativeInterfaceIsImplemented_Implementation(uObject, TInterface) \
        assertConditionEndBracketWithBreak()

#define assertNativeInterfaceIsImplemented_withContinue(uObject, TInterface) \
        assertNativeInterfaceIsImplemented_Implementation(uObject, TInterface) \
        assertConditionEndBracketWithContinue()

// assertDataTableRowIsFound
#define assertDataTableRowIsFound_return(dataTable, row, rowName, ...) \
		assertDataTableRowIsFound_Implementation(dataTable, row, rowName)

#define assertDataTableRowIsFound_ignore(dataTable, row, rowName) \
		assertDataTableRowIsFound_Implementation_ignore(dataTable, row, rowName)

#define assertDataTableRowIsFound_withBreak(dataTable, row, rowName) \
		assertDataTableRowIsFound_Implementation_break(dataTable, row, rowName)

#define assertDataTableRowIsFound_withContinue(dataTable, row, rowName) \
		assertDataTableRowIsFound_Implementation_continue(dataTable, row, rowName)

// assertBlackboardKeyIsValid
#define assertBlackboardKeyIsValid_return(blackboard, keyName, ...)\
		assertBlackboardKeyIsValid_Implementation(blackboard, keyName)

#define assertBlackboardKeyIsValid_ignore(blackboard, keyName)\
		assertBlackboardKeyIsValid_Implementation_ignore(blackboard, keyName)

#define assertBlackboardKeyIsValid_withBreak(blackboard, keyName)\
		assertBlackboardKeyIsValid_Implementation_break(blackboard, keyName)

#define assertBlackboardKeyIsValid_withContinue(blackboard, keyName)\
		assertBlackboardKeyIsValid_Implementation_continue(blackboard, keyName)