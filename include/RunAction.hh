#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
public:
    RunAction(G4double mass_kg);
    ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void AddEdep(G4double edep);

private:
    G4Accumulable<G4double> fEdep;
    G4double fMass_kg;
};

#endif
