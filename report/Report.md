# Operating Systems Assignment 3

**Name:** `[STUDENT NAME TO FILL]`  
**Register Number:** `192411144`

## Machine-specific evidence

`GCC 15.2.0, Ubuntu 26.04 LTS, WSL2 kernel 6.18.33.2-microsoft-standard-WSL2 were collected. CPU model, physical memory, and machine-specific page-fault counts not claimed until captured locally.`

Actual WSL evidence includes the page-table translator tests, 64 MiB random access report
(16,385 minor faults in 1,000,000 accesses), page-replacement outputs, and the edge-device
latency run. These are measurements from this environment, not guarantees for other machines.

## Q1 — Linking, Loading and Address Binding

The implementation uses a harmless demo-transform library. Static and dynamic variants, `dlopen`, `/proc/self/maps`, library replacement, and missing-library handling are included. Compile-time binding fixes addresses before execution; load-time linking resolves shared-library locations with relocation; execution-time binding includes runtime addresses, heap allocation and dynamic loading. The linker combines objects and symbols, while the loader maps segments and applies relocations. A bank should normally prefer dynamic linking for security fixes and disk/physical-page sharing, but static linking is useful for isolated deployments where library availability is restricted. Static binaries often start with fewer loader lookups, but updates require rebuilding.

## Q2 — Paging

The page-table translator checks segment bounds and reports page offset and frame number. Page-table sizing assumes 8-byte PTEs: 32-bit, 4-KB pages has 1,048,576 entries and 8 MiB for a single full flat table; 48-bit has 67,108,864 entries per 9-bit level at 4-KB granularity and practical multilevel tables allocate only used branches. Effective access time depends on TLB hit and miss latencies and page-fault treatment.

**External fragmentation diagram**

```text
Memory: [hole 64][used][hole 32][used][hole 128]
Total free=224 KB, but no contiguous run may satisfy a 160 KB request.
```

## Q3 — Segmentation

Segments represent logical regions: code, data and stack. Base+offset is translated only when the offset is at or below the limit. Segment protection is per segment and sharing is explicit. Pure paging avoids external fragmentation but has internal fragmentation; pure segmentation has external fragmentation and protection flexibility; combined segmentation/paging retains segment access control while paging controls allocation.

x86 conceptual diagram:

```text
logical address -> segment selector -> descriptor table -> segment base
               -> segment base + offset -> linear address
               -> page directory -> page table -> physical address
```

Modern 64-bit Linux generally uses a flat selector model with paging; the diagram is conceptual and does not describe the exact Windows/Linux 64-bit implementation.

## Q4 — Virtual Memory and Demand Paging

Page-fault service time is included or excluded by the stated model; here the example calculator allows both. At 100 ns memory access and 8 ms fault service:

\[
EAT = (1-p)(100 ns) + p(8 ms)
\]

The 24 GB workload/16 GB RAM claim is conditional on working-set locality and backing storage. A 10% slowdown relative to 100 ns:

\[
EAT = 110 ns
\]

This yields an extremely small fault rate in the supplied calculator. COW fork measurements remain noisy.

## Q5 — Page Replacement

The supplied FIFO, LRU, Optimal and Clock implementations provide measured fault counts and complexity. Belady's anomaly is workload and frame-count dependent. LRU has the stack property for demand-paging inclusion, so a superset of frames contains at least the smaller frame's resident set. Exact LRU updates metadata per reference and can be hardware-costly. Clock approximates LRU with reference bits and a circular hand.

## Q6 — Disk Management

Low-level formatting prepares tracks/sectors, partitioning divides a disk, and logical formatting creates a filesystem. The boot block stores the initial loader and boot firmware or bootloader locates the OS. RAID recommendations emphasize validated backups as the primary recovery mechanism. For six 4 TB drives, RAID 6 has 16 TB decimal capacity and can tolerate two concurrent or sequentially detected member failures while rebuilding.

## Q7 — Smart-Factory Edge Device

The 2 GB device should reserve 512 MB for OS/overhead, leaving 1536 MB for applications. A 1.5 GB ML working set plus control and logging may not fit and requires an explicit tradeoff or larger ML split. Locking should protect the control task only; ordinary Linux is not a hard-real-time guarantee. RTOS/no-VM designs can provide simpler bounded behavior but require more engineering to add memory isolation and tasks.

**Comparison and worked answers are expanded in the task files and scripts.**
