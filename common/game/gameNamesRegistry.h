#ifndef _H_GAME_NAMES_REGISTRY
#define _H_GAME_NAMES_REGISTRY

#if !defined( REGISTER_NAME )
#define REGISTER_NAME( name_ ) RED_DECLARE_NAME( name_ )
#define REGISTER_NAMED_NAME( varname_, string_ ) RED_DECLARE_NAMED_NAME( varname_, string_ )
#define REGISTER_NOT_REGISTERED
#endif

REGISTER_NAME( OnWorkStarted )
REGISTER_NAME( OnWorkEnded )
REGISTER_NAME( placer_left_eye )
REGISTER_NAME( placer_right_eye )

REGISTER_NAME( OnComponentTick )
REGISTER_NAME( OnCombatModeSet )

REGISTER_NAME( GetFriendlyName )
REGISTER_NAME( OnPostLoad )
REGISTER_NAME( IsKnockedUnconscious )

REGISTER_NAME( OilBonus )
REGISTER_NAME( crafting_schematics )
REGISTER_NAME( alchemy_recipes )
REGISTER_NAME( GetAlchemyRecipes )
REGISTER_NAME( GetCraftingSchematicsNames )

REGISTER_NAME( quality )
REGISTER_NAME( upgrade )
REGISTER_NAME( item_name )
REGISTER_NAME( craftedItem_name )

REGISTER_NAME( type_general )
REGISTER_NAME( _bonus )
REGISTER_NAME( quest_bonus )

REGISTER_NAME( mod_noprice )
REGISTER_NAME( mod_funds )
REGISTER_NAME( mod_sale )
REGISTER_NAME( mod_repair )
REGISTER_NAME( mod_removeupgrade )
REGISTER_NAME( mod_disassemble )
REGISTER_NAME( mod_removeenchantment )
REGISTER_NAME( mod_addslot )
REGISTER_NAME( mod_craftitem )
REGISTER_NAME( mod_crafting )
REGISTER_NAME( mod_enchantment )
REGISTER_NAME( mod_legendary )
REGISTER_NAME( mod_secondary )

REGISTER_NAME( area_nml )
REGISTER_NAME( area_nml_bonus )
REGISTER_NAME( area_novigrad )
REGISTER_NAME( area_novigrad_bonus )
REGISTER_NAME( area_skellige )
REGISTER_NAME( area_skellige_bonus )

REGISTER_NAME( item_color )
REGISTER_NAME( dye_default )
REGISTER_NAME( dye_black )
REGISTER_NAME( dye_blue )
REGISTER_NAME( dye_brown )
REGISTER_NAME( dye_gray )
REGISTER_NAME( dye_green )
REGISTER_NAME( dye_orange )
REGISTER_NAME( dye_pink )
REGISTER_NAME( dye_purple )
REGISTER_NAME( dye_red )
REGISTER_NAME( dye_turquoise )
REGISTER_NAME( dye_white )
REGISTER_NAME( dye_yellow )

REGISTER_NAMED_NAME( item_dye_default, "Dye Default" )
REGISTER_NAMED_NAME( item_dye_black, "Dye Black" )
REGISTER_NAMED_NAME( item_dye_blue, "Dye Blue" )
REGISTER_NAMED_NAME( item_dye_brown, "Dye Brown" )
REGISTER_NAMED_NAME( item_dye_gray, "Dye Gray" )
REGISTER_NAMED_NAME( item_dye_green, "Dye Green" )
REGISTER_NAMED_NAME( item_dye_orange, "Dye Orange" )
REGISTER_NAMED_NAME( item_dye_pink, "Dye Pink" )
REGISTER_NAMED_NAME( item_dye_purple, "Dye Purple" )
REGISTER_NAMED_NAME( item_dye_red, "Dye Red" )
REGISTER_NAMED_NAME( item_dye_turquoise, "Dye Turquoise" )
REGISTER_NAMED_NAME( item_dye_white, "Dye White" )
REGISTER_NAMED_NAME( item_dye_yellow, "Dye Yellow" )

// Names defined in namesRegistry.h
// REGISTER_NAME( steelsword )
// REGISTER_NAME( silversword ) 
REGISTER_NAME( armor )
REGISTER_NAME( pants )
REGISTER_NAME( boots )
REGISTER_NAME( gloves )

REGISTER_NAMED_NAME( BeastOil_1, "Beast Oil 1" )
REGISTER_NAMED_NAME( BeastOil_2, "Beast Oil 2" )
REGISTER_NAMED_NAME( BeastOil_3, "Beast Oil 3" )
REGISTER_NAME( oil_beast )

