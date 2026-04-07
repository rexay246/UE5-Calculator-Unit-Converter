#include "UArithmeticAPIBPLibrary.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogArithmeticAPI, Log, All);

void* UArithmeticAPIBPLibrary::DLLHandle = nullptr;

UArithmeticAPIBPLibrary::CreateCalculatorFn		UArithmeticAPIBPLibrary::pCreateCalculator = nullptr;
UArithmeticAPIBPLibrary::DestroyCalculatorFn	UArithmeticAPIBPLibrary::pDestroyCalculator = nullptr;
UArithmeticAPIBPLibrary::SetOperationFn			UArithmeticAPIBPLibrary::pSetOperation = nullptr;
UArithmeticAPIBPLibrary::ComputeFn				UArithmeticAPIBPLibrary::pCompute = nullptr;

static void* BindExport(void* Dll, const TCHAR* Name)
{
	void* Addr = FPlatformProcess::GetDllExport(Dll, Name);
	if (!Addr)
	{
		UE_LOG(LogArithmeticAPI, Error, TEXT("Failed to bind export: %s"), Name);
	}
	return Addr;
}

bool UArithmeticAPIBPLibrary::EnsureLoaded()
{
	if (DLLHandle) return (pCreateCalculator && pDestroyCalculator && pSetOperation && pCompute);

	// Look in Project/Binaries/Win64/
	const FString DllPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries/Win64/ArithmeticAPI.dll"));
	DLLHandle = FPlatformProcess::GetDllHandle(*DllPath);
	if (!DLLHandle)
	{
		UE_LOG(LogArithmeticAPI, Error, TEXT("Could not load %s"), *DllPath);
		return false;
	}

	pCreateCalculator = reinterpret_cast<CreateCalculatorFn>(BindExport(DLLHandle, TEXT("CreateCalculator")));
	pDestroyCalculator = reinterpret_cast<DestroyCalculatorFn>(BindExport(DLLHandle, TEXT("DestroyCalculator")));
	pSetOperation = reinterpret_cast<SetOperationFn>(BindExport(DLLHandle, TEXT("SetOperation")));
	pCompute = reinterpret_cast<ComputeFn>(BindExport(DLLHandle, TEXT("Compute")));

	const bool ok = (pCreateCalculator && pDestroyCalculator && pSetOperation && pCompute);
	if (!ok)
	{
		UE_LOG(LogArithmeticAPI, Error, TEXT("ArithmeticAPI.dll missing one or more exports."));
	}
	return ok;
}

int64 UArithmeticAPIBPLibrary::CreateCalculator()
{
	if (!EnsureLoaded()) return 0;
	void* Ptr = pCreateCalculator ? pCreateCalculator() : nullptr;
	return static_cast<int64>(reinterpret_cast<intptr_t>(Ptr));
}

void UArithmeticAPIBPLibrary::DestroyCalculator(int64 Handle)
{
	if (!EnsureLoaded() || !Handle) return;
	void* Ptr = reinterpret_cast<void*>(static_cast<intptr_t>(Handle));
	pDestroyCalculator(Ptr);
}

void UArithmeticAPIBPLibrary::SetOperation(int64 Handle, EArithmeticOp Op)
{
	if (!EnsureLoaded() || !Handle) return;
	void* Ptr = reinterpret_cast<void*>(static_cast<intptr_t>(Handle));
	pSetOperation(Ptr, static_cast<int>(Op));
}

double UArithmeticAPIBPLibrary::Compute(int64 Handle, double A, double B)
{
	if (!EnsureLoaded() || !Handle) return 0.0;
	void* Ptr = reinterpret_cast<void*>(static_cast<intptr_t>(Handle));
	return pCompute(Ptr, A, B);
}