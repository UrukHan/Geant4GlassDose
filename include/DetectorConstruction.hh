#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction(double worldL, double worldW, double worldH,
                         double sampleL, double sampleW, double sampleH,
                         double density);
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
    void DefineMaterials();

    double fWorldLength, fWorldWidth, fWorldHeight;
    double fSampleLength, fSampleWidth, fSampleHeight;
    double fDensity;

    G4LogicalVolume* fScoringVolume;
};

#endif
