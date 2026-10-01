# Game Tutorial

| Input               | Action                                                         |
| ------------------- | -------------------------------------------------------------- |
| `A / D`             | Move left / right                                              |
| `Space`             | Jump                                                           |
| `Mouse`             | Aim when a shooting weapon is equipped                         |
| `Left Click`        | Shoot / Melee attack / interact with UI buttons                |
| `Mouse Wheel ↑ / ↓` | Switch weapons                                                 |
| `1 - 9`             | Select weapon directly                                         |
| `E`                 | Interact with checkpoints & chargers when inside their trigger |
| `Esc`                | Pause / Resume                                                 |
| `R`                 | Apply & save Options settings                                  |
| `F1`                | Toggle Fullscreen                                              |

### Movement & Aiming

- **Shooting weapon equipped (e.g. Blaster):** player faces the cursor. `A / D` move forward or backward relative to the facing direction.
- The player's aiming animation changes based on the cursor's vertical position: **horizontal, diagonal up, straight up, or diagonal down**.
- Moving the cursor further up/down changes the aiming animation when the corresponding angle threshold is reached. The weapon's firing point follows the weapon position shown in the current aiming animation.
- **Left Click with a shooting weapon:** fires toward the exact cursor position and rotation at the moment of firing, regardless of the current aiming animation angle.
- **No shooting weapon equipped:** the melee weapon is selected (e.g. bare hands). `A / D` control left/right orientation directly; the player does not face the cursor.
- **Left Click with the melee weapon:** performs a melee attack.
- When a shooting weapon is collected, it is added to the inventory and can be selected directly with its corresponding number key (`1 - 9`) or by using the mouse wheel.
- Example: `1` → melee, `2` → Blaster, `3` → weapon 3.

### Interactions

- **Weapons / Health / Ammo:** walk into the item to collect it.
- **Checkpoints (Flags) / Health & Ammo Chargers:** enter their trigger, then press `E`.
- **UI:** move the cursor over a button and press `Left Click`.
- **Options:** after changing settings, press the **Refresh** UI button or `R` to apply and save them.
- **Fullscreen:** press `F1` to toggle between fullscreen and window mode. When returning to window mode, the game restores the current resolution saved in Options. Fullscreen adapts to the monitor's resolution.
