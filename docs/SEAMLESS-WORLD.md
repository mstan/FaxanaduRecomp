# Seamless world preview

Owner request: 2026-10-27. Tracking: `beads-2dw.17.2`; shared CIRAM upload:
`beads-2dw.1.108`. Isolated branch: `feat/seamless-world-20261027`, based on
released Faxanadu `6a297c2`. This is an experimental local-play preview,
not a fully qualified replacement or release.

## Playable behavior

Enable **Seamless World (Experimental)** in Mods. Ordinary reciprocal screen
connections form a continuous world: the camera follows the player, adjacent
terrain is visible, and neighboring native actors advance before entry.
Room handoffs keep those actor instances rather than respawning them.
Horizontal movement and climbing continue through supported seams without
the original stop-and-scroll sequence.

**Fit to screen is adaptive.** Window width and height determine the actual
world viewport at the selected pixel zoom. Wide windows show more horizontal
terrain; portrait windows show more vertical terrain. The HUD stays centered
and scales down when the viewport is narrower than 256 pixels. Mouse wheel
changes pixel zoom; F4 toggles a connected-map overview, capped at the
preview's 4096x2048 presentation limit. Empty space outside the connected
geometry remains empty; terrain is not stretched or repeated to fill it.

Doors, region changes and connections that cannot be embedded consistently
retain native portal transitions. Original key checks, scripts and progress
remain in charge. Native inventory, dialogue and pause use native presentation.
Native controls: Select opens inventory; B closes it; Start pauses/unpauses.
This preview is exclusive with Play as Link until their adapters are qualified
together. Both enhancements remain available separately.

## Implementation and reuse

Faxanadu's verified USA disassembly and prior native loader/actor fixtures
were reused. The approach follows the Zelda seamless-world room-instance
prototype (`beads-2dw.18.3`) but uses Faxanadu's actual neighbor tables,
256x208 playfields, native ladders and screen-specific actors. A whole-game
rewrite would replace already functioning combat, scripted doors and mantra
progression; reusing the original routines is the smaller coherent change.

`fax_world.c` calls the ROM's screen decoder and actor/image loaders inside
complete isolated machines. Each room owns actor arrays, local timers/RNG,
terrain, collision borders, graphics and palette. The real player, stack,
inventory, music, global events and persistent saves retain their ownership.
Only explicit room-local fields transfer at a seam. Native actor routines
run in a visible-area halo, while inactive rooms retain their records.

The original player starts a right scroll when his right edge crosses at
x=241. This adapter retains the source until his origin wraps, preserving
continuous position. Wrapped floor/ladder samples read the correct neighboring
terrain. Vertical handoffs account for the original early scroll thresholds.
An isolated native player pose supplies tiles the NES raster clips at seams.

Native nametables also update at a handoff, preserving HUD data, so menus
and subsequent scripted transitions see the current terrain. The shared
`cyc_mod_ciram_upload` API validates bounds before any write, refuses isolated
calls, refreshes PPU caches and advances no emulated time. It addresses physical
CIRAM; the trusted caller remains responsible for layout and mirroring.

All content-qualified hooks and the payload CRC bind this profile to Faxanadu
USA `57dd23d1`. No ROM, disassembly, extracted graphics or map data is shipped.
World instance state and pending seam/collision policy serialize in a validated
mod record. Old save states need not be compatible; native mantra saves are
separate. The feature marks its session local-only.

## Validation and limits

Raw commands, inputs, per-frame world journals, hashes, complete states, PNGs
and receipts are retained under `G:/Temp/Codex/faxanadu-seamless-20261027/qa`.
All automated launches were hidden and muted with native saves disabled.

| Check | Result / scope |
| --- | --- |
| Horizontal crossings | Representative left/right exits in Trunk, Mist, Branch, Dartmoor and Zenis; native/interpreter state and trace agreement, destination reached, no stop-and-scroll in qualified per-frame journals |
| Vertical ladder | Real Trunk 3->4 upward ladder and 4->3 downward return, with no scrolling mode; downward native/interpreter state agreement |
| Neighbor actors | Actual room positions/ticks change before entry and remain in the adopted instance; no cross-room combat claim |
| Native door rules | Trunk 13->11 normal door; Trunk 11->13 refuses without J key, opens after a granted key and native use dialogue; native/interpreter state agreement |
| Inventory / native terrain | Native Select inventory and B close after a seamless handoff; native background remains the destination room |
| Current-build restore | Supported right seam: complete final state and rendered picture reproduce exactly after save/load; native/interpreter state and rolling trace match |
| Adaptive Fit | Actual SDL 1536x720 -> 512x240, 600x1200 -> 200x400, 3840x720 -> 1280x240; complete HUD remains visible in portrait |
| Shared CIRAM API | Invalid bounds/NULL and isolated upload refused; upload/restore succeeds; serialized complete machine unchanged after the probe |
| Catalog / prepared helper | Feature activation without CLI override; hidden helper loads and pauses all prepared states; owner configuration restored to normal audio |

Assistance supplied player positions, health/protection, original screen-loader
entries and the explicitly granted J key. It did not set door success, quest
completion, enemy HP or victory flags. Initial failed Dartmoor/Zenis probes
had already fallen out of their source rooms during setup; corrected entrances
were checked against baseline movement and retained separately. The initial
invalid fixtures are not accepted coverage. Branch's return probe naturally
falls onto a lower platform after crossing; equal final Y is not required.

Component timings are exposed through TCP and retained in the receipts. They
are simulation/render/upload costs, not total host frame-time measurements.
Normal views run a bounded halo; wide/map views activate more rooms and cost
more. Initial region decoding and native portal delays remain separate costs.

Still open: enemy/projectile migration and combat while participants belong to
different rooms; broader boss, secret, breakable terrain, death/retry and ending
coverage; complete progression/mantra gameplay audit; Link integration; full-map
costs and other hosts. Actors chase a projected local player in neighboring
rooms. This can change encounter timing compared with stock and needs human
playtesting. No full playthrough, netplay, legacy-host or non-USA claim is made.

## Reproduction and prepared playtest

Build with the pinned engine and normal `tools/build.ps1` pipeline. The engine
includes the previously qualified adaptive drawable-size getter and this
preview's bounded CIRAM upload. SDL-free builds retain a portable timing fallback
and omit SDL/TCP event integration; the standalone SDL-free object compile
also passes. Only Windows x64 has been built for this preview so far.

```powershell
python tests/world/integration.py --exe <FaxanaduRecomp.exe> --rom <USA-ROM> `
  --state <current-build-supported-right-exit.cycstate> --out <QA-directory>
```

The fixture must place the native player at x=240 on a supported right exit.
The test records source/binary identities, executes native/interpreter routes,
checks every logged scroll mode and compares current-build replay.

Developer CLI: `--world-view off|seamless|atlas`; `--world-size WxH` fixes the
viewport for reproducibility, so omit it for adaptive Fit. TCP: `fax_world`,
`fax_world_room` and `fax_world_probe`. `NESRECOMP_WORLD_TRACE=<path>` explicitly
enables the per-frame CSV; ordinary launches create no world journal.

The task's `preview/Open-preview.ps1` starts a normal window, normal audio and
a localhost checklist. The first setup is paused. Tests can be switched and
resumed without an agent, and individual Pass/Fail/Deferred notes persist in
`observations.json`. The helper disables native saves and uses its own profile.
It has been verified hidden; an owner-facing game has not been launched.
