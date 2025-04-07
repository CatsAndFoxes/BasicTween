#pragma once

#include "CoreMinimal.h"
#include "Ease.h"
#include "TweenWorldSubSystem.h"
#include "Engine/World.h"

class SWidget;

template<typename T>
class FTween
{
public:
	explicit FTween(const TSharedPtr<SWidget> InWidget, TFunction<void(T)> InUpdateFunction, const float InDuration = 1.0f, const EasingFunction Ease = FEase::Linear(), const float InDelay = 0.0f) :
		Widget(InWidget),
		UnrealObject(nullptr),
		UpdateFunction(InUpdateFunction),
		Duration(InDuration),
		Easing(Ease),
		Delay(InDelay)
	{}

	explicit FTween(const TWeakObjectPtr<> InObject, TFunction<void(T)> InUpdateFunction, const float InDuration = 1.0f, const EasingFunction Ease = FEase::Linear(), const float InDelay = 0.0f) :
		Widget(nullptr),
		UnrealObject(InObject),
		UpdateFunction(InUpdateFunction),
		Duration(InDuration),
		Easing(Ease),
		Delay(InDelay)
	{}

	void Start()
	{
		Time = -Delay;
		if (Duration == 0.f)
		{
			CurrentValue = TargetValue;
			return;
		}
	
		if (Widget.IsValid())
		{

			auto Lambda = [&, *this](const float InCurrentTime, const double InDeltaTime) mutable
			{
				if (!Widget.IsValid())
				{
					return EActiveTimerReturnType::Stop;
				}
			
				return Update(InDeltaTime);
			};

			const FWidgetActiveTimerDelegate Fct = FWidgetActiveTimerDelegate::CreateLambda(Lambda);
			ActiveTimerHandle = Widget.Get()->RegisterActiveTimer(0.f, Fct);
		}
		else if (UnrealObject.IsValid())
		{
			if (const UWorld* World = UnrealObject->GetWorld())
			{
				UTweenWorldSubSystem* SubSystem = World->GetSubsystem<UTweenWorldSubSystem>();

				auto Lambda = [&, *this](const double InDeltaTime) mutable
				{
					if (!UnrealObject.IsValid())
					{
						return false;
					}
			
					return Update(InDeltaTime) != EActiveTimerReturnType::Stop;
				};
				
				SubSystem->AddDelegate(FTickDelegate::CreateLambda(Lambda));
			}
		}
	}
	
	void Stop()
	{
		if (Widget.IsValid() && ActiveTimerHandle.IsValid())
		{
			Widget->UnRegisterActiveTimer(ActiveTimerHandle.Pin().ToSharedRef());
		}
		else if (UnrealObject.IsValid())
		{
			Time = Duration;
		}
	}

	EActiveTimerReturnType Update(float InDeltaTime)
	{
		Time += InDeltaTime;

		if (Time < 0.f) 
		{
			return EActiveTimerReturnType::Continue;
		}

		if (Time > Duration) 
		{
			UponCompletion.ExecuteIfBound();
			CurrentValue = TargetValue;
			UpdateFunction(TargetValue);
			
			return EActiveTimerReturnType::Stop;
		}

		CurrentValue = StartValue + Easing(Time / Duration) * (TargetValue - StartValue);
		UpdateFunction(CurrentValue);
		
		return EActiveTimerReturnType::Continue;
	}

	FTween& OnComplete(FSimpleDelegate pDelegate) 
	{
		UponCompletion = pDelegate;
		return *this;
	}

	FTween<T>& From(T pFrom) 
	{
		StartValue = pFrom;
		return *this;
	}

	FTween<T>& To(T pTo) 
	{
		TargetValue = pTo;
		return *this;
	}

private:
	TSharedPtr<SWidget> Widget;
	TWeakObjectPtr<> UnrealObject;
	
	TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;
	FDelegateHandle DelegateHandle;

	T StartValue;
	T TargetValue;
	T CurrentValue;

	float Time = 0.f;

	TFunction<void(T)> UpdateFunction = [](T Value) {};
	float Duration;
	EasingFunction Easing = FEase::Linear();
	float Delay;

	FSimpleDelegate UponCompletion;
};


