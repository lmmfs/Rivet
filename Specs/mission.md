# Rivet — Mission

Rivet is a lightweight, bespoke general-purpose game engine written in C++ and OpenGL.
It exposes a procedural, raylib-style API (free functions) — a library, not an editor.

Rivet is built around a shared platform core (windowing, input, events, audio, assets, UI) with separate, swappable renderer and physics modules for 2D and 3D. A game picks the modules it needs; nothing else is pulled in.

## Principles

- **Shared core, modular capability** — Platform code is written once; 2D and 3D are separate modules built on top.
- **Lightweight over monolithic** — Ship only what's needed, no bloat.
- **Simplicity first** — Prefer clear, procedural APIs (free functions) over deep abstractions.
- **Hand-roll first** — Build subsystems from scratch when practical; fall back to external libs only when the complexity isn't worth the learning.
- **Incremental delivery** — Small, working phases; every commit should compile and run.
