#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
class USceneComponent;
class UStaticMesh;
#include "BP_Road_A1__pf2147252582.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/ModularHouses/Blueprints/Road/BP_Road_A1.BP_Road_A1_C", OverrideNativeName="BP_Road_A1_C"))
class ABP_Road_A1_C__pf2147252582 : public AActor
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="DefaultSceneRoot"))
	USceneComponent* bpv__DefaultSceneRoot__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Array", Category="Default", OverrideNativeName="Array"))
	TArray<UStaticMesh*> bpv__Array__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Select Mesh", Category="Default", UIMin="0", UIMax="1", OverrideNativeName="Select Mesh"))
	int32 bpv__SelectxMesh__pfT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Side 2", Category="Default", UIMin="0", UIMax="3", OverrideNativeName="Side_2"))
	int32 bpv__Side_2__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Array 2", Category="Default", OverrideNativeName="Array_2"))
	TArray<UStaticMesh*> bpv__Array_2__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Non Mirored ", Category="Default", OverrideNativeName="Non Mirored "))
	bool bpv__NonxMiroredx__pfTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Road End", Category="Default", OverrideNativeName="Road End"))
	bool bpv__RoadxEnd__pfT;
	ABP_Road_A1_C__pf2147252582(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Comment="/**\t * Construction script, the place to spawn components and do other setup.\t * @note Name used in CreateBlueprint function\t */", DisplayName="Construction Script", ToolTip="Construction script, the place to spawn components and do other setup.@note Name used in CreateBlueprint function", Category, CppFromBpEvent, OverrideNativeName="UserConstructionScript"))
	virtual void bpf__UserConstructionScript__pf();
public:
};
