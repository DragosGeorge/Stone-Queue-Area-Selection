# Metin Queue — Area Selection

An extension for the Metin Queue system that allows players to quickly select multiple Metin Stones directly from the game world.

Instead of adding each stone individually, players can draw a selection area with the mouse, similar to the selection box on a Windows desktop. Every visible Metin Stone within that area is automatically detected and added to the queue.

## Demonstration

[▶ Watch the video demonstration](./demonstration.mp4)

![Demo](demonstration.mp4)

## How to use

1. Hold the **CTRL** key.
2. Press and hold the left mouse button, then drag over the desired area.
3. Release the mouse button to confirm the selection.
4. Metin Stones within the selected area are automatically added to the queue.

## Features

- Simple visual selection inspired by the familiar Windows selection box.
- Detects visible Metin Stones within the selected area.
- Automatically ignores destroyed stones and duplicate entries.
- Respects the configured Metin Queue capacity.
- Prioritizes stones from nearest to farthest relative to the player.
- Correctly follows changes in camera position and viewing angle.
- Preserves the existing queue behavior and visual effects.

## Notes

The system can only select Metin Stones that are currently loaded and visible to the game client. Stones outside the rendering range cannot be added until the player moves close enough for them to load.

This feature is optional and can be enabled or disabled independently from the existing Metin Queue system.
