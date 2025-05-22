# Geant4GlassDose
Calculation of the irradiation dose for lead silicate glass samples by a proton beam with an energy of 200 MeV

# Init
```
cd build
cmake -DCMAKE_PREFIX_PATH="C:\Program Files\Geant4-11.3" ..
cmake --build . --config Release
```
After that you will get the executable file in the folder:
build\Release\GlassDose.exe

# Run particles simulation
```
/run/initialize
/control/execute vis.mac
/run/beamOn 10000
```


# For accumulation of photon prods on visualization if necessary, add in file vis.mac:
/vis/scene/endOfEventAction accumulate

№ By default, the colors in the visualization are:
Positively charged particles (e.g. protons) are shown in blue.
Negatively charged particles (e.g. electrons) are shown in red.
Neutral particles (e.g. gamma rays) are shown in green.

