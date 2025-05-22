#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class RunAction;
class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(RunAction* runAction, G4LogicalVolume* scoringVolume);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

private:
    RunAction* fRunAction;
    G4LogicalVolume* fScoringVolume;
};

#endif
