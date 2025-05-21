#include "SteppingAction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4VSolid.hh"

SteppingAction::SteppingAction(RunAction* runAction, G4LogicalVolume* scoringVolume)
: G4UserSteppingAction(), fRunAction(runAction), fScoringVolume(scoringVolume) { }

SteppingAction::~SteppingAction() { }

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  G4double edep = step->GetTotalEnergyDeposit();

  if (edep > 0.) {
    G4double volumeSize = volume->GetSolid()->GetCubicVolume();
    G4double density = volume->GetMaterial()->GetDensity();
    G4double mass = volumeSize * density;

    G4double dose = edep / mass;
    fRunAction->AddDose(dose);
  }
}
