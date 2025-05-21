#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();
  virtual G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
  void DefineMaterials();
  G4LogicalVolume* fScoringVolume = nullptr;
};

#endif
