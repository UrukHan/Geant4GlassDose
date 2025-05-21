#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() { }

ActionInitialization::~ActionInitialization() { }

void ActionInitialization::BuildForMaster() const {
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const {
  auto runAction = new RunAction;
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(runAction);

  auto detectorConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  SetUserAction(new SteppingAction(runAction, detectorConstruction->GetScoringVolume()));
}
