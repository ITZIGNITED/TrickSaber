#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "lapiz/shared/macros.hpp"

#include "System/Object.hpp"
#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/BeatmapKey.hpp"
#include "GlobalNamespace/BeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapLevelsModel.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "System/IDisposable.hpp"

#include "SaberTrickManager.hpp"

#include "Zenject/IInitializable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(TrickSaber, GlobalTrickManager, System::Object, ::Zenject::IInitializable*, ::System::IDisposable*) {
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Coroutine*, _noteTimer);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::AudioSource*, _audioSource);
    DECLARE_INSTANCE_METHOD(UnityEngine::AudioSource*, get_audioSource);

    DECLARE_INSTANCE_FIELD(GlobalNamespace::BeatmapObjectManager*, beatmapObjectManager);
    DECLARE_INSTANCE_FIELD(LeftSaberTrickManager*, leftSaberTrickManager);
    DECLARE_INSTANCE_FIELD(RightSaberTrickManager*, rightSaberTrickManager);

    DECLARE_INSTANCE_METHOD(bool, get_enabled);
    DECLARE_INSTANCE_METHOD(void, set_enabled, bool value);
    DECLARE_INSTANCE_FIELD(bool, saberClashCheckerEnabled);

    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::BeatmapKey, _beatmapKey);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::BeatmapLevel*, _beatmapLevel);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::BeatmapLevelsModel*, _beatmapLevelsModel);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::AudioTimeSyncController*, _audioTimeSyncController);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _slowmoStepAmount);
    DECLARE_INSTANCE_FIELD_PRIVATE(bool, _isMultiplayer);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Coroutine*, _applySlowmoCoroutine);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Coroutine*, _endSlowmoCoroutine);
    DECLARE_INSTANCE_FIELD_PRIVATE(bool, _slowmoApplied);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _endSlowmoTarget);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _originalTimeScale);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _timeSinceLastNote);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    DECLARE_INSTANCE_METHOD(void, OnTrickStarted, TrickAction trickAction);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested, TrickAction trickAction);
    DECLARE_INSTANCE_METHOD(void, OnTrickEnded, TrickAction trickAction);
    DECLARE_PRIVATE_METHOD(void, SetTimescale, float timescale);
    DECLARE_INSTANCE_METHOD(bool, CanDoTrick);
    DECLARE_PRIVATE_METHOD(void, OnNoteWasSpawned, UnityW<GlobalNamespace::NoteController> noteController);
    DECLARE_INSTANCE_METHOD(bool, IsTrickInState, TrickAction trickAction, TrickState state);
    DECLARE_INSTANCE_METHOD(bool, IsDoingTrick);


    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetup, LeftSaberTrickManager* leftSaberTrickManager, RightSaberTrickManager* rightSaberTrickManager);

    private:
        custom_types::Helpers::Coroutine ApplySlowmoSmooth(float amount, float originalTimescale);
        custom_types::Helpers::Coroutine EndSlowmoSmooth();
        custom_types::Helpers::Coroutine NoteSpawnTimer();
};
