#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "TrickSaberFlowCoordinator.hpp"
#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#include "bsml/shared/BSML/MenuButtons/MenuButton.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(TrickSaber::UI, SettingsUI, Il2CppObject, ::System::IDisposable*, ::Zenject::IInitializable* ) {
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityW<TrickSaberFlowCoordinator>, _trickSaberFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityW<GlobalNamespace::MainFlowCoordinator>, _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityW<BSML::MenuButton>, _menuButton);

    DECLARE_CTOR(ctor, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, TrickSaberFlowCoordinator* trickSaberFlowCoordinator);
    DECLARE_INSTANCE_METHOD(void, ShowFlow);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
};
