// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnitConverterAPI.generated.h"

/**
 * Unit Converter API for Blueprint.
 * Provides Miles, Feet, Centimeters conversions.
 */

UENUM(BlueprintType)
enum class EUnitType : uint8
{
    Miles        UMETA(DisplayName = "Miles"),
    Feet         UMETA(DisplayName = "Feet"),
    Centimeters  UMETA(DisplayName = "Centimeters"),
};

UCLASS()
class UNREALOOP_CALCULATOR_API UUnitConverterAPI : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Convert Value from 'From' unit to 'To' unit (enum-based). */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Units", DisplayName = "Convert Units")
    static double ConvertUnits(double Value, EUnitType From, EUnitType To);

    /**
     * Convenience variant: Convert by integer indices that match the enum order.
     * 0 = Miles, 1 = Feet, 2 = Centimeters
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Units", DisplayName = "Convert Units (By Index)")
    static double ConvertUnitsByIndex(double Value, int32 FromIndex, int32 ToIndex);

private:
    /** Returns how many centimeters == 1 unit for 'Unit'. */
    static bool UnitFactorToCm(EUnitType Unit, double& OutToCm);

    /** Bounds-checked helper for index -> enum mapping. */
    static bool IndexToUnit(int32 Index, EUnitType& OutUnit);
};
