import csv

MEMORY_NS = 100.0
TLB_NS = 10.0
MISS_NS = 100.0

with open("results/tlb_ratios.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    writer.writerow(["tlb_hit_ratio", "memory_ns", "tlb_ns", "tlb_miss_ns", "eat_ns"])
    for ratio in (0.80, 0.95, 0.99):
        eat = ratio * (TLB_NS + MEMORY_NS) + (1.0 - ratio) * (TLB_NS + MISS_NS + MEMORY_NS)
        writer.writerow([ratio, MEMORY_NS, TLB_NS, MISS_NS, eat])
