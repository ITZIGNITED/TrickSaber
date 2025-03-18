#include "logging.hpp"
#include "hooking.hpp"
#include "config.hpp"
#include "scotland2/shared/loader.hpp"

#include "custom-types/shared/register.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"

#include "Installers/GameInstaller.hpp"
#include "Installers/MenuInstaller.hpp"

#include "System/ArgumentNullException.hpp"

#include "bsml/shared/BSMLDataCache.hpp"
#include "assets.hpp"

modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

extern "C" __attribute__((visibility("default"))) void setup(CModInfo& info) {
    modInfo.assign(info);
}

extern "C" __attribute__((visibility("default"))) void late_load() {
    if (!LoadConfig()) SaveConfig();
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    Hooks::InstallHooks();

    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<TrickSaber::Installers::MenuInstaller*>(Lapiz::Zenject::Location::Menu);
    zenjector->Install<TrickSaber::Installers::GameInstaller*>(Lapiz::Zenject::Location::StandardPlayer);
}

BSML_DATACACHE(logosmall_png) {
    return IncludedAssets::LogoSmall_png;
}
