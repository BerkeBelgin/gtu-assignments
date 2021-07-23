#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
class UPrimitiveComponent;
#include "BP_DroneMotorComponent__pf2264400134.generated.h"
UCLASS(config=Engine, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/PhysQuad/Blueprints/BP_DroneMotorComponent.BP_DroneMotorComponent_C", OverrideNativeName="BP_DroneMotorComponent_C"))
class UBP_DroneMotorComponent_C__pf2264400134 : public USceneComponent
{
public:
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Force", Category="Default", MultiLine="true", BlueprintPrivate="true", OverrideNativeName="Force"))
	float bpv__Force__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Physics Body", Category="Default", MultiLine="true", BlueprintPrivate="true", OverrideNativeName="Physics Body"))
	UPrimitiveComponent* bpv__PhysicsxBody__pfT;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_AsPrimitive_Component"))
	UPrimitiveComponent* b0l__K2Node_DynamicCast_AsPrimitive_Component__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_DynamicCast_bSuccess"))
	bool b0l__K2Node_DynamicCast_bSuccess__pf;
	UBP_DroneMotorComponent_C__pf2264400134(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	void bpf__ExecuteUbergraph_BP_DroneMotorComponent__pf_0(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_DroneMotorComponent__pf_1(int32 bpp__EntryPoint__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Reset"))
	virtual void bpf__Reset__pf();
	UFUNCTION(meta=(Comment="/** \t * Blueprint implementable event for when the component is beginning play, called before its owning actor\'s BeginPlay\t * or when the component is dynamically created if the Actor has already BegunPlay. \t */", DisplayName="Begin Play", ToolTip="Blueprint implementable event for when the component is beginning play, called before its owning actor\'s BeginPlayor when the component is dynamically created if the Actor has already BegunPlay.", CppFromBpEvent, OverrideNativeName="ReceiveBeginPlay"))
	virtual void bpf__ReceiveBeginPlay__pf();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Add Force"))
	virtual void bpf__AddxForce__pfT(float bpp__Force__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Apply Force"))
	virtual void bpf__ApplyxForce__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Add Torque"))
	virtual void bpf__AddxTorque__pfT(FVector bpp__Torque__pf);
public:
};
