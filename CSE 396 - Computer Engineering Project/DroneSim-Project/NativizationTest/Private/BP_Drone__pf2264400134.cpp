#include "DroneSim.h"
#include "BP_Drone__pf2264400134.h"
#include "GeneratedCodeHelpers.h"
#include "Runtime/Engine/Classes/Engine/InputAxisDelegateBinding.h"
#include "Runtime/Engine/Classes/Engine/InputActionDelegateBinding.h"
#include "Runtime/Engine/Classes/Engine/ComponentDelegateBinding.h"
#include "Runtime/Engine/Classes/Engine/SimpleConstructionScript.h"
#include "Runtime/Engine/Classes/Engine/SCS_Node.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SkinnedMeshComponent.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineBaseTypes.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Runtime/Engine/Classes/Engine/NetSerialization.h"
#include "Runtime/PhysicsCore/Public/PhysicalMaterials/PhysicalMaterial.h"
#include "Runtime/PhysicsCore/Public/PhysicsSettingsEnums.h"
#include "Runtime/PhysicsCore/Public/PhysicalMaterials/PhysicalMaterialPropertyBase.h"
#include "Runtime/PhysicsCore/Public/Chaos/ChaosEngineInterface.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/NavMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/MovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PhysicsVolume.h"
#include "Runtime/Engine/Classes/GameFramework/Volume.h"
#include "Runtime/Engine/Classes/Engine/Brush.h"
#include "Runtime/Engine/Classes/Components/BrushComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BodySetup.h"
#include "Runtime/PhysicsCore/Public/BodySetupCore.h"
#include "Runtime/PhysicsCore/Public/BodySetupEnums.h"
#include "Runtime/Engine/Classes/PhysicsEngine/AggregateGeom.h"
#include "Runtime/Engine/Classes/PhysicsEngine/SphereElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/ShapeElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BoxElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/SphylElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/ConvexElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/TaperedCapsuleElem.h"
#include "Runtime/Engine/Classes/PhysicsEngine/BodyInstance.h"
#include "Runtime/PhysicsCore/Public/BodyInstanceCore.h"
#include "Runtime/Engine/Classes/Engine/BrushBuilder.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationTypes.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"
#include "Runtime/Engine/Classes/GameFramework/Info.h"
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Engine/StreamableRenderAsset.h"
#include "Runtime/Engine/Classes/Engine/TextureDefines.h"
#include "Runtime/Engine/Public/PerPlatformProperties.h"
#include "Runtime/Engine/Classes/Engine/AssetUserData.h"
#include "Runtime/Engine/Classes/Interfaces/Interface_AssetUserData.h"
#include "Runtime/Engine/Classes/EditorFramework/AssetImportData.h"
#include "Runtime/Engine/Classes/GameFramework/LocalMessage.h"
#include "Runtime/Engine/Classes/GameFramework/OnlineReplStructs.h"
#include "Runtime/CoreUObject/Public/UObject/CoreOnline.h"
#include "Runtime/Engine/Classes/GameFramework/EngineMessage.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavAgentInterface.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "Runtime/AIModule/Classes/AIResourceInterface.h"
#include "Runtime/GameplayTasks/Classes/GameplayTaskResource.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationData.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationDataInterface.h"
#include "Runtime/Engine/Classes/AI/Navigation/PathFollowingAgentInterface.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTCompositeNode.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTNode.h"
#include "Runtime/GameplayTasks/Classes/GameplayTaskOwnerInterface.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTTaskNode.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTService.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTAuxiliaryNode.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTDecorator.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardAssetProvider.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraph.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphSchema.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphNode.h"
#include "Runtime/Engine/Classes/EdGraph/EdGraphPin.h"
#include "Runtime/Engine/Classes/Engine/Blueprint.h"
#include "Runtime/GameplayTasks/Classes/GameplayTask.h"
#include "Runtime/NavigationSystem/Public/NavFilters/NavigationQueryFilter.h"
#include "Runtime/NavigationSystem/Public/NavAreas/NavArea.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavAreaBase.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISense.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h"
#include "Runtime/AIModule/Classes/AISubsystem.h"
#include "Runtime/AIModule/Classes/AISystem.h"
#include "Runtime/Engine/Classes/AI/AISystemBase.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeManager.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryManager.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryOption.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryGenerator.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryNode.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/Items/EnvQueryItemType.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryTest.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h"
#include "Runtime/AIModule/Classes/DataProviders/AIDataProvider.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EQSQueryResultSourceInterface.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryContext.h"
#include "Runtime/AIModule/Classes/Blueprint/AIAsyncTaskBlueprintProxy.h"
#include "Runtime/AIModule/Classes/AITypes.h"
#include "Runtime/AIModule/Classes/HotSpots/AIHotSpotManager.h"
#include "Runtime/AIModule/Classes/Navigation/NavLocalGridManager.h"
#include "Runtime/AIModule/Classes/Perception/AISenseEvent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig.h"
#include "Runtime/AIModule/Classes/Actions/PawnActionsComponent.h"
#include "Runtime/AIModule/Classes/Actions/PawnAction.h"
#include "Runtime/GameplayTasks/Classes/GameplayTasksComponent.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionListenerInterface.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "Runtime/Engine/Public/VisualLogger/VisualLoggerDebugSnapshotInterface.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Camera/PlayerCameraManager.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Widget.h"
#include "Runtime/UMG/Public/Components/Visual.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Runtime/UMG/Public/Slate/WidgetTransform.h"
#include "Runtime/SlateCore/Public/Types/SlateEnums.h"
#include "Runtime/SlateCore/Public/Input/NavigationReply.h"
#include "Runtime/SlateCore/Public/Layout/Clipping.h"
#include "Runtime/SlateCore/Public/Layout/Geometry.h"
#include "Runtime/SlateCore/Public/Input/Events.h"
#include "Runtime/SlateCore/Public/Styling/SlateColor.h"
#include "Runtime/SlateCore/Public/Styling/SlateBrush.h"
#include "Runtime/SlateCore/Public/Layout/Margin.h"
#include "Runtime/UMG/Public/Components/PanelWidget.h"
#include "Runtime/UMG/Public/Components/PanelSlot.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/Engine/Classes/Engine/Player.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/ScriptViewportClient.h"
#include "Runtime/Engine/Classes/Engine/Console.h"
#include "Runtime/Engine/Classes/Engine/DebugDisplayProperty.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/WorldSettings.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemConfig.h"
#include "Runtime/Engine/Classes/GameFramework/DefaultPhysicsVolume.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsCollisionHandler.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"
#include "Runtime/Engine/Classes/Sound/SoundClass.h"
#include "Runtime/Engine/Classes/Sound/SoundModulationDestination.h"
#include "Runtime/AudioExtensions/Public/IAudioModulation.h"
#include "Runtime/Engine/Classes/Sound/AudioOutputTarget.h"
#include "Runtime/Engine/Classes/Sound/SoundWaveLoadingBehavior.h"
#include "Runtime/Engine/Classes/Sound/SoundSubmix.h"
#include "Runtime/Engine/Classes/Sound/SoundSubmixSend.h"
#include "Runtime/Engine/Classes/Sound/SoundWave.h"
#include "Runtime/AudioPlatformConfiguration/Public/AudioCompressionSettings.h"
#include "Runtime/Engine/Classes/Sound/SoundGroups.h"
#include "Runtime/Engine/Classes/Engine/CurveTable.h"
#include "Runtime/Engine/Classes/Sound/SoundEffectSubmix.h"
#include "Runtime/Engine/Classes/Sound/SoundEffectPreset.h"
#include "Runtime/AudioExtensions/Public/ISoundfieldFormat.h"
#include "Runtime/Engine/Classes/Sound/SoundMix.h"
#include "Runtime/Engine/Classes/Sound/SoundConcurrency.h"
#include "Runtime/Engine/Classes/Sound/SoundAttenuation.h"
#include "Runtime/Engine/Classes/Engine/Attenuation.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "Runtime/Engine/Classes/Curves/RichCurve.h"
#include "Runtime/Engine/Classes/Curves/RealCurve.h"
#include "Runtime/Engine/Classes/Curves/IndexedCurve.h"
#include "Runtime/Engine/Classes/Curves/KeyHandle.h"
#include "Runtime/Engine/Classes/Curves/CurveBase.h"
#include "Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h"
#include "Runtime/Engine/Classes/Sound/SoundEffectSource.h"
#include "Runtime/Engine/Classes/Sound/SoundSourceBusSend.h"
#include "Runtime/Engine/Classes/Sound/SoundSourceBus.h"
#include "Runtime/Engine/Classes/Sound/AudioBus.h"
#include "Runtime/Engine/Classes/GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/GameFramework/GameSession.h"
#include "Runtime/Engine/Classes/GameFramework/GameStateBase.h"
#include "Runtime/Engine/Classes/GameFramework/SpectatorPawn.h"
#include "Runtime/Engine/Classes/GameFramework/DefaultPawn.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"
#include "Runtime/Engine/Classes/PhysicalMaterials/PhysicalMaterialMask.h"
#include "Runtime/Engine/Classes/Materials/MaterialLayersFunctions.h"
#include "Runtime/Engine/Classes/Materials/MaterialFunctionInterface.h"
#include "Runtime/Engine/Classes/EditorFramework/ThumbnailInfo.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Materials/MaterialExpression.h"
#include "Runtime/Engine/Classes/Materials/MaterialFunction.h"
#include "Runtime/Engine/Classes/Materials/MaterialExpressionComment.h"
#include "Runtime/Engine/Classes/Materials/MaterialExpressionMaterialFunctionCall.h"
#include "Runtime/Engine/Classes/Materials/MaterialExpressionFunctionInput.h"
#include "Runtime/Engine/Classes/Materials/MaterialExpressionFunctionOutput.h"
#include "Runtime/Engine/Public/MaterialShared.h"
#include "Runtime/Engine/Classes/Engine/BlendableInterface.h"
#include "Runtime/Engine/Public/MaterialCachedData.h"
#include "Runtime/Engine/Classes/Engine/Font.h"
#include "Runtime/Engine/Classes/Engine/FontImportOptions.h"
#include "Runtime/SlateCore/Public/Fonts/CompositeFont.h"
#include "Runtime/SlateCore/Public/Fonts/FontBulkData.h"
#include "Runtime/SlateCore/Public/Fonts/FontProviderInterface.h"
#include "Runtime/Engine/Classes/VT/RuntimeVirtualTexture.h"
#include "Runtime/Engine/Public/VT/RuntimeVirtualTextureEnum.h"
#include "Runtime/Engine/Classes/VT/VirtualTexture.h"
#include "Runtime/Engine/Classes/Curves/CurveLinearColor.h"
#include "Runtime/Engine/Classes/Curves/CurveLinearColorAtlas.h"
#include "Runtime/Engine/Classes/Materials/MaterialParameterCollection.h"
#include "Runtime/Landscape/Classes/LandscapeGrassType.h"
#include "Runtime/Engine/Classes/Engine/SubsurfaceProfile.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"
#include "Runtime/StaticMeshDescription/Public/StaticMeshDescription.h"
#include "Runtime/MeshDescription/Public/MeshDescriptionBase.h"
#include "Runtime/MeshDescription/Public/MeshTypes.h"
#include "Runtime/Engine/Public/Components.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavCollisionBase.h"
#include "Runtime/Engine/Classes/Interfaces/Interface_CollisionDataProvider.h"
#include "Runtime/Engine/Classes/Engine/MeshMerging.h"
#include "Runtime/Engine/Classes/Engine/TextureStreamingTypes.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"
#include "Runtime/Engine/Classes/GameFramework/SpectatorPawnMovement.h"
#include "Runtime/Engine/Classes/GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "Runtime/Engine/Classes/Debug/ReporterGraph.h"
#include "Runtime/Engine/Classes/Debug/ReporterBase.h"
#include "Runtime/Engine/Classes/GameFramework/DebugTextInfo.h"
#include "Runtime/Engine/Classes/Engine/ServerStatReplicator.h"
#include "Runtime/Engine/Classes/GameFramework/GameNetworkManager.h"
#include "Runtime/Engine/Classes/Sound/ReverbSettings.h"
#include "Runtime/Engine/Classes/Sound/ReverbEffect.h"
#include "Runtime/Engine/Classes/Sound/AudioVolume.h"
#include "Runtime/Engine/Classes/Engine/NetConnection.h"
#include "Runtime/Engine/Classes/Engine/ChildConnection.h"
#include "Runtime/Engine/Classes/Engine/PackageMapClient.h"
#include "Runtime/Engine/Classes/Engine/NetDriver.h"
#include "Runtime/Engine/Classes/Engine/Channel.h"
#include "Runtime/Engine/Classes/Engine/ReplicationDriver.h"
#include "Runtime/Engine/Classes/Engine/BookmarkBase.h"
#include "DmgTypeBP_Environmental__pf1001828891.h"
#include "Runtime/Engine/Classes/Engine/BookMark.h"
#include "Runtime/Engine/Classes/Engine/MaterialMerging.h"
#include "Runtime/Engine/Classes/Engine/Level.h"
#include "Runtime/Engine/Classes/Components/ModelComponent.h"
#include "Runtime/Engine/Classes/Engine/LevelActorContainer.h"
#include "Runtime/Engine/Classes/Engine/LevelScriptActor.h"
#include "Runtime/Engine/Classes/Engine/NavigationObjectBase.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationDataChunk.h"
#include "Runtime/Engine/Classes/Engine/MapBuildDataRegistry.h"
#include "Runtime/Engine/Classes/Engine/LevelScriptBlueprint.h"
#include "Runtime/Engine/Classes/Engine/BlueprintCore.h"
#include "Runtime/Engine/Classes/Engine/BlueprintGeneratedClass.h"
#include "Runtime/Engine/Classes/Engine/TimelineTemplate.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Runtime/Engine/Classes/Curves/CurveVector.h"
#include "Runtime/Engine/Classes/Engine/InheritableComponentHandler.h"
#include "Runtime/CoreUObject/Public/UObject/CoreNetTypes.h"
#include "Runtime/Engine/Classes/Engine/Breakpoint.h"
#include "Runtime/Engine/Public/Blueprint/BlueprintExtension.h"
#include "Runtime/Engine/Classes/Components/LineBatchComponent.h"
#include "Runtime/Engine/Classes/Engine/LevelStreaming.h"
#include "Runtime/Engine/Classes/Engine/LevelStreamingVolume.h"
#include "Runtime/Engine/Classes/Engine/DemoNetDriver.h"
#include "Runtime/Engine/Classes/Particles/ParticleEventManager.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/Engine/Classes/AI/Navigation/AvoidanceManager.h"
#include "Runtime/Engine/Classes/Engine/GameInstance.h"
#include "Runtime/Engine/Classes/GameFramework/OnlineSession.h"
#include "Runtime/Engine/Classes/Materials/MaterialParameterCollectionInstance.h"
#include "Runtime/Engine/Classes/Engine/WorldComposition.h"
#include "Runtime/Engine/Classes/Particles/WorldPSCPool.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Runtime/Engine/Classes/Particles/ParticleEmitter.h"
#include "Runtime/Engine/Public/ParticleHelper.h"
#include "Runtime/Engine/Classes/Particles/ParticleLODLevel.h"
#include "Runtime/Engine/Classes/Particles/ParticleModuleRequired.h"
#include "Runtime/Engine/Classes/Particles/ParticleModule.h"
#include "Runtime/Engine/Classes/Particles/ParticleSpriteEmitter.h"
#include "Runtime/Engine/Classes/Distributions/DistributionFloat.h"
#include "Runtime/Engine/Classes/Distributions/Distribution.h"
#include "Runtime/Engine/Classes/Particles/SubUVAnimation.h"
#include "Runtime/Engine/Classes/Particles/TypeData/ParticleModuleTypeDataBase.h"
#include "Runtime/Engine/Classes/Particles/Spawn/ParticleModuleSpawn.h"
#include "Runtime/Engine/Classes/Particles/Spawn/ParticleModuleSpawnBase.h"
#include "Runtime/Engine/Classes/Particles/Event/ParticleModuleEventGenerator.h"
#include "Runtime/Engine/Classes/Particles/Event/ParticleModuleEventBase.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Particles/Event/ParticleModuleEventSendToGame.h"
#include "Runtime/Engine/Classes/Particles/Orbit/ParticleModuleOrbit.h"
#include "Runtime/Engine/Classes/Particles/Orbit/ParticleModuleOrbitBase.h"
#include "Runtime/Engine/Classes/Distributions/DistributionVector.h"
#include "Runtime/Engine/Classes/Particles/Event/ParticleModuleEventReceiverBase.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstance.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceBasePropertyOverrides.h"
#include "Runtime/Engine/Public/StaticParameterSet.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemReplay.h"
#include "Runtime/Engine/Classes/Engine/InterpCurveEdSetup.h"
#include "Runtime/Engine/Classes/Layers/Layer.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/EngineCustomTimeStep.h"
#include "Runtime/Engine/Classes/Engine/TimecodeProvider.h"
#include "Runtime/SlateCore/Public/Styling/SlateTypes.h"
#include "Runtime/UMG/Public/Blueprint/WidgetNavigation.h"
#include "Runtime/SlateCore/Public/Layout/FlowDirection.h"
#include "Runtime/UMG/Public/Binding/PropertyBinding.h"
#include "Runtime/UMG/Public/Binding/DynamicPropertyPath.h"
#include "Runtime/PropertyPath/Public/PropertyPathHelpers.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"
#include "Runtime/MovieScene/Public/MovieSceneSequence.h"
#include "Runtime/MovieScene/Public/MovieSceneSignedObject.h"
#include "Runtime/MovieScene/Public/MovieSceneObjectBindingID.h"
#include "Runtime/MovieScene/Public/Compilation/MovieSceneCompiledDataManager.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvaluationTemplate.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneTrackIdentifier.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvaluationTrack.h"
#include "Runtime/MovieScene/Public/MovieSceneTrack.h"
#include "Runtime/MovieScene/Public/MovieSceneTrackEvaluationField.h"
#include "Runtime/MovieScene/Public/MovieSceneSection.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneCompletionMode.h"
#include "Runtime/MovieScene/Public/Evaluation/Blending/MovieSceneBlendType.h"
#include "Runtime/MovieScene/Public/Generators/MovieSceneEasingFunction.h"
#include "Runtime/MovieScene/Public/MovieSceneFrameMigration.h"
#include "Runtime/MovieScene/Public/Generators/MovieSceneEasingCurves.h"
#include "Runtime/MovieScene/Public/MovieScene.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneSegment.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvalTemplate.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneTrackImplementation.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneSequenceHierarchy.h"
#include "Runtime/MovieScene/Public/MovieSceneSequenceID.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneSequenceTransform.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneTimeTransform.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneTimeWarping.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneSequenceInstanceData.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvaluationField.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvaluationKey.h"
#include "Runtime/MovieScene/Public/MovieSceneFwd.h"
#include "Runtime/MovieScene/Public/MovieSceneSpawnable.h"
#include "Runtime/MovieScene/Public/MovieScenePossessable.h"
#include "Runtime/MovieScene/Public/MovieSceneBinding.h"
#include "Runtime/MovieScene/Public/MovieSceneFolder.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimationBinding.h"
#include "Runtime/Slate/Public/Widgets/Layout/Anchors.h"
#include "Runtime/UMG/Public/Animation/UMGSequencePlayer.h"
#include "Runtime/MovieScene/Public/Evaluation/MovieSceneEvaluationTemplateInstance.h"
#include "Runtime/MovieScene/Public/EntitySystem/MovieSceneEntitySystemLinker.h"
#include "Runtime/MovieScene/Public/EntitySystem/MovieSceneEntitySystemGraphs.h"
#include "Runtime/UMG/Public/Blueprint/DragDropOperation.h"
#include "Runtime/Engine/Classes/Camera/CameraShakeBase.h"
#include "Runtime/Engine/Classes/Camera/CameraAnimInst.h"
#include "Runtime/Engine/Classes/Camera/CameraAnim.h"
#include "Runtime/Engine/Classes/Matinee/InterpGroup.h"
#include "Runtime/Engine/Classes/Matinee/InterpTrack.h"
#include "Runtime/Engine/Classes/Matinee/InterpTrackInst.h"
#include "Runtime/Engine/Classes/Engine/Scene.h"
#include "Runtime/Engine/Classes/Engine/TextureCube.h"
#include "Runtime/Engine/Classes/Matinee/InterpGroupInst.h"
#include "Runtime/Engine/Classes/Matinee/InterpTrackMove.h"
#include "Runtime/Engine/Classes/Matinee/InterpTrackInstMove.h"
#include "Runtime/Engine/Classes/Camera/CameraTypes.h"
#include "Runtime/Engine/Classes/Camera/CameraShakeSourceComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraShake.h"
#include "Runtime/Engine/Classes/Camera/CameraModifier.h"
#include "Runtime/Engine/Classes/Particles/EmitterCameraLensEffectBase.h"
#include "Runtime/Engine/Classes/Particles/Emitter.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraModifier_CameraShake.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/UMG/Public/Animation/UMGSequenceTickManager.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/UMG/Public/Components/NamedSlotInterface.h"
#include "Runtime/Engine/Classes/GameFramework/UpdateLevelVisibilityLevelInfo.h"
#include "Runtime/Engine/Classes/Haptics/HapticFeedbackEffect_Base.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "Runtime/Engine/Classes/GameFramework/ForceFeedbackEffect.h"
#include "Runtime/Engine/Classes/GameFramework/TouchInterface.h"
#include "Runtime/Engine/Classes/Matinee/InterpTrackInstDirector.h"
#include "Runtime/Engine/Classes/GameFramework/CheatManager.h"
#include "Runtime/Engine/Classes/Engine/DebugCameraController.h"
#include "Runtime/Engine/Classes/Components/DrawFrustumComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "Runtime/Engine/Classes/Animation/AnimCompositeBase.h"
#include "Runtime/Engine/Classes/Animation/AnimSequenceBase.h"
#include "Runtime/Engine/Classes/Animation/AnimationAsset.h"
#include "Runtime/Engine/Classes/Animation/Skeleton.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "Runtime/Engine/Classes/Animation/SmartName.h"
#include "Runtime/Engine/Classes/Animation/BlendProfile.h"
#include "Runtime/Engine/Public/BoneContainer.h"
#include "Runtime/Engine/Classes/Interfaces/Interface_PreviewMeshProvider.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshLODSettings.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "Runtime/Engine/Public/Animation/AnimTypes.h"
#include "Runtime/Engine/Classes/Animation/AnimBoneCompressionSettings.h"
#include "Runtime/Engine/Classes/Animation/AnimBoneCompressionCodec.h"
#include "Runtime/Engine/Classes/Animation/AnimCurveCompressionSettings.h"
#include "Runtime/Engine/Classes/Animation/AnimCurveCompressionCodec.h"
#include "Runtime/Engine/Classes/Animation/AnimCurveCompressionCodec_CompressedRichCurve.h"
#include "Runtime/Engine/Classes/Animation/AnimEnums.h"
#include "Runtime/Engine/Classes/Animation/CustomAttributes.h"
#include "Runtime/Engine/Classes/Curves/StringCurve.h"
#include "Runtime/Engine/Classes/Curves/IntegralCurve.h"
#include "Runtime/Engine/Classes/Curves/SimpleCurve.h"
#include "Runtime/Engine/Public/SkeletalMeshReductionSettings.h"
#include "Runtime/Engine/Public/Animation/NodeMappingContainer.h"
#include "Runtime/Engine/Public/Animation/NodeMappingProviderInterface.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicalAnimationComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintTemplate.h"
#include "Runtime/Engine/Classes/PhysicsEngine/ConstraintInstance.h"
#include "Runtime/Engine/Classes/PhysicsEngine/ConstraintTypes.h"
#include "Runtime/Engine/Classes/PhysicsEngine/ConstraintDrives.h"
#include "Runtime/Engine/Classes/Animation/MorphTarget.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Public/Animation/PoseSnapshot.h"
#include "Runtime/Engine/Public/Animation/AnimNotifyQueue.h"
#include "Runtime/Engine/Classes/Animation/AnimLinkableElement.h"
#include "Runtime/Engine/Classes/Animation/AnimNotifies/AnimNotify.h"
#include "Runtime/Engine/Classes/Animation/AnimNotifies/AnimNotifyState.h"
#include "Runtime/ClothingSystemRuntimeInterface/Public/ClothingAssetBase.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSampling.h"
#include "Runtime/Engine/Public/Animation/SkinWeightProfile.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshEditorData.h"
#include "Runtime/Engine/Classes/Animation/PreviewAssetAttachComponent.h"
#include "Runtime/Engine/Classes/Animation/Rig.h"
#include "Runtime/Engine/Classes/Animation/AnimMetaData.h"
#include "Runtime/Engine/Classes/Animation/AssetMappingTable.h"
#include "Runtime/Engine/Classes/Animation/PoseAsset.h"
#include "Runtime/Engine/Public/Animation/AnimCurveTypes.h"
#include "Runtime/Engine/Public/AlphaBlend.h"
#include "Runtime/Engine/Classes/Animation/TimeStretchCurve.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementReplication.h"
#include "Runtime/Engine/Classes/GameFramework/RootMotionSource.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationAvoidanceTypes.h"
#include "Runtime/Engine/Public/AI/RVOAvoidanceInterface.h"
#include "Runtime/Engine/Classes/Interfaces/NetworkPredictionInterface.h"
#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"
#include "Runtime/Engine/Classes/Matinee/MatineeActor.h"
#include "Runtime/Engine/Classes/Matinee/InterpData.h"
#include "Runtime/Engine/Classes/Matinee/InterpGroupDirector.h"
#include "Runtime/Engine/Classes/Matinee/InterpFilter.h"
#include "Runtime/Engine/Public/ComponentInstanceDataCache.h"
#include "Runtime/Engine/Public/SceneTypes.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavRelevantInterface.h"
#include "Runtime/Engine/Public/HitProxies.h"
#include "Runtime/Engine/Public/LODSyncInterface.h"
#include "Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationInteractor.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprintGeneratedClass.h"
#include "Runtime/Engine/Classes/Engine/DynamicBlueprintBinding.h"
#include "Runtime/Engine/Classes/Animation/AnimStateMachineTypes.h"
#include "Runtime/Engine/Classes/Animation/AnimClassInterface.h"
#include "Runtime/Engine/Classes/Animation/AnimNodeBase.h"
#include "Runtime/PropertyAccess/Public/PropertyAccess.h"
#include "Runtime/Engine/Public/SingleAnimationPlayData.h"
#include "Runtime/ClothingSystemRuntimeInterface/Public/ClothingSimulationFactory.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "Runtime/Engine/Classes/Engine/PoseWatch.h"
#include "Runtime/ClothingSystemRuntimeNv/Public/ClothingSimulationFactoryNv.h"
#include "BP_DroneMotorComponent__pf2264400134.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "BP_PIDControllerComponent__pf2264400134.h"
#include "../Plugins/UE4Duino/Source/UE4Duino/Public/Serial.h"
#include "UI_DroneHUD__pf58196802.h"
#include "Runtime/Engine/Classes/Kismet/KismetStringLibrary.h"
#include "Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetArrayLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/CollisionProfile.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/Engine/Public/Slate/SGameLayerManager.h"
#include "Runtime/SlateCore/Public/Rendering/RenderingCommon.h"
#include "Runtime/Engine/Classes/Slate/SlateBrushAsset.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/AudioMixer/Public/Quartz/AudioMixerClockHandle.h"
#include "Runtime/Engine/Classes/Sound/QuartzQuantizationUtilities.h"
#include "Runtime/Engine/Classes/GameFramework/ForceFeedbackAttenuation.h"
#include "Runtime/Engine/Classes/Components/ForceFeedbackComponent.h"
#include "Runtime/Engine/Classes/Sound/DialogueWave.h"
#include "Runtime/Engine/Classes/Sound/DialogueTypes.h"
#include "Runtime/Engine/Classes/Sound/DialogueVoice.h"
#include "Runtime/Engine/Classes/Sound/DialogueSoundWaveProxy.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "Runtime/Engine/Classes/Kismet/KismetNodeHelperLibrary.h"


