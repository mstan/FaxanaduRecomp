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
terrain; portrait windows show more vertical terrain. The camera clamps to
the connected region's edges, keeping the floor at the viewport bottom when
the region is shorter than the view. The HUD stays centered
and scales down when the viewport is narrower than 256 pixels. Mouse wheel
changes pixel zoom; F4 toggles a connected-map overview, capped at the
preview's 4096x2048 presentation limit. Empty space outside the connected
geometry remains empty; terrain is not stretched or repeated to fill it.

Doors, region changes and connections that cannot be embedded consistently
retain native portal transitions. Original key checks, scripts and progress
remain in charge. Start pause freezes the expanded world without changing its
aspect ratio. The native inventory appears over the frozen expanded world;
only its text boxes cover the scene, so actors remain visible both inside and
outside the original NES bounds. Its complete panel scales down in narrow
windows. Dialogue retains a completed world pose and camera throughout the
opening, text, and closing; native text and portrait panels cover that scene.
Death retains its native animation inside the adaptive canvas.
Neighboring terrain uses the current region background palette, including
native fades. All visible actors use the active world scene's sprite palette;
cached building or portrait palettes cannot recolor neighboring NPCs/enemies.
Native controls: Select opens inventory; B closes it; Start pauses/unpauses.
The painted gate in the first Trunk room has no registered Up destination in
the USA game. The preview preserves that behavior; its registered-door setup
provides an actual unlocked Up interaction.
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
| Pause / inventory aspect | Original Start and Select inputs retain the expanded picture and frozen room records, with native/interpreter agreement; host-paused wide/portrait resizes preserve the paused frame and neighboring ticks |
| Camera / scripts | Camera bounds checked at real wide/portrait drawable sizes; death/animation/message frames retain the adaptive canvas. Real NPC and locked-door dialogue retain completed actors and stable pixels throughout the message, preserve guest execution against the original, and reproduce exactly through save/load; shop portrait panels and closing also checked |
| Town palette | Eight connected Eolis rooms match native terrain samples; stale white instance palettes cannot recolor terrain. Static setup probes were neutral; the actual death/retry route reproduces stale neighboring NPC-room palettes in the old build, and the candidate corrects them with an identical complete guest core state |
| Sprite palette | Actual death/retry A/B preserves actor OAM, CHR and complete guest core state. All 357 changed sprite pixels in two affected NPC rooms map from stale building colors to the native outdoor palette; poisoning neighboring sprite palettes no longer changes NPC or enemy colors |
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
python tests/world/dialogue.py --exe <FaxanaduRecomp.exe> --rom <USA-ROM> `
  --npc-state <stock-Up-contact.cycstate> --door-state <stock-locked-door.cycstate> `
  --out <dialogue-QA-directory>
```

The fixture must place the native player at x=240 on a supported right exit.
Prepared outdoor fixtures must enter through `Game_SetupAndLoadOutsideArea`
or explicitly supply the native destination palette when using the horizontal
area-change loader. The latter retains its caller's palette argument; using it
alone can produce mechanically valid geometry with incorrect colors. Earlier
preview states had that preparation defect and are superseded.
The test records source/binary identities, executes native/interpreter routes,
checks every logged scroll mode and compares current-build replay.
The dialogue test requires Pillow and visible, nonblinking player fixtures.
Its original/candidate and interpreter comparisons cover the actual dialogue
input, pixel stability, opening pose, closing, palette isolation and restore.
An existing clipped-player scratch draw failure at `$B982` occurs once in both
the preceding and current builds with the x=3 NPC fixture; it is retained in
the raw logs and is not evidence of a new regression or a fully audited edge
renderer. The normal seam regression reports no failures.

Developer CLI: `--world-view off|seamless|atlas`; `--world-size WxH` fixes the
viewport for reproducibility, so omit it for adaptive Fit. TCP: `fax_world`,
`fax_world_room` and `fax_world_probe`. `NESRECOMP_WORLD_TRACE=<path>` explicitly
enables the per-frame CSV; ordinary launches create no world journal.

The task's `preview/Open-preview.ps1` starts a normal window, normal audio and
a localhost checklist. The first setup is paused. Tests can be switched and
resumed without an agent, and individual Pass/Fail/Deferred notes persist in
`observations.json`. The helper disables native saves and uses its own profile.
The owner has playtested earlier checkpoints; individual failures and subsequent
candidate evidence remain separate. Human acceptance of this checkpoint is open.
