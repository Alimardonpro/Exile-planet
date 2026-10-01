// Copyright Exile Planet. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExilePlayerController.generated.h"

class UExileHUDWidget;

/**
 * Custom player controller managing UI overlays, input states, and vehicle/character possession transitions.
 */
UCLASS()
class EXILEPLANET_API AExilePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AExilePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	/** Active HUD widget instance */
	UFUNCTION(BlueprintPure, Category = "Exile|UI")
	UExileHUDWidget* GetHUDWidget() const { return ActiveHUDWidget; }

	/** Toggle UI mouse cursor for menus or interaction panels */
	UFUNCTION(BlueprintCallable, Category = "Exile|Input")
	void SetUIMode(bool bEnableUI);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Exile|UI")
	TSubclassOf<UExileHUDWidget> HUDWidgetClass;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Exile|UI")
	TObjectPtr<UExileHUDWidget> ActiveHUDWidget;
};
