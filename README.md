# 🚀 BasicTween: Simple, Powerful Tweening for Unreal Engine

**BasicTween** is a lightweight C++ animation library for Unreal Engine (no support for Blueprint), designed to simplify and streamline the creation of smooth animations, transitions, and effects across UI widgets and traditional engine objects. Whether you're animating UI components or in-game actors, BasicTween offers a concise and expressive API that reduces boilerplate code and enhances readability.

---

## ✨ Key Features:

- **Simple & Expressive API:** Quickly define animations with minimal setup.
- **Cross-Compatible:** Works seamlessly with both Slate UI widgets and traditional Unreal Engine actors.
- **Rich Easing Functions:** Offers numerous easing types (e.g., `SineOut`, `ElasticOut`, `BackOut`, `ExponentialOut`) to create natural, fluid animations.
- **Flexible Control:** Supports delays, chaining, and precise timing control for complex animation sequences.
- **Performance-Friendly:** Optimized to minimize overhead and ensure smooth runtime performance.

---

## 🎬 Example Applications:

### Actor Scale Animation

Animate the scale of an in-game actor (with a lambda):

```cpp
FTween<FVector>(TWeakObjectPtr<>(Actor),
  [Actor](FVector Value){
    Actor->SetActorScale3D(Value);
  },
  0.5f,
  FEase::ElasticOut()
)
.From(FVector(0.6f, 0.4f, 0.2f))
.To(FVector::OneVector)
.Start();
```

### UI Button Scale Animation

Animate button scaling for dynamic visual feedback:

```cpp
FTween<float>(Button, [&, Button](const float InScale) {
    const FVector2D Size = Button->GetDesiredSize();
    const FVector2D Translation = FVector2D((1.0f - InScale) * 0.5f * Size.X, (1.0f - InScale) * 0.5f * Size.Y);
    Button->SetRenderTransform(FSlateRenderTransform(FScale2D(InScale), Translation));
}, 0.25f, FEase::ExponentialOut(), Delay).From(0.3f).To(1.0f).Start();
```

### Dialog Panel Opening Effect

Create engaging opening animations for dialog panels:

```cpp
void SDialogPanel::Open()
{
  FTween TweenOpen = FTween(MainWidget, AnimateOpenClose(), 0.3f, FEase::BackOut());
  TweenOpen.From(FVector2D(0.3f, 0.f)).To(FVector2D(1.f, 1.f)).Start();
}


TFunction<void(FVector2D)> SDialogPanel::AnimateOpenClose()
{
	return [&](const FVector2D CurrentScale)
	{
		Size = MainWidget->GetDesiredSize();
		const FVector2D Translation = FVector2d((1.0f - CurrentScale.X) * 0.5f * Size.X, (1.0f - CurrentScale.X) * 0.5f * Size.Y);
		MainWidget->SetRenderTransform(FSlateRenderTransform(FScale2D(CurrentScale.X), Translation));
		MainWidget->SetRenderOpacity(CurrentScale.Y);
	};
}
```


### UI Icon Animation

Add subtle yet effective icon animations using sine easing:

```cpp
float FromScale = 1.0f;
TOptional<FSlateRenderTransform> LocalRenderTransform = GetRenderTransform();
if (LocalRenderTransform.IsSet()) {
    FromScale = LocalRenderTransform->GetMatrix().GetScale().GetVector().X;
}

FVector2D InSize = Box->GetCachedGeometry().GetLocalSize();

FTween<float>(Box, [&, InSize](const float InScale) {
    Box->SetRenderTransform(FSlateRenderTransform(FScale2D(InScale), 0.5f * InSize * (1.0f - InScale)));
}, 0.25f, FEase::SineOut()).From(FromScale).To(TargetScale).Start();
```

## 🛠️ Quick Start Guide:
To integrate BasicTween into your Unreal Engine project:

### Clone the Repository:

```
git clone https://github.com/CatsAndFoxes/BasicTween.git
```

### Include in Project:
Add the BasicTween module to your project's plugins folder.

### Activate Plugin:
In your Unreal Engine project settings, enable the BasicTween plugin.

### Include in Your Code:

```cpp
#include "BasicTween/Public/BasicTween.h"
```

Now, you're ready to easily craft engaging animations throughout your Unreal projects.

## 📃 Licensing:
BasicTween is released under the MIT License, freely available for personal and commercial use, modification, and redistribution.

