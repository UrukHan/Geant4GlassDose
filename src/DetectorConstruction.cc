#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction(double worldL, double worldW, double worldH,
                                           double sampleL, double sampleW, double sampleH,
                                           double density)
    : fWorldLength(worldL), fWorldWidth(worldW), fWorldHeight(worldH),
      fSampleLength(sampleL), fSampleWidth(sampleW), fSampleHeight(sampleH),
      fDensity(density), fScoringVolume(nullptr) { }

DetectorConstruction::~DetectorConstruction() { }

void DetectorConstruction::DefineMaterials() {
    auto nist = G4NistManager::Instance();

    G4Material* PbGlass = new G4Material("PbGlass", fDensity*g/cm3, 3);
    PbGlass->AddElement(nist->FindOrBuildElement("Si"), 1);
    PbGlass->AddElement(nist->FindOrBuildElement("O"), 2);
    PbGlass->AddElement(nist->FindOrBuildElement("Pb"), 1);

    nist->FindOrBuildMaterial("G4_AIR");
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    DefineMaterials();

    auto air = G4Material::GetMaterial("G4_AIR");
    auto PbGlass = G4Material::GetMaterial("PbGlass");

    auto solidWorld = new G4Box("World",
                                fWorldWidth/2.*cm,
                                fWorldHeight/2.*cm,
                                fWorldLength/2.*cm);
    auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    auto physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0, true);

    auto solidSample = new G4Box("Sample",
                                 fSampleWidth/2.*cm,
                                 fSampleHeight/2.*cm,
                                 fSampleLength/2.*cm);
    auto logicSample = new G4LogicalVolume(solidSample, PbGlass, "Sample");
    new G4PVPlacement(nullptr, {}, logicSample, "Sample", logicWorld, false, 0, true);

    fScoringVolume = logicSample;

    return physWorld;
}
