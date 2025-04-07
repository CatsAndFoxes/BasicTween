#include "TweenWorldSubSystem.h"

void UTweenWorldSubSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 Index = Delegates.Num() - 1; Index >= 0; --Index)
	{
		const bool bContinue = Delegates[Index].Execute(DeltaTime);
		if (!bContinue)
		{
			Delegates.RemoveAt(Index);
		}
	}
}

TStatId UTweenWorldSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(TweenWorldSubSystem, STATGROUP_Tickables);
}

void UTweenWorldSubSystem::AddDelegate(const FTickDelegate& Delegate)
{
	Delegates.Add(Delegate);
}
