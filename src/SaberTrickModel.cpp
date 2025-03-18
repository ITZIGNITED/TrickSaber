#include "SaberTrickModel.hpp"
#include "SpinTrickTrailMovement.hpp"

#include "logging.hpp"
#include "config.hpp"

#include "UnityEngine/WaitForSeconds.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "bsml/shared/BSML/SharedCoroutineStarter.hpp"

DEFINE_TYPE(TrickSaber, SaberTrickModel);

namespace TrickSaber {
    void SaberTrickModel::Inject(::Zenject::DiContainer* container, Lapiz::Sabers::SaberModelManager* saberModelManager) {
        _saberModelManager = saberModelManager;

        _isMultiplayer = container->TryResolve<GlobalNamespace::MultiplayerPlayersManager*>();
    }

    void SaberTrickModel::ChangeToActualSaber() {
        if (!_originalParent || !_originalParent->m_CachedPtr.m_value) return;
        auto modelT = _originalSaberModel->get_transform();
        modelT->SetParent(_originalParent, true);
        _rigidbody->set_position({0, 0, 0});
        _rigidbody->set_rotation(UnityEngine::Quaternion::get_identity());
        modelT->get_transform()->set_localPosition({0, 0, 0});
        modelT->get_transform()->set_localRotation(UnityEngine::Quaternion::get_identity());
        _rigidbody->set_interpolation(TrickSaber::RigidbodyInterpolation::None);
    }

    void SaberTrickModel::ChangeToTrickModel() {
        _originalParent = _originalSaberModel->get_transform()->get_parent();
        _originalSaberModel->get_transform()->SetParent(nullptr, true);
        _rigidbody->set_interpolation(TrickSaber::RigidbodyInterpolation::Interpolate);
    }

    void SaberTrickModel::AddRigidbody(UnityEngine::GameObject* gameObject) {
        _rigidbody = gameObject->AddComponent<TrickSaber::Rigidbody*>();
        _rigidbody->set_useGravity(false);
        _rigidbody->set_isKinematic(true);
        _rigidbody->set_detectCollisions(false);
        _rigidbody->set_maxAngularVelocity(800);
    }

    custom_types::Helpers::Coroutine SaberTrickModel::Init(GlobalNamespace::Saber* saber, bool& result) {
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(BSML::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(GetSaberModel(saber, _originalSaberModel))));

        if (!_originalSaberModel) {
            result = false;
            INFO("Couldn't find saber model, destroying trick model!");
            co_return;
        }

        _trickModel = _originalSaberModel;
        _saberTransform = saber->get_transform();

        AddRigidbody(_trickModel);

        if (!config.hitNotesDuringTrick || _isMultiplayer) {
            // Make trails use transforms that are parented to the model rather than the VR controller
            // This way, scores aren't affected while trails look proper
            saber->get_gameObject()->AddComponent<SpinTrickTrailMovement*>()->Init(saber, _originalSaberModel->GetComponent<GlobalNamespace::SaberModelController*>());
        } else {
            // Parent transforms to Saber to affect cut collisions
            // Trails are also fixed by using this
            saber->_saberBladeTopTransform->SetParent(_trickModel->get_transform(), true);
            saber->_saberBladeBottomTransform->SetParent(_trickModel->get_transform(), true);
        }

        result = true;
        co_return;
    }

    custom_types::Helpers::Coroutine SaberTrickModel::GetSaberModel(GlobalNamespace::Saber* saber, UnityEngine::GameObject*& result) {
        static auto GetModelController = CRASH_UNLESS(il2cpp_utils::resolve_icall<::UnityEngine::Component*, ::UnityEngine::GameObject*, ::System::Type*, bool>("UnityEngine.GameObject::GetComponentInChildren"));
        GlobalNamespace::SaberModelController* smc = nullptr;

        static constexpr const float timeout = 2.0f;
        static constexpr const float interval = 0.3f;
        float time = 0;

        while (!smc && saber && saber->m_CachedPtr.m_value) {
            UnityEngine::Component* component = GetModelController(saber->get_gameObject(), csTypeOf(GlobalNamespace::SaberModelController*), true);
            if (component != nullptr && component->m_CachedPtr.m_value != nullptr) {
                result = component->get_gameObject();
                if (!result) {
                    WARNING("Saber model not found! Retrying...");
                } else {
                    co_return;
                }
                co_return;
            } else {
                WARNING("Saber model not found! Retrying...");
            }

            if (time > timeout) {
                DEBUG("Saber model not found! Timeout reached.");
                break;
            };

            time += interval;
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(UnityEngine::WaitForSeconds::New_ctor(interval));
        }

        result = nullptr;
        co_return;
    }

    TrickSaber::Rigidbody* SaberTrickModel::get_rigidbody() { return _rigidbody; }
    UnityEngine::GameObject* SaberTrickModel::get_trickModel() { return _trickModel; }
    UnityEngine::GameObject* SaberTrickModel::get_originalSaberModel() { return _originalSaberModel; }
}
