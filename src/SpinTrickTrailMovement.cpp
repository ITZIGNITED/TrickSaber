#include "SpinTrickTrailMovement.hpp"

#include "GlobalNamespace/TimeHelper.hpp"
#include "GlobalNamespace/SaberTrail.hpp"

DEFINE_TYPE(TrickSaber, SpinTrickTrailMovement);

namespace TrickSaber {
    void SpinTrickTrailMovement::Init(GlobalNamespace::Saber* saber, GlobalNamespace::SaberModelController* saberModelController) {
        _topTransform = Object::Instantiate(saber->_saberBladeTopTransform, saberModelController->get_transform(), true);
        _botTransform = Object::Instantiate(saber->_saberBladeBottomTransform, saberModelController->get_transform(), true);

        _trailMovementData = GlobalNamespace::SaberMovementData::New_ctor();
        saberModelController->_saberTrail->_movementData = _trailMovementData->i___GlobalNamespace__IBladeMovementData();
    }

    void SpinTrickTrailMovement::Update() {
        if (_trailMovementData) {
            _trailMovementData->AddNewData(_topTransform->get_position(), _botTransform->get_position(), GlobalNamespace::TimeHelper::get_time());
        }
    }
}
