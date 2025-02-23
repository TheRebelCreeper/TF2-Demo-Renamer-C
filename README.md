# TF2 Demo Renamer
### [Download here!](https://github.com/TheRebelCreeper/TF2-Demo-Renamer-C/releases)
Parses demo files and adds the map name to the end of the file name  
To install just drag the .exe file to the same directory as the demo files.  
Ideally used with valve auto recording, supports prefix.
### Example
`rebel_2024-08-16_22-39-43.dem` will be renamed to `rebel_2024-08-16_22-39-43_cp_sunshine.dem` and  
`rebel_2024-08-16_22-39-43.json` will be renamed to `rebel_2024-08-16_22-39-43_cp_sunshine.json`


## How to build
Requires https://pcre2project.github.io/pcre2/

Windows mingw64:
```
cd pcre2/; cmake -G "MinGW Makefiles" -B build; cmake --build build/
```
