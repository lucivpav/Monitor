# Monitor
Tired of the shit-ass Dell monitors which are clumsy to alter the screen intensity? This program lets you adjust the brightness and contrast to the same value, so you don't need to manually slide both sliders. Dell, please, learn from EIZO what good UX looks like.

This CLI program currently works on Windows only. It uses Win32 API. Inspired by https://superuser.com/a/933564.

## Usage
```
Monitor.exe -- prints the usage information
Monitor.exe /show -- prints current brightness and contrast for every monitor detected

Monitor.exe /set 1 60 -- sets both brightness and contrast to 60% of monitor with id 1
Monitor.exe /brighter 1 -- increases the brightness and contrast to +10% of monitor with id 1
Monitor.exe /darker 1 -- decreases the brightness and contrast to -10% of monitor with id 1

Monitor.exe /set 60 -- sets both brightness and contrast to 60% of all monitors
Monitor.exe /brighter -- increases the brightness and contrast to +10% of all monitors
Monitor.exe /darker -- decreases the brightness and contrast to -10% of all monitors
```

## Building
Simply add the few source files into an empty Visual Studio C++ Windows solution and compile it.
