This is a remake of Scott Cawthon's "Five Nights at Freddy's 3" game. All rights reserved to him.
## Notes
This is a passion project. I love FNAF 3 and wanted to see it ported to other systems. If you haven't already, check out the steam page for [Five Nights at Freddys 3](https://store.steampowered.com/app/354140/Five_Nights_at_Freddys_3/)
## Controls
Press **Enter** to Fullscreen. I assume you know how to play FNAF 3.
## How to build
```
make
```
## How to install
```
make
make install // If on Linux
make clean
```
You can uninstall with ``make uninstall``. If you only want to run it ``make all`` works too.
## What is yet to be implemented
If it's not listed, you are safe to assume it works.
- Springtrap movement (70% done)
- Main menu, and any submenus
- Happiest day minigames (Unlikely to be implemented, unless I get the motivation to do so)
- Phantom Mangle
- Phantom Puppet
- Phantom Chica
- Savefiles
## Important note
The game looks for the assets  folder in the parent directory where the game is being contained
```
├── bin
│   └── fnaf3
└── assets
    └── 0.png
    └── 1.png
    └── ...
```
