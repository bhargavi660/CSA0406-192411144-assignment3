import csv

import csv
import random

def fault_count(refs, frames, policy):
    resident = []
    last_use = {}
    clock_ref = {}
    hand = 0
    faults = 0
    for i, page in enumerate(refs):
        if page in resident:
            last_use[page] = i
            if policy == "CLOCK":
                clock_ref[page] = 1
            continue
        faults += 1
        if len(resident) < frames:
            resident.append(page)
        elif policy == "FIFO":
            resident.pop(0)
            resident.append(page)
        elif policy == "LRU":
            victim = min(resident, key=lambda p: last_use[p])
            resident.remove(victim)
            resident.append(page)
        elif policy == "OPTIMAL":
            farthest = -1
            victim = resident[0]
            for p in resident:
                try:
                    next_use = refs.index(p, i + 1)
                except ValueError:
                    next_use = len(refs)
                if next_use > farthest:
                    farthest = next_use
                    victim = p
            resident.remove(victim)
            resident.append(page)
        else:
            while clock_ref.get(resident[hand], 0):
                clock_ref[resident[hand]] = 0
                hand = (hand + 1) % frames
            resident[hand] = page
            clock_ref[page] = 1
            hand = (hand + 1) % frames
        last_use[page] = i
        clock_ref[page] = 1
    return faults

random.seed(0x05062026)
strong = [random.choice(range(8)) if random.random() < 0.8 else random.randrange(64) for _ in range(10000)]
random_refs = [random.randrange(64) for _ in range(10000)]
with open("results/evaluation.csv", "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f)
    w.writerow(["policy", "workload", "frames", "faults"])
    for workload_name, refs in (("strong_locality", strong), ("random", random_refs)):
        for policy in ("FIFO", "LRU", "OPTIMAL", "CLOCK"):
            for frames in range(3, 11):
                w.writerow([policy, workload_name, frames, fault_count(refs, frames, policy)])