#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
PRAGMA_DISABLE_OPTIMIZATION
ABP_Drone_C__pf2264400134::ABP_Drone_C__pf2264400134(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	bpv__DroneBody__pf = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DroneBody"));
	bpv__MotorFL__pf = CreateDefaultSubobject<UBP_DroneMotorComponent_C__pf2264400134>(TEXT("MotorFL"));
	bpv__MotorFR__pf = CreateDefaultSubobject<UBP_DroneMotorComponent_C__pf2264400134>(TEXT("MotorFR"));
	bpv__MotorBL__pf = CreateDefaultSubobject<UBP_DroneMotorComponent_C__pf2264400134>(TEXT("MotorBL"));
	bpv__MotorBR__pf = CreateDefaultSubobject<UBP_DroneMotorComponent_C__pf2264400134>(TEXT("MotorBR"));
	bpv__SpringArm__pf = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	bpv__ThirdPersonCamera__pf = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	bpv__PropBR__pf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropBR"));
	bpv__PropFR__pf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropFR"));
	bpv__PropFL__pf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropFL"));
	bpv__PropBL__pf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropBL"));
	bpv__GimbalCamera__pf = CreateDefaultSubobject<UCameraComponent>(TEXT("GimbalCamera"));
	RootComponent = bpv__DroneBody__pf;
	bpv__AltStabilizationPID__pf = CreateDefaultSubobject<UBP_PIDControllerComponent_C__pf2264400134>(TEXT("AltStabilizationPID"));
	bpv__PitchStabilizationPID__pf = CreateDefaultSubobject<UBP_PIDControllerComponent_C__pf2264400134>(TEXT("PitchStabilizationPID"));
	bpv__RollStabilizationPID__pf = CreateDefaultSubobject<UBP_PIDControllerComponent_C__pf2264400134>(TEXT("RollStabilizationPID"));
	bpv__YawStabilizationPID__pf = CreateDefaultSubobject<UBP_PIDControllerComponent_C__pf2264400134>(TEXT("YawStabilizationPID"));
	bpv__DroneBody__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__DroneBody__pf->ClothingSimulationFactory = UClothingSimulationFactoryNv::StaticClass();
	bpv__DroneBody__pf->SkeletalMesh = CastChecked<USkeletalMesh>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->UsedAssets[0], ECastCheckedType::NullAllowed);
	bpv__DroneBody__pf->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	static TWeakFieldPtr<FProperty> __Local__1{};
	const FProperty* __Local__0 = __Local__1.Get();
	if (nullptr == __Local__0)
	{
		__Local__0 = (UPrimitiveComponent::StaticClass())->FindPropertyByName(FName(TEXT("bGenerateOverlapEvents")));
		check(__Local__0);
		__Local__1 = __Local__0;
	}
	(((FBoolProperty*)__Local__0)->SetPropertyValue_InContainer((bpv__DroneBody__pf), true, 0));
	auto& __Local__2 = (*(AccessPrivateProperty<TEnumAsByte<ECollisionChannel> >(&(bpv__DroneBody__pf->BodyInstance), FBodyInstance::__PPO__ObjectType() )));
	__Local__2 = ECollisionChannel::ECC_PhysicsBody;
	auto& __Local__3 = (*(AccessPrivateProperty<TEnumAsByte<ECollisionEnabled::Type> >(&(bpv__DroneBody__pf->BodyInstance), FBodyInstance::__PPO__CollisionEnabled() )));
	__Local__3 = ECollisionEnabled::Type::QueryAndPhysics;
	bpv__DroneBody__pf->BodyInstance.bNotifyRigidBodyCollision = true;
	bpv__DroneBody__pf->BodyInstance.bOverrideMaxAngularVelocity = true;
	bpv__DroneBody__pf->BodyInstance.PositionSolverIterationCount = 12;
	auto& __Local__4 = (*(AccessPrivateProperty<FCollisionResponse >(&(bpv__DroneBody__pf->BodyInstance), FBodyInstance::__PPO__CollisionResponses() )));
	auto& __Local__5 = (*(AccessPrivateProperty<TArray<FResponseChannel> >(&(__Local__4), FCollisionResponse::__PPO__ResponseArray() )));
	__Local__5 = TArray<FResponseChannel> ();
	bpv__DroneBody__pf->BodyInstance.MaxAngularVelocity = 200.000000f;
	bpv__DroneBody__pf->BodyInstance.bSimulatePhysics = true;
	bpv__DroneBody__pf->BodyInstance.bStartAwake = false;
	bpv__DroneBody__pf->SetCollisionProfileName(FName(TEXT("Custom")));
	static TWeakFieldPtr<FProperty> __Local__7{};
	const FProperty* __Local__6 = __Local__7.Get();
	if (nullptr == __Local__6)
	{
		__Local__6 = (UActorComponent::StaticClass())->FindPropertyByName(FName(TEXT("bCanEverAffectNavigation")));
		check(__Local__6);
		__Local__7 = __Local__6;
	}
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__DroneBody__pf), false, 0));
	bpv__MotorFL__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__MotorFL__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	auto& __Local__8 = (*(AccessPrivateProperty<FVector >((bpv__MotorFL__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__8 = FVector(10.000000, -10.000000, 3.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__MotorFL__pf), false, 0));
	bpv__MotorFR__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__MotorFR__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	auto& __Local__9 = (*(AccessPrivateProperty<FVector >((bpv__MotorFR__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__9 = FVector(10.000000, 10.000000, 3.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__MotorFR__pf), false, 0));
	bpv__MotorBL__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__MotorBL__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	auto& __Local__10 = (*(AccessPrivateProperty<FVector >((bpv__MotorBL__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__10 = FVector(-10.000000, -10.000000, 3.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__MotorBL__pf), false, 0));
	bpv__MotorBR__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__MotorBR__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	auto& __Local__11 = (*(AccessPrivateProperty<FVector >((bpv__MotorBR__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__11 = FVector(-10.000000, 10.000000, 3.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__MotorBR__pf), false, 0));
	bpv__SpringArm__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__SpringArm__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	bpv__SpringArm__pf->TargetArmLength = 100.000000f;
	bpv__SpringArm__pf->SocketOffset = FVector(0.000000, 0.000000, 50.000000);
	bpv__SpringArm__pf->ProbeChannel = ECollisionChannel::ECC_WorldStatic;
	bpv__SpringArm__pf->bDoCollisionTest = false;
	bpv__SpringArm__pf->bInheritPitch = false;
	bpv__SpringArm__pf->bInheritRoll = false;
	bpv__SpringArm__pf->bEnableCameraRotationLag = true;
	bpv__SpringArm__pf->CameraLagSpeed = 50.000000f;
	auto& __Local__12 = (*(AccessPrivateProperty<FVector >((bpv__SpringArm__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__12 = FVector(0.000000, 0.000000, 4.509161);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__SpringArm__pf), false, 0));
	bpv__ThirdPersonCamera__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__ThirdPersonCamera__pf->AttachToComponent(bpv__SpringArm__pf, FAttachmentTransformRules::KeepRelativeTransform );
	auto& __Local__13 = (*(AccessPrivateProperty<FRotator >((bpv__ThirdPersonCamera__pf), USceneComponent::__PPO__RelativeRotation() )));
	__Local__13 = FRotator(-14.999984, 0.000000, 0.000000);
	auto& __Local__14 = (*(AccessPrivateProperty<FVector >((bpv__ThirdPersonCamera__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__14 = FVector(0.100000, 0.100000, 0.100000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__ThirdPersonCamera__pf), false, 0));
	bpv__PropBR__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__PropBR__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform , TEXT("prop_br"));
	auto& __Local__15 = (*(AccessPrivateProperty<UStaticMesh* >((bpv__PropBR__pf), UStaticMeshComponent::__PPO__StaticMesh() )));
	__Local__15 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->UsedAssets[1], ECastCheckedType::NullAllowed);
	bpv__PropBR__pf->bApplyImpulseOnDamage = false;
	bpv__PropBR__pf->bReplicatePhysicsToAutonomousProxy = false;
	bpv__PropBR__pf->BodyInstance.MassScale = 0.000000f;
	bpv__PropBR__pf->BodyInstance.bEnableGravity = false;
	bpv__PropBR__pf->BodyInstance.bAutoWeld = false;
	bpv__PropBR__pf->SetCollisionProfileName(FName(TEXT("NoCollision")));
	auto& __Local__16 = (*(AccessPrivateProperty<FVector >((bpv__PropBR__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__16 = FVector(1.000000, 1.000000, 1.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__PropBR__pf), true, 0));
	bpv__PropFR__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__PropFR__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform , TEXT("prop_fr"));
	auto& __Local__17 = (*(AccessPrivateProperty<UStaticMesh* >((bpv__PropFR__pf), UStaticMeshComponent::__PPO__StaticMesh() )));
	__Local__17 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->UsedAssets[2], ECastCheckedType::NullAllowed);
	bpv__PropFR__pf->bApplyImpulseOnDamage = false;
	bpv__PropFR__pf->bReplicatePhysicsToAutonomousProxy = false;
	bpv__PropFR__pf->BodyInstance.MassScale = 0.000000f;
	bpv__PropFR__pf->BodyInstance.bEnableGravity = false;
	bpv__PropFR__pf->BodyInstance.bAutoWeld = false;
	bpv__PropFR__pf->SetCollisionProfileName(FName(TEXT("NoCollision")));
	auto& __Local__18 = (*(AccessPrivateProperty<FVector >((bpv__PropFR__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__18 = FVector(1.000000, 1.000000, 1.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__PropFR__pf), true, 0));
	bpv__PropFL__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__PropFL__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform , TEXT("prop_fl"));
	auto& __Local__19 = (*(AccessPrivateProperty<UStaticMesh* >((bpv__PropFL__pf), UStaticMeshComponent::__PPO__StaticMesh() )));
	__Local__19 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->UsedAssets[1], ECastCheckedType::NullAllowed);
	bpv__PropFL__pf->bApplyImpulseOnDamage = false;
	bpv__PropFL__pf->bReplicatePhysicsToAutonomousProxy = false;
	bpv__PropFL__pf->BodyInstance.MassScale = 0.000000f;
	bpv__PropFL__pf->BodyInstance.bEnableGravity = false;
	bpv__PropFL__pf->BodyInstance.bAutoWeld = false;
	bpv__PropFL__pf->SetCollisionProfileName(FName(TEXT("NoCollision")));
	auto& __Local__20 = (*(AccessPrivateProperty<FVector >((bpv__PropFL__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__20 = FVector(1.000000, 1.000000, 1.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__PropFL__pf), true, 0));
	bpv__PropBL__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__PropBL__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform , TEXT("prop_bl"));
	auto& __Local__21 = (*(AccessPrivateProperty<UStaticMesh* >((bpv__PropBL__pf), UStaticMeshComponent::__PPO__StaticMesh() )));
	__Local__21 = CastChecked<UStaticMesh>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->UsedAssets[2], ECastCheckedType::NullAllowed);
	bpv__PropBL__pf->bApplyImpulseOnDamage = false;
	bpv__PropBL__pf->bReplicatePhysicsToAutonomousProxy = false;
	bpv__PropBL__pf->BodyInstance.MassScale = 0.000000f;
	bpv__PropBL__pf->BodyInstance.bEnableGravity = false;
	bpv__PropBL__pf->BodyInstance.bAutoWeld = false;
	bpv__PropBL__pf->SetCollisionProfileName(FName(TEXT("NoCollision")));
	auto& __Local__22 = (*(AccessPrivateProperty<FVector >((bpv__PropBL__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__22 = FVector(1.000000, 1.000000, 1.000000);
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__PropBL__pf), true, 0));
	bpv__GimbalCamera__pf->CreationMethod = EComponentCreationMethod::Native;
	bpv__GimbalCamera__pf->AttachToComponent(bpv__DroneBody__pf, FAttachmentTransformRules::KeepRelativeTransform );
	bpv__GimbalCamera__pf->bLockToHmd = false;
	bpv__GimbalCamera__pf->PostProcessSettings.bOverride_VignetteIntensity = true;
	bpv__GimbalCamera__pf->PostProcessSettings.AutoExposureBiasBackup = 1.000000f;
	auto& __Local__23 = (*(AccessPrivateProperty<FVector >((bpv__GimbalCamera__pf), USceneComponent::__PPO__RelativeLocation() )));
	__Local__23 = FVector(18.851936, -0.000006, 3.388066);
	auto& __Local__24 = (*(AccessPrivateProperty<FVector >((bpv__GimbalCamera__pf), USceneComponent::__PPO__RelativeScale3D() )));
	__Local__24 = FVector(0.100000, 0.100000, 0.100000);
	bpv__GimbalCamera__pf->bAutoActivate = false;
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__GimbalCamera__pf), false, 0));
	bpv__AltStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__AltStabilizationPID__pf), false, 0));
	bpv__PitchStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__PitchStabilizationPID__pf), false, 0));
	bpv__RollStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__RollStabilizationPID__pf), false, 0));
	bpv__YawStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	(((FBoolProperty*)__Local__6)->SetPropertyValue_InContainer((bpv__YawStabilizationPID__pf), false, 0));
	bpv__Motors__pf = TArray<UBP_DroneMotorComponent_C__pf2264400134*> ();
	bpv__LastxThrottlexForcexApplied__pfTTT = 0.000000f;
	bpv__LastxPitchxForcexApplied__pfTTT = 0.000000f;
	bpv__LastxRollxForcexApplied__pfTTT = 0.000000f;
	bpv__LastxYawxTorquexApplied__pfTTT = 0.000000f;
	bpv__DesiredxAltitude__pfT = 0.000000f;
	bpv__GravityxForce__pfT = 980.000000f;
	bpv__MaxxSpeed__pfT = 1800.000000f;
	bpv__MaxxClimbxSpeed__pfTT = 500.000000f;
	bpv__MaxxDescentxSpeed__pfTT = -300.000000f;
	bpv__MaxxAngularxVelocity__pfTT = 200.000000f;
	bpv__MaxxTiltxAngle__pfTT = 45.000000f;
	bpv__MaxxPropellerxRPS__pfTT = 30.000000f;
	bpv__PitchxRollxForcexMultiplier__pfTTT = 10.000000f;
	bpv__CounterxPitchxAngle__pfTT = 0.000000f;
	bpv__CounterxRollxAngle__pfTT = 0.000000f;
	bpv__GimbalxPitch__pfT = 0.000000f;
	bpv__YawxTorquexForce__pfTT = 10000.000000f;
	bpv__Enabled__pf = false;
	bpv__Crashed__pf = false;
	bpv__TakeoffxPerformed__pfT = false;
	bpv__Landed__pf = true;
	bpv__DronexMode__pfT = E__DroneModeEnum__pf::NewEnumerator0;
	bpv__Joystick__pf = nullptr;
	bpv__HandGesture__pf = nullptr;
	bpv__JoystickInput__pf = TArray<float> ();
	bpv__JoystickInput__pf.Reserve(6);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__JoystickInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf = TArray<float> ();
	bpv__HandGestureInput__pf.Reserve(6);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__HandGestureInput__pf.Add(0.000000f);
	bpv__Empty__pf = TArray<float> ();
	bpv__Empty__pf.Reserve(6);
	bpv__Empty__pf.Add(0.000000f);
	bpv__Empty__pf.Add(0.000000f);
	bpv__Empty__pf.Add(0.000000f);
	bpv__Empty__pf.Add(0.000000f);
	bpv__Empty__pf.Add(0.000000f);
	bpv__Empty__pf.Add(0.000000f);
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;
	auto& __Local__25 = (*(AccessPrivateProperty<EActorUpdateOverlapsMethod >((this), AActor::__PPO__DefaultUpdateOverlapsMethodDuringLevelStreaming() )));
	__Local__25 = EActorUpdateOverlapsMethod::OnlyUpdateMovable;
}
PRAGMA_ENABLE_OPTIMIZATION
void ABP_Drone_C__pf2264400134::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
	if(bpv__DroneBody__pf)
	{
		bpv__DroneBody__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__MotorFL__pf)
	{
		bpv__MotorFL__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__MotorFR__pf)
	{
		bpv__MotorFR__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__MotorBL__pf)
	{
		bpv__MotorBL__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__MotorBR__pf)
	{
		bpv__MotorBR__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__SpringArm__pf)
	{
		bpv__SpringArm__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__ThirdPersonCamera__pf)
	{
		bpv__ThirdPersonCamera__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__PropBR__pf)
	{
		bpv__PropBR__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__PropFR__pf)
	{
		bpv__PropFR__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__PropFL__pf)
	{
		bpv__PropFL__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__PropBL__pf)
	{
		bpv__PropBL__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__GimbalCamera__pf)
	{
		bpv__GimbalCamera__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__AltStabilizationPID__pf)
	{
		bpv__AltStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__PitchStabilizationPID__pf)
	{
		bpv__PitchStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__RollStabilizationPID__pf)
	{
		bpv__RollStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	}
	if(bpv__YawStabilizationPID__pf)
	{
		bpv__YawStabilizationPID__pf->CreationMethod = EComponentCreationMethod::Native;
	}
}
PRAGMA_DISABLE_OPTIMIZATION
void ABP_Drone_C__pf2264400134::__CustomDynamicClassInitialization(UDynamicClass* InDynamicClass)
{
	ensure(0 == InDynamicClass->ReferencedConvertedFields.Num());
	ensure(0 == InDynamicClass->MiscConvertedSubobjects.Num());
	ensure(0 == InDynamicClass->DynamicBindingObjects.Num());
	ensure(0 == InDynamicClass->ComponentTemplates.Num());
	ensure(0 == InDynamicClass->Timelines.Num());
	ensure(0 == InDynamicClass->ComponentClassOverrides.Num());
	ensure(nullptr == InDynamicClass->AnimClassImplementation);
	InDynamicClass->AssembleReferenceTokenStream();
	// List of all referenced converted enums
	InDynamicClass->ReferencedConvertedFields.Add(LoadObject<UEnum>(nullptr, TEXT("/Game/PhysQuad/Blueprints/DroneModeEnum.DroneModeEnum")));
	// List of all referenced converted classes
	InDynamicClass->ReferencedConvertedFields.Add(UBP_DroneMotorComponent_C__pf2264400134::StaticClass());
	InDynamicClass->ReferencedConvertedFields.Add(UBP_PIDControllerComponent_C__pf2264400134::StaticClass());
	InDynamicClass->ReferencedConvertedFields.Add(UUI_DroneHUD_C__pf58196802::StaticClass());
	FConvertedBlueprintsDependencies::FillUsedAssetsInDynamicClass(InDynamicClass, &__StaticDependencies_DirectlyUsedAssets);
	auto __Local__26 = NewObject<USceneComponent>(InDynamicClass, USceneComponent::StaticClass(), TEXT("DefaultSceneRoot_GEN_VARIABLE"), (EObjectFlags)0x00280029);
	InDynamicClass->ComponentTemplates.Add(__Local__26);
	auto __Local__27 = NewObject<UInputAxisDelegateBinding>(InDynamicClass, UInputAxisDelegateBinding::StaticClass(), TEXT("InputAxisDelegateBinding_1"), (EObjectFlags)0x00000000);
	InDynamicClass->DynamicBindingObjects.Add(__Local__27);
	auto __Local__28 = NewObject<UInputActionDelegateBinding>(InDynamicClass, UInputActionDelegateBinding::StaticClass(), TEXT("InputActionDelegateBinding_1"), (EObjectFlags)0x00000000);
	InDynamicClass->DynamicBindingObjects.Add(__Local__28);
	auto __Local__29 = NewObject<UComponentDelegateBinding>(InDynamicClass, UComponentDelegateBinding::StaticClass(), TEXT("ComponentDelegateBinding_1"), (EObjectFlags)0x00000000);
	InDynamicClass->DynamicBindingObjects.Add(__Local__29);
	static TWeakFieldPtr<FProperty> __Local__31{};
	const FProperty* __Local__30 = __Local__31.Get();
	if (nullptr == __Local__30)
	{
		__Local__30 = (UActorComponent::StaticClass())->FindPropertyByName(FName(TEXT("bCanEverAffectNavigation")));
		check(__Local__30);
		__Local__31 = __Local__30;
	}
	(((FBoolProperty*)__Local__30)->SetPropertyValue_InContainer((__Local__26), false, 0));
	__Local__27->InputAxisDelegateBindings = TArray<FBlueprintInputAxisDelegateBinding> ();
	__Local__27->InputAxisDelegateBindings.AddUninitialized(6);
	FBlueprintInputAxisDelegateBinding::StaticStruct()->InitializeStruct(__Local__27->InputAxisDelegateBindings.GetData(), 6);
	auto& __Local__32 = __Local__27->InputAxisDelegateBindings[0];
	__Local__32.InputAxisName = FName(TEXT("Throttle"));
	__Local__32.FunctionNameToBind = FName(TEXT("InpAxisEvt_Throttle_K2Node_InputAxisEvent_0"));
	auto& __Local__33 = __Local__27->InputAxisDelegateBindings[1];
	__Local__33.InputAxisName = FName(TEXT("Throttle"));
	__Local__33.bOverrideParentBinding = false;
	auto& __Local__34 = __Local__27->InputAxisDelegateBindings[2];
	__Local__34.InputAxisName = FName(TEXT("Gimbal"));
	__Local__34.bOverrideParentBinding = false;
	auto& __Local__35 = __Local__27->InputAxisDelegateBindings[3];
	__Local__35.InputAxisName = FName(TEXT("Yaw"));
	__Local__35.bOverrideParentBinding = false;
	auto& __Local__36 = __Local__27->InputAxisDelegateBindings[4];
	__Local__36.InputAxisName = FName(TEXT("Pitch"));
	__Local__36.bOverrideParentBinding = false;
	auto& __Local__37 = __Local__27->InputAxisDelegateBindings[5];
	__Local__37.InputAxisName = FName(TEXT("Roll"));
	__Local__37.bOverrideParentBinding = false;
	__Local__28->InputActionDelegateBindings = TArray<FBlueprintInputActionDelegateBinding> ();
	__Local__28->InputActionDelegateBindings.AddUninitialized(4);
	FBlueprintInputActionDelegateBinding::StaticStruct()->InitializeStruct(__Local__28->InputActionDelegateBindings.GetData(), 4);
	auto& __Local__38 = __Local__28->InputActionDelegateBindings[0];
	__Local__38.InputActionName = FName(TEXT("Drone Mode Cycle"));
	__Local__38.InputKeyEvent = EInputEvent::IE_Released;
	__Local__38.FunctionNameToBind = FName(TEXT("InpActEvt_Drone Mode Cycle_K2Node_InputActionEvent_0"));
	auto& __Local__39 = __Local__28->InputActionDelegateBindings[1];
	__Local__39.InputActionName = FName(TEXT("Camera Switch"));
	__Local__39.FunctionNameToBind = FName(TEXT("InpActEvt_Camera Switch_K2Node_InputActionEvent_1"));
	auto& __Local__40 = __Local__28->InputActionDelegateBindings[2];
	__Local__40.InputActionName = FName(TEXT("Reset"));
	__Local__40.InputKeyEvent = EInputEvent::IE_Released;
	__Local__40.FunctionNameToBind = FName(TEXT("InpActEvt_Reset_K2Node_InputActionEvent_3"));
	auto& __Local__41 = __Local__28->InputActionDelegateBindings[3];
	__Local__41.InputActionName = FName(TEXT("Motors"));
	__Local__41.InputKeyEvent = EInputEvent::IE_Released;
	__Local__41.FunctionNameToBind = FName(TEXT("InpActEvt_Motors_K2Node_InputActionEvent_2"));
	__Local__29->ComponentDelegateBindings = TArray<FBlueprintComponentDelegateBinding> ();
	__Local__29->ComponentDelegateBindings.AddUninitialized(1);
	FBlueprintComponentDelegateBinding::StaticStruct()->InitializeStruct(__Local__29->ComponentDelegateBindings.GetData(), 1);
	auto& __Local__42 = __Local__29->ComponentDelegateBindings[0];
	__Local__42.ComponentPropertyName = FName(TEXT("DroneBody"));
	__Local__42.DelegatePropertyName = FName(TEXT("OnComponentHit"));
	__Local__42.FunctionNameToBind = FName(TEXT("BndEvt__DroneBody_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature"));
}
PRAGMA_ENABLE_OPTIMIZATION
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_0(int32 bpp__EntryPoint__pf)
{
	bool bpfv__CallFunc_Not_PreBool_ReturnValue__pf{};
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_6__pf{};
	bool bpfv__CallFunc_Greater_FloatFloat_ReturnValue_1__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue_3__pf{};
	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 78:
			{
			}
		case 79:
			{
			}
		case 80:
			{
			}
		case 81:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_6__pf = UKismetMathLibrary::Not_PreBool(b0l__Temp_bool_Variable_3__pf);
				b0l__Temp_bool_Variable_3__pf = bpfv__CallFunc_Not_PreBool_ReturnValue_6__pf;
			}
		case 82:
			{
				if (!b0l__Temp_bool_Variable_3__pf)
				{
					__CurrentState = 85;
					break;
				}
			}
		case 83:
			{
			}
		case 84:
			{
				bpv__Enabled__pf = b0l__Temp_bool_Variable_3__pf;
				__CurrentState = -1;
				break;
			}
		case 85:
			{
				__CurrentState = 84;
				break;
			}
		case 205:
			{
				__CurrentState = 79;
				break;
			}
		case 225:
			{
			}
		case 226:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue__pf = UKismetMathLibrary::Not_PreBool(bpv__Enabled__pf);
				bpfv__CallFunc_Greater_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Greater_FloatFloat(b0l__K2Node_InputAxisEvent_AxisValue__pf, 0.000000);
				bpfv__CallFunc_BooleanAND_ReturnValue_3__pf = UKismetMathLibrary::BooleanAND(bpfv__CallFunc_Greater_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Not_PreBool_ReturnValue__pf);
				if (!bpfv__CallFunc_BooleanAND_ReturnValue_3__pf)
				{
					__CurrentState = -1;
					break;
				}
				__CurrentState = 79;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_1(int32 bpp__EntryPoint__pf)
{
	int32 bpfv__CallFunc_Conv_ByteToInt_ReturnValue__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue_4__pf{};
	int32 bpfv__CallFunc_MakeLiteralInt_ReturnValue__pf{};
	int32 bpfv__CallFunc_Percent_IntInt_ReturnValue__pf{};
	uint8 bpfv__CallFunc_Conv_IntToByte_ReturnValue__pf{};
	uint8 bpfv__CallFunc_GetValidValue_ReturnValue__pf{};
	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 197:
			{
			}
		case 198:
			{
				bpfv__CallFunc_MakeLiteralInt_ReturnValue__pf = UKismetSystemLibrary::MakeLiteralInt(2);
				bpfv__CallFunc_Percent_IntInt_ReturnValue__pf = UKismetMathLibrary::Percent_IntInt(b0l__Temp_int_Variable__pf, bpfv__CallFunc_MakeLiteralInt_ReturnValue__pf);
				bpfv__CallFunc_Conv_IntToByte_ReturnValue__pf = UKismetMathLibrary::Conv_IntToByte(bpfv__CallFunc_Percent_IntInt_ReturnValue__pf);
				bpfv__CallFunc_GetValidValue_ReturnValue__pf = UKismetNodeHelperLibrary::GetValidValue(CastChecked<UEnum>(CastChecked<UDynamicClass>(ABP_Drone_C__pf2264400134::StaticClass())->ReferencedConvertedFields[0]), bpfv__CallFunc_Conv_IntToByte_ReturnValue__pf);
				bpv__DronexMode__pfT = static_cast<E__DroneModeEnum__pf>(bpfv__CallFunc_GetValidValue_ReturnValue__pf);
			}
		case 199:
			{
				b0l__K2Node_SwitchEnum_CmpSuccess_1__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator1));
				if (!b0l__K2Node_SwitchEnum_CmpSuccess_1__pf)
				{
					__CurrentState = 200;
					break;
				}
				__CurrentState = -1;
				break;
			}
		case 200:
			{
				if(::IsValid(bpv__GimbalCamera__pf))
				{
					bpv__GimbalCamera__pf->USceneComponent::K2_SetRelativeRotation(FRotator(0.000000,0.000000,0.000000), false, /*out*/ b0l__CallFunc_K2_SetRelativeRotation_SweepHitResult__pf, false);
				}
				__CurrentState = -1;
				break;
			}
		case 206:
			{
			}
		case 207:
			{
			}
		case 208:
			{
			}
		case 209:
			{
			}
		case 210:
			{
				bpfv__CallFunc_Conv_ByteToInt_ReturnValue__pf = UKismetMathLibrary::Conv_ByteToInt(static_cast<uint8>(bpv__DronexMode__pfT));
				bpfv__CallFunc_Add_IntInt_ReturnValue_4__pf = UKismetMathLibrary::Add_IntInt(bpfv__CallFunc_Conv_ByteToInt_ReturnValue__pf, 1);
				b0l__Temp_int_Variable__pf = bpfv__CallFunc_Add_IntInt_ReturnValue_4__pf;
			}
		case 211:
			{
				bpfv__CallFunc_Conv_ByteToInt_ReturnValue__pf = UKismetMathLibrary::Conv_ByteToInt(static_cast<uint8>(bpv__DronexMode__pfT));
				bpfv__CallFunc_Conv_ByteToInt_ReturnValue__pf = b0l__Temp_int_Variable__pf;
			}
		case 212:
			{
				__CurrentState = 197;
				break;
			}
		case 224:
			{
				__CurrentState = 206;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_2(int32 bpp__EntryPoint__pf)
{
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue_1__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue_2__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue_3__pf{};
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_1__pf{};
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_2__pf{};
	FVector bpfv__CallFunc_MakeVector_ReturnValue__pf(EForceInit::ForceInit);
	bool bpfv__CallFunc_K2_SetActorRotation_ReturnValue__pf{};
	bool bpfv__CallFunc_K2_SetActorLocation_ReturnValue__pf{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FVector bpfv__CallFunc_GetActorForwardVector_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_Conv_VectorToRotator_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue_1__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue__pf{};
	FRotator bpfv__CallFunc_MakeRotator_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_RInterpTo_ReturnValue__pf(EForceInit::ForceInit);
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_3__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue__pf{};
	float bpfv__CallFunc_Abs_ReturnValue__pf{};
	float bpfv__CallFunc_Abs_ReturnValue_1__pf{};
	float bpfv__CallFunc_Abs_ReturnValue_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf{};
	FRotator bpfv__CallFunc_MakeRotator_ReturnValue_1__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf{};
	FRotator bpfv__CallFunc_MakeRotator_ReturnValue_2__pf(EForceInit::ForceInit);
	bool bpfv__CallFunc_IsValid_ReturnValue_2__pf{};
	FString bpfv__CallFunc_Readln_ReturnValue__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue__pf{};
	float bpfv__CallFunc_Conv_StringToFloat_ReturnValue__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue__pf{};
	FString bpfv__CallFunc_Conv_FloatToString_ReturnValue__pf{};
	bool bpfv__CallFunc_IsOpened_ReturnValue__pf{};
	bool bpfv__CallFunc_IsValid_ReturnValue_3__pf{};
	FString bpfv__CallFunc_Readln_ReturnValue_1__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue_1__pf{};
	float bpfv__CallFunc_Conv_StringToFloat_ReturnValue_1__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue_1__pf{};
	FString bpfv__CallFunc_Conv_FloatToString_ReturnValue_1__pf{};
	bool bpfv__CallFunc_IsOpened_ReturnValue_1__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue_2__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue_2__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue_3__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue_3__pf{};
	bool bpfv__CallFunc_IsValid_ReturnValue_4__pf{};
	bool bpfv__CallFunc_IsOpened_ReturnValue_2__pf{};
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf{};
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf{};
	bool bpfv__CallFunc_IsValid_ReturnValue_5__pf{};
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_2__pf{};
	bool bpfv__CallFunc_IsOpened_ReturnValue_3__pf{};
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_3__pf{};
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_7__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue_2__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 1:
			{
				b0l__Temp_int_Loop_Counter_Variable__pf = 0;
			}
		case 2:
			{
				b0l__Temp_int_Array_Index_Variable__pf = 0;
			}
		case 3:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue__pf, FString(TEXT(",")), true);
				bpfv__CallFunc_Array_Length_ReturnValue__pf = FCustomThunkTemplates::Array_Length(b0l__CallFunc_ParseIntoArray_ReturnValue__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue__pf = UKismetMathLibrary::Less_IntInt(b0l__Temp_int_Loop_Counter_Variable__pf, bpfv__CallFunc_Array_Length_ReturnValue__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue__pf)
				{
					__CurrentState = 8;
					break;
				}
			}
		case 4:
			{
				b0l__Temp_int_Array_Index_Variable__pf = b0l__Temp_int_Loop_Counter_Variable__pf;
			}
		case 5:
			{
				__StateStack.Push(6);
				__CurrentState = 11;
				break;
			}
		case 6:
			{
			}
		case 7:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue__pf = UKismetMathLibrary::Add_IntInt(b0l__Temp_int_Loop_Counter_Variable__pf, 1);
				b0l__Temp_int_Loop_Counter_Variable__pf = bpfv__CallFunc_Add_IntInt_ReturnValue__pf;
				__CurrentState = 3;
				break;
			}
		case 8:
			{
			}
		case 9:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("end")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
			}
		case 10:
			{
				if(::IsValid(bpv__Joystick__pf))
				{
					bpv__Joystick__pf->USerial::Flush();
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 11:
			{
			}
		case 12:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue__pf, FString(TEXT(",")), true);
				FCustomThunkTemplates::Array_Get(b0l__CallFunc_ParseIntoArray_ReturnValue__pf, b0l__Temp_int_Array_Index_Variable__pf, /*out*/ b0l__CallFunc_Array_Get_Item__pf);
				bpfv__CallFunc_Conv_StringToFloat_ReturnValue__pf = UKismetStringLibrary::Conv_StringToFloat(b0l__CallFunc_Array_Get_Item__pf);
				FCustomThunkTemplates::Array_Set(bpv__JoystickInput__pf, b0l__Temp_int_Array_Index_Variable__pf, bpfv__CallFunc_Conv_StringToFloat_ReturnValue__pf, true);
			}
		case 13:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue__pf, FString(TEXT(",")), true);
				FCustomThunkTemplates::Array_Get(b0l__CallFunc_ParseIntoArray_ReturnValue__pf, b0l__Temp_int_Array_Index_Variable__pf, /*out*/ b0l__CallFunc_Array_Get_Item__pf);
				bpfv__CallFunc_Conv_StringToFloat_ReturnValue__pf = UKismetStringLibrary::Conv_StringToFloat(b0l__CallFunc_Array_Get_Item__pf);
				bpfv__CallFunc_Conv_FloatToString_ReturnValue__pf = UKismetStringLibrary::Conv_FloatToString(bpfv__CallFunc_Conv_StringToFloat_ReturnValue__pf);
				UKismetSystemLibrary::PrintString(this, bpfv__CallFunc_Conv_FloatToString_ReturnValue__pf, true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 20.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 14:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 15:
			{
			}
		case 16:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_2__pf = UKismetMathLibrary::Not_PreBool(b0l__Temp_bool_Variable_1__pf);
				b0l__Temp_bool_Variable_1__pf = bpfv__CallFunc_Not_PreBool_ReturnValue_2__pf;
			}
		case 17:
			{
				if (!b0l__Temp_bool_Variable_1__pf)
				{
					__CurrentState = 20;
					break;
				}
			}
		case 18:
			{
			}
		case 19:
			{
				bpv__Enabled__pf = b0l__Temp_bool_Variable_1__pf;
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 20:
			{
				__CurrentState = 19;
				break;
			}
		case 28:
			{
			}
		case 29:
			{
			}
		case 30:
			{
				bpfv__CallFunc_IsValid_ReturnValue_5__pf = UKismetSystemLibrary::IsValid(bpv__HandGesture__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue_5__pf)
				{
					__CurrentState = 14;
					break;
				}
			}
		case 31:
			{
			}
		case 32:
			{
				if(::IsValid(bpv__HandGesture__pf))
				{
					bpfv__CallFunc_IsOpened_ReturnValue_3__pf = bpv__HandGesture__pf->USerial::IsOpened();
				}
				if (!bpfv__CallFunc_IsOpened_ReturnValue_3__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 33:
			{
				__StateStack.Push(34);
				__CurrentState = 56;
				break;
			}
		case 34:
			{
			}
		case 35:
			{
				bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpv__HandGestureInput__pf[4], 1.000000);
				if (!bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_2__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 36:
			{
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpv__DroneBody__pf->SetPhysicsLinearVelocity(FVector(0.000000,0.000000,0.000000), false, FName(TEXT("None")));
				}
			}
		case 37:
			{
				bpfv__CallFunc_MakeVector_ReturnValue__pf = UKismetMathLibrary::MakeVector(0.000000, 0.000000, 0.000000);
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpv__DroneBody__pf->UPrimitiveComponent::SetAllPhysicsAngularVelocityInDegrees(bpfv__CallFunc_MakeVector_ReturnValue__pf, false);
				}
			}
		case 38:
			{
				bpv__DesiredxAltitude__pfT = 0.000000;
			}
		case 39:
			{
				if(::IsValid(bpv__PitchStabilizationPID__pf))
				{
					bpv__PitchStabilizationPID__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__RollStabilizationPID__pf))
				{
					bpv__RollStabilizationPID__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__YawStabilizationPID__pf))
				{
					bpv__YawStabilizationPID__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__AltStabilizationPID__pf))
				{
					bpv__AltStabilizationPID__pf->bpf__Reset__pf();
				}
			}
		case 40:
			{
				if(::IsValid(bpv__MotorFL__pf))
				{
					bpv__MotorFL__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__MotorFR__pf))
				{
					bpv__MotorFR__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__MotorBL__pf))
				{
					bpv__MotorBL__pf->bpf__Reset__pf();
				}
				if(::IsValid(bpv__MotorBR__pf))
				{
					bpv__MotorBR__pf->bpf__Reset__pf();
				}
			}
		case 41:
			{
				bpfv__CallFunc_K2_SetActorRotation_ReturnValue__pf = AActor::K2_SetActorRotation(FRotator(0.000000,126.562431,0.000000), true);
			}
		case 42:
			{
				bpfv__CallFunc_K2_SetActorLocation_ReturnValue__pf = AActor::K2_SetActorLocation(FVector(-52300.964844,-8895.025391,47.211655), false, /*out*/ b0l__CallFunc_K2_SetActorLocation_SweepHitResult__pf, true);
			}
		case 43:
			{
				if (!bpv__Enabled__pf)
				{
					__CurrentState = 45;
					break;
				}
			}
		case 44:
			{
				bpf__SwitchxMotors__pfT();
			}
		case 45:
			{
				bpv__Enabled__pf = false;
			}
		case 46:
			{
				bpv__Crashed__pf = false;
			}
		case 47:
			{
				bpv__TakeoffxPerformed__pfT = false;
			}
		case 48:
			{
				bpv__Landed__pf = true;
			}
		case 49:
			{
				bpv__CounterxRollxAngle__pfTT = 0.000000;
			}
		case 50:
			{
				bpv__CounterxPitchxAngle__pfTT = 0.000000;
			}
		case 51:
			{
				bpv__LastxThrottlexForcexApplied__pfTTT = 0.000000;
			}
		case 52:
			{
				bpv__LastxPitchxForcexApplied__pfTTT = 0.000000;
			}
		case 53:
			{
				bpv__LastxRollxForcexApplied__pfTTT = 0.000000;
			}
		case 54:
			{
				bpv__LastxYawxTorquexApplied__pfTTT = 0.000000;
			}
		case 55:
			{
				bpv__GimbalxPitch__pfT = 0.000000;
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 56:
			{
				bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpv__HandGestureInput__pf[0], 1.000000);
				bpfv__CallFunc_Not_PreBool_ReturnValue_7__pf = UKismetMathLibrary::Not_PreBool(bpv__Enabled__pf);
				bpfv__CallFunc_BooleanAND_ReturnValue_2__pf = UKismetMathLibrary::BooleanAND(bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_3__pf, bpfv__CallFunc_Not_PreBool_ReturnValue_7__pf);
				if (!bpfv__CallFunc_BooleanAND_ReturnValue_2__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 57:
			{
				__CurrentState = 15;
				break;
			}
		case 58:
			{
			}
		case 59:
			{
				bpv__Enabled__pf = b0l__Temp_bool_Variable__pf;
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 60:
			{
				__CurrentState = 59;
				break;
			}
		case 61:
			{
			}
		case 62:
			{
			}
		case 63:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_1__pf = UKismetMathLibrary::Not_PreBool(b0l__Temp_bool_Variable__pf);
				b0l__Temp_bool_Variable__pf = bpfv__CallFunc_Not_PreBool_ReturnValue_1__pf;
			}
		case 64:
			{
				if (!b0l__Temp_bool_Variable__pf)
				{
					__CurrentState = 60;
					break;
				}
				__CurrentState = 58;
				break;
			}
		case 65:
			{
				__StateStack.Push(66);
				__CurrentState = 73;
				break;
			}
		case 66:
			{
			}
		case 67:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue_1__pf = UKismetMathLibrary::Add_IntInt(b0l__Temp_int_Loop_Counter_Variable_1__pf, 1);
				b0l__Temp_int_Loop_Counter_Variable_1__pf = bpfv__CallFunc_Add_IntInt_ReturnValue_1__pf;
			}
		case 68:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue_1__pf, FString(TEXT(",")), true);
				bpfv__CallFunc_Array_Length_ReturnValue_1__pf = FCustomThunkTemplates::Array_Length(b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue_1__pf = UKismetMathLibrary::Less_IntInt(b0l__Temp_int_Loop_Counter_Variable_1__pf, bpfv__CallFunc_Array_Length_ReturnValue_1__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue_1__pf)
				{
					__CurrentState = 70;
					break;
				}
			}
		case 69:
			{
				b0l__Temp_int_Array_Index_Variable_1__pf = b0l__Temp_int_Loop_Counter_Variable_1__pf;
				__CurrentState = 65;
				break;
			}
		case 70:
			{
			}
		case 71:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("end")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
			}
		case 72:
			{
				if(::IsValid(bpv__HandGesture__pf))
				{
					bpv__HandGesture__pf->USerial::Flush();
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 73:
			{
			}
		case 74:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue_1__pf, FString(TEXT(",")), true);
				FCustomThunkTemplates::Array_Get(b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf, b0l__Temp_int_Array_Index_Variable_1__pf, /*out*/ b0l__CallFunc_Array_Get_Item_1__pf);
				bpfv__CallFunc_Conv_StringToFloat_ReturnValue_1__pf = UKismetStringLibrary::Conv_StringToFloat(b0l__CallFunc_Array_Get_Item_1__pf);
				FCustomThunkTemplates::Array_Set(bpv__HandGestureInput__pf, b0l__Temp_int_Array_Index_Variable_1__pf, bpfv__CallFunc_Conv_StringToFloat_ReturnValue_1__pf, true);
			}
		case 75:
			{
				b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf = UKismetStringLibrary::ParseIntoArray(bpfv__CallFunc_Readln_ReturnValue_1__pf, FString(TEXT(",")), true);
				FCustomThunkTemplates::Array_Get(b0l__CallFunc_ParseIntoArray_ReturnValue_1__pf, b0l__Temp_int_Array_Index_Variable_1__pf, /*out*/ b0l__CallFunc_Array_Get_Item_1__pf);
				bpfv__CallFunc_Conv_StringToFloat_ReturnValue_1__pf = UKismetStringLibrary::Conv_StringToFloat(b0l__CallFunc_Array_Get_Item_1__pf);
				bpfv__CallFunc_Conv_FloatToString_ReturnValue_1__pf = UKismetStringLibrary::Conv_FloatToString(bpfv__CallFunc_Conv_StringToFloat_ReturnValue_1__pf);
				UKismetSystemLibrary::PrintString(this, bpfv__CallFunc_Conv_FloatToString_ReturnValue_1__pf, true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 20.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 76:
			{
				b0l__Temp_int_Loop_Counter_Variable_1__pf = 0;
			}
		case 77:
			{
				b0l__Temp_int_Array_Index_Variable_1__pf = 0;
				__CurrentState = 68;
				break;
			}
		case 86:
			{
			}
		case 87:
			{
				if(::IsValid(bpv__Joystick__pf))
				{
					bpfv__CallFunc_IsOpened_ReturnValue_2__pf = bpv__Joystick__pf->USerial::IsOpened();
				}
				if (!bpfv__CallFunc_IsOpened_ReturnValue_2__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 88:
			{
				__StateStack.Push(89);
				__CurrentState = 91;
				break;
			}
		case 89:
			{
			}
		case 90:
			{
				bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpv__JoystickInput__pf[4], 1.000000);
				if (!bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
				__CurrentState = 36;
				break;
			}
		case 91:
			{
				bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpv__JoystickInput__pf[5], 1.000000);
				if (!bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
				__CurrentState = 61;
				break;
			}
		case 92:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 93:
			{
			}
		case 94:
			{
			}
		case 95:
			{
				bpfv__CallFunc_IsValid_ReturnValue_4__pf = UKismetSystemLibrary::IsValid(bpv__Joystick__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue_4__pf)
				{
					__CurrentState = 92;
					break;
				}
				__CurrentState = 86;
				break;
			}
		case 96:
			{
			}
		case 97:
			{
				FCustomThunkTemplates::Array_Get(bpv__Empty__pf, b0l__Temp_int_Array_Index_Variable_3__pf, /*out*/ b0l__CallFunc_Array_Get_Item_3__pf);
				FCustomThunkTemplates::Array_Set(bpv__JoystickInput__pf, b0l__Temp_int_Array_Index_Variable_3__pf, b0l__CallFunc_Array_Get_Item_3__pf, true);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 98:
			{
				__StateStack.Push(99);
				__CurrentState = 105;
				break;
			}
		case 99:
			{
			}
		case 100:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue_2__pf = UKismetMathLibrary::Add_IntInt(b0l__Temp_int_Loop_Counter_Variable_2__pf, 1);
				b0l__Temp_int_Loop_Counter_Variable_2__pf = bpfv__CallFunc_Add_IntInt_ReturnValue_2__pf;
			}
		case 101:
			{
				bpfv__CallFunc_Array_Length_ReturnValue_2__pf = FCustomThunkTemplates::Array_Length(bpv__Empty__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue_2__pf = UKismetMathLibrary::Less_IntInt(b0l__Temp_int_Loop_Counter_Variable_2__pf, bpfv__CallFunc_Array_Length_ReturnValue_2__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue_2__pf)
				{
					__CurrentState = 103;
					break;
				}
			}
		case 102:
			{
				b0l__Temp_int_Array_Index_Variable_2__pf = b0l__Temp_int_Loop_Counter_Variable_2__pf;
				__CurrentState = 98;
				break;
			}
		case 103:
			{
			}
		case 104:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("Joystick ConnectionLost")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 105:
			{
			}
		case 106:
			{
				FCustomThunkTemplates::Array_Get(bpv__Empty__pf, b0l__Temp_int_Array_Index_Variable_2__pf, /*out*/ b0l__CallFunc_Array_Get_Item_2__pf);
				FCustomThunkTemplates::Array_Set(bpv__JoystickInput__pf, b0l__Temp_int_Array_Index_Variable_2__pf, b0l__CallFunc_Array_Get_Item_2__pf, true);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 107:
			{
				b0l__Temp_int_Loop_Counter_Variable_2__pf = 0;
			}
		case 108:
			{
				b0l__Temp_int_Array_Index_Variable_2__pf = 0;
				__CurrentState = 101;
				break;
			}
		case 109:
			{
			}
		case 110:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("Joystick ConnectionLost")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 111:
			{
			}
		case 112:
			{
			}
		case 113:
			{
				b0l__Temp_int_Loop_Counter_Variable_3__pf = 0;
			}
		case 114:
			{
				b0l__Temp_int_Array_Index_Variable_3__pf = 0;
			}
		case 115:
			{
				bpfv__CallFunc_Array_Length_ReturnValue_3__pf = FCustomThunkTemplates::Array_Length(bpv__Empty__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue_3__pf = UKismetMathLibrary::Less_IntInt(b0l__Temp_int_Loop_Counter_Variable_3__pf, bpfv__CallFunc_Array_Length_ReturnValue_3__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue_3__pf)
				{
					__CurrentState = 109;
					break;
				}
			}
		case 116:
			{
				b0l__Temp_int_Array_Index_Variable_3__pf = b0l__Temp_int_Loop_Counter_Variable_3__pf;
			}
		case 117:
			{
				__StateStack.Push(118);
				__CurrentState = 96;
				break;
			}
		case 118:
			{
			}
		case 119:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue_3__pf = UKismetMathLibrary::Add_IntInt(b0l__Temp_int_Loop_Counter_Variable_3__pf, 1);
				b0l__Temp_int_Loop_Counter_Variable_3__pf = bpfv__CallFunc_Add_IntInt_ReturnValue_3__pf;
				__CurrentState = 115;
				break;
			}
		case 120:
			{
			}
		case 121:
			{
				__CurrentState = 107;
				break;
			}
		case 142:
			{
			}
		case 143:
			{
				__StateStack.Push(144);
				__CurrentState = 171;
				break;
			}
		case 144:
			{
				__StateStack.Push(145);
				__CurrentState = 161;
				break;
			}
		case 145:
			{
				__StateStack.Push(146);
				__CurrentState = 28;
				break;
			}
		case 146:
			{
				__StateStack.Push(147);
				__CurrentState = 93;
				break;
			}
		case 147:
			{
			}
		case 148:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_3__pf = UKismetMathLibrary::Not_PreBool(bpv__Crashed__pf);
				bpfv__CallFunc_BooleanAND_ReturnValue__pf = UKismetMathLibrary::BooleanAND(bpv__Enabled__pf, bpfv__CallFunc_Not_PreBool_ReturnValue_3__pf);
				if (!bpfv__CallFunc_BooleanAND_ReturnValue__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 149:
			{
				__StateStack.Push(150);
				__CurrentState = 156;
				break;
			}
		case 150:
			{
				__StateStack.Push(151);
				__CurrentState = 154;
				break;
			}
		case 151:
			{
			}
		case 152:
			{
				b0l__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator0));
				if (!b0l__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 153;
					break;
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 153:
			{
				bpfv__CallFunc_GetActorForwardVector_ReturnValue__pf = AActor::GetActorForwardVector();
				if(::IsValid(bpv__GimbalCamera__pf))
				{
					bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__GimbalCamera__pf->USceneComponent::K2_GetComponentRotation();
				}
				bpfv__CallFunc_Conv_VectorToRotator_ReturnValue__pf = UKismetMathLibrary::Conv_VectorToRotator(bpfv__CallFunc_GetActorForwardVector_ReturnValue__pf);
				bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue_1__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
				UKismetMathLibrary::BreakRotator(bpfv__CallFunc_Conv_VectorToRotator_ReturnValue__pf, /*out*/ b0l__CallFunc_BreakRotator_Roll__pf, /*out*/ b0l__CallFunc_BreakRotator_Pitch__pf, /*out*/ b0l__CallFunc_BreakRotator_Yaw__pf);
				bpfv__CallFunc_MapRangeClamped_ReturnValue__pf = UKismetMathLibrary::MapRangeClamped(bpv__GimbalxPitch__pfT, -1.000000, 1.000000, -90.000000, 90.000000);
				bpfv__CallFunc_FClamp_ReturnValue__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_MapRangeClamped_ReturnValue__pf, -90.000000, 30.000000);
				bpfv__CallFunc_MakeRotator_ReturnValue__pf = UKismetMathLibrary::MakeRotator(0.000000, bpfv__CallFunc_FClamp_ReturnValue__pf, b0l__CallFunc_BreakRotator_Yaw__pf);
				bpfv__CallFunc_RInterpTo_ReturnValue__pf = UKismetMathLibrary::RInterpTo(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, bpfv__CallFunc_MakeRotator_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue_1__pf, 50.000000);
				if(::IsValid(bpv__GimbalCamera__pf))
				{
					bpv__GimbalCamera__pf->USceneComponent::K2_SetWorldRotation(bpfv__CallFunc_RInterpTo_ReturnValue__pf, false, /*out*/ b0l__CallFunc_K2_SetWorldRotation_SweepHitResult__pf, false);
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 154:
			{
				bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
				bpf__GetxAxes__pfT(/*out*/ b0l__CallFunc_Get_Axes_Throttle__pf, /*out*/ b0l__CallFunc_Get_Axes_Pitch__pf, /*out*/ b0l__CallFunc_Get_Axes_Roll__pf, /*out*/ b0l__CallFunc_Get_Axes_Yaw__pf, /*out*/ b0l__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Yaw__pf);
				bpfv__CallFunc_Abs_ReturnValue_1__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Roll__pf);
				bpfv__CallFunc_Abs_ReturnValue_2__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Pitch__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Add_FloatFloat(b0l__CallFunc_Get_Axes_Throttle__pf, bpfv__CallFunc_Abs_ReturnValue_2__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf, bpfv__CallFunc_Abs_ReturnValue_1__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Abs_ReturnValue__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf, 1.000000);
				bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf, 0.000000, 5.000000, 0.500000, 1.000000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpv__MaxxPropellerxRPS__pfTT, bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf, 358.000000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf, -1.000000);
				bpfv__CallFunc_MakeRotator_ReturnValue_2__pf = UKismetMathLibrary::MakeRotator(0.000000, 0.000000, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf);
				if(::IsValid(bpv__PropFR__pf))
				{
					bpv__PropFR__pf->USceneComponent::K2_AddLocalRotation(bpfv__CallFunc_MakeRotator_ReturnValue_2__pf, false, /*out*/ b0l__CallFunc_K2_AddLocalRotation_SweepHitResult_1__pf, false);
				}
				if(::IsValid(bpv__PropBL__pf))
				{
					bpv__PropBL__pf->USceneComponent::K2_AddLocalRotation(bpfv__CallFunc_MakeRotator_ReturnValue_2__pf, false, /*out*/ b0l__CallFunc_K2_AddLocalRotation_SweepHitResult_1__pf, false);
				}
			}
		case 155:
			{
				bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
				bpf__GetxAxes__pfT(/*out*/ b0l__CallFunc_Get_Axes_Throttle__pf, /*out*/ b0l__CallFunc_Get_Axes_Pitch__pf, /*out*/ b0l__CallFunc_Get_Axes_Roll__pf, /*out*/ b0l__CallFunc_Get_Axes_Yaw__pf, /*out*/ b0l__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Yaw__pf);
				bpfv__CallFunc_Abs_ReturnValue_1__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Roll__pf);
				bpfv__CallFunc_Abs_ReturnValue_2__pf = UKismetMathLibrary::Abs(b0l__CallFunc_Get_Axes_Pitch__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Add_FloatFloat(b0l__CallFunc_Get_Axes_Throttle__pf, bpfv__CallFunc_Abs_ReturnValue_2__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf, bpfv__CallFunc_Abs_ReturnValue_1__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Abs_ReturnValue__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf, 1.000000);
				bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf, 0.000000, 5.000000, 0.500000, 1.000000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpv__MaxxPropellerxRPS__pfTT, bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf, 358.000000);
				bpfv__CallFunc_MakeRotator_ReturnValue_1__pf = UKismetMathLibrary::MakeRotator(0.000000, 0.000000, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf);
				if(::IsValid(bpv__PropFL__pf))
				{
					bpv__PropFL__pf->USceneComponent::K2_AddLocalRotation(bpfv__CallFunc_MakeRotator_ReturnValue_1__pf, false, /*out*/ b0l__CallFunc_K2_AddLocalRotation_SweepHitResult__pf, false);
				}
				if(::IsValid(bpv__PropBR__pf))
				{
					bpv__PropBR__pf->USceneComponent::K2_AddLocalRotation(bpfv__CallFunc_MakeRotator_ReturnValue_1__pf, false, /*out*/ b0l__CallFunc_K2_AddLocalRotation_SweepHitResult__pf, false);
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 156:
			{
				bpf__HandlexThrottle__pfT();
			}
		case 157:
			{
				bpf__HandlexPitch__pfT();
			}
		case 158:
			{
				bpf__HandlexRoll__pfT();
			}
		case 159:
			{
				bpf__HandlexYaw__pfT();
			}
		case 160:
			{
				bpf__ApplyxForces__pfT();
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 161:
			{
			}
		case 162:
			{
			}
		case 163:
			{
				bpfv__CallFunc_IsValid_ReturnValue_3__pf = UKismetSystemLibrary::IsValid(bpv__HandGesture__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue_3__pf)
				{
					__CurrentState = 170;
					break;
				}
			}
		case 164:
			{
			}
		case 165:
			{
				if(::IsValid(bpv__HandGesture__pf))
				{
					bpfv__CallFunc_IsOpened_ReturnValue_1__pf = bpv__HandGesture__pf->USerial::IsOpened();
				}
				if (!bpfv__CallFunc_IsOpened_ReturnValue_1__pf)
				{
					__CurrentState = 111;
					break;
				}
			}
		case 166:
			{
				if(::IsValid(bpv__HandGesture__pf))
				{
					bpfv__CallFunc_Readln_ReturnValue_1__pf = bpv__HandGesture__pf->USerial::Readln(/*out*/ b0l__CallFunc_Readln_bSuccess_1__pf);
				}
			}
		case 167:
			{
				if (!b0l__CallFunc_Readln_bSuccess_1__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 168:
			{
			}
		case 169:
			{
				__CurrentState = 76;
				break;
			}
		case 170:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 171:
			{
			}
		case 172:
			{
			}
		case 173:
			{
				bpfv__CallFunc_IsValid_ReturnValue_2__pf = UKismetSystemLibrary::IsValid(bpv__Joystick__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue_2__pf)
				{
					__CurrentState = 180;
					break;
				}
			}
		case 174:
			{
			}
		case 175:
			{
				if(::IsValid(bpv__Joystick__pf))
				{
					bpfv__CallFunc_IsOpened_ReturnValue__pf = bpv__Joystick__pf->USerial::IsOpened();
				}
				if (!bpfv__CallFunc_IsOpened_ReturnValue__pf)
				{
					__CurrentState = 120;
					break;
				}
			}
		case 176:
			{
				if(::IsValid(bpv__Joystick__pf))
				{
					bpfv__CallFunc_Readln_ReturnValue__pf = bpv__Joystick__pf->USerial::Readln(/*out*/ b0l__CallFunc_Readln_bSuccess__pf);
				}
			}
		case 177:
			{
				if (!b0l__CallFunc_Readln_bSuccess__pf)
				{
					__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
					break;
				}
			}
		case 178:
			{
			}
		case 179:
			{
				__CurrentState = 1;
				break;
			}
		case 180:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 190:
			{
				__CurrentState = 36;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_3(int32 bpp__EntryPoint__pf)
{
	FVector bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf(EForceInit::ForceInit);
	APlayerController* bpfv__CallFunc_GetPlayerController_ReturnValue__pf{};
	USerial* bpfv__CallFunc_OpenComPort_ReturnValue__pf{};
	USerial* bpfv__CallFunc_OpenComPort_ReturnValue_1__pf{};
	UUI_DroneHUD_C__pf58196802* bpfv__CallFunc_Create_ReturnValue__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 122:
			{
			}
		case 123:
			{
				__StateStack.Push(124);
				__CurrentState = 134;
				break;
			}
		case 124:
			{
				__StateStack.Push(125);
				__CurrentState = 132;
				break;
			}
		case 125:
			{
				__StateStack.Push(126);
				__CurrentState = 135;
				break;
			}
		case 126:
			{
				__StateStack.Push(127);
				__CurrentState = 136;
				break;
			}
		case 127:
			{
			}
		case 128:
			{
				bpfv__CallFunc_OpenComPort_ReturnValue_1__pf = USerial::OpenComPort(/*out*/ b0l__CallFunc_OpenComPort_bOpened_1__pf, 255, 9600);
			}
		case 129:
			{
				if (!b0l__CallFunc_OpenComPort_bOpened_1__pf)
				{
					__CurrentState = 141;
					break;
				}
			}
		case 130:
			{
				bpv__HandGesture__pf = bpfv__CallFunc_OpenComPort_ReturnValue_1__pf;
			}
		case 131:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("port open")), true, true, FLinearColor(0.000000,0.000000,0.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 132:
			{
				if(::IsValid(bpv__ThirdPersonCamera__pf))
				{
					bpv__ThirdPersonCamera__pf->SetActive(true, false);
				}
			}
		case 133:
			{
				bpfv__CallFunc_Create_ReturnValue__pf = CastChecked<UUI_DroneHUD_C__pf58196802>(UWidgetBlueprintLibrary::Create(this, UUI_DroneHUD_C__pf58196802::StaticClass(), ((APlayerController*)nullptr)), ECastCheckedType::NullAllowed);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 134:
			{
				bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf = AActor::K2_GetActorLocation();
				UKismetMathLibrary::BreakVector(bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf, /*out*/ b0l__CallFunc_BreakVector_X__pf, /*out*/ b0l__CallFunc_BreakVector_Y__pf, /*out*/ b0l__CallFunc_BreakVector_Z__pf);
				bpv__DesiredxAltitude__pfT = b0l__CallFunc_BreakVector_Z__pf;
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 135:
			{
				bpfv__CallFunc_GetPlayerController_ReturnValue__pf = UGameplayStatics::GetPlayerController(this, 0);
				UWidgetBlueprintLibrary::SetInputMode_GameOnly(bpfv__CallFunc_GetPlayerController_ReturnValue__pf);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 136:
			{
				bpfv__CallFunc_OpenComPort_ReturnValue__pf = USerial::OpenComPort(/*out*/ b0l__CallFunc_OpenComPort_bOpened__pf, 256, 9600);
			}
		case 137:
			{
				if (!b0l__CallFunc_OpenComPort_bOpened__pf)
				{
					__CurrentState = 140;
					break;
				}
			}
		case 138:
			{
				bpv__Joystick__pf = bpfv__CallFunc_OpenComPort_ReturnValue__pf;
			}
		case 139:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("port open")), true, true, FLinearColor(0.000000,0.000000,0.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 140:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("failed to open")), true, true, FLinearColor(0.000000,0.000000,0.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 141:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("failed to open")), true, true, FLinearColor(0.000000,0.000000,0.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_4(int32 bpp__EntryPoint__pf)
{
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_5__pf{};
	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 201:
			{
				if(::IsValid(bpv__ThirdPersonCamera__pf))
				{
					bpv__ThirdPersonCamera__pf->SetActive(false, false);
				}
				__CurrentState = -1;
				break;
			}
		case 202:
			{
				if(::IsValid(bpv__GimbalCamera__pf))
				{
					bpv__GimbalCamera__pf->SetActive(true, false);
				}
				__CurrentState = 201;
				break;
			}
		case 203:
			{
				if(::IsValid(bpv__ThirdPersonCamera__pf))
				{
					bpv__ThirdPersonCamera__pf->SetActive(true, false);
				}
				__CurrentState = -1;
				break;
			}
		case 204:
			{
				if(::IsValid(bpv__GimbalCamera__pf))
				{
					bpv__GimbalCamera__pf->SetActive(false, false);
				}
				__CurrentState = 203;
				break;
			}
		case 217:
			{
				__CurrentState = 202;
				break;
			}
		case 218:
			{
				__CurrentState = 204;
				break;
			}
		case 219:
			{
			}
		case 220:
			{
			}
		case 221:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_5__pf = UKismetMathLibrary::Not_PreBool(b0l__Temp_bool_Variable_2__pf);
				b0l__Temp_bool_Variable_2__pf = bpfv__CallFunc_Not_PreBool_ReturnValue_5__pf;
			}
		case 222:
			{
				if (!b0l__Temp_bool_Variable_2__pf)
				{
					__CurrentState = 218;
					break;
				}
				__CurrentState = 217;
				break;
			}
		case 223:
			{
				__CurrentState = 219;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_5(int32 bpp__EntryPoint__pf)
{
	bool bpfv__CallFunc_IsValid_ReturnValue__pf{};
	bool bpfv__CallFunc_IsValid_ReturnValue_1__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 21:
			{
			}
		case 22:
			{
			}
		case 23:
			{
				bpfv__CallFunc_IsValid_ReturnValue__pf = UKismetSystemLibrary::IsValid(bpv__Joystick__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue__pf)
				{
					__CurrentState = 27;
					break;
				}
			}
		case 24:
			{
			}
		case 25:
			{
				if(::IsValid(bpv__Joystick__pf))
				{
					bpv__Joystick__pf->USerial::Close();
				}
			}
		case 26:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("close port")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 27:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 191:
			{
			}
		case 192:
			{
				bpfv__CallFunc_IsValid_ReturnValue_1__pf = UKismetSystemLibrary::IsValid(bpv__HandGesture__pf);
				if (!bpfv__CallFunc_IsValid_ReturnValue_1__pf)
				{
					__CurrentState = 196;
					break;
				}
			}
		case 193:
			{
			}
		case 194:
			{
				if(::IsValid(bpv__HandGesture__pf))
				{
					bpv__HandGesture__pf->USerial::Close();
				}
			}
		case 195:
			{
				UKismetSystemLibrary::PrintString(this, FString(TEXT("close port")), true, true, FLinearColor(0.000000,0.660000,1.000000,1.000000), 2.000000);
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 196:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 213:
			{
			}
		case 214:
			{
				__StateStack.Push(215);
				__CurrentState = 21;
				break;
			}
		case 215:
			{
			}
		case 216:
			{
				__CurrentState = 191;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__ExecuteUbergraph_BP_Drone__pf_6(int32 bpp__EntryPoint__pf)
{
	float bpfv__CallFunc_VSize_ReturnValue__pf{};
	bool bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf{};
	FVector bpfv__CallFunc_GetActorUpVector_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_Dot_VectorVector_ReturnValue__pf{};
	bool bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf{};
	bool bpfv__CallFunc_Not_PreBool_ReturnValue_4__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue_1__pf{};
	int32 __CurrentState = bpp__EntryPoint__pf;
	do
	{
		switch( __CurrentState )
		{
		case 181:
			{
			}
		case 182:
			{
			}
		case 183:
			{
				bpfv__CallFunc_VSize_ReturnValue__pf = UKismetMathLibrary::VSize(b0l__K2Node_ComponentBoundEvent_NormalImpulse__pf);
				bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Greater_FloatFloat(bpfv__CallFunc_VSize_ReturnValue__pf, 300.000000);
				if (!bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 187;
					break;
				}
			}
		case 184:
			{
				bpv__Crashed__pf = true;
			}
		case 185:
			{
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpv__DroneBody__pf->SetPhysicsLinearVelocity(FVector(0.000000,0.000000,0.000000), false, FName(TEXT("None")));
				}
			}
		case 186:
			{
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpv__DroneBody__pf->UPrimitiveComponent::SetPhysicsAngularVelocityInDegrees(FVector(0.000000,0.000000,0.000000), false, FName(TEXT("None")));
				}
				__CurrentState = -1;
				break;
			}
		case 187:
			{
				bpfv__CallFunc_GetActorUpVector_ReturnValue__pf = AActor::GetActorUpVector();
				bpfv__CallFunc_Dot_VectorVector_ReturnValue__pf = UKismetMathLibrary::Dot_VectorVector(bpfv__CallFunc_GetActorUpVector_ReturnValue__pf, FVector(0.000000,0.000000,1.000000));
				bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Less_FloatFloat(bpfv__CallFunc_Dot_VectorVector_ReturnValue__pf, 0.300000);
				if (!bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 188;
					break;
				}
				__CurrentState = 184;
				break;
			}
		case 188:
			{
				bpfv__CallFunc_Not_PreBool_ReturnValue_4__pf = UKismetMathLibrary::Not_PreBool(bpv__Landed__pf);
				bpfv__CallFunc_BooleanAND_ReturnValue_1__pf = UKismetMathLibrary::BooleanAND(bpv__TakeoffxPerformed__pfT, bpfv__CallFunc_Not_PreBool_ReturnValue_4__pf);
				if (!bpfv__CallFunc_BooleanAND_ReturnValue_1__pf)
				{
					__CurrentState = -1;
					break;
				}
			}
		case 189:
			{
				bpv__Landed__pf = true;
				__CurrentState = -1;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__InpAxisEvt_Throttle_K2Node_InputAxisEvent_0__pf(float bpp__AxisValue__pf)
{
	b0l__K2Node_InputAxisEvent_AxisValue__pf = bpp__AxisValue__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_0(225);
}
void ABP_Drone_C__pf2264400134::bpf__ReceiveEndPlay__pf(EEndPlayReason::Type bpp__EndPlayReason__pf)
{
	b0l__K2Node_Event_EndPlayReason__pf = bpp__EndPlayReason__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_5(213);
}
void ABP_Drone_C__pf2264400134::bpf__SwitchxMotors__pfT()
{
	bpf__ExecuteUbergraph_BP_Drone__pf_0(205);
}
void ABP_Drone_C__pf2264400134::bpf__BndEvt__DroneBody_K2Node_ComponentBoundEvent_0_ComponentHitSignature__DelegateSignature__pf(UPrimitiveComponent* bpp__HitComponent__pf, AActor* bpp__OtherActor__pf, UPrimitiveComponent* bpp__OtherComp__pf, FVector bpp__NormalImpulse__pf, FHitResult const& bpp__Hit__pf__const)
{
	typedef FHitResult  T__Local__43;
	T__Local__43& bpp__Hit__pf = *const_cast<T__Local__43 *>(&bpp__Hit__pf__const);
	b0l__K2Node_ComponentBoundEvent_HitComponent__pf = bpp__HitComponent__pf;
	b0l__K2Node_ComponentBoundEvent_OtherActor__pf = bpp__OtherActor__pf;
	b0l__K2Node_ComponentBoundEvent_OtherComp__pf = bpp__OtherComp__pf;
	b0l__K2Node_ComponentBoundEvent_NormalImpulse__pf = bpp__NormalImpulse__pf;
	b0l__K2Node_ComponentBoundEvent_Hit__pf = bpp__Hit__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_6(181);
}
void ABP_Drone_C__pf2264400134::bpf__ReceiveTick__pf(float bpp__DeltaSeconds__pf)
{
	b0l__K2Node_Event_DeltaSeconds__pf = bpp__DeltaSeconds__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_2(142);
}
void ABP_Drone_C__pf2264400134::bpf__ReceiveBeginPlay__pf()
{
	bpf__ExecuteUbergraph_BP_Drone__pf_3(122);
}
void ABP_Drone_C__pf2264400134::bpf__InpActEvt_DronexModexCycle_K2Node_InputActionEvent_0__pfTT(FKey bpp__Key__pf)
{
	b0l__K2Node_InputActionEvent_Key__pf = bpp__Key__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_1(224);
}
void ABP_Drone_C__pf2264400134::bpf__InpActEvt_CameraxSwitch_K2Node_InputActionEvent_1__pfT(FKey bpp__Key__pf)
{
	b0l__K2Node_InputActionEvent_Key_1__pf = bpp__Key__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_4(223);
}
void ABP_Drone_C__pf2264400134::bpf__InpActEvt_Motors_K2Node_InputActionEvent_2__pf(FKey bpp__Key__pf)
{
	b0l__K2Node_InputActionEvent_Key_2__pf = bpp__Key__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_0(78);
}
void ABP_Drone_C__pf2264400134::bpf__InpActEvt_Reset_K2Node_InputActionEvent_3__pf(FKey bpp__Key__pf)
{
	b0l__K2Node_InputActionEvent_Key_3__pf = bpp__Key__pf;
	bpf__ExecuteUbergraph_BP_Drone__pf_2(190);
}
void ABP_Drone_C__pf2264400134::bpf__UserConstructionScript__pf()
{
	TArray<UBP_DroneMotorComponent_C__pf2264400134*> bpfv__K2Node_MakeArray_Array__pf{};
	bpfv__K2Node_MakeArray_Array__pf.SetNum(4, true);
	bpfv__K2Node_MakeArray_Array__pf[0] = bpv__MotorFR__pf;
	bpfv__K2Node_MakeArray_Array__pf[1] = bpv__MotorBL__pf;
	bpfv__K2Node_MakeArray_Array__pf[2] = bpv__MotorFL__pf;
	bpfv__K2Node_MakeArray_Array__pf[3] = bpv__MotorBR__pf;
	bpv__Motors__pf = bpfv__K2Node_MakeArray_Array__pf;
}
void ABP_Drone_C__pf2264400134::bpf__HandlexThrottle__pfT()
{
	float bpfv__CallFunc_Get_Axes_Throttle__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch__pf{};
	float bpfv__CallFunc_Get_Axes_Roll__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf{};
	bool bpfv__K2Node_SwitchEnum_CmpSuccess__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Subtract_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue_3__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_1__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_1__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_1__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_1__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_1__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_2__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_2__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_2__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_2__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_2__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf{};
	bool bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_3__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_3__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_3__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_3__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_3__pf{};
	bool bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf{};
	FVector bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	float bpfv__CallFunc_SelectFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Abs_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf{};
	int32 __CurrentState = 9;
	do
	{
		switch( __CurrentState )
		{
		case 9:
			{
			}
		case 1:
			{
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator0));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 2;
					break;
				}
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator1));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 7;
					break;
				}
				__CurrentState = -1;
				break;
			}
		case 2:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_3__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_3__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_3__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_3__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_3__pf);
				bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NotEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Throttle_3__pf, 0.000000);
				if (!bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 6;
					break;
				}
			}
		case 3:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_2__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_2__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_2__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_2__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_2__pf);
				bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Less_FloatFloat(bpfv__CallFunc_Get_Axes_Throttle_2__pf, 0.000000);
				bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf = AActor::K2_GetActorLocation();
				bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
				UKismetMathLibrary::BreakVector(bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
				bpfv__CallFunc_SelectFloat_ReturnValue__pf = UKismetMathLibrary::SelectFloat(bpv__MaxxDescentxSpeed__pfTT, bpv__MaxxClimbxSpeed__pfTT, bpfv__CallFunc_Less_FloatFloat_ReturnValue__pf);
				bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(bpfv__CallFunc_SelectFloat_ReturnValue__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Abs_ReturnValue__pf, bpfv__CallFunc_Get_Axes_Throttle_2__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_BreakVector_Z__pf, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf);
				bpv__DesiredxAltitude__pfT = bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf;
			}
		case 4:
			{
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxDescentxSpeed__pfTT);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf, 4.000000);
				bpfv__CallFunc_Subtract_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Subtract_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxClimbxSpeed__pfTT);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxClimbxSpeed__pfTT);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue_2__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Subtract_FloatFloat_ReturnValue__pf, 4.000000);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue_3__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf, 4.000000);
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Get_Axes_Throttle_1__pf, -1.000000, 1.000000, bpfv__CallFunc_Divide_FloatFloat_ReturnValue_2__pf, bpfv__CallFunc_Divide_FloatFloat_ReturnValue_3__pf);
				bpfv__CallFunc_FClamp_ReturnValue__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_MapRangeClamped_ReturnValue_1__pf, bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Divide_FloatFloat_ReturnValue_3__pf);
				bpv__LastxThrottlexForcexApplied__pfTTT = bpfv__CallFunc_FClamp_ReturnValue__pf;
			}
		case 5:
			{
				bpf__Throttle__pf(bpv__LastxThrottlexForcexApplied__pfTTT);
				__CurrentState = -1;
				break;
			}
		case 6:
			{
				bpf__AltitudexStabilization__pfT();
				__CurrentState = -1;
				break;
			}
		case 7:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxClimbxSpeed__pfTT);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf, 4.000000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf, -1.000000);
				bpfv__CallFunc_MapRangeClamped_ReturnValue__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Get_Axes_Throttle__pf, -1.000000, 1.000000, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf);
				bpv__LastxThrottlexForcexApplied__pfTTT = bpfv__CallFunc_MapRangeClamped_ReturnValue__pf;
			}
		case 8:
			{
				bpf__Throttle__pf(bpv__LastxThrottlexForcexApplied__pfTTT);
				__CurrentState = -1;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__Throttle__pf(float bpp__Force__pf)
{
	int32 bpfv__Temp_int_Loop_Counter_Variable__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue__pf{};
	int32 bpfv__Temp_int_Array_Index_Variable__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue__pf{};
	UBP_DroneMotorComponent_C__pf2264400134* bpfv__CallFunc_Array_Get_Item__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = 13;
	do
	{
		switch( __CurrentState )
		{
		case 13:
			{
			}
		case 1:
			{
			}
		case 2:
			{
			}
		case 3:
			{
				bpfv__Temp_int_Loop_Counter_Variable__pf = 0;
			}
		case 4:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = 0;
			}
		case 5:
			{
				bpfv__CallFunc_Array_Length_ReturnValue__pf = FCustomThunkTemplates::Array_Length(bpv__Motors__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue__pf = UKismetMathLibrary::Less_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, bpfv__CallFunc_Array_Length_ReturnValue__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue__pf)
				{
					__CurrentState = 10;
					break;
				}
			}
		case 6:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = bpfv__Temp_int_Loop_Counter_Variable__pf;
			}
		case 7:
			{
				__StateStack.Push(8);
				__CurrentState = 11;
				break;
			}
		case 8:
			{
			}
		case 9:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue__pf = UKismetMathLibrary::Add_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, 1);
				bpfv__Temp_int_Loop_Counter_Variable__pf = bpfv__CallFunc_Add_IntInt_ReturnValue__pf;
				__CurrentState = 5;
				break;
			}
		case 10:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 11:
			{
			}
		case 12:
			{
				FCustomThunkTemplates::Array_Get(bpv__Motors__pf, bpfv__Temp_int_Array_Index_Variable__pf, /*out*/ bpfv__CallFunc_Array_Get_Item__pf);
				if(::IsValid(bpfv__CallFunc_Array_Get_Item__pf))
				{
					bpfv__CallFunc_Array_Get_Item__pf->bpf__AddxForce__pfT(bpp__Force__pf);
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__AltitudexStabilization__pfT()
{
	float bpfv__NewxForce__pfT{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FVector bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	float bpfv__CallFunc_PID_Output__pf{};
	bool bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_SelectFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue__pf{};
	bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf = AActor::K2_GetActorLocation();
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_K2_GetActorLocation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	if(::IsValid(bpv__AltStabilizationPID__pf))
	{
		bpv__AltStabilizationPID__pf->bpf__PID__pf(bpv__DesiredxAltitude__pfT, bpfv__CallFunc_BreakVector_Z__pf, -1.000000, 1.000000, /*out*/ bpfv__CallFunc_PID_Output__pf);
	}
	bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxDescentxSpeed__pfTT);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GravityxForce__pfT, bpv__MaxxClimbxSpeed__pfTT);
	bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf, 4.000000);
	bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf, 4.000000);
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Greater_FloatFloat(bpfv__CallFunc_PID_Output__pf, 0.000000);
	bpfv__CallFunc_SelectFloat_ReturnValue__pf = UKismetMathLibrary::SelectFloat(bpfv__CallFunc_Divide_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf, bpfv__CallFunc_Greater_FloatFloat_ReturnValue__pf);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_PID_Output__pf, bpfv__CallFunc_SelectFloat_ReturnValue__pf);
	bpfv__CallFunc_FInterpTo_ReturnValue__pf = UKismetMathLibrary::FInterpTo(bpv__LastxThrottlexForcexApplied__pfTTT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 50.000000);
	bpfv__NewxForce__pfT = bpfv__CallFunc_FInterpTo_ReturnValue__pf;
	bpf__Throttle__pf(bpfv__NewxForce__pfT);
	bpv__LastxThrottlexForcexApplied__pfTTT = bpfv__NewxForce__pfT;
}
void ABP_Drone_C__pf2264400134::bpf__LimitxVelocities__pfT()
{
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	FVector bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	FVector bpfv__CallFunc_MakeVector_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_FClamp_ReturnValue__pf{};
	FVector bpfv__CallFunc_ClampVectorSize_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X_1__pf{};
	float bpfv__CallFunc_BreakVector_Y_1__pf{};
	float bpfv__CallFunc_BreakVector_Z_1__pf{};
	FVector bpfv__CallFunc_MakeVector_ReturnValue_1__pf(EForceInit::ForceInit);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf = bpv__DroneBody__pf->UPrimitiveComponent::GetPhysicsLinearVelocity(FName(TEXT("None")));
	}
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpv__MaxxSpeed__pfT, -1.000000);
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	bpfv__CallFunc_MakeVector_ReturnValue__pf = UKismetMathLibrary::MakeVector(bpfv__CallFunc_BreakVector_X__pf, bpfv__CallFunc_BreakVector_Y__pf, 0.000000);
	bpfv__CallFunc_FClamp_ReturnValue__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_BreakVector_Z__pf, bpv__MaxxDescentxSpeed__pfTT, bpv__MaxxClimbxSpeed__pfTT);
	bpfv__CallFunc_ClampVectorSize_ReturnValue__pf = UKismetMathLibrary::ClampVectorSize(bpfv__CallFunc_MakeVector_ReturnValue__pf, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpv__MaxxSpeed__pfT);
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_ClampVectorSize_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X_1__pf, /*out*/ bpfv__CallFunc_BreakVector_Y_1__pf, /*out*/ bpfv__CallFunc_BreakVector_Z_1__pf);
	bpfv__CallFunc_MakeVector_ReturnValue_1__pf = UKismetMathLibrary::MakeVector(bpfv__CallFunc_BreakVector_X_1__pf, bpfv__CallFunc_BreakVector_Y_1__pf, bpfv__CallFunc_FClamp_ReturnValue__pf);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpv__DroneBody__pf->SetPhysicsLinearVelocity(bpfv__CallFunc_MakeVector_ReturnValue_1__pf, false, FName(TEXT("None")));
	}
}
void ABP_Drone_C__pf2264400134::bpf__ApplyxForces__pfT()
{
	int32 bpfv__Temp_int_Loop_Counter_Variable__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue__pf{};
	int32 bpfv__Temp_int_Array_Index_Variable__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue__pf{};
	UBP_DroneMotorComponent_C__pf2264400134* bpfv__CallFunc_Array_Get_Item__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = 13;
	do
	{
		switch( __CurrentState )
		{
		case 13:
			{
			}
		case 1:
			{
			}
		case 2:
			{
			}
		case 3:
			{
				bpfv__Temp_int_Loop_Counter_Variable__pf = 0;
			}
		case 4:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = 0;
			}
		case 5:
			{
				bpfv__CallFunc_Array_Length_ReturnValue__pf = FCustomThunkTemplates::Array_Length(bpv__Motors__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue__pf = UKismetMathLibrary::Less_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, bpfv__CallFunc_Array_Length_ReturnValue__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue__pf)
				{
					__CurrentState = 10;
					break;
				}
			}
		case 6:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = bpfv__Temp_int_Loop_Counter_Variable__pf;
			}
		case 7:
			{
				__StateStack.Push(8);
				__CurrentState = 11;
				break;
			}
		case 8:
			{
			}
		case 9:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue__pf = UKismetMathLibrary::Add_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, 1);
				bpfv__Temp_int_Loop_Counter_Variable__pf = bpfv__CallFunc_Add_IntInt_ReturnValue__pf;
				__CurrentState = 5;
				break;
			}
		case 10:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 11:
			{
			}
		case 12:
			{
				FCustomThunkTemplates::Array_Get(bpv__Motors__pf, bpfv__Temp_int_Array_Index_Variable__pf, /*out*/ bpfv__CallFunc_Array_Get_Item__pf);
				if(::IsValid(bpfv__CallFunc_Array_Get_Item__pf))
				{
					bpfv__CallFunc_Array_Get_Item__pf->bpf__ApplyxForce__pfT();
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__Pitch__pf(float bpp__Force__pf)
{
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpp__Force__pf, -1.000000);
	if(::IsValid(bpv__MotorBL__pf))
	{
		bpv__MotorBL__pf->bpf__AddxForce__pfT(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
	}
	if(::IsValid(bpv__MotorBR__pf))
	{
		bpv__MotorBR__pf->bpf__AddxForce__pfT(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
	}
	if(::IsValid(bpv__MotorFR__pf))
	{
		bpv__MotorFR__pf->bpf__AddxForce__pfT(bpp__Force__pf);
	}
	if(::IsValid(bpv__MotorFL__pf))
	{
		bpv__MotorFL__pf->bpf__AddxForce__pfT(bpp__Force__pf);
	}
}
void ABP_Drone_C__pf2264400134::bpf__Roll__pf(float bpp__Force__pf)
{
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpp__Force__pf, -1.000000);
	if(::IsValid(bpv__MotorFR__pf))
	{
		bpv__MotorFR__pf->bpf__AddxForce__pfT(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
	}
	if(::IsValid(bpv__MotorBR__pf))
	{
		bpv__MotorBR__pf->bpf__AddxForce__pfT(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
	}
	if(::IsValid(bpv__MotorFL__pf))
	{
		bpv__MotorFL__pf->bpf__AddxForce__pfT(bpp__Force__pf);
	}
	if(::IsValid(bpv__MotorBL__pf))
	{
		bpv__MotorBL__pf->bpf__AddxForce__pfT(bpp__Force__pf);
	}
}
void ABP_Drone_C__pf2264400134::bpf__HandlexPitch__pfT()
{
	float bpfv__CallFunc_Get_Axes_Throttle__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch__pf{};
	float bpfv__CallFunc_Get_Axes_Roll__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bool bpfv__K2Node_SwitchEnum_CmpSuccess__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Get_Forward_Velocity_Velocity__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_1__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_1__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_1__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_1__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_1__pf{};
	float bpfv__CallFunc_Abs_ReturnValue__pf{};
	bool bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	bool bpfv__CallFunc_Pitch_Stabilization_Angle_Reached__pf{};
	float bpfv__CallFunc_BreakRotator_Roll__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf{};
	bool bpfv__CallFunc_Pitch_Stabilization_Angle_Reached_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_4__pf{};
	int32 __CurrentState = 9;
	do
	{
		switch( __CurrentState )
		{
		case 9:
			{
			}
		case 1:
			{
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator0));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 2;
					break;
				}
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator1));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 8;
					break;
				}
				__CurrentState = -1;
				break;
			}
		case 2:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NotEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Pitch_1__pf, 0.000000);
				if (!bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 5;
					break;
				}
			}
		case 3:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Multiply_FloatFloat(bpv__MaxxTiltxAngle__pfTT, -1.000000);
				bpfv__CallFunc_MapRangeClamped_ReturnValue__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Get_Axes_Pitch_1__pf, -1.000000, 1.000000, bpv__MaxxTiltxAngle__pfTT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf);
				bpf__PitchxStabilization__pfT(bpfv__CallFunc_MapRangeClamped_ReturnValue__pf, /*out*/ bpfv__CallFunc_Pitch_Stabilization_Angle_Reached__pf);
			}
		case 4:
			{
				bpf__GetxForwardxVelocity__pfTT(/*out*/ bpfv__CallFunc_Get_Forward_Velocity_Velocity__pf);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Get_Forward_Velocity_Velocity__pf, bpv__MaxxSpeed__pfT);
				bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf);
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
				}
				UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_BreakRotator_Pitch__pf, -0.650000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_4__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf, bpfv__CallFunc_Abs_ReturnValue__pf);
				bpv__CounterxPitchxAngle__pfTT = bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_4__pf;
				__CurrentState = -1;
				break;
			}
		case 5:
			{
				bpf__PitchxStabilization__pfT(bpv__CounterxPitchxAngle__pfTT, /*out*/ bpfv__CallFunc_Pitch_Stabilization_Angle_Reached_1__pf);
			}
		case 6:
			{
				if (!bpfv__CallFunc_Pitch_Stabilization_Angle_Reached_1__pf)
				{
					__CurrentState = -1;
					break;
				}
			}
		case 7:
			{
				bpv__CounterxPitchxAngle__pfTT = 0.000000;
				__CurrentState = -1;
				break;
			}
		case 8:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Get_Axes_Pitch__pf, bpv__PitchxRollxForcexMultiplier__pfTTT);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, -1.000000);
				bpf__Pitch__pf(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf);
				__CurrentState = -1;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__HandlexRoll__pfT()
{
	float bpfv__CallFunc_Get_Axes_Throttle__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch__pf{};
	float bpfv__CallFunc_Get_Axes_Roll__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bool bpfv__K2Node_SwitchEnum_CmpSuccess__pf{};
	float bpfv__CallFunc_Get_Right_Velocity_Velocity__pf{};
	float bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_Abs_ReturnValue__pf{};
	float bpfv__CallFunc_BreakRotator_Roll__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_1__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_1__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_1__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_1__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf{};
	bool bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf{};
	bool bpfv__CallFunc_Roll_Stabilization_Angle_Reached__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue__pf{};
	bool bpfv__CallFunc_Roll_Stabilization_Angle_Reached_1__pf{};
	int32 __CurrentState = 9;
	do
	{
		switch( __CurrentState )
		{
		case 9:
			{
			}
		case 1:
			{
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator0));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 2;
					break;
				}
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator1));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 8;
					break;
				}
				__CurrentState = -1;
				break;
			}
		case 2:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NotEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Roll_1__pf, 0.000000);
				if (!bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 5;
					break;
				}
			}
		case 3:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Multiply_FloatFloat(bpv__MaxxTiltxAngle__pfTT, -1.000000);
				bpfv__CallFunc_MapRangeClamped_ReturnValue__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Get_Axes_Roll_1__pf, -1.000000, 1.000000, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_3__pf, bpv__MaxxTiltxAngle__pfTT);
				bpf__RollxStabilization__pfT(bpfv__CallFunc_MapRangeClamped_ReturnValue__pf, /*out*/ bpfv__CallFunc_Roll_Stabilization_Angle_Reached_1__pf);
			}
		case 4:
			{
				bpf__GetxRightxVelocity__pfTT(/*out*/ bpfv__CallFunc_Get_Right_Velocity_Velocity__pf);
				bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf = FCustomThunkTemplates::Divide_FloatFloat(bpfv__CallFunc_Get_Right_Velocity_Velocity__pf, bpv__MaxxSpeed__pfT);
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
				}
				bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(bpfv__CallFunc_Divide_FloatFloat_ReturnValue__pf);
				UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_BreakRotator_Roll__pf, -0.650000);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_Abs_ReturnValue__pf);
				bpv__CounterxRollxAngle__pfTT = bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_2__pf;
				__CurrentState = -1;
				break;
			}
		case 5:
			{
				bpf__RollxStabilization__pfT(bpv__CounterxRollxAngle__pfTT, /*out*/ bpfv__CallFunc_Roll_Stabilization_Angle_Reached__pf);
			}
		case 6:
			{
				if (!bpfv__CallFunc_Roll_Stabilization_Angle_Reached__pf)
				{
					__CurrentState = -1;
					break;
				}
			}
		case 7:
			{
				bpv__CounterxRollxAngle__pfTT = 0.000000;
				__CurrentState = -1;
				break;
			}
		case 8:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Get_Axes_Roll__pf, bpv__PitchxRollxForcexMultiplier__pfTTT);
				bpf__Roll__pf(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
				__CurrentState = -1;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__HandlexYaw__pfT()
{
	bool bpfv__K2Node_SwitchEnum_CmpSuccess__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch__pf{};
	float bpfv__CallFunc_Get_Axes_Roll__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal__pf{};
	float bpfv__CallFunc_Get_Axes_Throttle_1__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch_1__pf{};
	float bpfv__CallFunc_Get_Axes_Roll_1__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw_1__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal_1__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bool bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf{};
	int32 __CurrentState = 5;
	do
	{
		switch( __CurrentState )
		{
		case 5:
			{
			}
		case 1:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw_1__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal_1__pf);
				bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NotEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Yaw_1__pf, 0.000000);
				if (!bpfv__CallFunc_NotEqual_FloatFloat_ReturnValue__pf)
				{
					__CurrentState = 3;
					break;
				}
			}
		case 2:
			{
				bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal__pf);
				bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Get_Axes_Yaw__pf, bpv__MaxxAngularxVelocity__pfTT);
				bpf__YawxStabilization__pfT(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf);
				__CurrentState = -1;
				break;
			}
		case 3:
			{
				bpfv__K2Node_SwitchEnum_CmpSuccess__pf = UKismetMathLibrary::NotEqual_ByteByte(static_cast<uint8>(bpv__DronexMode__pfT), static_cast<uint8>(E__DroneModeEnum__pf::NewEnumerator0));
				if (!bpfv__K2Node_SwitchEnum_CmpSuccess__pf)
				{
					__CurrentState = 4;
					break;
				}
				__CurrentState = -1;
				break;
			}
		case 4:
			{
				bpf__YawxStabilization__pfT(0.000000);
				__CurrentState = -1;
				break;
			}
		default:
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__PitchxStabilization__pfT(float bpp__StabilizexatxAngle__pfTT, /*out*/ bool& bpp__AnglexReached__pfT)
{
	float bpfv__NewxForce__pfT{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakRotator_Roll__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw__pf{};
	float bpfv__CallFunc_BreakRotator_Roll_1__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch_1__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw_1__pf{};
	bool bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_PID_Output__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue__pf{};
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw_1__pf);
	if(::IsValid(bpv__PitchStabilizationPID__pf))
	{
		bpv__PitchStabilizationPID__pf->bpf__PID__pf(bpp__StabilizexatxAngle__pfTT, bpfv__CallFunc_BreakRotator_Pitch_1__pf, -1.000000, 1.000000, /*out*/ bpfv__CallFunc_PID_Output__pf);
	}
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_PID_Output__pf, bpv__PitchxRollxForcexMultiplier__pfTTT);
	bpfv__CallFunc_FInterpTo_ReturnValue__pf = UKismetMathLibrary::FInterpTo(bpv__LastxPitchxForcexApplied__pfTTT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 50.000000);
	bpfv__NewxForce__pfT = bpfv__CallFunc_FInterpTo_ReturnValue__pf;
	bpf__Pitch__pf(bpfv__NewxForce__pfT);
	bpv__LastxPitchxForcexApplied__pfTTT = bpfv__NewxForce__pfT;
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw__pf);
	bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NearlyEqual_FloatFloat(bpp__StabilizexatxAngle__pfTT, bpfv__CallFunc_BreakRotator_Pitch__pf, 5.000000);
	bpp__AnglexReached__pfT = bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf;
}
void ABP_Drone_C__pf2264400134::bpf__RollxStabilization__pfT(float bpp__StabilizexatxAngle__pfTT, /*out*/ bool& bpp__AnglexReached__pfT)
{
	float bpfv__NewxForce__pfT{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakRotator_Roll__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw__pf{};
	float bpfv__CallFunc_BreakRotator_Roll_1__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch_1__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw_1__pf{};
	bool bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_PID_Output__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue__pf{};
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw__pf);
	if(::IsValid(bpv__RollStabilizationPID__pf))
	{
		bpv__RollStabilizationPID__pf->bpf__PID__pf(bpp__StabilizexatxAngle__pfTT, bpfv__CallFunc_BreakRotator_Roll__pf, -1.000000, 1.000000, /*out*/ bpfv__CallFunc_PID_Output__pf);
	}
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_PID_Output__pf, bpv__PitchxRollxForcexMultiplier__pfTTT);
	bpfv__CallFunc_FInterpTo_ReturnValue__pf = UKismetMathLibrary::FInterpTo(bpv__LastxRollxForcexApplied__pfTTT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 50.000000);
	bpfv__NewxForce__pfT = bpfv__CallFunc_FInterpTo_ReturnValue__pf;
	bpf__Roll__pf(bpfv__NewxForce__pfT);
	bpv__LastxRollxForcexApplied__pfTTT = bpfv__NewxForce__pfT;
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch_1__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw_1__pf);
	bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NearlyEqual_FloatFloat(bpp__StabilizexatxAngle__pfTT, bpfv__CallFunc_BreakRotator_Roll_1__pf, 5.000000);
	bpp__AnglexReached__pfT = bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf;
}
void ABP_Drone_C__pf2264400134::bpf__YawxStabilization__pfT(float bpp__DesiredxAngularxVelocity__pfTT)
{
	float bpfv__NewxTorque__pfT{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FVector bpfv__CallFunc_GetPhysicsAngularVelocityInDegrees_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	float bpfv__CallFunc_PID_Output__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue__pf{};
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_GetPhysicsAngularVelocityInDegrees_ReturnValue__pf = bpv__DroneBody__pf->UPrimitiveComponent::GetPhysicsAngularVelocityInDegrees(FName(TEXT("None")));
	}
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_GetPhysicsAngularVelocityInDegrees_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	if(::IsValid(bpv__YawStabilizationPID__pf))
	{
		bpv__YawStabilizationPID__pf->bpf__PID__pf(bpp__DesiredxAngularxVelocity__pfTT, bpfv__CallFunc_BreakVector_Z__pf, -1.000000, 1.000000, /*out*/ bpfv__CallFunc_PID_Output__pf);
	}
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_PID_Output__pf, bpv__YawxTorquexForce__pfTT);
	bpfv__CallFunc_FInterpTo_ReturnValue__pf = UKismetMathLibrary::FInterpTo(bpv__LastxYawxTorquexApplied__pfTTT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 10.000000);
	bpfv__NewxTorque__pfT = bpfv__CallFunc_FInterpTo_ReturnValue__pf;
	bpf__Yaw__pf(bpfv__NewxTorque__pfT);
	bpv__LastxYawxTorquexApplied__pfTTT = bpfv__NewxTorque__pfT;
}
void ABP_Drone_C__pf2264400134::bpf__StopxDrifting__pfT()
{
	float bpfv__CallFunc_Get_Axes_Throttle__pf{};
	float bpfv__CallFunc_Get_Axes_Pitch__pf{};
	float bpfv__CallFunc_Get_Axes_Roll__pf{};
	float bpfv__CallFunc_Get_Axes_Yaw__pf{};
	float bpfv__CallFunc_Get_Axes_Gimbal__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_BreakRotator_Roll__pf{};
	float bpfv__CallFunc_BreakRotator_Pitch__pf{};
	float bpfv__CallFunc_BreakRotator_Yaw__pf{};
	bool bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf{};
	bool bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf{};
	bool bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue_1__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue__pf{};
	bool bpfv__CallFunc_BooleanAND_ReturnValue_1__pf{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_2__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue__pf{};
	float bpfv__CallFunc_FInterpTo_ReturnValue_1__pf{};
	float bpfv__CallFunc_SelectFloat_ReturnValue__pf{};
	float bpfv__CallFunc_SelectFloat_ReturnValue_1__pf{};
	FVector bpfv__CallFunc_MakeVector_ReturnValue__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_GreaterGreater_VectorRotator_ReturnValue__pf(EForceInit::ForceInit);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf = bpv__DroneBody__pf->UPrimitiveComponent::GetPhysicsLinearVelocity(FName(TEXT("None")));
	}
	bpf__GetxAxes__pfT(/*out*/ bpfv__CallFunc_Get_Axes_Throttle__pf, /*out*/ bpfv__CallFunc_Get_Axes_Pitch__pf, /*out*/ bpfv__CallFunc_Get_Axes_Roll__pf, /*out*/ bpfv__CallFunc_Get_Axes_Yaw__pf, /*out*/ bpfv__CallFunc_Get_Axes_Gimbal__pf);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Roll__pf, 0.000000);
	UKismetMathLibrary::BreakRotator(bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakRotator_Roll__pf, /*out*/ bpfv__CallFunc_BreakRotator_Pitch__pf, /*out*/ bpfv__CallFunc_BreakRotator_Yaw__pf);
	bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::EqualEqual_FloatFloat(bpfv__CallFunc_Get_Axes_Pitch__pf, 0.000000);
	bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf = UKismetMathLibrary::NearlyEqual_FloatFloat(bpfv__CallFunc_BreakRotator_Pitch__pf, 0.000000, 5.000000);
	bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::NearlyEqual_FloatFloat(bpfv__CallFunc_BreakRotator_Roll__pf, 0.000000, 5.000000);
	bpfv__CallFunc_BooleanAND_ReturnValue__pf = UKismetMathLibrary::BooleanAND(bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue_1__pf, bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue__pf);
	bpfv__CallFunc_BooleanAND_ReturnValue_1__pf = UKismetMathLibrary::BooleanAND(bpfv__CallFunc_EqualEqual_FloatFloat_ReturnValue__pf, bpfv__CallFunc_NearlyEqual_FloatFloat_ReturnValue_1__pf);
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_2__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf = UKismetMathLibrary::LessLess_VectorRotator(bpfv__CallFunc_GetPhysicsLinearVelocity_ReturnValue__pf, bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_2__pf);
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	bpfv__CallFunc_FInterpTo_ReturnValue__pf = UKismetMathLibrary::FInterpTo(bpfv__CallFunc_BreakVector_X__pf, 0.000000, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 1.000000);
	bpfv__CallFunc_FInterpTo_ReturnValue_1__pf = UKismetMathLibrary::FInterpTo(bpfv__CallFunc_BreakVector_Y__pf, 0.000000, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf, 1.000000);
	bpfv__CallFunc_SelectFloat_ReturnValue__pf = UKismetMathLibrary::SelectFloat(bpfv__CallFunc_FInterpTo_ReturnValue__pf, bpfv__CallFunc_BreakVector_X__pf, bpfv__CallFunc_BooleanAND_ReturnValue__pf);
	bpfv__CallFunc_SelectFloat_ReturnValue_1__pf = UKismetMathLibrary::SelectFloat(bpfv__CallFunc_FInterpTo_ReturnValue_1__pf, bpfv__CallFunc_BreakVector_Y__pf, bpfv__CallFunc_BooleanAND_ReturnValue_1__pf);
	bpfv__CallFunc_MakeVector_ReturnValue__pf = UKismetMathLibrary::MakeVector(bpfv__CallFunc_SelectFloat_ReturnValue__pf, bpfv__CallFunc_SelectFloat_ReturnValue_1__pf, bpfv__CallFunc_BreakVector_Z__pf);
	bpfv__CallFunc_GreaterGreater_VectorRotator_ReturnValue__pf = UKismetMathLibrary::GreaterGreater_VectorRotator(bpfv__CallFunc_MakeVector_ReturnValue__pf, bpfv__CallFunc_K2_GetComponentRotation_ReturnValue_1__pf);
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpv__DroneBody__pf->SetPhysicsLinearVelocity(bpfv__CallFunc_GreaterGreater_VectorRotator_ReturnValue__pf, false, FName(TEXT("None")));
	}
}
void ABP_Drone_C__pf2264400134::bpf__GetxAxes__pfT(/*out*/ float& bpp__Throttle__pf, /*out*/ float& bpp__Pitch__pf, /*out*/ float& bpp__Roll__pf, /*out*/ float& bpp__Yaw__pf, /*out*/ float& bpp__Gimbal__pf)
{
	float bpfv__CallFunc_GetInputAxisValue_ReturnValue__pf{};
	float bpfv__CallFunc_Array_Get_Item__pf{};
	float bpfv__CallFunc_Array_Get_Item_1__pf{};
	float bpfv__CallFunc_GetInputAxisValue_ReturnValue_1__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_Array_Get_Item_2__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue__pf{};
	float bpfv__CallFunc_Deadzone_Axis_Zoned_Axis__pf{};
	float bpfv__CallFunc_Array_Get_Item_3__pf{};
	float bpfv__CallFunc_GetInputAxisValue_ReturnValue_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf{};
	float bpfv__CallFunc_Array_Get_Item_4__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue_1__pf{};
	float bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_1__pf{};
	float bpfv__CallFunc_Array_Get_Item_5__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_4__pf{};
	float bpfv__CallFunc_Array_Get_Item_6__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_5__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue_2__pf{};
	float bpfv__CallFunc_Array_Get_Item_7__pf{};
	float bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_2__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_6__pf{};
	float bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf{};
	float bpfv__CallFunc_GetInputAxisValue_ReturnValue_3__pf{};
	float bpfv__CallFunc_GetInputAxisValue_ReturnValue_4__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_7__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue_3__pf{};
	float bpfv__CallFunc_Add_FloatFloat_ReturnValue_8__pf{};
	float bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_3__pf{};
	float bpfv__CallFunc_FClamp_ReturnValue_4__pf{};
	bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf = UGameplayStatics::GetWorldDeltaSeconds(this);
	bpfv__CallFunc_GetInputAxisValue_ReturnValue_3__pf = AActor::GetInputAxisValue(FName(TEXT("Gimbal")));
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_GetInputAxisValue_ReturnValue_3__pf, bpfv__CallFunc_GetWorldDeltaSeconds_ReturnValue__pf);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf, 0.200000);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_8__pf = UKismetMathLibrary::Add_FloatFloat(bpv__GimbalxPitch__pfT, bpfv__CallFunc_Multiply_FloatFloat_ReturnValue_1__pf);
	bpfv__CallFunc_FClamp_ReturnValue_4__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_Add_FloatFloat_ReturnValue_8__pf, -1.000000, 1.000000);
	bpv__GimbalxPitch__pfT = bpfv__CallFunc_FClamp_ReturnValue_4__pf;
	bpfv__CallFunc_GetInputAxisValue_ReturnValue__pf = AActor::GetInputAxisValue(FName(TEXT("Roll")));
	FCustomThunkTemplates::Array_Get(bpv__HandGestureInput__pf, 3, /*out*/ bpfv__CallFunc_Array_Get_Item__pf);
	FCustomThunkTemplates::Array_Get(bpv__JoystickInput__pf, 3, /*out*/ bpfv__CallFunc_Array_Get_Item_1__pf);
	bpfv__CallFunc_GetInputAxisValue_ReturnValue_1__pf = AActor::GetInputAxisValue(FName(TEXT("Pitch")));
	bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Array_Get_Item_1__pf, bpfv__CallFunc_Array_Get_Item__pf);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue__pf, bpfv__CallFunc_GetInputAxisValue_ReturnValue__pf);
	FCustomThunkTemplates::Array_Get(bpv__HandGestureInput__pf, 2, /*out*/ bpfv__CallFunc_Array_Get_Item_2__pf);
	bpfv__CallFunc_FClamp_ReturnValue__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_Add_FloatFloat_ReturnValue_1__pf, -1.000000, 1.000000);
	bpf__DeadzonexAxis__pfT(bpfv__CallFunc_FClamp_ReturnValue__pf, 0.250000, /*out*/ bpfv__CallFunc_Deadzone_Axis_Zoned_Axis__pf);
	FCustomThunkTemplates::Array_Get(bpv__JoystickInput__pf, 2, /*out*/ bpfv__CallFunc_Array_Get_Item_3__pf);
	bpfv__CallFunc_GetInputAxisValue_ReturnValue_2__pf = AActor::GetInputAxisValue(FName(TEXT("Yaw")));
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Array_Get_Item_3__pf, bpfv__CallFunc_Array_Get_Item_2__pf);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_2__pf, bpfv__CallFunc_GetInputAxisValue_ReturnValue_1__pf);
	FCustomThunkTemplates::Array_Get(bpv__HandGestureInput__pf, 1, /*out*/ bpfv__CallFunc_Array_Get_Item_4__pf);
	bpfv__CallFunc_FClamp_ReturnValue_1__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_Add_FloatFloat_ReturnValue_3__pf, -1.000000, 1.000000);
	bpf__DeadzonexAxis__pfT(bpfv__CallFunc_FClamp_ReturnValue_1__pf, 0.250000, /*out*/ bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_1__pf);
	FCustomThunkTemplates::Array_Get(bpv__JoystickInput__pf, 1, /*out*/ bpfv__CallFunc_Array_Get_Item_5__pf);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_4__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Array_Get_Item_5__pf, bpfv__CallFunc_Array_Get_Item_4__pf);
	FCustomThunkTemplates::Array_Get(bpv__HandGestureInput__pf, 0, /*out*/ bpfv__CallFunc_Array_Get_Item_6__pf);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_5__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_4__pf, bpfv__CallFunc_GetInputAxisValue_ReturnValue_2__pf);
	bpfv__CallFunc_FClamp_ReturnValue_2__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_Add_FloatFloat_ReturnValue_5__pf, -1.000000, 1.000000);
	FCustomThunkTemplates::Array_Get(bpv__JoystickInput__pf, 0, /*out*/ bpfv__CallFunc_Array_Get_Item_7__pf);
	bpf__DeadzonexAxis__pfT(bpfv__CallFunc_FClamp_ReturnValue_2__pf, 0.250000, /*out*/ bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_2__pf);
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_6__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Array_Get_Item_7__pf, bpfv__CallFunc_Array_Get_Item_6__pf);
	bpfv__CallFunc_GetInputAxisValue_ReturnValue_4__pf = AActor::GetInputAxisValue(FName(TEXT("Throttle")));
	bpfv__CallFunc_Add_FloatFloat_ReturnValue_7__pf = UKismetMathLibrary::Add_FloatFloat(bpfv__CallFunc_Add_FloatFloat_ReturnValue_6__pf, bpfv__CallFunc_GetInputAxisValue_ReturnValue_4__pf);
	bpfv__CallFunc_FClamp_ReturnValue_3__pf = UKismetMathLibrary::FClamp(bpfv__CallFunc_Add_FloatFloat_ReturnValue_7__pf, -1.000000, 1.000000);
	bpf__DeadzonexAxis__pfT(bpfv__CallFunc_FClamp_ReturnValue_3__pf, 0.250000, /*out*/ bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_3__pf);
	bpp__Throttle__pf = bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_3__pf;
	bpp__Pitch__pf = bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_1__pf;
	bpp__Roll__pf = bpfv__CallFunc_Deadzone_Axis_Zoned_Axis__pf;
	bpp__Yaw__pf = bpfv__CallFunc_Deadzone_Axis_Zoned_Axis_2__pf;
	bpp__Gimbal__pf = bpv__GimbalxPitch__pfT;
}
void ABP_Drone_C__pf2264400134::bpf__DeadzonexAxis__pfT(float bpp__Axis__pf, float bpp__Deadzone__pf, /*out*/ float& bpp__ZonedxAxis__pfT)
{
	float bpfv__CallFunc_SignOfFloat_ReturnValue__pf{};
	float bpfv__CallFunc_Abs_ReturnValue__pf{};
	float bpfv__CallFunc_MapRangeClamped_ReturnValue__pf{};
	float bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf{};
	bpfv__CallFunc_SignOfFloat_ReturnValue__pf = UKismetMathLibrary::SignOfFloat(bpp__Axis__pf);
	bpfv__CallFunc_Abs_ReturnValue__pf = UKismetMathLibrary::Abs(bpp__Axis__pf);
	bpfv__CallFunc_MapRangeClamped_ReturnValue__pf = UKismetMathLibrary::MapRangeClamped(bpfv__CallFunc_Abs_ReturnValue__pf, bpp__Deadzone__pf, 1.000000, 0.000000, 1.000000);
	bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_FloatFloat(bpfv__CallFunc_SignOfFloat_ReturnValue__pf, bpfv__CallFunc_MapRangeClamped_ReturnValue__pf);
	bpp__ZonedxAxis__pfT = bpfv__CallFunc_Multiply_FloatFloat_ReturnValue__pf;
}
void ABP_Drone_C__pf2264400134::bpf__Yaw__pf(float bpp__Torque__pf)
{
	int32 bpfv__Temp_int_Loop_Counter_Variable__pf{};
	int32 bpfv__CallFunc_Add_IntInt_ReturnValue__pf{};
	int32 bpfv__Temp_int_Array_Index_Variable__pf{};
	FVector bpfv__CallFunc_GetUpVector_ReturnValue__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_Multiply_VectorFloat_ReturnValue__pf(EForceInit::ForceInit);
	UBP_DroneMotorComponent_C__pf2264400134* bpfv__CallFunc_Array_Get_Item__pf{};
	int32 bpfv__CallFunc_Array_Length_ReturnValue__pf{};
	bool bpfv__CallFunc_Less_IntInt_ReturnValue__pf{};
	TArray< int32, TInlineAllocator<8> > __StateStack;

	int32 __CurrentState = 13;
	do
	{
		switch( __CurrentState )
		{
		case 13:
			{
			}
		case 1:
			{
			}
		case 2:
			{
			}
		case 3:
			{
				bpfv__Temp_int_Loop_Counter_Variable__pf = 0;
			}
		case 4:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = 0;
			}
		case 5:
			{
				bpfv__CallFunc_Array_Length_ReturnValue__pf = FCustomThunkTemplates::Array_Length(bpv__Motors__pf);
				bpfv__CallFunc_Less_IntInt_ReturnValue__pf = UKismetMathLibrary::Less_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, bpfv__CallFunc_Array_Length_ReturnValue__pf);
				if (!bpfv__CallFunc_Less_IntInt_ReturnValue__pf)
				{
					__CurrentState = 10;
					break;
				}
			}
		case 6:
			{
				bpfv__Temp_int_Array_Index_Variable__pf = bpfv__Temp_int_Loop_Counter_Variable__pf;
			}
		case 7:
			{
				__StateStack.Push(8);
				__CurrentState = 11;
				break;
			}
		case 8:
			{
			}
		case 9:
			{
				bpfv__CallFunc_Add_IntInt_ReturnValue__pf = UKismetMathLibrary::Add_IntInt(bpfv__Temp_int_Loop_Counter_Variable__pf, 1);
				bpfv__Temp_int_Loop_Counter_Variable__pf = bpfv__CallFunc_Add_IntInt_ReturnValue__pf;
				__CurrentState = 5;
				break;
			}
		case 10:
			{
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		case 11:
			{
			}
		case 12:
			{
				if(::IsValid(bpv__DroneBody__pf))
				{
					bpfv__CallFunc_GetUpVector_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::GetUpVector();
				}
				bpfv__CallFunc_Multiply_VectorFloat_ReturnValue__pf = UKismetMathLibrary::Multiply_VectorFloat(bpfv__CallFunc_GetUpVector_ReturnValue__pf, bpp__Torque__pf);
				FCustomThunkTemplates::Array_Get(bpv__Motors__pf, bpfv__Temp_int_Array_Index_Variable__pf, /*out*/ bpfv__CallFunc_Array_Get_Item__pf);
				if(::IsValid(bpfv__CallFunc_Array_Get_Item__pf))
				{
					bpfv__CallFunc_Array_Get_Item__pf->bpf__AddxTorque__pfT(bpfv__CallFunc_Multiply_VectorFloat_ReturnValue__pf);
				}
				__CurrentState = (__StateStack.Num() > 0) ? __StateStack.Pop(/*bAllowShrinking=*/ false) : -1;
				break;
			}
		default:
			check(false); // Invalid state
			break;
		}
	} while( __CurrentState != -1 );
}
void ABP_Drone_C__pf2264400134::bpf__GetxForwardxVelocity__pfTT(/*out*/ float& bpp__Velocity__pf)
{
	FVector bpfv__CallFunc_GetVelocity_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	bpfv__CallFunc_GetVelocity_ReturnValue__pf = GetVelocity();
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf = UKismetMathLibrary::LessLess_VectorRotator(bpfv__CallFunc_GetVelocity_ReturnValue__pf, bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf);
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	bpp__Velocity__pf = bpfv__CallFunc_BreakVector_X__pf;
}
void ABP_Drone_C__pf2264400134::bpf__GetxRightxVelocity__pfTT(/*out*/ float& bpp__Velocity__pf)
{
	FVector bpfv__CallFunc_GetVelocity_ReturnValue__pf(EForceInit::ForceInit);
	FRotator bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf(EForceInit::ForceInit);
	FVector bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf(EForceInit::ForceInit);
	float bpfv__CallFunc_BreakVector_X__pf{};
	float bpfv__CallFunc_BreakVector_Y__pf{};
	float bpfv__CallFunc_BreakVector_Z__pf{};
	bpfv__CallFunc_GetVelocity_ReturnValue__pf = GetVelocity();
	if(::IsValid(bpv__DroneBody__pf))
	{
		bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf = bpv__DroneBody__pf->USceneComponent::K2_GetComponentRotation();
	}
	bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf = UKismetMathLibrary::LessLess_VectorRotator(bpfv__CallFunc_GetVelocity_ReturnValue__pf, bpfv__CallFunc_K2_GetComponentRotation_ReturnValue__pf);
	UKismetMathLibrary::BreakVector(bpfv__CallFunc_LessLess_VectorRotator_ReturnValue__pf, /*out*/ bpfv__CallFunc_BreakVector_X__pf, /*out*/ bpfv__CallFunc_BreakVector_Y__pf, /*out*/ bpfv__CallFunc_BreakVector_Z__pf);
	bpp__Velocity__pf = bpfv__CallFunc_BreakVector_Y__pf;
}
PRAGMA_DISABLE_OPTIMIZATION
void ABP_Drone_C__pf2264400134::__StaticDependencies_DirectlyUsedAssets(TArray<FBlueprintDependencyData>& AssetsToLoad)
{
	const FCompactBlueprintDependencyData LocCompactBlueprintDependencyData[] =
	{
		{0, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  SkeletalMesh /Game/PhysQuad/Meshes/SK_DroneBody.SK_DroneBody 
		{1, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  StaticMesh /Game/PhysQuad/Meshes/SM_DronePropCW.SM_DronePropCW 
		{2, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  StaticMesh /Game/PhysQuad/Meshes/SM_DronePropCCW.SM_DronePropCCW 
	};
	for(const FCompactBlueprintDependencyData& CompactData : LocCompactBlueprintDependencyData)
	{
		AssetsToLoad.Add(FBlueprintDependencyData(F__NativeDependencies::Get(CompactData.ObjectRefIndex), CompactData));
	}
}
PRAGMA_ENABLE_OPTIMIZATION
PRAGMA_DISABLE_OPTIMIZATION
void ABP_Drone_C__pf2264400134::__StaticDependenciesAssets(TArray<FBlueprintDependencyData>& AssetsToLoad)
{
	__StaticDependencies_DirectlyUsedAssets(AssetsToLoad);
	const FCompactBlueprintDependencyData LocCompactBlueprintDependencyData[] =
	{
		{3, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.SkeletalMeshComponent 
		{4, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/ClothingSystemRuntimeNv.ClothingSimulationFactoryNv 
		{5, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.SpringArmComponent 
		{6, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.CameraComponent 
		{7, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.StaticMeshComponent 
		{8, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.SceneComponent 
		{9, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  ScriptStruct /Script/InputCore.Key 
		{10, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  ScriptStruct /Script/Engine.HitResult 
		{11, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.PrimitiveComponent 
		{12, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.Actor 
		{13, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.PlayerController 
		{14, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/UE4Duino.Serial 
		{15, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Enum /Script/Engine.EEndPlayReason 
		{16, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.KismetStringLibrary 
		{17, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.KismetArrayLibrary 
		{18, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.KismetMathLibrary 
		{19, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.KismetSystemLibrary 
		{20, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/UMG.WidgetBlueprintLibrary 
		{21, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.GameplayStatics 
		{22, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.KismetNodeHelperLibrary 
		{23, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/Engine.Pawn 
		{24, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, true, false)},  //  ScriptStruct /Script/Engine.PointerToUberGraphFrame 
		{25, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Font /Engine/EngineFonts/Roboto.Roboto 
		{26, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/UMG.UserWidget 
		{27, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.KismetTextLibrary 
		{28, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  ScriptStruct /Script/Engine.FormatArgumentData 
		{29, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Enum /Script/Engine.EFormatArgumentType 
		{30, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Enum /Script/Engine.ETextGender 
		{31, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Enum /Script/UMG.ESlateVisibility 
		{32, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  Class /Script/UMG.TextBlock 
		{33, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, true, false)},  //  Class /Script/Engine.ActorComponent 
		{34, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  BlueprintGeneratedClass /Game/PhysQuad/Blueprints/BP_DroneMotorComponent.BP_DroneMotorComponent_C 
		{35, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  BlueprintGeneratedClass /Game/PhysQuad/Blueprints/BP_PIDControllerComponent.BP_PIDControllerComponent_C 
		{36, FBlueprintDependencyType(false, true, false, false), FBlueprintDependencyType(false, false, false, false)},  //  WidgetBlueprintGeneratedClass /Game/PhysQuad/Widgets/UI_DroneHUD.UI_DroneHUD_C 
		{37, FBlueprintDependencyType(true, false, false, false), FBlueprintDependencyType(false, false, false, false)},  //  UserDefinedEnum /Game/PhysQuad/Blueprints/DroneModeEnum.DroneModeEnum 
	};
	for(const FCompactBlueprintDependencyData& CompactData : LocCompactBlueprintDependencyData)
	{
		AssetsToLoad.Add(FBlueprintDependencyData(F__NativeDependencies::Get(CompactData.ObjectRefIndex), CompactData));
	}
}
PRAGMA_ENABLE_OPTIMIZATION
struct FRegisterHelper__ABP_Drone_C__pf2264400134
{
	FRegisterHelper__ABP_Drone_C__pf2264400134()
	{
		FConvertedBlueprintsDependencies::Get().RegisterConvertedClass(TEXT("/Game/PhysQuad/Blueprints/BP_Drone"), &ABP_Drone_C__pf2264400134::__StaticDependenciesAssets);
	}
	static FRegisterHelper__ABP_Drone_C__pf2264400134 Instance;
};
FRegisterHelper__ABP_Drone_C__pf2264400134 FRegisterHelper__ABP_Drone_C__pf2264400134::Instance;
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
