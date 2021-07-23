#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "BP_PIDControllerComponent__pf2264400134.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/PhysQuad/Blueprints/BP_PIDControllerComponent.BP_PIDControllerComponent_C", OverrideNativeName="BP_PIDControllerComponent_C"))
class UBP_PIDControllerComponent_C__pf2264400134 : public UActorComponent
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Gains", Category="Default", MultiLine="true", tooltip="PID gain values", OverrideNativeName="Gains"))
	FVector bpv__Gains__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Error", Category="Default", OverrideNativeName="LastError"))
	float bpv__LastError__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Integral", Category="Default", OverrideNativeName="LastIntegral"))
	float bpv__LastIntegral__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Output", Category="Default", OverrideNativeName="Output"))
	float bpv__Output__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Debug", Category="Default", MultiLine="true", tooltip="Output debug values to screen", OverrideNativeName="Debug"))
	bool bpv__Debug__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Debug Color", Category="Default", MultiLine="true", tooltip="Debug message color", OverrideNativeName="Debug Color"))
	FLinearColor bpv__DebugxColor__pfT;
	UBP_PIDControllerComponent_C__pf2264400134(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="PID"))
	virtual void bpf__PID__pf(float bpp__Target__pf, float bpp__Current__pf, float bpp__Min__pf, float bpp__Max__pf, /*out*/ float& bpp__Output__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Reset"))
	virtual void bpf__Reset__pf();
public:
};
