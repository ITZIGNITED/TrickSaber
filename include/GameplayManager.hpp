#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "Zenject/IInitializable.hpp"
#include "Zenject/DiContainer.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(TrickSaber, GameplayManager, Il2CppObject, ::Zenject::IInitializable*) {
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::PauseMenuManager*, _pauseMenuManager);
    DECLARE_INSTANCE_METHOD(void, DisableScoreSubmissionIfNeeded);
    DECLARE_INSTANCE_METHOD(void, DisableScore, bool disable, StringW reason);
    DECLARE_INSTANCE_METHOD(void, CreateCheckBox);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);

    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container);
};
