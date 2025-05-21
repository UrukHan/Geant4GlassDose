#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv) {
  auto runManager = new G4RunManager;
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new QBBC);
  runManager->SetUserInitialization(new ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  if (argc > 1) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  } else {
    auto ui = new G4UIExecutive(argc, argv);
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}
