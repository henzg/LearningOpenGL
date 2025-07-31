# OpenGL Graphics Pipeline Sandbox

This project is a minimal OpenGL sandbox designed for learning and experimentation. Its primary focus is understanding the graphics rendering pipeline at a low level, including how data flows through vertex buffers, shaders, and texture units.

## Purpose

The goal of this project is to build foundational knowledge of real-time rendering by working directly with OpenGL. It serves as a stepping stone toward eventually building a simple rendering engine or deepening understanding of how modern graphics systems work behind the scenes.

## What This Project Covers

- Vertex and index buffers
- Vertex array objects (VAOs)
- Basic shader programs (vertex + fragment)
- Texture loading and rendering
- Drawing geometry with proper pipeline setup

## In Progress / Planned Features

- Integrate Dear ImGui for real-time debugging and UI experimentation
- Add basic transformations (model/view/projection)
- Explore multiple shaders and texture units
- Potentially modularize into a lightweight graphics engine framework

## Project Philosophy

This is not a game or engine — it’s a low-level testbed for graphics programming. The focus is simplicity, clarity, and learning by building from scratch. All code is written with readability and experimentation in mind.

## Requirements

- C++17 or later
- OpenGL 3.3+
- GLFW
- GLAD
- stb_image (for texture loading)
