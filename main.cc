#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

json LoadConfig(const std::string& filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    G4Exception("main", "FileNotFound", FatalException, "Cannot open config file.");
  return json::parse(f);
}

int main(int argc, char** argv) {
  auto config = LoadConfig("config.json");

  auto world = config["world_size_cm"];
  auto sample = config["sample_size_cm"];
  double density = config["sample_density_g_cm3"];
  bool visualization = config["visualization"];

  auto runManager = new G4RunManager;
  runManager->SetUserInitialization(
    new DetectorConstruction(
      world["length"], world["width"], world["height"],
      sample["length"], sample["width"], sample["height"],
      density
    )
  );
  runManager->SetUserInitialization(new FTFP_BERT);
  runManager->SetUserInitialization(
    new ActionInitialization(sample["length"], sample["width"], sample["height"], density)
  );

  G4VisExecutive* visManager = nullptr;
  if (visualization) {
    visManager = new G4VisExecutive;
    visManager->Initialize();
  }

  auto UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/initialize");

  if (visualization)
    UImanager->ApplyCommand("/control/execute vis.mac");

  std::string particle = config["particle"];
  double energy_MeV = config["energy_MeV"];
  auto pos = config["position_cm"];
  auto dir = config["direction"];
  int num_particles = config["number_of_particles"];

  UImanager->ApplyCommand("/gun/particle " + particle);
  UImanager->ApplyCommand("/gun/energy " + std::to_string(energy_MeV) + " MeV");
  UImanager->ApplyCommand("/gun/position " +
    std::to_string(pos[0].get<double>()) + " " +
    std::to_string(pos[1].get<double>()) + " " +
    std::to_string(pos[2].get<double>()) + " cm"
  );
  UImanager->ApplyCommand("/gun/direction " +
    std::to_string(dir[0].get<double>()) + " " +
    std::to_string(dir[1].get<double>()) + " " +
    std::to_string(dir[2].get<double>())
  );

  UImanager->ApplyCommand("/run/beamOn " + std::to_string(num_particles));

  std::cout << "Press ENTER to exit..." << std::endl;
  std::cin.get();

  delete visManager;
  delete runManager;
}
