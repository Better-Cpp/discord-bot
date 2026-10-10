# discord-bot

A C++ discord bot for the Better-Cpp discord server

## Requirements

- GCC 16 or later for C++ 26
- CMake 4.0 or later
- Ninja 1.5 or higher
- Conan 2 or later

## Build

```bash
conan build . --build=missing -pr:a profiles/gcc-16
```

## Run

```bash
export BOT_TOKEN="YOUR_DISCORD_BOT_TOKEN"
./build/Release/bot
```
