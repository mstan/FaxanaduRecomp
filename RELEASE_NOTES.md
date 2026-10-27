# v2.5.0 - experimental Seamless mod

Adds **Seamless** at the top of Mods, marked **Experimental** and disabled by
default. Enable it to join supported connected rooms into a continuous world
with moving neighboring actors and adaptive **Fit to screen** widescreen.

- The camera follows across supported horizontal and ladder seams, clamps at
  region edges, and adapts to wide or portrait windows without stretching.
- Pause, inventory and dialogue retain the expanded view. Characters stay in
  place during dialogue; neighboring terrain, NPCs and enemies use the correct
  world colors. Death and retry preserve the adaptive canvas.
- Resize freely; mouse wheel changes pixel zoom, and F4 shows the connected map.
  Start pauses, Select opens inventory, and B closes it.
- Doors, key checks and scripted region changes retain their native behavior.
  Seamless and Play as Link are separate, mutually exclusive local-play mods.

**Validation:** the owner passed a preliminary playtest. Automated checks cover
representative seams and ladders, native door rules, NPC and portrait dialogue,
pause/inventory, adaptive resizing, death/retry, current-build save/load, and
native/interpreter agreement. Broader progression, bosses and secrets remain
under qualification; combat/projectiles across room ownership boundaries are
incomplete. See [Seamless details and limits](https://github.com/mstan/FaxanaduRecomp/blob/v2.5.0/docs/SEAMLESS-WORLD.md).

Download and extract `FaxanaduRecomp-windows-x64.zip`, run the executable, and
select your own **Faxanadu USA** ROM. Windows x64 runtime dependencies and both
mod catalogs are included. No ROMs, extracted owner assets, player settings or
saves are included. Native mantra saves remain supported; save states are
build-specific.
