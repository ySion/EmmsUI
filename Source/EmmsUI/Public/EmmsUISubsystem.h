#pragma once
#include "Subsystems/WorldSubsystem.h"
#include "MMWidget.h"
#include "EmmsUISubsystem.generated.h"

#if WITH_EDITOR
class IAssetViewport;
#endif

USTRUCT()
struct FEmmsViewportOverlay
{
	GENERATED_BODY()

	UPROPERTY()
	UMMWidget* Widget = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UGameViewportClient> ViewportClient;

	UPROPERTY()
	uint64 LastDrawUITickCounter = 0;

#if WITH_EDITOR
	TWeakPtr<IAssetViewport> AssetViewport;
#endif
};

USTRUCT()
struct FEmmsPendingAssetLoad
{
	GENERATED_BODY()

	UPROPERTY()
	UObject* Asset = nullptr;

	UPROPERTY()
	bool bLoading = false;

	UPROPERTY()
	uint64 LastRequestedFrameCounter = 0;

	UPROPERTY()
	uint64 LastRequestedUITickCounter = 0;
};

UCLASS()
class UEmmsUISubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TMap<FName, FEmmsViewportOverlay> ViewportOverlays;

	UPROPERTY()
	TMap<FString, FEmmsPendingAssetLoad> PendingLoads;

	uint64 UITickCounter = 0;

	void RemoveOverlayWidget(FEmmsViewportOverlay Overlay);
	UObject* AsyncLoadAsset(const FString& AssetPath);

	virtual TStatId GetStatId() const override { return GetStatID(); }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual void Tick(float DeltaTime) override;
	virtual void Deinitialize() override;
};