#pragma once

#include "CoreMinimal.h"

UENUM()
enum class Ease
{
    Linear,
    Stepped,
    QuadIn,
    QuadOut,
    QuadInOut,
    CubicIn,
    CubicOut,
    CubicInOut,
    QuarticIn,
    QuarticOut,
    QuarticInOut,
    QuinticIn,
    QuinticOut,
    QuinticInOut,
    SineIn,
    SineOut,
    SineInOut,
    ExponentialIn,
    ExponentialOut,
    ExponentialInOut,
    CircularIn,
    CircularOut,
    CircularInOut,
    BounceIn,
    BounceOut,
    BounceInOut,
    ElasticIn,
    ElasticOut,
    ElasticInOut,
    BackIn,
    BackOut,
    BackInOut
};

typedef TFunction<float(const float)> EasingFunction;

class FEase
{
public:
	static EasingFunction GetEaseFunction(const Ease Type)
    {
		switch (Type)
	    {
            case Ease::Linear: return Linear();
            case Ease::QuadIn: return PowIn(2.0f);
            case Ease::QuadOut: return PowOut(2.0f);
            case Ease::QuadInOut: return PowInOut(2.0f);
            case Ease::CubicIn: return PowIn(3.0f);
            case Ease::CubicOut: return PowOut(3.0f);
            case Ease::CubicInOut: return PowInOut(3.0f);
            case Ease::QuarticIn: return PowIn(4.0f);
            case Ease::QuarticOut: return PowOut(4.0f);
            case Ease::QuarticInOut: return PowInOut(4.0f);
            case Ease::QuinticIn: return PowIn(5.0f);
            case Ease::QuinticOut: return PowOut(5.0f);
            case Ease::QuinticInOut: return PowInOut(5.0f);
            case Ease::SineIn: return SineIn();
            case Ease::SineOut: return SineOut();
            case Ease::SineInOut: return SineInOut();
            case Ease::ExponentialIn: return ExponentialIn();
            case Ease::ExponentialOut: return ExponentialOut();
            case Ease::ExponentialInOut: return ExponentialInOut();
            case Ease::CircularIn: return CircularIn();
            case Ease::CircularOut: return CircularOut();
            case Ease::CircularInOut: return CircularInOut();
            case Ease::BounceIn: return BounceIn();
            case Ease::BounceOut: return BounceOut();
            case Ease::BounceInOut: return BounceInOut();
            case Ease::ElasticIn: return ElasticIn();
            case Ease::ElasticOut: return ElasticOut();
            case Ease::ElasticInOut: return ElasticInOut();
            case Ease::BackIn: return BackIn();
            case Ease::BackOut: return BackOut();
            case Ease::BackInOut: return BackInOut();
            default: return Linear();
		}
	}

    FORCEINLINE static EasingFunction Linear()
    {
        return [](const float Alpha) { return Alpha; };
	}

    FORCEINLINE static EasingFunction PowIn(float Pow) 
    {
        return [Pow](const float Alpha) { return FMath::Pow(Alpha, Pow); };
	}

    FORCEINLINE static EasingFunction PowOut(float Pow) 
    {
        return [Pow](const float Alpha) { return 1.0f - FMath::Pow(1.0f - Alpha, Pow); };
    }

    FORCEINLINE static EasingFunction PowInOut(float Pow) 
    {
        return [Pow](const float Alpha) 
        {
            float Value = 2.f * Alpha;
            if ((Value *= 2.0f) < 1.0f)
            {
                return 0.5f * FMath::Pow(Value, Pow);
            }

            return 1.0f - 0.5f * FMath::Abs(FMath::Pow(2.0f - Value, Pow));
        };
	}

    FORCEINLINE static EasingFunction SineIn() 
    {
        return [](const float Alpha) 
        {
            return 1.0f - FMath::Cos(Alpha * HALF_PI);
        };
    }

    FORCEINLINE static EasingFunction SineOut() 
    {
        return [](const float Alpha) 
        {
            return FMath::Sin(Alpha * HALF_PI);
        };
    }

    FORCEINLINE static EasingFunction SineInOut() 
    {
        return [](const float Alpha) 
        {
            return -0.5f * (FMath::Cos(PI * Alpha) - 1.f);
        };
    }

    FORCEINLINE static EasingFunction ElasticIn(float Amplitude = 1.f, float Period = 0.3f) 
    {
        return [Amplitude, Period](const float Alpha) 
        {
            if (Alpha <= 0.f)
            {
                return 0.f;
            }
            
            if (Alpha >= 1.f)
            {
                return 1.f;
            }
            
            const float S = Period / TWO_PI * FMath::Asin(1.0f / Amplitude);
            const float Value = Alpha - 1.0f;
            return -(Amplitude * FMath::Pow(2.0f, 10.0f * Value) * FMath::Sin((Value - S) * TWO_PI / Period));
        };
    }

    FORCEINLINE static EasingFunction ElasticOut(float Amplitude = 1.f, float Period = 0.3f) 
    {
        return [Amplitude, Period](const float Alpha) 
        {
            if (Alpha <= 0.f)
            {
                return 0.f;
            }
            
            if (Alpha >= 1.f)
            {
                return 1.f;
            }
            
            const float S = Period / TWO_PI * FMath::Asin(1.0f / Amplitude);
            return Amplitude * FMath::Pow(2.0f, -10.0f * Alpha) * FMath::Sin((Alpha - S) * TWO_PI / Period) + 1.0f;
        };
    }

