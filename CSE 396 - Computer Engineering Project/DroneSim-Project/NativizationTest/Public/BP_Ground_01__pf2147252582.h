#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
class UMaterialInterface;
#include "BP_Ground_01__pf2147252582.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/ModularHouses/Blueprints/Road/BP_Ground_01.BP_Ground_01_C", OverrideNativeName="BP_Ground_01_C"))
class ABP_Ground_01_C__pf2147252582 : public AStaticMeshActor
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Lenght", Category="Default", ClampMax="120", OverrideNativeName="Lenght"))
	int32 bpv__Lenght__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Width", Category="Default", ClampMax="120", OverrideNativeName="Width"))
	int32 bpv__Width__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Material", Category="Default", OverrideNativeName="Material"))
	UMaterialInterface* bpv__Material__pf;
	ABP_Ground_01_C__pf2147252582(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Comment="/**\t * Construction script, the place to spawn components and do other setup.\t * @note Name used in CreateBlueprint function\t */", DisplayName="Construction Script", ToolTip="Construction script, the place to spawn components and do other setup.@note Name used in CreateBlueprint function", Category, CppFromBpEvent, OverrideNativeName="UserConstructionScript"))
	virtual void bpf__UserConstructionScript__pf();
public:
};
