# Rivet — Tech Stack

| Layer        | Choice          | Version | Notes                              |
|--------------|-----------------|---------|-------------------------------------|
| Platform     | Linux           | —       | Wayland tested; X11 untested        |
| Language     | C++             | C++23   |                                     |
| Build        | CMake           | ≥ 3.14  | Unix Makefiles, FetchContent        |
| Windowing    | GLFW            | 3.4     | Wayland backend (X11 disabled)      |
| GL Loader    | GLAD            | 2.0.8   | OpenGL 4.6 Core                     |
| Math         | GLM             | 1.0.1   |                                     |
| Logging      | spdlog          | 1.16.0  |                                     |
| Image        | stb_image       | 2.30    | Vendored                            |
| PCH          | Rvtph.h         | —       | Precompiled header                  |
