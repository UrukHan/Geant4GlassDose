#include "RunAction.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"
#include "G4RunManager.hh"

RunAction::RunAction()
: G4UserRunAction(), fDose(0.)
{
  G4AccumulableManager::Instance()->RegisterAccumulable(fDose);
}

RunAction::~RunAction() { }

void RunAction::BeginOfRunAction(const G4Run*)
{
  G4AccumulableManager::Instance()->Reset();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4AccumulableManager::Instance()->Merge();

  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4double dose = fDose.GetValue();
  G4cout << "The run consists of " << nofEvents << " protons." << G4endl;
  G4cout << "Cumulated dose per run: " << G4BestUnit(dose, "Dose") << G4endl;
}

void RunAction::AddDose(G4double dose)
{
  fDose += dose;
}
