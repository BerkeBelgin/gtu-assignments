#pragma once
#include "Blueprint/BlueprintSupport.h"
#include "DroneModeEnum__pf2264400134.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
class UCameraComponent;
class UStaticMeshComponent;
class UBP_PIDControllerComponent_C__pf2264400134;
class USkeletalMeshComponent;
class USpringArmComponent;
class UBP_DroneMotorComponent_C__pf2264400134;
class USerial;
class UPrimitiveComponent;
class AActor;
#include "BP_Drone__pf2264400134.generated.h"
UCLASS(config=Game, Blueprintable, BlueprintType, meta=(ReplaceConverted="/Game/PhysQuad/Blueprints/BP_Drone.BP_Drone_C", OverrideNativeName="BP_Drone_C"))
class ABP_Drone_C__pf2264400134 : public APawn
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="GimbalCamera"))
	UCameraComponent* bpv__GimbalCamera__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="PropBL"))
	UStaticMeshComponent* bpv__PropBL__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="PropFL"))
	UStaticMeshComponent* bpv__PropFL__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="PropFR"))
	UStaticMeshComponent* bpv__PropFR__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="PropBR"))
	UStaticMeshComponent* bpv__PropBR__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="YawStabilizationPID"))
	UBP_PIDControllerComponent_C__pf2264400134* bpv__YawStabilizationPID__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="RollStabilizationPID"))
	UBP_PIDControllerComponent_C__pf2264400134* bpv__RollStabilizationPID__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="PitchStabilizationPID"))
	UBP_PIDControllerComponent_C__pf2264400134* bpv__PitchStabilizationPID__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="AltStabilizationPID"))
	UBP_PIDControllerComponent_C__pf2264400134* bpv__AltStabilizationPID__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="DroneBody"))
	USkeletalMeshComponent* bpv__DroneBody__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="ThirdPersonCamera"))
	UCameraComponent* bpv__ThirdPersonCamera__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="SpringArm"))
	USpringArmComponent* bpv__SpringArm__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="MotorBR"))
	UBP_DroneMotorComponent_C__pf2264400134* bpv__MotorBR__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="MotorBL"))
	UBP_DroneMotorComponent_C__pf2264400134* bpv__MotorBL__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="MotorFR"))
	UBP_DroneMotorComponent_C__pf2264400134* bpv__MotorFR__pf;
	UPROPERTY(BlueprintReadWrite, NonTransactional, meta=(Category="Default", OverrideNativeName="MotorFL"))
	UBP_DroneMotorComponent_C__pf2264400134* bpv__MotorFL__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Motors", Category="Calculated", MultiLine="true", OverrideNativeName="Motors"))
	TArray<UBP_DroneMotorComponent_C__pf2264400134*> bpv__Motors__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Throttle Force Applied", Category="Calculated", MultiLine="true", OverrideNativeName="Last Throttle Force Applied"))
	float bpv__LastxThrottlexForcexApplied__pfTTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Pitch Force Applied", Category="Calculated", MultiLine="true", OverrideNativeName="Last Pitch Force Applied"))
	float bpv__LastxPitchxForcexApplied__pfTTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Roll Force Applied", Category="Calculated", MultiLine="true", OverrideNativeName="Last Roll Force Applied"))
	float bpv__LastxRollxForcexApplied__pfTTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Last Yaw Torque Applied", Category="Calculated", MultiLine="true", OverrideNativeName="Last Yaw Torque Applied"))
	float bpv__LastxYawxTorquexApplied__pfTTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Desired Altitude", Category="Calculated", MultiLine="true", OverrideNativeName="Desired Altitude"))
	float bpv__DesiredxAltitude__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Gravity Force", Category="Constants", MultiLine="true", tooltip="kg*cm/s^2", OverrideNativeName="Gravity Force"))
	float bpv__GravityxForce__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Speed", Category="Constants", MultiLine="true", tooltip="m/s", OverrideNativeName="Max Speed"))
	float bpv__MaxxSpeed__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Climb Speed", Category="Constants", MultiLine="true", tooltip="m/s", OverrideNativeName="Max Climb Speed"))
	float bpv__MaxxClimbxSpeed__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Descent Speed", Category="Constants", MultiLine="true", tooltip="-m/s (MUST be negative)", OverrideNativeName="Max Descent Speed"))
	float bpv__MaxxDescentxSpeed__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Angular Velocity", Category="Constants", MultiLine="true", tooltip="deg/s", OverrideNativeName="Max Angular Velocity"))
	float bpv__MaxxAngularxVelocity__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Tilt Angle", Category="Constants", MultiLine="true", tooltip="deg", OverrideNativeName="Max Tilt Angle"))
	float bpv__MaxxTiltxAngle__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Max Propeller RPS", Category="Constants", MultiLine="true", tooltip="rotations per second", OverrideNativeName="Max Propeller RPS"))
	float bpv__MaxxPropellerxRPS__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Pitch Roll Force Multiplier", Category="Constants", MultiLine="true", tooltip="kg*cm/s^2", OverrideNativeName="Pitch Roll Force Multiplier"))
	float bpv__PitchxRollxForcexMultiplier__pfTTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Counter Pitch Angle", Category="Calculated", MultiLine="true", OverrideNativeName="Counter Pitch Angle"))
	float bpv__CounterxPitchxAngle__pfTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Counter Roll Angle", Category="Calculated", MultiLine="true", OverrideNativeName="Counter Roll Angle"))
	float bpv__CounterxRollxAngle__pfTT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Gimbal Pitch", Category="Calculated", MultiLine="true", OverrideNativeName="Gimbal Pitch"))
	float bpv__GimbalxPitch__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Yaw Torque Force", Category="Constants", MultiLine="true", tooltip="kgfcm", OverrideNativeName="Yaw Torque Force"))
	float bpv__YawxTorquexForce__pfTT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Enabled", Category="Flags", MultiLine="true", tooltip="Are motors on?", OverrideNativeName="Enabled"))
	bool bpv__Enabled__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Crashed", Category="Flags", MultiLine="true", tooltip="Has crashed?", OverrideNativeName="Crashed"))
	bool bpv__Crashed__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Takeoff Performed", Category="Flags", MultiLine="true", tooltip="Did take off?", OverrideNativeName="Takeoff Performed"))
	bool bpv__TakeoffxPerformed__pfT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Landed", Category="Flags", MultiLine="true", tooltip="Has landed?", OverrideNativeName="Landed"))
	bool bpv__Landed__pf;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Drone Mode", Category="Flags", MultiLine="true", tooltip="Drone Flight Mode", OverrideNativeName="Drone Mode"))
	E__DroneModeEnum__pf bpv__DronexMode__pfT;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Joystick", Category="Default", MultiLine="true", OverrideNativeName="Joystick"))
	USerial* bpv__Joystick__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Hand Gesture", Category="Default", MultiLine="true", OverrideNativeName="HandGesture"))
	USerial* bpv__HandGesture__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Joystick Input", Category="Default", MultiLine="true", OverrideNativeName="JoystickInput"))
	TArray<float> bpv__JoystickInput__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Hand Gesture Input", Category="Default", MultiLine="true", OverrideNativeName="HandGestureInput"))
	TArray<float> bpv__HandGestureInput__pf;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Empty", Category="Default", MultiLine="true", OverrideNativeName="Empty"))
	TArray<float> bpv__Empty__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Loop_Counter_Variable"))
	int32 b0l__Temp_int_Loop_Counter_Variable__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Array_Index_Variable"))
	int32 b0l__Temp_int_Array_Index_Variable__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Loop_Counter_Variable_1"))
	int32 b0l__Temp_int_Loop_Counter_Variable_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Array_Index_Variable_1"))
	int32 b0l__Temp_int_Array_Index_Variable_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_InputActionEvent_Key_2"))
	FKey b0l__K2Node_InputActionEvent_Key_2__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Loop_Counter_Variable_2"))
	int32 b0l__Temp_int_Loop_Counter_Variable_2__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Array_Index_Variable_2"))
	int32 b0l__Temp_int_Array_Index_Variable_2__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Loop_Counter_Variable_3"))
	int32 b0l__Temp_int_Loop_Counter_Variable_3__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Array_Index_Variable_3"))
	int32 b0l__Temp_int_Array_Index_Variable_3__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_bool_Variable"))
	bool b0l__Temp_bool_Variable__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_int_Variable"))
	int32 b0l__Temp_int_Variable__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_bool_Variable_1"))
	bool b0l__Temp_bool_Variable_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_K2_SetActorLocation_SweepHitResult"))
	FHitResult b0l__CallFunc_K2_SetActorLocation_SweepHitResult__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_Event_DeltaSeconds"))
	float b0l__K2Node_Event_DeltaSeconds__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakVector_X"))
	float b0l__CallFunc_BreakVector_X__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakVector_Y"))
	float b0l__CallFunc_BreakVector_Y__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakVector_Z"))
	float b0l__CallFunc_BreakVector_Z__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_HitComponent"))
	UPrimitiveComponent* b0l__K2Node_ComponentBoundEvent_HitComponent__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherActor"))
	AActor* b0l__K2Node_ComponentBoundEvent_OtherActor__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_OtherComp"))
	UPrimitiveComponent* b0l__K2Node_ComponentBoundEvent_OtherComp__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_NormalImpulse"))
	FVector b0l__K2Node_ComponentBoundEvent_NormalImpulse__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_ComponentBoundEvent_Hit"))
	FHitResult b0l__K2Node_ComponentBoundEvent_Hit__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakRotator_Roll"))
	float b0l__CallFunc_BreakRotator_Roll__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakRotator_Pitch"))
	float b0l__CallFunc_BreakRotator_Pitch__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_BreakRotator_Yaw"))
	float b0l__CallFunc_BreakRotator_Yaw__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_InputActionEvent_Key_3"))
	FKey b0l__K2Node_InputActionEvent_Key_3__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_K2_SetWorldRotation_SweepHitResult"))
	FHitResult b0l__CallFunc_K2_SetWorldRotation_SweepHitResult__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Get_Axes_Throttle"))
	float b0l__CallFunc_Get_Axes_Throttle__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Get_Axes_Pitch"))
	float b0l__CallFunc_Get_Axes_Pitch__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Get_Axes_Roll"))
	float b0l__CallFunc_Get_Axes_Roll__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Get_Axes_Yaw"))
	float b0l__CallFunc_Get_Axes_Yaw__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Get_Axes_Gimbal"))
	float b0l__CallFunc_Get_Axes_Gimbal__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_K2_AddLocalRotation_SweepHitResult"))
	FHitResult b0l__CallFunc_K2_AddLocalRotation_SweepHitResult__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_K2_AddLocalRotation_SweepHitResult_1"))
	FHitResult b0l__CallFunc_K2_AddLocalRotation_SweepHitResult_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_K2_SetRelativeRotation_SweepHitResult"))
	FHitResult b0l__CallFunc_K2_SetRelativeRotation_SweepHitResult__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_OpenComPort_bOpened"))
	bool b0l__CallFunc_OpenComPort_bOpened__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_SwitchEnum_CmpSuccess"))
	bool b0l__K2Node_SwitchEnum_CmpSuccess__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_Event_EndPlayReason"))
	TEnumAsByte<EEndPlayReason::Type> b0l__K2Node_Event_EndPlayReason__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_OpenComPort_bOpened_1"))
	bool b0l__CallFunc_OpenComPort_bOpened_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Readln_bSuccess"))
	bool b0l__CallFunc_Readln_bSuccess__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_ParseIntoArray_ReturnValue"))
	TArray<FString> b0l__CallFunc_ParseIntoArray_ReturnValue__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Array_Get_Item"))
	FString b0l__CallFunc_Array_Get_Item__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_bool_Variable_2"))
	bool b0l__Temp_bool_Variable_2__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_InputActionEvent_Key_1"))
	FKey b0l__K2Node_InputActionEvent_Key_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Readln_bSuccess_1"))
	bool b0l__CallFunc_Readln_bSuccess_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_ParseIntoArray_ReturnValue_1"))
	TArray<FString> b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Array_Get_Item_1"))
	FString b0l__CallFunc_Array_Get_Item_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Array_Get_Item_2"))
	float b0l__CallFunc_Array_Get_Item_2__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="Temp_bool_Variable_3"))
	bool b0l__Temp_bool_Variable_3__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_SwitchEnum_CmpSuccess_1"))
	bool b0l__K2Node_SwitchEnum_CmpSuccess_1__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="CallFunc_Array_Get_Item_3"))
	float b0l__CallFunc_Array_Get_Item_3__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_InputActionEvent_Key"))
	FKey b0l__K2Node_InputActionEvent_Key__pf;
	UPROPERTY(Transient, DuplicateTransient, meta=(OverrideNativeName="K2Node_InputAxisEvent_AxisValue"))
	float b0l__K2Node_InputAxisEvent_AxisValue__pf;
	ABP_Drone_C__pf2264400134(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;
	static void __CustomDynamicClassInitialization(UDynamicClass* InDynamicClass);
	static void __StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	static void __StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad);
	void bpf__ExecuteUbergraph_BP_Drone__pf_0(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_1(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_2(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_3(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_4(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_5(int32 bpp__EntryPoint__pf);
	void bpf__ExecuteUbergraph_BP_Drone__pf_6(int32 bpp__EntryPoint__pf);
	UFUNCTION(meta=(OverrideNativeName="InpAxisEvt_Throttle_K2Node_InputAxisEvent_0"))
	virtual void bpf__InpAxisEvt_Throttle_K2Node_InputAxisEvent_0__pf(float bpp__AxisValue__pf);
	UFUNCTION(meta=(Comment="/** Event to notify blueprints this actor is being deleted or removed from a level. */", DisplayName="End Play", Keywords="delete", ToolTip="Event to notify blueprints this actor is being deleted or removed from a level.", CppFromBpEvent, OverrideNativeName="ReceiveEndPlay"))
	virtual void bpf__ReceiveEndPlay__pf(EEndPlayReason::Type bpp__EndPlayReason__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Switch Motors"))
	virtual void bpf__SwitchxMotors__pfT();
	UFUNCTION(meta=(OverrideNativeName="BndEvt__DroneBody_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature"))
	virtual void bpf__BndEvt__DroneBody_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature__pf(UPrimitiveComponent* bpp__HitComponent__pf, AActor* bpp__OtherActor__pf, UPrimitiveComponent* bpp__OtherComp__pf, FVector bpp__NormalImpulse__pf, FHitResult const& bpp__Hit__pf__const);
	UFUNCTION(meta=(Comment="/** Event called every frame, if ticking is enabled */", DisplayName="Tick", ToolTip="Event called every frame, if ticking is enabled", CppFromBpEvent, OverrideNativeName="ReceiveTick"))
	virtual void bpf__ReceiveTick__pf(float bpp__DeltaSeconds__pf);
	UFUNCTION(meta=(Comment="/** Event when play begins for this actor. */", DisplayName="BeginPlay", ToolTip="Event when play begins for this actor.", CppFromBpEvent, OverrideNativeName="ReceiveBeginPlay"))
	virtual void bpf__ReceiveBeginPlay__pf();
	UFUNCTION(meta=(OverrideNativeName="InpActEvt_Drone Mode Cycle_K2Node_InputActionEvent_0"))
	virtual void bpf__InpActEvt_DronexModexCycle_K2Node_InputActionEvent_0__pfTT(FKey bpp__Key__pf);
	UFUNCTION(meta=(OverrideNativeName="InpActEvt_Camera Switch_K2Node_InputActionEvent_1"))
	virtual void bpf__InpActEvt_CameraxSwitch_K2Node_InputActionEvent_1__pfT(FKey bpp__Key__pf);
	UFUNCTION(meta=(OverrideNativeName="InpActEvt_Motors_K2Node_InputActionEvent_2"))
	virtual void bpf__InpActEvt_Motors_K2Node_InputActionEvent_2__pf(FKey bpp__Key__pf);
	UFUNCTION(meta=(OverrideNativeName="InpActEvt_Reset_K2Node_InputActionEvent_3"))
	virtual void bpf__InpActEvt_Reset_K2Node_InputActionEvent_3__pf(FKey bpp__Key__pf);
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true", Comment="/**\t * Construction script, the place to spawn components and do other setup.\t * @note Name used in CreateBlueprint function\t */", DisplayName="Construction Script", ToolTip="Construction script, the place to spawn components and do other setup.@note Name used in CreateBlueprint function", Category, CppFromBpEvent, OverrideNativeName="UserConstructionScript"))
	virtual void bpf__UserConstructionScript__pf();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Handle Throttle"))
	virtual void bpf__HandlexThrottle__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Throttle"))
	virtual void bpf__Throttle__pf(float bpp__Force__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Altitude Stabilization"))
	virtual void bpf__AltitudexStabilization__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Limit Velocities"))
	virtual void bpf__LimitxVelocities__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Apply Forces"))
	virtual void bpf__ApplyxForces__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Pitch"))
	virtual void bpf__Pitch__pf(float bpp__Force__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Roll"))
	virtual void bpf__Roll__pf(float bpp__Force__pf);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Handle Pitch"))
	virtual void bpf__HandlexPitch__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Handle Roll"))
	virtual void bpf__HandlexRoll__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Handle Yaw"))
	virtual void bpf__HandlexYaw__pfT();
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Pitch Stabilization"))
	virtual void bpf__PitchxStabilization__pfT(float bpp__StabilizexatxAngle__pfTT, /*out*/ bool& bpp__AnglexReached__pfT);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Roll Stabilization"))
	virtual void bpf__RollxStabilization__pfT(float bpp__StabilizexatxAngle__pfTT, /*out*/ bool& bpp__AnglexReached__pfT);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Yaw Stabilization"))
	virtual void bpf__YawxStabilization__pfT(float bpp__DesiredxAngularxVelocity__pfTT);
	UFUNCTION(BlueprintCallable, meta=(Tooltip="Manual horizontal linear damping", Category, OverrideNativeName="Stop Drifting"))
	virtual void bpf__StopxDrifting__pfT();
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category, OverrideNativeName="Get Axes"))
	virtual void bpf__GetxAxes__pfT(/*out*/ float& bpp__Throttle__pf, /*out*/ float& bpp__Pitch__pf, /*out*/ float& bpp__Roll__pf, /*out*/ float& bpp__Yaw__pf, /*out*/ float& bpp__Gimbal__pf);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category, OverrideNativeName="Deadzone Axis"))
	virtual void bpf__DeadzonexAxis__pfT(float bpp__Axis__pf, float bpp__Deadzone__pf, /*out*/ float& bpp__ZonedxAxis__pfT);
	UFUNCTION(BlueprintCallable, meta=(Category, OverrideNativeName="Yaw"))
	virtual void bpf__Yaw__pf(float bpp__Torque__pf);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category, OverrideNativeName="Get Forward Velocity"))
	virtual void bpf__GetxForwardxVelocity__pfTT(/*out*/ float& bpp__Velocity__pf);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category, OverrideNativeName="Get Right Velocity"))
	virtual void bpf__GetxRightxVelocity__pfTT(/*out*/ float& bpp__Velocity__pf);
public:
};
