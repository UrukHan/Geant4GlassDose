#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization(double sampleL, double sampleW, double sampleH, double density) {
    double volume_cm3 = sampleL * sampleW * sampleH;
    fMass_kg = volume_cm3 * density / 1000.0; // g to kg
}

ActionInitialization::~ActionInitialization() { }

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction(fMass_kg));
}

void ActionInitialization::Build() const {
    auto runAction = new RunAction(fMass_kg);
    SetUserAction(runAction);
    SetUserAction(new PrimaryGeneratorAction());

    auto detectorConstruction = static_cast<const DetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    SetUserAction(new SteppingAction(runAction, detectorConstruction->GetScoringVolume()));
}
