# Seamless v2.5.0 release qualification

The owner accepted `2cc7cb4` as a **preliminary** playtest pass on 2026-10-27
and explicitly authorized merging and releasing the experimental mod. This
does not establish full progression or cross-room combat coverage.

The shipped executable is identical to that accepted checkpoint:

- Executable SHA256: `74daf96cd6b85ef81f7b988a888e9e0024012c378e00b61a53cf9866bd6176e2`
- Windows ZIP SHA256: `55d380e0bbeb232fc9b4bff4d541020f1612af8101b787e245cda76a63165f9e`
- Engine pin: `957e9902de9b91107e61bc981f2ca871c8740446`
- Launcher pin: `c11a4b6c649164b6951eff107f4607dcef117dd5`
- USA payload CRC32: `57dd23d1`; native CPU backend and LLE PPU.

The engine integrates its current master, adds the bounded CIRAM handoff API,
and safely cleans package staging without overriding file protections. Its
post-playtest integration changes no compiled runtime behavior; the binary
identity above was checked directly.

| Gate | Result |
| --- | --- |
| Actual packaged launcher | Seamless is first, named Seamless, with amber EXP/EXPERIMENTAL marking and disabled default |
| UI enable and PLAY | First-row checkbox activates the mod without a CLI override; CIRAM bounds/isolation/upload/exact-state probe passes |
| Disabled catalog | Installed but disabled gives an identical complete state to stock and retains the native aspect |
| Enabled catalog | Correct continuous room handoff, adaptive picture, native/interpreter state and trace equality, exact current-build restore and picture |
| Fresh boot | 5,500 frames from startup match between native and interpreter using the packaged catalog |
| Dialogue regression | 24 checks pass: complete actors, no opening pose jump, stable pixels, script lifetime, original guest equality, backend parity, restore, neighboring sprite palette isolation |
| Seam/pause/inventory | Existing 20 checks pass, including complete state/picture restore and paused actor retention |
| Portrait and resizing | Actual shop interaction and wide/portrait SDL resizes retain actors, camera and expanded geometry |
| Actual death/retry colors | Complete guest core and actor OAM/CHR are unchanged; all 357 changed pixels in two affected NPC rooms map to the original outdoor palette |
| Existing Link mode | All eight spells, HP/MP effects, native/interpreter state/trace/picture, picker/effect restore, disabled default and wrong-ROM/invalid-state rejection pass |
| Package | ZIP integrity, complete PE C++ runtime closure, both opt-in catalogs and ROM/player-data exclusion pass; no loading-speed packages ship |
| Portable source | SDL-free compile passes |

Raw evidence is retained at
`G:/Temp/Codex/faxanadu-seamless-20261027/qa`: `release250`,
`dialogue-regression`, `dialogue-portable`, `dialogue-window`, and
`dialogue-sprites`. Earlier individual owner failures remain recorded beside
their later fixes. All automated launches were hidden and muted; native saves
and owner settings were preserved.

Remaining qualification and limitations are listed in
[Seamless world](SEAMLESS-WORLD.md). The existing x=3 clipped-player scratch-draw
failure occurs in both comparison builds and remains documented there; the
normal seamless crossing gate reports no failures. No full playthrough,
netplay, Link/Seamless combination, or non-Windows runtime claim is made.
