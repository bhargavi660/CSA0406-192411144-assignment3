import csv, random

random.seed(0x05062026)
with open("results/workloads.csv","w",newline="",encoding="utf-8") as f:
    w=csv.writer(f);w.writerow(["workload","seed","reference","index"])
    strong=[random.choice(range(8)) if random.random()<0.8 else random.randrange(64) for _ in range(10000)]
    random_refs=[random.randrange(64) for _ in range(10000)]
    w.writerow(["strong_locality","845695542","",""])
    for i,p in enumerate(strong):w.writerow(["strong_locality","845695542",p,i])
    w.writerow(["random","845695542","",""])
    for i,p in enumerate(random_refs):w.writerow(["random","845695542",p,i])