    FORCEINLINE static EasingFunction ElasticInOut(float Amplitude = 1.f, float Period = 0.45f) 
    {
        return [Amplitude, Period](const float Alpha) 
        {
            if (Alpha <= 0.f)
            {
                return 0.f;
            }
            
            if (Alpha >= 1.f)
            {
                return 1.f;
            }

            const float S = Period / (TWO_PI) * FMath::FastAsin(1.f / Amplitude);
            const float ModifiedAlpha = Alpha * 2.f;
        
            if (ModifiedAlpha < 1.f)
            {
                return -0.5f * (Amplitude * FMath::Pow(2.f, 10.f * (ModifiedAlpha - 1.f)) * FMath::Sin((ModifiedAlpha - 1.f - S) * (TWO_PI) / Period));
            }
            
            return Amplitude * FMath::Pow(2.f, -10.f * (ModifiedAlpha - 1.f)) * FMath::Sin((ModifiedAlpha - 1.f - S) * (TWO_PI) / Period) * 0.5f + 1.f;
        };
    }

    FORCEINLINE static EasingFunction ExponentialIn() 
    {
        return [](const float Alpha) { return FMath::Pow(2.f, 10.f * (Alpha - 1.f)); };
    }

    FORCEINLINE static EasingFunction ExponentialOut() 
    {
        return [](const float Alpha) { return 1.f - FMath::Pow(2.f, -10.f * Alpha); };
    }

    FORCEINLINE static EasingFunction ExponentialInOut() 
    {
        return [](const float Alpha) {
            if (Alpha < 0.5f)
            {
                return FMath::Pow(2.0f, 20.0f * Alpha - 10.0f) * 0.5f;
            }

            return 1.0f - FMath::Pow(2.0f, -20.0f * Alpha + 10.0f) * 0.5f;
        };
    }

    FORCEINLINE static EasingFunction CircularIn() 
    {
        return [](const float Alpha) 
        {
            return -(FMath::Sqrt(1.f - FMath::Square(Alpha)) - 1.f);
        };
    }

    FORCEINLINE static EasingFunction CircularOut() 
    {
        return [](const float Alpha) 
        {
            return FMath::Sqrt(1.f - FMath::Square(Alpha));
        };
    }

    FORCEINLINE static EasingFunction CircularInOut() 
    {
        return [](const float Alpha) 
        {
            float Value = 2.f * Alpha;
            if (Value < 1.0f)
            {
                return 0.5f * FMath::Sqrt(1.f - FMath::Square(Value)) - 1.f;
            }
            
            Value -= 2.f;
            return 0.5f * (FMath::Sqrt(1.f - FMath::Square(Value)) + 1.f);
        };
    }

private:
    FORCEINLINE static float Bounce(float Alpha) 
    {
        if (Alpha < 1.f / 2.75f) 
        {
            return 7.5625f * FMath::Square(Alpha);
        }
        
        if (Alpha < 2.f / 2.75f) 
        {
            Alpha -= 1.5f / 2.75f;
            return 7.5625f * FMath::Square(Alpha) + 0.75f;
        }
        
        if (Alpha < 2.5 / 2.75) 
        {
            Alpha -= 2.25f / 2.75f;
            return 7.5625f * FMath::Square(Alpha) + 0.9375f;
        }
        
        Alpha -= 2.625f / 2.75f;
        return 7.5625f * FMath::Square(Alpha) + 0.984375f;
    }

public:
    FORCEINLINE static EasingFunction BounceIn() 
    {
        return [](const float Alpha) { return Bounce(1.f - Alpha); }; 
    }

    FORCEINLINE static EasingFunction BounceOut() 
    {
        return [](const float Alpha) { return Bounce(Alpha); };
    }

    FORCEINLINE static EasingFunction BounceInOut() 
    {
        return [](const float Alpha) { return 0.5 * (Alpha < 0.5 ? Bounce(1.f - Alpha) : Bounce(Alpha)); };
    }

    FORCEINLINE static EasingFunction BackIn(float Amount = 1.5f) 
    {
        return [Amount](const float Alpha) 
        {
            return Alpha * Alpha * ((Amount + 1.0f) * Alpha - Amount);
        };
    }

    FORCEINLINE static EasingFunction BackOut(float Amount = 1.5f) 
    {
        return [Amount](const float Alpha) 
        {
            const float Value = Alpha - 1.0f;
            return Value * Value * ((Amount + 1.0f) * Value + Amount) + 1.0f;
        };
    }

    FORCEINLINE static EasingFunction BackInOut(float Amount = 1.5f) 
    {
        Amount *= 1.525;
        return [Amount](const float Alpha) 
        {
            float Value = Alpha * 2.f;
            if (Value < 1.0f)
            {
                return 0.5f * (Value * Value * ((Amount + 1.0f) * Value - Amount));
            }

            Value -= 2.0f;
            return 0.5f * (Value * Value * ((Amount + 1.0f) * Value + Amount) + 2.0f);
        };
    }
};
