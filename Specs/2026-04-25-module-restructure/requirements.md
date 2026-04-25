# Phase 12 — Module Restructure: Requirements

## Scope
Reorganise the Rivet source tree so that the platform core, 2D renderer, 2D physics, and future 3D modules each live in clearly separated directories. No new functionality is introduced in this phase.

## Motivation
Phases 13–15 will add a 3D renderer and 3D physics module. Without a clear directory structure first, adding 3D would create ambiguous include paths and clutter the existing source. This phase creates the skeleton those modules will live in.

## Target directory layout

```
Rivet/Source/Rivet/
├── Core/               ← App, Window, Input, Logger, Editor, Events, Assets, Audio, UI, Math
├── Renderer/
│   ├── Common/         ← Shader, Buffer, BufferLayout, Texture
│   ├── 2D/             ← Renderer (was Renderer2D), Camera (was Camera2D)
│   └── 3D/             ← empty, ready for Phase 13
├── Physics/
│   ├── 2D/             ← Physics, PhysicsTypes (was Physics.h, PhysicsTypes.h)
│   └── 3D/             ← empty, ready for Phase 14
└── Rivet.h             ← umbrella header, updated includes
```

## Decisions
- **File renaming:** the `2D`/`3D` suffix is dropped from file names; the containing folder provides that context (e.g. `Renderer2D.h` → `Renderer/2D/Renderer.h`).
- **No API changes:** all public-facing types, namespaces, and free functions remain identical. Only file paths change.
- **Namespace unchanged:** `Rivet::`, `Rivet::Renderer2D::`, `Rivet::Physics::` namespaces are NOT renamed in this phase.
- **PCH (`Rvtph.h`):** updated only if it directly includes moved files.
- **3D placeholders:** `Renderer/3D/` and `Physics/3D/` directories are created but left empty; they will be populated in Phases 13–14.

## Out of scope
- Any new rendering or physics functionality
- Renaming C++ namespaces
- Changes to the Sandbox application logic