REGISTER_NAMED_NAME( CursedOil_1, "Cursed Oil 1" )
REGISTER_NAMED_NAME( CursedOil_2, "Cursed Oil 2" )
REGISTER_NAMED_NAME( CursedOil_3, "Cursed Oil 3" )
REGISTER_NAME( oil_cursed )

REGISTER_NAMED_NAME( HangedManVenom_1, "Hanged Man Venom 1" )
REGISTER_NAMED_NAME( HangedManVenom_2, "Hanged Man Venom 2" )
REGISTER_NAMED_NAME( HangedManVenom_3, "Hanged Man Venom 3" )
REGISTER_NAME( oil_venom )

REGISTER_NAMED_NAME( HybridOil_1, "Hybrid Oil 1" )
REGISTER_NAMED_NAME( HybridOil_2, "Hybrid Oil 2" )
REGISTER_NAMED_NAME( HybridOil_3, "Hybrid Oil 3" )
REGISTER_NAME( oil_hybrid )

REGISTER_NAMED_NAME( InsectoidOil_1, "Insectoid Oil 1" )
REGISTER_NAMED_NAME( InsectoidOil_2, "Insectoid Oil 2" )
REGISTER_NAMED_NAME( InsectoidOil_3, "Insectoid Oil 3" )
REGISTER_NAME( oil_insectoid )

REGISTER_NAMED_NAME( MagicalsOil_1, "Magicals Oil 1" )
REGISTER_NAMED_NAME( MagicalsOil_2, "Magicals Oil 2" )
REGISTER_NAMED_NAME( MagicalsOil_3, "Magicals Oil 3" )
REGISTER_NAME( oil_magical )

REGISTER_NAMED_NAME( NecrophageOil_1, "Necrophage Oil 1" )
REGISTER_NAMED_NAME( NecrophageOil_2, "Necrophage Oil 2" )
REGISTER_NAMED_NAME( NecrophageOil_3, "Necrophage Oil 3" )
REGISTER_NAME( oil_necrophage )

REGISTER_NAMED_NAME( SpecterOil_1, "Specter Oil 1" )
REGISTER_NAMED_NAME( SpecterOil_2, "Specter Oil 2" )
REGISTER_NAMED_NAME( SpecterOil_3, "Specter Oil 3" )
REGISTER_NAME( oil_specter )

REGISTER_NAMED_NAME( VampireOil_1, "Vampire Oil 1" )
REGISTER_NAMED_NAME( VampireOil_2, "Vampire Oil 2" )
REGISTER_NAMED_NAME( VampireOil_3, "Vampire Oil 3" )
REGISTER_NAME( oil_vampire )

REGISTER_NAMED_NAME( DraconideOil_1, "Draconide Oil 1" )
REGISTER_NAMED_NAME( DraconideOil_2, "Draconide Oil 2" )
REGISTER_NAMED_NAME( DraconideOil_3, "Draconide Oil 3" )
REGISTER_NAME( oil_draconide )

REGISTER_NAMED_NAME( OgreOil_1, "Ogre Oil 1" )
REGISTER_NAMED_NAME( OgreOil_2, "Ogre Oil 2" )
REGISTER_NAMED_NAME( OgreOil_3, "Ogre Oil 3" )
REGISTER_NAME( oil_ogre )

REGISTER_NAMED_NAME( RelicOil_1, "Relic Oil 1" )
REGISTER_NAMED_NAME( RelicOil_2, "Relic Oil 2" )
REGISTER_NAMED_NAME( RelicOil_3, "Relic Oil 3" )
REGISTER_NAME( oil_relic )

