## idTech4A++ (Harmattan Edition)
#### DOOM III/Quake 4/Prey(2006) for Android/Linux, 毁灭战士3/雷神之锤4/掠食(2006)安卓/Linux移植版. Original named DIII4A++, based on com.n0n3m4.diii4a
**Latest version:**
1.1.0harmattan38(natasha)  
**最新更新日期:**
2024-01-15  
**Arch:**
arm64 armv7-a  
**Platform:**
Android 4.4+  
**License:**
GPLv3

----------------------------------------------------------------------------------
### Feature
* Linux/Windows(MinGW) build(testing)
* multi-threading renderer
* png/dds texture image
* jpeg/png/bmp/dds format of screenshot
* obj format static model
* dae format static model
* pure soft shadow with shadow-mapping
* OpenGLES2.0/OpenGLES3.0
* OpenAL(soft) and EFX Reverb
* no-lighting rendering and no-lighting material
* translucent stencil shadow
* DOOM3 mods: DOOM3(with full body awareness mod); The Lost Mission; Classic DOOM; Rivensin; Hardcorps; Overthinked; SABot-a7x; HexenEOC; Fragging-Free
* Quake4(with bot mod, full body awareness mod) and Raven's idTech4 engine
* Prey(2006)(with full body awareness mod) and HumanHead's idTech4 engine

