#pragma once
#include "Engine/Sound/Sound.h"
#include "Engine/Sound/WorldSound.h"
#include "Objects/Camera/CameraFocus.h"
#include "Objects/Camera/CameraScrollTracker.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Breakables/BreakableBarrel.h"
#include "Objects/Platformer/Breakables/BreakableCage.h"
#include "Objects/Platformer/Breakables/CagedAnimals/CagedAnimals.h"
#include "Objects/Platformer/Breakables/Vase.h"
#include "Objects/Platformer/Camera/CameraControl.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Chests/Chest.h"
#include "Objects/Platformer/Chests/CipherChest.h"
#include "Objects/Platformer/Chests/MetalChest.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Cinematic/SquallyShip.h"
#include "Objects/Platformer/Collectables/IOUDrop.h"
#include "Objects/Platformer/Decor/FireplaceFire.h"
#include "Objects/Platformer/Decor/MagicWall.h"
#include "Objects/Platformer/Decor/Torch.h"
#include "Objects/Platformer/Interactables/AlchemyLab/AlchemyLab.h"
#include "Objects/Platformer/Interactables/Anvil/Anvil.h"
#include "Objects/Platformer/Interactables/Doors/CastleGate/CastleGate.h"
#include "Objects/Platformer/Interactables/Doors/EdgePortal.h"
#include "Objects/Platformer/Interactables/Doors/Gate/Gate.h"
#include "Objects/Platformer/Interactables/Doors/LanternGate/EdgeLanternGate.h"
#include "Objects/Platformer/Interactables/Doors/LanternGate/LanternGate.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/DarkPortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/FirePortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/FrostPortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/NaturePortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/VoidPortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/WaterPortal.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/WindPortal.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/AddDoor/AddDoor.h"
#include "Objects/Platformer/Interactables/Doors/PuzzleDoors/MulDoor/MulDoor.h"
#include "Objects/Platformer/Interactables/Doors/Temple/TempleDoor.h"
#include "Objects/Platformer/Interactables/Doors/TrapDoor/TrapDoor.h"
#include "Objects/Platformer/Interactables/Doors/TrapDoor/TrapDoorFrame.h"
#include "Objects/Platformer/Interactables/Doors/Warp.h"
#include "Objects/Platformer/Interactables/Doors/WoodenGate/WoodenGate.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemAttacking.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemEndOfDemo.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemHacking.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemHexusCards.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemPickPocket.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotemSwimHack.h"
#include "Objects/Platformer/Interactables/LifeStone.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Interactables/Tent.h"
#include "Objects/Platformer/Interactables/Spawns/PortalSpawn.h"
#include "Objects/Platformer/Interactables/Spawns/WoodDoorSpawn.h"
#include "Objects/Platformer/Liquids/Water.h"
#include "Objects/Platformer/Physics/Catapult/Catapult.h"
#include "Objects/Platformer/Physics/FloatingAsteroid/FloatingAsteroid.h"
#include "Objects/Platformer/Physics/FloatingCrate/FloatingCrate.h"
#include "Objects/Platformer/Physics/FloatingRock/FloatingRock.h"
#include "Objects/Platformer/Physics/FloatingWoodenBeam/FloatingWoodenBeam.h"
#include "Objects/Platformer/Physics/Wind/Wind.h"
#include "Objects/Platformer/Physics/WoodenCrate/WoodenCrate.h"
#include "Objects/Platformer/Shops/ShopItem.h"
#include "Objects/Platformer/Shops/ShopPoolMinos.h"
#include "Objects/Platformer/Shops/ShopPoolToben.h"
#include "Objects/Platformer/Spawns/CombatSpawn.h"
#include "Objects/Platformer/Switches/Lever/Lever.h"
#include "Objects/Platformer/Switches/StoneButton/StoneButton.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Objects/Platformer/Transportation/Airship1.h"
#include "Objects/Platformer/Transportation/Airship2.h"
#include "Objects/Platformer/Transportation/Ship.h"
#include "Objects/Platformer/Traps/FloatingBomb/FloatingBomb.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHug.h"
#include "Objects/Platformer/Traps/Laser/Laser.h"
#include "Objects/Platformer/Traps/Launchers/DartLauncher/DartLauncher.h"
#include "Objects/Platformer/Traps/Launchers/DartTripodLauncher/DartTripodLauncher.h"
#include "Objects/Platformer/Traps/Launchers/DartTripodLauncher/DartTripodLauncherSqualr.h"
#include "Objects/Platformer/Traps/Launchers/FireLauncher/FireLauncher.h"
#include "Objects/Platformer/Traps/Launchers/FireLauncher/FireLauncherSqualr.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlail.h"
#include "Objects/Platformer/Traps/MetalSpikes/MetalSpikes.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBlade.h"
#include "Objects/Platformer/Traps/SpikedBall/SpikedBall.h"
#include "Objects/Platformer/Traps/SpikedLog/SpikedLog.h"
#include "Objects/Platformer/Traps/WoodenSpikes/WoodenSpikes.h"
#include "Objects/Platformer/Interactables/Tutorials/FloatTutorialPortal.h"
