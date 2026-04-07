// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UArithmeticAPIBPLibrary.generated.h"

/** Matches the C-API: OperationKind { Add=0, Sub=1, Mul=2, Div=3 } */
UENUM(BlueprintType)
enum class EArithmeticOp : uint8
{
	Add = 0 UMETA(DisplayName = "Add"),
	Sub = 1 UMETA(DisplayName = "Sub"),
	Mul = 2 UMETA(DisplayName = "Multiply"),
	Div = 3 UMETA(DisplayName = "Divide")
};

/** Blueprint-callable glue to ArithmeticAPI.dll */
UCLASS()
class UNREALOOP_CALCULATOR_API UArithmeticAPIBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Loads the DLL on first use if needed, returns an opaque handle as int64 (store in a Blueprint Integer64 variable). */
	UFUNCTION(BlueprintCallable, Category = "ArithmeticAPI")
	static int64 CreateCalculator();

	UFUNCTION(BlueprintCallable, Category = "ArithmeticAPI")
	static void DestroyCalculator(int64 Handle);

	UFUNCTION(BlueprintCallable, Category = "ArithmeticAPI")
	static void SetOperation(int64 Handle, EArithmeticOp Op);

	/** Computes using current Op; returns NaN on divide-by-zero. */
	UFUNCTION(BlueprintCallable, Category = "ArithmeticAPI")
	static double Compute(int64 Handle, double A, double B);

private:
	static bool EnsureLoaded(); // loads/binds once

	// DLL handle and C function pointers
	static void* DLLHandle;

	typedef void* (__cdecl* CreateCalculatorFn)();
	typedef void(__cdecl* DestroyCalculatorFn)(void*);
	typedef void(__cdecl* SetOperationFn)(void*, int);
	typedef int(__cdecl* GetOperationFn)(void*);
	typedef double(__cdecl* ComputeFn)(void*, double, double);

	static CreateCalculatorFn pCreateCalculator;
	static DestroyCalculatorFn pDestroyCalculator;
	static SetOperationFn     pSetOperation;
	static ComputeFn          pCompute;
};