// W3NOD - MSTEINKE - TTP # 119786 Player can have two types of the same 'Lesser runestone'.
REGISTER_NAMED_NAME( DEP_STRIBOG_RUNE,					"Stribog rune" )
REGISTER_NAMED_NAME( DEP_STRIBOG_RUNE_RARE,				"Stribog rune rare" )
REGISTER_NAMED_NAME( DEP_DAZHBOG_RUNE,					"Dazhbog rune" )
REGISTER_NAMED_NAME( DEP_DAZHBOG_RUNE_RARE,				"Dazhbog rune rare" )
REGISTER_NAMED_NAME( DEP_DEVANA_RUNE,					"Devana rune" )
REGISTER_NAMED_NAME( DEP_DEVANA_RUNE_RARE,				"Devana rune rare" )
REGISTER_NAMED_NAME( DEP_ZORIA_RUNE,					"Zoria rune" )
REGISTER_NAMED_NAME( DEP_ZORIA_RUNE_RARE,				"Zoria rune rare" )
REGISTER_NAMED_NAME( DEP_MORANA_RUNE,					"Morana rune" )
REGISTER_NAMED_NAME( DEP_MORANA_RUNE_RARE,				"Morana rune rare" )
REGISTER_NAMED_NAME( DEP_TRIGLAV_RUNE,					"Triglav rune" )
REGISTER_NAMED_NAME( DEP_TRIGLAV_RUNE_RARE,				"Triglav rune rare" )
REGISTER_NAMED_NAME( DEP_SVAROG_RUNE,					"Svarog rune" )
REGISTER_NAMED_NAME( DEP_SVAROG_RUNE_RARE,				"Svarog rune rare" )
REGISTER_NAMED_NAME( DEP_VELES_RUNE,					"Veles rune" )
REGISTER_NAMED_NAME( DEP_VELES_RUNE_RARE,				"Veles rune rare" )
REGISTER_NAMED_NAME( DEP_PERUN_RUNE,					"Perun rune" )
REGISTER_NAMED_NAME( DEP_PERUN_RUNE_RARE,				"Perun rune rare" )
REGISTER_NAMED_NAME( DEP_ELEMENTAL_RUNE,				"Elemental rune" )
REGISTER_NAMED_NAME( DEP_ELEMENTAL_RUNE_RARE,			"Elemental rune rare" )
REGISTER_NAMED_NAME( DEP_FORGOTTEN_SOUL,				"Forgotten soul" )
REGISTER_NAMED_NAME( DEP_FORGOTTEN_SOUL_RARE,			"Forgotten soul rare" )
REGISTER_NAMED_NAME( DEP_PHILOSOPHERS_STONE,			"Philosophers stone" )
REGISTER_NAMED_NAME( DEP_PHILOSOPHERS_STONE_RARE,		"Philosophers stone rare" )
REGISTER_NAMED_NAME( DEP_SHATTERED_CORE,				"Shattered core" )
REGISTER_NAMED_NAME( DEP_SHATTERED_CORE_RARE,			"Shattered core rare" )
REGISTER_NAMED_NAME( DEP_PHOSPHORESCENT_CRYSTAL,		"Phosphorescent crystal" )
REGISTER_NAMED_NAME( DEP_PHOSPHORESCENT_CRYSTAL_RARE,	"Phosphorescent crystal rare" )

