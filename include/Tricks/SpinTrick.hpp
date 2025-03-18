#pragma once

#include "Trick.hpp"
#include "UnityEngine/Transform.hpp"
#include "custom-types/shared/coroutine.hpp"

DECLARE_CLASS_CUSTOM(TrickSaber::Tricks, SpinTrick, TrickSaber::Tricks::Trick) {
    DECLARE_INSTANCE_FIELD_PRIVATE(bool, _isVelocityDependent);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::Transform*, _saberModelTransform);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _spinSpeed);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _largestSpinSpeed);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _finalSpinSpeed);

    DECLARE_INSTANCE_METHOD(void, OnTrickStart);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndRequested);
    DECLARE_INSTANCE_METHOD(void, OnTrickEndImmediately);
    DECLARE_INSTANCE_METHOD(void, OnInit);
    DECLARE_INSTANCE_METHOD(void, OnSpinEnd);

    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_CTOR(ctor);

    private:
        custom_types::Helpers::Coroutine LerpToOriginalRotation();
        custom_types::Helpers::Coroutine CompleteRotation();
};
