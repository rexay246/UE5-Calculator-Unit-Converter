// Fill out your copyright notice in the Description page of Project Settings.

// UnitConverterAPI.cpp

#include "UnitConverterAPI.h"
#include <limits> // for std::numeric_limits

// Returns: how many centimeters == 1 unit of 'Unit'
bool UUnitConverterAPI::UnitFactorToCm(EUnitType Unit, double& OutToCm)
{
    switch (Unit)
    {
    case EUnitType::Miles:
        OutToCm = 160934.4;
        return true;

    case EUnitType::Feet:
        OutToCm = 30.48;
        return true;

    case EUnitType::Centimeters:
        OutToCm = 1;
        return true;

    default:
        // (optional) #TODO: log a warning for unknown unit
        return false;
    }
}

// Map UI indices -> enum (must match Combo order: 0=Miles, 1=Feet, 2=Centimeters)
bool UUnitConverterAPI::IndexToUnit(int32 Index, EUnitType& OutUnit)
{
    switch (Index)
    {
    case 0:
        OutUnit = EUnitType::Miles;
        return true;

    case 1:
        OutUnit = EUnitType::Feet;
        return true;

    case 2:
        OutUnit = EUnitType::Centimeters;
        return true;

    default:
        return false; // unknown index
    }
}

// Enum-based conversion
double UUnitConverterAPI::ConvertUnits(double Value, EUnitType From, EUnitType To)
{
    double FromFactorCm = 0.0;
    double ToFactorCm = 0.0;

    if (!UnitFactorToCm(From, FromFactorCm) || !UnitFactorToCm(To, ToFactorCm))
    {
        // return if unknown unit is requested
        return std::numeric_limits<double>::quiet_NaN();
    }
    double result = Value * FromFactorCm / ToFactorCm;
    return result;
}

// Index-based conversion (Blueprint will call this)
double UUnitConverterAPI::ConvertUnitsByIndex(double Value, int32 FromIndex, int32 ToIndex)
{
    EUnitType FromUnit, ToUnit;

    if (!IndexToUnit(FromIndex, FromUnit) || !IndexToUnit(ToIndex, ToUnit))
    {
        // return if unknown index
        return std::numeric_limits<double>::quiet_NaN();
    }
    return ConvertUnits(Value, FromUnit, ToUnit);
}

