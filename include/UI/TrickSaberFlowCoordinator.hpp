#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"

#include "ViewControllers/BindingsViewController.hpp"
#include "ViewControllers/MiscViewController.hpp"
#include "ViewControllers/ThresholdViewController.hpp"

DECLARE_CLASS_CODEGEN(TrickSaber::UI, TrickSaberFlowCoordinator, HMUI::FlowCoordinator) {
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::MainFlowCoordinator*, _mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD_PRIVATE(ViewControllers::BindingsViewController*, _bindingsViewController);
    DECLARE_INSTANCE_FIELD_PRIVATE(ViewControllers::MiscViewController*, _miscViewController);
    DECLARE_INSTANCE_FIELD_PRIVATE(ViewControllers::ThresholdViewController*, _thresholdViewController);

    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, ViewControllers::BindingsViewController* bindingsViewController, ViewControllers::MiscViewController* miscViewController, ViewControllers::ThresholdViewController* thresholdViewController);

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::FlowCoordinator::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::FlowCoordinator::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, BackButtonWasPressed, &HMUI::FlowCoordinator::BackButtonWasPressed, HMUI::ViewController* topViewController);
};
