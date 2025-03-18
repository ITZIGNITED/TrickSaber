#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/GameObject.hpp"
#include "Zenject/Installer.hpp"
#include "Zenject/InjectContext.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::Installers, GameInstaller, ::Zenject::Installer) {
    DECLARE_OVERRIDE_METHOD_MATCH(void, InstallBindings, &::Zenject::Installer::InstallBindings);
    DECLARE_PRIVATE_METHOD(void, BindTrickManager, GlobalNamespace::SaberType saberType);
    DECLARE_PRIVATE_METHOD(UnityEngine::GameObject*, GetSaber, ::Zenject::InjectContext* ctx, GlobalNamespace::SaberType saberType);
    DECLARE_DEFAULT_CTOR();
};
