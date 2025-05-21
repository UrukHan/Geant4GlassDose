#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() { }
DetectorConstruction::~DetectorConstruction() { }

void DetectorConstruction::DefineMaterials() {
  auto nist = G4NistManager::Instance();

  // PbGlass (свинцово-силикатное стекло)
  G4double density = 4.0*g/cm3;
  auto PbGlass = new G4Material("PbGlass", density, 3);
  PbGlass->AddElement(nist->FindOrBuildElement("Si"), 1);
  PbGlass->AddElement(nist->FindOrBuildElement("O"), 2);
  PbGlass->AddElement(nist->FindOrBuildElement("Pb"), 1);

  // Воздух
  nist->FindOrBuildMaterial("G4_AIR");
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  DefineMaterials();

  auto air = G4Material::GetMaterial("G4_AIR");
  auto PbGlass = G4Material::GetMaterial("PbGlass");

  // Мир (воздух)
  auto solidWorld = new G4Box("World", 30*cm, 30*cm, 30*cm);
  auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");
  auto physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0, true);

  // Образец (PbGlass, куб 10 см)
  auto solidSample = new G4Box("Sample", 5*cm, 5*cm, 5*cm);
  auto logicSample = new G4LogicalVolume(solidSample, PbGlass, "Sample");
  new G4PVPlacement(nullptr, {}, logicSample, "Sample", logicWorld, false, 0, true);

  fScoringVolume = logicSample;

  return physWorld;
}
