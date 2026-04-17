# Rivet — Mission

Rivet is a lightweight, bespoke general-purpose 2D game engine written in C++ and OpenGL.
It exposes a procedural, raylib-style API (free functions) — a library, not an editor.

## Principles

- **2D focused** — Purpose-built for 2D games; no 3D complexity.
- **Lightweight over monolithic** — Ship only what's needed, no bloat.
- **Simplicity first** — Prefer clear, procedural APIs (free functions) over deep abstractions.
- **Hand-roll first** — Build subsystems from scratch when practical; fall back to external libs only when the complexity isn't worth the learning.
- **Incremental delivery** — Small, working phases; every commit should compile and run.