[<img src="https://fdroid.gitlab.io/artwork/badge/get-it-on.png"
     alt="Get it on F-Droid"
     height="80">](https://f-droid.org/packages/com.karin.idTech4Amm/)

Or download the latest APK from the [Releases Section](https://github.com/glKarin/com.n0n3m4.diii4a/releases/latest).
Tag with `-free` only for F-Droid update.

| Feature | Github | F-Droid |
|:-|:-:|:-:|
| Ouya TV | Yes | No |

----------------------------------------------------------------------------------
### Update

* Fixed shadow mapping on non-Adreno GPU.
* Support level loading finished pause(cvar `com_skipLevelLoadPause`) in Quake4.

----------------------------------------------------------------------------------

#### About Prey(2006)
###### For playing Prey(2006)([jmarshall](https://github.com/jmarshall23) 's [PreyDoom](https://github.com/jmarshall23/PreyDoom)). Now can play all levels, but some levels has bugs.
> 1. Putting PC Prey game data file to `preybase` folder and START directly.
> 2. Some problems solution: e.g. using cvar `harm_ui_translateAlienFont` to translate Alien text on GUI.
> 3. Exists bugs: e.g. some incorrect collision(using `noclip`), some GUIs not work(Music CD in RoadHouse).
> 4. If settings UI is not work, can edit `preyconfig.cfg` for binding extras key.
> > * bind "Your key of spirit walk" "_impulse54"
> > * bind "Your key of second mode attack of weapons" "_attackAlt"
> > * bind "Your key of toggle lighter" "_impulse16"
> > * bind "Your key of drop" "_impulse25"

----------------------------------------------------------------------------------

#### About Quake IV
###### For playing Quake 4([jmarshall](https://github.com/jmarshall23) 's [Quake4Doom](https://github.com/jmarshall23/Quake4Doom)). Now can play all levels, but some levels has bugs.  
> 1. Putting PC Quake 4 game data file to `q4base` folder and START directly.
> 2. Suggest to extract Quake 4 patch resource to `q4base` game data folder first(in menu `Other` -> `Extract resource`).
> - `SABot a9 mod` multiplayer-game map aas files and bot scripts(for bots in multiplayer-game).

###### Problems and resolutions  
> 1. ~~Door-opening/Collision~~: Now collision bug has fixed, e.g. trigger, vehicle, AI, elevator, health-station, all doors can be opened.
> 2. *Main-menu*: Now main menu and MP game menu is work, but without background color. But some GUIs can not interactive.
> 3. ~~Sound~~: It looks work well now.
> 4. ~~Loading-UI~~: It looks work well now.
> 5. ~~Multiplayer-Game~~: Now is working well with bots(added SABot a7 mod support, but need `SABot a9 mod` file and Multiplayer-Game map AAS file, now set cvar `harm_g_autoGenAASFileInMPGame` to 1 for generating a bad AAS file when loading map in Multiplayer-Game and not valid AAS file in current map, you can also put your MP map's AAS file to `maps/mp` folder(aas32)).
> 6. *Script error*: Some maps have any script errors, it can not cause game crash, but maybe have impact on the game process.
> 7. *Particle system*: Now is not work(Quake4 using new advanced `BSE` particle system, it not open-source, `jmarshall` has realized and added by decompiling `ETQW`'s BSE binary file, also see [jmarshall23/Quake4BSE](https://github.com/jmarshall23/Quake4BSE)), but it not work yet. Now implementing a OpenBSE with DOOM3 original FX/Particle system, some effects can played, but has incorrect render.
> 8. *Entity render*: Some game entities render incorrect.
> 9. ~~Font~~: Support Q4 format fonts now. [IlDucci](https://github.com/IlDucci)'s DOOM3-format fonts of Quake 4 is not need on longer.

----------------------------------------------------------------------------------
### Screenshot
> Game

<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_bathroom.png" alt="Classic bathroom">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_bathroom_jill_stars.png" alt="Classic bathroom in Rivensin mod">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_quake4_game_2.png" alt="Quake IV on DOOM3">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_prey_girlfriend.png" alt="Prey(2006) on DOOM3">

> Mod

<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_roe.png" width="50%" alt="Resurrection of Evil"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_the_lost_mission.png" width="50%" alt="The lost mission">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_classic_doom3.png" width="50%" alt="Classic DOOM"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_hardcorps.png" width="50%" alt="Hardcorps">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_doom3_rivensin.png" width="50%" alt="Rivensin"><img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_quake4.png" width="50%" alt="Quake IV">
<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/package/screenshot/Screenshot_prey.png" width="50%" alt="Prey(2006)">

> Quake 4 on Debian

<img src="https://github.com/glKarin/com.n0n3m4.diii4a/raw/master/Quake4_on_Debian.png" alt="Quake 4 on Debian">
----------------------------------------------------------------------------------

### Changes:

[Change logs](CHANGES.md ':include')

----------------------------------------------------------------------------------

### Build:

#### Engine
> 1. _MULTITHREAD: Add multithread support for rendering.
> 2. _USING_STB: Using stb header for jpeg/png/dds texture image and jpeg/png/bmp/dds screenshot support.
> 3. _K_CLANG: If compiling by clang not GCC.
> 4. _MODEL_OBJ: Add obj static model support.
> 5. _MODEL_DAE: Add dae static model support.
> 6. _SHADOW_MAPPING: Add Shadow mapping support.
> 7. _OPENGLES3: Add OpenGLES3.0 support.
> 8. _OPENAL _OPENAL_EFX _OPENAL_SOFT: Add OpenAL(soft) and EFX Reverb support.
> 9. _NO_LIGHT: Add no lighting support.
> 10. _TRANSLUCENT_STENCIL_SHADOW: Add translucent stencil shadow support.

#### If want to port `Quake4` or `Prey(2006)` to PC or other platform of based on `DOOM3` engine open-source version, because DIII4A based on Android platform and OpenGL ES2.0, so has some differences with original version. But I mark some macros in source as patches at all changes, although must find these macros in source code and manual use these patches.
#### And for keeping original DOOM3 source file structures, for all new source files, I put them on a new folder, and in these folder has same directory structure with DOOM3(e.g. framework, renderer, idlib...).

#### Quake 4
##### `_RAVEN`, `_QUAKE4` is patches macros, find them in `DIII4A` source code.
##### All new sources files put on `raven` folder.
> 1. _RAVEN: for compile `core engine (DOOM3 source code)` and `idlib (DOOM3 source code)`.
> 2. _QUAKE4: for compile `game (Q4SDK source code)` library.
> 3. Build core engine: define macro `_RAVEN`, `_RAVEN_FX(OpenBSE if need, unnecessary)`
> 4. Build game library: define macro `_RAVEN`, `_QUAKE4`
##### About `BSE`
Because `BSE` not open-source, so I default supply a `NULL` implement and a uncompleted but working implement with DOOM3 Particle/Fx system(using macros `_RAVEN_FX` marked).
##### About `BOT`
Define macro `MOD_BOTS` will compile SABot a7(from DOOM3) mod source code for bot support in multiplayer-game.

#### Prey(2006)
##### `_HUMANHEAD`, `_PREY` is patches macros, find them in `DIII4A` source code.
##### All new sources files put on `humanhead` folder.
> 1. _HUMANHEAD: for compile `core engine (DOOM3 source code)` and `idlib (DOOM3 source code)`.
> 2. _PREY: for compile `game (PreySDK source code)` library.
> 3. Build core engine: define macro `_HUMANHEAD`
> 4. Build game library: define macro `_HUMANHEAD`, `_PREY`, and original SDK macros `HUMANHEAD`

#### Android
##### Define macro `__ANDROID__`.
> 1. _OPENSLES: Add OpenSLES support for sound.

#### Linux
##### Define macro `__linux__`.
> 1. Support ALSA.

#### Windows(MinGW)
##### Define macro `_WIN32` and `WIN32`.
> 1. REQUIRE SDL2, zlib
> 2. NOT SUPPORT OpenGLES3, OpenAL, cURL

----------------------------------------------------------------------------------

### About:

* Source in `assets/source` folder in APK file.
	
----------------------------------------------------------------------------------

### Branch:

> `master`:
> * /idTech4Amm: frontend source
> * /Q3E /Q3E/src/main/jni/doom3: game source

> `free`:
> * For F-Droid pure free version.

> `package`:
> * /screenshot: screenshot pictures
> * /source: Reference source
> * /pak: Game resource
> * /CHECK_FOR_UPDATE.json: Check for update config JSON

> `n0n3m4_original_old_version`:
> * Original old `n0n3m4` version source.

----------------------------------------------------------------------------------
### Extras download:

* [Baidu网盘: https://pan.baidu.com/s/1hXvKmrajAACfcCj9_ThZ_w](https://pan.baidu.com/s/1hXvKmrajAACfcCj9_ThZ_w) 提取码: `pyyj`
* [Baidu贴吧: BEYONDK2000](https://tieba.baidu.com/p/6825594793)
* [F-Droid(different signature)](https://f-droid.org/packages/com.karin.idTech4Amm/)
----------------------------------------------------------------------------------
