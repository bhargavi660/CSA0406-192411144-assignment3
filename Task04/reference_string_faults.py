import csv

reference = [7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1]
with open("results/reference_faults.csv", "w", newline="", encoding="utf-8") as f:
    w = csv.writer(f)
    w.writerow(["frames", "faults"])
    for frames in range(1, 8):
        resident = []
        faults = 0
        for page in reference:
            if page not in resident:
                faults += 1
                if len(resident) >= frames:
                    resident.pop(0)
                resident.append(page)
        w.writerow([frames, faults])
