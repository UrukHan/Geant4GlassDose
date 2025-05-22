#include "RunAction.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"

RunAction::RunAction(G4double mass_kg)
 : G4UserRunAction(), fEdep(0.), fMass_kg(mass_kg)
{
    G4AccumulableManager::Instance()->RegisterAccumulable(fEdep);
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

    // edep_MeV уже в MeV из Geant4 (без лишних множителей!)
    G4double edep_MeV = fEdep.GetValue();

    // Перевод в джоули явно и однозначно
    G4double edep_Joule = edep_MeV * 1.60218e-13;

    // Правильный расчёт дозы в Gy
    G4double dose_Gy = edep_Joule / fMass_kg;

    G4cout << "\n====================================" << G4endl;
    G4cout << " Results for this run:" << G4endl;
    G4cout << "------------------------------------" << G4endl;
    G4cout << " Number of protons           : " << nofEvents << G4endl;

    // Теперь точно верный вывод энергии
    if (edep_MeV >= 1e6)
        G4cout << " Total deposited energy      : " << edep_MeV / 1e6 << " TeV" << G4endl;
    else if (edep_MeV >= 1e3)
        G4cout << " Total deposited energy      : " << edep_MeV / 1e3 << " GeV" << G4endl;
    else
        G4cout << " Total deposited energy      : " << edep_MeV << " MeV" << G4endl;

    if (dose_Gy >= 1)
        G4cout << " Dose this run               : " << dose_Gy << " Gy" << G4endl;
    else if (dose_Gy >= 1e-3)
        G4cout << " Dose this run               : " << dose_Gy * 1e3 << " mGy" << G4endl;
    else if (dose_Gy >= 1e-6)
        G4cout << " Dose this run               : " << dose_Gy * 1e6 << " μGy" << G4endl;
    else
        G4cout << " Dose this run               : " << dose_Gy * 1e9 << " nGy" << G4endl;

    G4cout << "====================================\n" << G4endl;
}



void RunAction::AddEdep(G4double edep)
{
    fEdep += edep;
}
