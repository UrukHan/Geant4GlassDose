#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() { }
DetectorConstruction::~DetectorConstruction() { }

void DetectorConstruction::DefineMaterials() {
  G4double density = 4.0*g/cm3;
  auto PbGlass = new G4Material("PbGlass", density, 3);
  PbGlass->AddElement(G4NistManager::Instance()->FindOrBuildElement("Si"), 1);
  PbGlass->AddElement(G4NistManager::Instance()->FindOrBuildElement("O"), 2);
  PbGlass->AddElement(G4NistManager::Instance()->FindOrBuildElement("Pb"), 1);
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  DefineMaterials();

  auto PbGlass = G4Material::GetMaterial("PbGlass");

  auto solidWorld = new G4Box("World", 20*cm, 20*cm, 20*cm);
  auto logicWorld = new G4LogicalVolume(solidWorld, PbGlass, "World");
  auto physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0, true);

  fScoringVolume = logicWorld;

  return physWorld;
}

