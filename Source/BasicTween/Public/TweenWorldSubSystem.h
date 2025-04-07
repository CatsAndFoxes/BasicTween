#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "TweenWorldSubSystem.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FTickDelegate, float);

UCLASS()
class BASICTWEEN_API UTweenWorldSubSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	void AddDelegate(const FTickDelegate& Delegate);

private:
	TArray<FTickDelegate> Delegates;
};
