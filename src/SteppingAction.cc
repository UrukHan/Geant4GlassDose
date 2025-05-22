#include "SteppingAction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

SteppingAction::SteppingAction(RunAction* runAction, G4LogicalVolume* scoringVolume)
  : G4UserSteppingAction(), fRunAction(runAction), fScoringVolume(scoringVolume) { }

SteppingAction::~SteppingAction() { }

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const auto* det = static_cast<const DetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = det->GetScoringVolume();
  }

  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  if (volume != fScoringVolume) return;

  G4double edep = step->GetTotalEnergyDeposit();
  if (edep > 0.)
    fRunAction->AddEdep(edep);
}