REGISTER_NAMED_NAME( ITEM_RUNE_STRIBOG_LESSER,			"Rune stribog lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_STRIBOG,					"Rune stribog" )
REGISTER_NAMED_NAME( ITEM_RUNE_STRIBOG_GREATER,			"Rune stribog greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_DAZHBOG_LESSER,			"Rune dazhbog lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_DAZHBOG,					"Rune dazhbog" )
REGISTER_NAMED_NAME( ITEM_RUNE_DAZHBOG_GREATER,			"Rune dazhbog greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_DEVANA_LESSER,			"Rune devana lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_DEVANA,					"Rune devana" )
REGISTER_NAMED_NAME( ITEM_RUNE_DEVANA_GREATER,			"Rune devana greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_ZORIA_LESSER,			"Rune zoria lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_ZORIA,					"Rune zoria" )
REGISTER_NAMED_NAME( ITEM_RUNE_ZORIA_GREATER,			"Rune zoria greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_MORANA_LESSER,			"Rune morana lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_MORANA,					"Rune morana" )
REGISTER_NAMED_NAME( ITEM_RUNE_MORANA_GREATER,			"Rune morana greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_TRIGLAV_LESSER,			"Rune triglav lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_TRIGLAV,					"Rune triglav" )
REGISTER_NAMED_NAME( ITEM_RUNE_TRIGLAV_GREATER,			"Rune triglav greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_SVAROG_LESSER,			"Rune svarog lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_SVAROG,					"Rune svarog" )
REGISTER_NAMED_NAME( ITEM_RUNE_SVAROG_GREATER,			"Rune svarog greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_VELES_LESSER,			"Rune veles lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_VELES,					"Rune veles" )
REGISTER_NAMED_NAME( ITEM_RUNE_VELES_GREATER,			"Rune veles greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_PERUN_LESSER,			"Rune perun lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_PERUN,					"Rune perun" )
REGISTER_NAMED_NAME( ITEM_RUNE_PERUN_GREATER,			"Rune perun greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_ELEMENTAL_LESSER,		"Rune elemental lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_ELEMENTAL,				"Rune elemental" )
REGISTER_NAMED_NAME( ITEM_RUNE_ELEMENTAL_GREATER,		"Rune elemental greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_PIEROG_LESSER,			"Rune pierog lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_PIEROG,					"Rune pierog" )
REGISTER_NAMED_NAME( ITEM_RUNE_PIEROG_GREATER,			"Rune pierog greater" )

REGISTER_NAMED_NAME( ITEM_RUNE_TVAROG_LESSER,			"Rune tvarog lesser" )
REGISTER_NAMED_NAME( ITEM_RUNE_TVAROG,					"Rune tvarog" )
REGISTER_NAMED_NAME( ITEM_RUNE_TVAROG_GREATER,			"Rune tvarog greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_AARD_LESSER,			"Glyph aard lesser" )
REGISTER_NAMED_NAME( ITEM_GLYPH_AARD,					"Glyph aard" )
REGISTER_NAMED_NAME( ITEM_GLYPH_AARD_GREATER,			"Glyph aard greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_AXII_LESSER,			"Glyph axii lesser" )
REGISTER_NAMED_NAME( ITEM_GLYPH_AXII,					"Glyph axii" )
REGISTER_NAMED_NAME( ITEM_GLYPH_AXII_GREATER,			"Glyph axii greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_IGNI_LESSER,			"Glyph igni lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_IGNI,					"Glyph igni" )
REGISTER_NAMED_NAME( ITEM_GLPYH_IGNI_GREATER,			"Glyph igni greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_QUEN_LESSER,			"Glyph quen lesser" )
REGISTER_NAMED_NAME( ITEM_GLYPH_QUEN,					"Glyph quen" )
REGISTER_NAMED_NAME( ITEM_GLYPH_QUEN_GREATER,			"Glyph quen greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_YRDEN_LESSER,			"Glyph yrden lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_YRDEN,					"Glyph yrden" )
REGISTER_NAMED_NAME( ITEM_GLPYH_YRDEN_GREATER,			"Glyph yrden greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_BINDING_LESSER,			"Glyph binding lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_BINDING,				"Glyph binding" )
REGISTER_NAMED_NAME( ITEM_GLPYH_BINDING_GREATER,		"Glyph binding greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_MENDING_LESSER,			"Glyph mending lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_MENDING,				"Glyph mending" )
REGISTER_NAMED_NAME( ITEM_GLPYH_MENDING_GREATER,		"Glyph mending greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_REINFORCEMENT_LESSER,	"Glyph reinforcement lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_REINFORCEMENT,			"Glyph reinforcement" )
REGISTER_NAMED_NAME( ITEM_GLPYH_REINFORCEMENT_GREATER,	"Glyph reinforcement greater" )

REGISTER_NAMED_NAME( ITEM_GLYPH_WARDING_LESSER,			"Glyph warding lesser" )
REGISTER_NAMED_NAME( ITEM_GLPYH_WARDING,				"Glyph warding" )
REGISTER_NAMED_NAME( ITEM_GLPYH_WARDING_GREATER,		"Glyph warding greater" )

// END W3MOD

REGISTER_NAME( ItemDurabilityModified )

REGISTER_NAME( W3MerchantNPC )

REGISTER_NAME( CMREntity )

// < Function Names >
REGISTER_NAME( SetCNameValue )
REGISTER_NAME( GetBlockName )
REGISTER_NAME( MonitorCreatureSpawned )
REGISTER_NAME( MonitorCreatureLost )
REGISTER_NAME( MonitorCreatureKilled )
REGISTER_NAME( OnFullRespawn )
REGISTER_NAME( GetObjectForPropertiesEdition )
REGISTER_NAME( SetPriority )
REGISTER_NAME( RegisterReactionSceneGroups )
// < Function Names />

// Saving
REGISTER_NAME( spawnedCreature );
REGISTER_NAME( entryGUID );
REGISTER_NAME( entryId );
REGISTER_NAME( entryHash );
REGISTER_NAME( lastOwningEntry );
REGISTER_NAME( creatureDefinition );
REGISTER_NAME( yaw );
REGISTER_NAME( encounter );
REGISTER_NAME( guardArea );
REGISTER_NAME( guardPursuitArea );
REGISTER_NAME( guardPursuitRange );
REGISTER_NAME( actionPointsArea );
REGISTER_NAME( wanderArea );
REGISTER_NAME( wanderPointsTag );
REGISTER_NAME( treeState )
REGISTER_NAME( savedNodesCount );
REGISTER_NAME( spawnPhaseIndex );
REGISTER_NAME( rerollTime );
REGISTER_NAME( currentActiveChild );
REGISTER_NAME( spawnLimit );
REGISTER_NAME( toSpawn );
REGISTER_NAME( recalculateTimeout );
REGISTER_NAME( selectedChild );
REGISTER_NAME( numSaved );
REGISTER_NAME( numCreatureDefinitions )
REGISTER_NAME( arrived )
REGISTER_NAME( poked )
REGISTER_NAME( dead )
REGISTER_NAME( CutControlBlock )
REGISTER_NAME( on )
REGISTER_NAME( delay )
REGISTER_NAME( OnGameLoadInitFinished )
REGISTER_NAME( OnGameLoadInitFinishedSuccess )
REGISTER_NAME( DisplayLockedSavePopup )
REGISTER_NAME( DisplayGameSaveErrorOutOfDiskSpace )
REGISTER_NAME( OnSaveCompleted )

// AI - just moved from namesRegistry, and needs sorting out
REGISTER_NAME( Initialize )
REGISTER_NAME( Main )
REGISTER_NAME( IsAvailable )
REGISTER_NAME( OnDestruction )
REGISTER_NAME( SpawnInstance )
REGISTER_NAME( OnTargetChanged )
REGISTER_NAME( Decorator )
REGISTER_NAME( DecoratorActivePriority )
REGISTER_NAME( SetIsAfraid )
REGISTER_NAME( RespondToMusic )
REGISTER_NAME( ReactivationDelayDecorator )
REGISTER_NAME( ReactionSceneFlowSynchro )
REGISTER_NAME( ReactionSceneFlowController )
REGISTER_NAME( ReactionSceneAssignments )
REGISTER_NAME( ReactionEventAIStorage )
REGISTER_NAME( DelayActivationDecorator )
REGISTER_NAME( ReactionSceneDefinitionDecorator )
REGISTER_NAME( AssignActor )
REGISTER_NAME( SceneEndNode )
REGISTER_NAME( SelectFleeDestination )
REGISTER_NAME( Composite )
REGISTER_NAME( Loop )
REGISTER_NAME( LoopForTime )
REGISTER_NAME( SelectRandom )
REGISTER_NAME( Sequence )
REGISTER_NAME( PersistantSequence )
REGISTER_NAME( SequenceCheckAvailabilty )
REGISTER_NAME( AimedSequence )
REGISTER_NAME( Special )
REGISTER_NAME( DynamicNodeBase )
REGISTER_NAME( DynamicNode )
REGISTER_NAME( Parallel )
REGISTER_NAME( Metanode )
REGISTER_NAME( AI )
REGISTER_NAME( Arbitrator )
REGISTER_NAME( AITemplate )
REGISTER_NAME( OnSpawn )
REGISTER_NAME( ScriptOnSpawn )
REGISTER_NAME( Subtree )
REGISTER_NAME( SubtreeList )
REGISTER_NAME( ConditionalTree )
REGISTER_NAME( BaseConditionalTree )
REGISTER_NAME( NPCTypeConditionalTree )
REGISTER_NAME( ConditionalBaseDecorator )
REGISTER_NAME( ConditionalBoolDecorator )
REGISTER_NAME( ConditionalNameDecorator );
REGISTER_NAME( ConditionalFlagTree )
REGISTER_NAME( ConditionalChooseBranch )
REGISTER_NAME( ScriptTerminal )
REGISTER_NAME( ScriptDecorator )
REGISTER_NAME( CreateBehTreeEnum )
REGISTER_NAME( AtomicAction )
REGISTER_NAME( BaseRotateToTarget )
REGISTER_NAME( RotateToTarget )
REGISTER_NAME( RotateToMatchActionTargetHeading )
REGISTER_NAME( AtomicLookAt )
REGISTER_NAME( AtomicMoveTo )
REGISTER_NAME( AtomicMoveToActionTarget )
REGISTER_NAME( AtomicMoveToCombatTarget )
REGISTER_NAME( MoveToActionTargetCustomSteeringGraph )
REGISTER_NAME( AtomicMoveToCustomPoint )
REGISTER_NAME( OnDeath )
REGISTER_NAME( PassMetaobstacles )
REGISTER_NAME( MoveToPredefinedPath )
REGISTER_NAME( SnapToNavigation )
REGISTER_NAME( PursueTarget )
REGISTER_NAME( BasePursueTarget )
REGISTER_NAME( AtomicPursueTagged )
REGISTER_NAME( DoNothing )
REGISTER_NAME( AtomicTeleport )
REGISTER_NAME( TeleportToActionTarget )
REGISTER_NAME( TeleportToActionTargetAndCheckPosition )
REGISTER_NAME( TeleportToWork )
REGISTER_NAME( ConditionShouldTeleportToWork )
REGISTER_NAME( AlreadyAtWork )
REGISTER_NAME( AttachToCurve )
REGISTER_NAME( FlyOnCurve )
REGISTER_NAME( GuardRetreat )
REGISTER_NAME( CompleteImmediately )
REGISTER_NAME( Despawn )
REGISTER_NAME( ScriptConditionalDecorator )
REGISTER_NAME( PlayAnimationOnSlot )
REGISTER_NAME( PlayAnimationEvent )
REGISTER_NAME( PlayAnimationManualMotionExtraction )
REGISTER_NAME( AtomicSheatheWeapon )
REGISTER_NAME( BeingHit )
REGISTER_NAME( DamageReaction )
REGISTER_NAME( CompleteInProximity )
REGISTER_NAME( SteeringGraphDecorator )
REGISTER_NAME( SteerWithTarget )
REGISTER_NAME( SteerWithCustomTarget )
REGISTER_NAME( SteeringTargeterDecorator )
REGISTER_NAME( SetSteeringTargetNode )
REGISTER_NAME( SetSteeringNamedTarget )
REGISTER_NAME( SetSteeringCustomPosition )
REGISTER_NAME( GetSubInitializerClassName )
REGISTER_NAME( GetContextMenuSpecialOptions )
REGISTER_NAME( RunSpecialOption )
REGISTER_NAME( params )
REGISTER_NAME( Init )
REGISTER_NAME( DeInit )
REGISTER_NAME( DurationRange )
REGISTER_NAME( TestCondition )
REGISTER_NAME( FinishAnimations )
REGISTER_NAME( BreakAnimations )
REGISTER_NAME( SteeringGraphsList )
REGISTER_NAME( Condition )
REGISTER_NAME( ConditionTrue )
REGISTER_NAME( ConditionReactionEvent )
REGISTER_NAME( ComplexCondition )
REGISTER_NAME( ConditionDistanceToActionTarget )
REGISTER_NAME( ConditionDistanceToNamedTarget )
REGISTER_NAME( ConditionLineofSight )
REGISTER_NAME( ConditionLineofSightToNamedTarget )
REGISTER_NAME( ConditionTargetNoticed )
REGISTER_NAME( ConditionCombatTargetNoticed )
REGISTER_NAME( ConditionDistanceToCombatTarget )
REGISTER_NAME( ConditionDistanceToCustomTarget )
REGISTER_NAME( ConditionDistanceToTagged )
REGISTER_NAME( ConditionCheckRotationToTarget )
REGISTER_NAME( ConditionCheckRotationToCombatTarget )
REGISTER_NAME( ConditionCheckRotationToActionTarget )
REGISTER_NAME( ConditionCheckRotationToNamedTarget )
REGISTER_NAME( ConditionIsConcsiousAtWork )
REGISTER_NAME( ConditionIsWorking )
REGISTER_NAME( ConditionIsInAttackRange )
REGISTER_NAME( ConditionIsInCameraView )
REGISTER_NAME( ConditionIsInGuardArea )
REGISTER_NAME( ConditionIsActionTargetInGuardArea )
REGISTER_NAME( ConditionIsThisActorInGuardArea )
REGISTER_NAME( ConditionIsCustomTargetInGuardArea )
REGISTER_NAME( ConditionClearLineToTarget )
REGISTER_NAME( ConditionExternalToggle )
REGISTER_NAME( ConditionMoveSpeedEngineVal )
REGISTER_NAME( ConditionWorkRelated )
REGISTER_NAME( ConditionIsAtWork )
REGISTER_NAME( ConditionCanUseChatSceneInAP )
REGISTER_NAME( ConditionIsSittingInInterior )
REGISTER_NAME( ConditionChance )
REGISTER_NAME( ExplorationQueueDecorator )
REGISTER_NAME( ExplorationQueueRegister )
REGISTER_NAME( ExplorationQueueUse )
REGISTER_NAME( AsyncQuery )
REGISTER_NAME( AsyncResult )
REGISTER_NAME( WalkableSpotQuery )
REGISTER_NAME( WalkableSpotRingQuery )
REGISTER_NAME( WalkableSpotClosestQuery )
REGISTER_NAME( WalkableSpotResult )
REGISTER_NAME( WasEventFiredRecentlyBase )
REGISTER_NAME( WasEventFiredRecently )
REGISTER_NAME( WasAnyOfEventsFiredRecently )
REGISTER_NAME( SynchronizedAnimation )
REGISTER_NAME( EndTask )
REGISTER_NAME( SelectTargetByTagDecorator )
REGISTER_NAME( SelectTargetByTagInAreaDecorator )
REGISTER_NAME( SelectPatrollingTargetDecorator )
REGISTER_NAME( SelectWanderingTargetDecorator )
REGISTER_NAME( SelectRandomTerrainPositionInArea )
REGISTER_NAME( WanderingTaggedTargetDecorator )
REGISTER_NAME( RandomWanderingTarget )
REGISTER_NAME( HistoryWanderingTarget )
REGISTER_NAME( DynamicWanderingTarget )
REGISTER_NAME( Uninterruptable )
REGISTER_NAME( SelectTargetByTag )
REGISTER_NAME( SetCustomMoveTarget )
REGISTER_NAME( SetCustomMoveTargetToPosition )
REGISTER_NAME( SetCustomMoveTargetToExpInteractionPoint )
REGISTER_NAME( SetCustomMoveTargetToExpDestinationPoint )
REGISTER_NAME( NotifyDoor )
REGISTER_NAME( UseExplorationAction )
REGISTER_NAME( TeleportToMetalinkDestination )
REGISTER_NAME( CustomSteering )
REGISTER_NAME( FollowFormation )
REGISTER_NAME( FollowCombatFormation )
REGISTER_NAME( KeepDistance )
REGISTER_NAME( FleeReaction )
REGISTER_NAME( FollowPredefinedPath )
REGISTER_NAME( FollowPredefinedPathWithCompanion )
REGISTER_NAME( Story )
REGISTER_NAME( ExternalListener )
REGISTER_NAME( ScriptedActionsListReader )
REGISTER_NAME( PlayScene )
REGISTER_NAME( BaseForcedBehavior )
REGISTER_NAME( ForcedBehavior )
REGISTER_NAME( DespawnRequest )
REGISTER_NAME( GetEditorFriendlyName )
REGISTER_NAME( startingBehavior )
REGISTER_NAME( interactionPoint )
REGISTER_NAME( destinationPoint )
REGISTER_NAME( metalinkComponent )
REGISTER_NAME( CrabSpawn )
REGISTER_NAME( CrittersSpawn )
REGISTER_NAME( Fire )
REGISTER_NAME( OnDamageFromBoids )
REGISTER_NAME( OnPlayerOpenedDoors )
REGISTER_NAME( SoftReactionsLocker )
REGISTER_NAME( DestroyTimer )
REGISTER_NAME( _acceptAll )
REGISTER_NAME( GreetingAction )

// < BehTree nodes>
REGISTER_NAME( ConditionPartyMembersCount )
REGISTER_NAME( AtomicMoveToWanderpoint )
REGISTER_NAME( PokeScriptedAction )
REGISTER_NAME( SelectPartyMemberAsActionTarget )
REGISTER_NAME( TrySelectingLeaderAndSetupFormation )
REGISTER_NAME( SetupFormation )
REGISTER_NAME( LeadFormation )
REGISTER_NAME( Formation )
REGISTER_NAME( HasCombatTarget )
REGISTER_NAME( SetupGuardArea )
REGISTER_NAME( CasualMovement )
REGISTER_NAME( Semaphore )
REGISTER_NAME( PriorityOnSemaphore )
REGISTER_NAME( ConditionSemaphoreInRange )
REGISTER_NAME( ConditionSemaphore )
REGISTER_NAME( SynchronizePartyWork )
//REGISTER_NAME( PlaySceneIntro )
// </ BehTree nodes>

// <AI events>
REGISTER_NAME( BoatReachedEndOfPath )
REGISTER_NAME( AI_RequestNextWanderingPoint )
REGISTER_NAME( AI_NewMovementAction )
REGISTER_NAME( AI_ArbitratorQuery )
REGISTER_NAME( AI_PlaySceneRequest )
REGISTER_NAME( AI_ForceInterruption )
REGISTER_NAME( AI_Load_Forced )
REGISTER_NAME( AI_CantPush )
REGISTER_NAME( AI_Forced_Cancel )
REGISTER_NAME( AI_MovementAction )
REGISTER_NAME( AI_ExplorationQueueCalculatePriority )
REGISTER_NAME( AI_ExplorationQueueReleaseLock )
REGISTER_NAME( AI_Change_Guard_Area )
REGISTER_NAME( AI_PredictPosition )
REGISTER_NAME( AI_LoadCustomWorkTree )
REGISTER_NAME( AI_ForceLastWork )
REGISTER_NAME( AI_DelayWork )
REGISTER_NAME( AI_DoorTriggerEntered )
REGISTER_NAME( AI_DoorTriggerExit )
REGISTER_NAME( AI_EnablePartyWorkSynchronization )
REGISTER_NAME( AI_DisablePartyWorkSynchronization )
REGISTER_NAME( poke_default )
REGISTER_NAME( PrePoolRequest )
REGISTER_NAME( OnPoolRequest )
REGISTER_NAME( OnReattachFromPoolAsync )
REGISTER_NAME( OnReattachFromPool )
REGISTER_NAME( ArrivedAtPath )
REGISTER_NAME( ForceArriveAtPath )
REGISTER_NAME( AI_CanTeleportOutOfSceneArea )
REGISTER_NAME( AI_AnimStateActivated )
REGISTER_NAME( AI_AnimStateDeactivated )
// </AI events>

// < AI others >
REGISTER_NAME( Refactor )
REGISTER_NAME( instanceClass )
REGISTER_NAME( listenToGameplayEvents )
REGISTER_NAME( listenToAnimEvents )
REGISTER_NAME( listener )
REGISTER_NAME( CURRENT_FORMATION )
REGISTER_NAME( FORMATION_ )
REGISTER_NAME( GUARD_AREA_DATA )
REGISTER_NAME( startingBehaviorPriority )
REGISTER_NAME( ReactionTarget )
REGISTER_NAME( RainStarted )
REGISTER_NAME( RainEnded )
REGISTER_NAME( BlendOutFromWork )
REGISTER_NAME( teleportToDestination )
REGISTER_NAME( AI_PreAsynchronousDestruction )
// </AI others >

//<XML keywords>
// Speed config 
REGISTER_NAME( speedConfig )
REGISTER_NAME( key_name )
REGISTER_NAME( walkSpeedAbs )
REGISTER_NAME( slowRunSpeedAbs )
REGISTER_NAME( fastRunSpeedAbs )
REGISTER_NAME( sprintSpeedAbs )

REGISTER_NAME( walkSpeedRel )
REGISTER_NAME( slowRunSpeedRel )
REGISTER_NAME( fastRunSpeedRel )
REGISTER_NAME( sprintSpeedRel )
//</XML keywords>

//<Steering Graph flags>
REGISTER_NAME( SpeedMultOnPath )
REGISTER_NAME( MaintainTargetSpeed )
REGISTER_NAME( CompanionOffset )
REGISTER_NAME( Road )
REGISTER_NAME( PreciseArrival )
REGISTER_NAME( CrowdPushThrough )
//</Steering Graph flags>

//<Swarms>
REGISTER_NAME( spawnPointType )
REGISTER_NAME( spawnPointType_name )
//</Swarms>

REGISTER_NAME( GenerateEntries )

REGISTER_NAME( ShowUserDialog )

REGISTER_NAME( OnStreamIn )
REGISTER_NAME( OnStreamOut )
REGISTER_NAME( OnGrab );
REGISTER_NAME( OnItemEnhanced );
REGISTER_NAME( OnPut );
REGISTER_NAME( OnEquippedItem )
REGISTER_NAME( OnHolsteredItem )
REGISTER_NAME( OnAppearanceChanged )
REGISTER_NAME( OnForceUpdateSoundInfo )
REGISTER_NAME( OnAttachmentUpdate )

REGISTER_NAME( OnGameDifficultyChanged )

REGISTER_NAME( SpecialSettingsGroupId );

REGISTER_NAMED_NAME( SilverSword1, "Silver sword 1" )
REGISTER_NAMED_NAME( SteelSword1, "Long Steel Sword" )
REGISTER_NAME( crossbow )
REGISTER_NAME( bolt )

// temporary attitude group priorities
REGISTER_NAME( EAttitudeGroupPriority )
REGISTER_NAME( AGP_SpawnTree )

REGISTER_NAME( LadderLoopAdjustment )

REGISTER_NAME( ReservationRelease )
REGISTER_NAME( mainMenu )

REGISTER_NAME( OnHandleWorldChange )

REGISTER_NAME( ForceSpawnItemOnStart )

REGISTER_NAME( SetDLCToStart )
REGISTER_NAME( LoadGame )

#if defined( REGISTER_NOT_REGISTERED )
#undef REGISTER_NAME
#undef REGISTER_NAMED_NAME
#undef REGISTER_NOT_REGISTERED
#endif

#endif // _H_GAME_NAMES_REGISTRY
