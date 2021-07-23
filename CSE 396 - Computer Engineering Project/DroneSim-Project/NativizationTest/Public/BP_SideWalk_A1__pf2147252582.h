#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
class USplineMeshComponent;
class UBillboardComponent;
class UMaterialInterface;
#include "BP_SideWalk_A1__pf2147252582.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/ModularHouses/Blueprints/Road/BP_SideWalk_A1.BP_SideWalk_A1_C", OverrideNativeName="BP_SideWalk_A1_C"))
class ABP_SideWalk_A1_C__pf2147252582 : public AActor
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="Side"))
	USplineMeshComponent* bpv__Side__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="Billboard1"))
	UBillboardComponent* bpv__Billboard1__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="End Transform", Category="Default", Tooltip="Transform determines the start position/tangent for the spline", OverrideNativeName="End transform"))
	FTransform bpv__Endxtransform__pfT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Start Transform", Category="Default", Tooltip="Transform determines the end position/tangent for the spline", OverrideNativeName="Start transform"))
	FTransform bpv__Startxtransform__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Width", Category="Default", ClampMin="120", ClampMax="2000", OverrideNativeName="Width"))
	float bpv__Width__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="End", Category="Default", OverrideNativeName="End"))
	FVector bpv__End__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Float 1", Category="Default", OverrideNativeName="Float_1"))
	float bpv__Float_1__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Current", Category="Default", OverrideNativeName="Current"))
	float bpv__Current__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Target", Category="Default", OverrideNativeName="Target"))
	float bpv__Target__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="New Var 0", Category="Default", OverrideNativeName="NewVar_0"))
	float bpv__NewVar_0__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Element 0", Category="Default", OverrideNativeName="Element 0"))
	UMaterialInterface* bpv__Elementx0__pfT;
	ABP_SideWalk_A1_C__pf2147252582(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Comment="/**\t * Construction script, the place to spawn components and do other setup.\t * @note Name used in CreateBlueprint function\t */", DisplayName="Construction Script", ToolTip="Construction script, the place to spawn components and do other setup.@note Name used in CreateBlueprint function", Category, CppFromBpEvent, OverrideNativeName="UserConstructionScript"))
	virtual void bpf__UserConstructionScript__pf();
public:
};
