# Play as Link

This optional mod replaces Faxanadu's player with Zelda II Link on the USA
cycle build. Enable **Play as Link** in Mods and select your **Zelda II: The
Adventure of Link (USA)** ROM. Restart gameplay after changing the mod selection.
The package is installed but disabled by default.

The release includes `Play-as-Link.nesmod` for installing the same package in
another compatible FaxanaduRecomp build. Its gameplay plugin is compiled into
this game; the package contains its manifest and instructions. It contains no
ROM, graphics, audio samples or executable code. The runtime verifies the
owner's Zelda II ROM before reading its graphics, display tables and sound
parameters. Both original ROMs stay on the player's computer.

## Controls

| Input | Action |
|---|---|
| Left / Right | Move with Zelda II acceleration and momentum |
| A | Jump; hold to control jump height |
| B | Sword; full-health swings also fire a sword beam |
| Down | Crouch; Down+B swings while crouched |
| Up / Down while airborne | Upstab while rising / downstab |
| Select | Open or close the spell picker |
| D-pad, A, B in picker | Choose, confirm, cancel |
| Up+B | Cast the selected spell |
| Start | Native Faxanadu inventory; B closes it |
| Down+Start | Use the selected native item |
| C / V on keyboard | Cast / spell picker shortcuts |

The default NES keyboard bindings are Z=A, X=B, Enter=Start and
Backslash=Select. Native dialogue still uses A to advance. Normal button
remapping applies. The optional C/V shortcuts are SDL scancodes in `config.ini`:

```ini
[Game]
LinkCastKey = 6
LinkPickerKey = 25
```

Set either shortcut to `0` to disable it. The picker pauses the world and
consumes its confirmation input. Casting with Up+B consumes that chord so
it cannot also open a door or start a sword swing.

## Abilities and progression

All moves and eight spells are available immediately. Faxanadu still supplies
health, magic, equipment, money, experience, shops, items, quest requirements,
boss defeats and mantra progress. Starting HP/MP follow Faxanadu's normal
rules; unlocking a spell does not grant the MP to cast it. Native in-game
progress does not acquire a dependency on a Link-specific save format.

| Spell | MP | Adaptation |
|---|---:|---|
| Shield | 10 | Halves native HP damage, with normal armor still applied |
| Jump | 5 | Uses Zelda II's higher jump trajectories |
| Life | 32 | Restores 15 of Faxanadu's 80 HP |
| Fairy | 25 | Small body and 1.5-pixel flight in either axis |
| Fire | 10 | Swings fire a projectile at any health |
| Reflect | 10 | Guarded native projectiles return as magic projectiles |
| Spell | 10 | Eligible ordinary enemies become harmless, stationary fairies |
| Thunder | 40 | Hits eligible live enemies through native Tilte damage/defense |

MP costs are the original level-eight costs scaled to Faxanadu's 80 MP and
rounded up. Shield, Jump, Fairy, Fire, Reflect and transformed enemies expire
when the room changes. Life and Thunder act once. Fairy expiry is deferred
until Link's ordinary body fits, so a narrow exit cannot embed him in terrain.
Spell excludes bosses and preserves each target's native identity and HP;
attacking a transformed enemy restores its normal behavior. Thunder retains
native magic defenses and defeat scripts.

The shield works automatically while facing a projectile and not attacking.
Native shield upgrades widen its guard coverage. A successful guard blocks
the projectile completely, as Link does; Faxanadu shield chip damage is not
used. Crouch reduces the hurtbox but retains a full-height terrain body;
Zelda II's stationary crouch must not crawl into an inescapable passage.

Physical hits, including beams, use Faxanadu's selected weapon and original
equipment modifiers, XP and defeat routines. Link has a basic sword even when
Faxanadu has no weapon equipped. Downstab contact bounces with the original
integer velocity of -2 and preserves the gravity fraction. Native ladders,
doors, scripted movement, knockback, death/retry and the ending retain control
when required. A jumps away from a ladder.

This first profile supports **Faxanadu USA, CRC32 `57dd23d1`** and the canonical
Zelda II USA payload, SHA-1 `11333adb723a5975e0ecca3aee8f4747aa8d2d26`.
The legacy CPU host does not include this mod. Link sessions are local-only
until rollback/netplay qualification is completed.

The Windows release recipe also stages the three required x64 Visual C++
runtime DLLs from the configured compiler's licensed redistributable directory.
`tools/make_release.ps1 -RedistDir <Microsoft.VC143.CRT>` can supply that
directory explicitly when the build machine uses a custom toolchain layout.

## Implementation

`mods/zelda2/link_controller.c` is an independent `ForeignController`. It has
no Faxanadu RAM addresses or world logic. Horizontal movement uses the
original signed 4.4 speed, maximum 1.5 pixels per tick. Vertical displacement
uses the original signed integer velocity plus a separate gravity accumulator.
It also owns the source walking/slash phases, vertical blades and projectile
timing. It advances once per emulated gameplay tick, never by wall-clock time.

`fax_link.c` adapts those requests to native metatiles, collision, actors and
scripts through 19 content-keyed mod hooks. RAM-only native helpers run in
isolated committed calls. Device/mapper-writing transitions are scheduled as
ordinary native tail calls through the hook's handled-RTS contract. The PRG
image is never patched. A room change clears local effects and reseeds from
native position. The adapter serializes controller, collision, projectile,
input, picker and frozen-picture state in its own validated mod record.
Malformed or incompatible records are rejected before application; older
save-state compatibility is not a contract. Native mantra saves are separate.

`link_assets.c` reads the owner's ROM after identity validation. It renders
source body/weapon/projectile/Fairy tiles over the native scene, respects
foreground masking and invulnerability visibility, and follows the native
death dissolve phase. Sword and beam cues are synthesized from source sound
parameters through the mod audio mixer; world music and sound remain native.
Spell cues reuse the beam cue rather than importing a second music engine.

The Faxanadu profile uses symbols from `chipx86/faxanadu`. The complete
reference rebuild was compared byte-for-byte with all 16 USA PRG banks.
Zelda II movement and display references come from the local `z2disassembly`
and are checked against executed original 6502 routines. No reference ROM or
extracted asset belongs in a commit or release archive.

## Validation

Run the owner-ROM controller oracle:

```powershell
cmake -S tests/link -B build-link-tests -DNESRECOMP_ROOT=<cycle-engine>
cmake --build build-link-tests --config Release
./build-link-tests/Release/link_controller_test.exe <zelda2-usa-rom>
python tools/verify_link_profile.py --rom <faxanadu-usa-rom>
```

The integration campaign takes a stock post-intro cycle checkpoint and creates
journaled HP/MP fixtures in the requested output directory:

```powershell
python tests/link/integration.py --exe <FaxanaduRecomp.exe> `
  --faxanadu-rom <faxanadu-usa-rom> --zelda2-rom <zelda2-usa-rom> `
  --baseline-state <stock-post-intro.cycstate> --out <F-or-G-output-directory>
```

It tests all eight spells, MP/healing, native/interpreter complete-state,
machine-trace and presentation agreement, picker and active-state continuation,
disabled/stock agreement, invalid records and incorrect owner-ROM gating.
The source oracle executes walking, randomized animation, jump, sword and
downstab-bounce routines from the actual Zelda II ROM.

See [Link QA](LINK_QA.md) for the assisted world/combat campaign and its limits.
