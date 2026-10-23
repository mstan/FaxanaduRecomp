# Link mod validation, 2026-10-23

The production build uses the game's pinned cycle engine `0498965` and the
USA Faxanadu profile. All automated games were hidden and muted, with native
audio emulation retained. Generated ROM copies, fixtures, logs, captures and
builds are under `G:/Temp/Codex/faxanadu/link-mod`, outside the source tree.
The original checkout's unrelated dirty files were preserved.

## Passed checks

| Check | Evidence / outcome |
|---|---|
| Original movement and animation | 7,276 checks against executed Zelda II walking, randomized walking animation, jumping, sword phases/display/beam timing and bounce routines; MSVC and GCC |
| Supported Faxanadu image | Full disassembly rebuild matched all 16 PRG banks; all 19 hook content keys verified |
| Eight spells | Native/interpreter complete states, machine traces and presentation match; MP costs and Life healing checked |
| Current-build save/load | Open-picker and active-effect continuation match uninterrupted execution for every spell |
| Mod gating | Installed-disabled equals stock; wrong owner ROM refuses activation; incompatible mod record rejected before load |
| Authored rooms | All 272 entries run through original area/table/screen loaders, followed by 272 native/interpreter movement-and-jump pairs with identical final states |
| Ladders | Climb and A dismount pass in Trunk, Mist, Branch, Dartmoor and Zenis; Eolis has no ladder segment in its authored data |
| Horizontal exits | Supported left and right exits pass in each of those five outside regions |
| Vertical exits | Actual native ladder ascent and Link-controlled downward transitions reach their native neighbors |
| Doors and requirements | Normal doors work; native J/Q/K key requirements remain enforced; native Demon's Ring handler retained |
| Inventory / items | Start shows native inventory and B closes it; Down+Start consumes a granted Red Potion and heals 32 to 80 HP after native A confirmation; Down+B retains that item |
| Vertical attacks | Upstab and downstab inflict native damage; downstab produces upward bounce after actual contact |
| Guard / Shield / Reflect | Same live projectile: rear hit reduces HP 80 to 52; Shield reduces it to 66; front guard leaves 80, removes the projectile; Reflect produces an outgoing magic projectile with life 128 |
| Spell / Thunder / Fire | A live ordinary enemy becomes a stationary harmless Fairy; Thunder produces native magic damage and defeat; Fire spawns from the sword |
| Death / retry | Native dissolve/fade/dialogue/retry runs with matching native/interpreter state; restored player has 80 HP |
| Ending | Real Shadow Eura defeat naturally reaches the King's room, dialogue, restored-world ending and title; native/interpreter states match |
| SDL window / keyboard | Hidden software-rendered window: V opens picker, NES keyboard input selects Jump, C casts for 5 MP; mantra encoder output unchanged |
| Audio | Muted 44,100 Hz combined world/sword/beam captures contain nonzero PCM and match byte-for-byte between native and interpreter |
| Release packaging | ROM/player-data exclusion, disabled default and PE import audit; licensed x64 Visual C++ runtime DLLs staged beside the executable |

The room count comes from the actual original pointer tables:

| Area | Screens |
|---|---:|
| Eolis | 9 |
| Trunk | 64 |
| Mist | 83 |
| Towns | 14 |
| Buildings | 10 |
| Branch | 40 |
| Dartmoor | 32 |
| Zenis | 20 |

The reference's human-readable `ZENITH_BLOCKS` and `DARTMOOR_BLOCKS` labels in
PRG2 are interchanged relative to the original runtime's area lookup. The
audit follows the runtime lookup. Twelve initial room probes naturally
transitioned to another room; these are recorded as transitions rather than
asserted as stationary room screenshots. Dynamic terrain differences are
retained in the report.

All eight real boss species reached the original big-enemy death entity
`$64` after recorded sword/beam damage: Rokusutahn `$11`, Ripasheiku `$2d`,
Zoradohna `$2e`, Borabohra `$2f`, Pakukame `$30`, Zorugeriru `$31`, King Grieve
`$32` and Shadow Eura `$33`. Native and interpreter states matched and the
player remained alive. Initial HP is recorded for each fixture; some source
encounters already contained prior native damage.

## Assistance and limits

Screen loaders, temporary player protection, HP/MP refills, teleports and
granted native equipment/items were used to reach the mechanics efficiently.
No boss HP, actor AI, victory flags or stage-success flags were changed to
obtain a claimed defeat or transition. Entrance prerequisites were bypassed
for isolated combat and room coverage. Guard/Shield/Reflect consequence tests
grant their spell effect as an explicit fixture prerequisite; normal spell
selection/casting is covered separately by the integration campaign.

The complete quest route, every door/alternate route and every item/enemy
combination remain unverified. A room load, matching backends or a screenshot
alone does not establish that room's complete mechanics. The traversal pass
is a short collision/movement regression probe, with scripted ownership and
natural transitions recorded. The assisted ending check begins with the
final boss encounter. Netplay, rollback qualification, non-USA ROMs and the
legacy host are outside this release's supported profile.

## Reproduction and retained evidence

The portable source-ROM oracle and post-intro integration commands are in
[the mod guide](LINK_MOD.md#validation). The local assisted campaigns retain
their fixture journals, original source hashes, exact command lines, input
schedules, RAM snapshots, controller CSVs, logs and PNGs under:

- `campaign-v3/screens.json`, `campaign-v3/geometry.json`
- `traversal/report.json`
- `campaign-v2/combat.json`, supplemented by `campaign-v3/combat.json` for
  Zoradohna and `ending-boss/combat.json` for the final-build Shadow Eura replay
- `interactions/report.json`, `followthrough-v2/report.json`
- `ability-qa/report.json`, `guard-effects-v2/report.json`, `upscroll/report.json`
- `integration-delivery/report.json`, `window-qa/report.json`, `audio-qa/report.json`
- `release-audit.json` for archive hashes and the complete PE import closure;
  the window report records the three bundled runtime DLLs actually loaded
- `pictures/` for the native ending checkpoints

Exploratory failed probes are retained too. The early horizontal probes used
unsupported airborne entrances; source-derived supported exits passed.
An old Zoradohna checkpoint was waiting in an Elixir dialogue; a fresh native
room entry passed. Potion and retry checks advance native dialogue with A.
The final potion snapshots show HP 56, 72, 80, 80 during actual healing.
An early downstab fixture intersected ceiling terrain; the clear floor-level
encounter records both native hits and bounce. Older disposable mod snapshots
were rejected after the death-state layout change and reseeded from their
preserved native RAM for the current-build traversal.
