# Xv6 – Filesystem Snapshot & Restore (Timeshift-like)

## Overview
This project adds a lightweight, Timeshift-style **snapshot & restore** feature to the xv6 filesystem. It saves a point-in-time copy of on-disk blocks into a reserved region and can restore the system to that snapshot later—useful for recovering from accidental deletes or corruption. :contentReference[oaicite:1]{index=1}

---

## Features
- **Block-level snapshots**: copy live data blocks into a reserved disk area.
- **One-command restore**: revert the filesystem to the saved snapshot.
- **User tools**: `snap` (create) and `restore` (restore).
- **Kernel syscalls**: `snapshot_create()` and `snapshot_restore()` exposed to userland. :contentReference[oaicite:2]{index=2}

---

## Modified Files (key changes)
- `kernel/fs.c` – block-level snapshot/restore logic (`snapshot_create_internal`, `snapshot_restore_internal`)
- `kernel/sysfile.c` – syscall wrappers (if not centralized in `sysproc.c`)
- `kernel/sysproc.c` – syscall handlers bridging to internal logic
- `kernel/defs.h` – declarations for snapshot functions
- `kernel/syscall.c` – syscall table entries
- `kernel/syscall.h` – syscall numbers (e.g., `SYS_snapshot_create`, `SYS_snapshot_restore`)
- `user/usys.S` – ecall stubs for the new syscalls
- `user/snap.c` – creates a snapshot
- `user/restore.c` – restores the snapshot
- `user/user.h` – user-space prototypes
- `kernel/param.h` – constants for snapshot region (e.g., `SNAPSHOT_START`, `SNAPSHOT_SIZE`) :contentReference[oaicite:3]{index=3}

---

##  Build & Run

# Bash
```
cd xv6-labs-2024
make clean
make qemu          # or: make qemu-nox
```


# In the xv6 shell:
```
$ echo hello > file1.txt
$ snap            # take a snapshot
$ rm file1.txt
$ restore         # restore to the snapshot
$ cat file1.txt   # -> hello
```

Makefile: ensure these programs are included on the image:
UPROGS += _snap _restore

## Design (high level)
Consistency point: operations run under xv6’s log to keep changes atomic.

Snapshot storage: a fixed on-disk region (SNAPSHOT_START, SNAPSHOT_SIZE) holds copied blocks.

Implementation idea: iterate data blocks during snapshot and copy them into the reserved area; during restore, copy them back into place.

## Testing
Deleting files after a snapshot and running restore brings them back.

Works across multiple files and simple workflows using snap/restore.

## Limitations &  Future Work
Current limitations

Fixed snapshot size/region (tunable in param.h)

Single snapshot region (no multi-snapshot index)

No per-file selective restore

Future improvements

Multi-snapshot support with metadata (IDs, timestamps)

Quotas/configurable snapshot regions

Interactive confirmations before rollback

## Repository Layout
xv6-labs-2024/
```
  kernel/   # fs.c, sysfile.c, sysproc.c, defs.h, syscall.c, syscall.h, param.h, ...
  user/     # snap.c, restore.c, user.h, usys.S, ...
```
## Credits / License
Based on MIT’s xv6 (MIT License). This repository adds snapshot & restore functionality and user utilities on top of the xv6 teaching OS.


