MEMORY_NS = 100
FAULT_S = 8e-3
FAULT_NS = FAULT_S * 1e9

print("Assumption: fault service time includes page transfer and restart; replace value if restart is separate.")
for rate in (1/1000, 1/100000, 1/1000000):
    eat_ns = (1-rate)*MEMORY_NS + rate*FAULT_NS
    print(f"fault_rate={rate:.9g}  EAT={eat_ns:.3f} ns")

# Solve exact 10 percent slowdown on memory access time:
target_ns = 110
rate = (target_ns - MEMORY_NS) / (FAULT_NS - MEMORY_NS)
print(f"10_percent_slowdown_fault_rate={rate:.12g}")
