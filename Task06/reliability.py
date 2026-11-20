from math import comb

p = float(input("Per-drive failure probability over interval (0 to 1): "))
n = 6
# RAID1 with n=2 mirrors
raid1_failure = p*p
# RAID5: array fails if 2 or more drives fail
raid5_failure = sum(comb(n,k)*(p**k)*((1-p)**(n-k)) for k in range(2,n+1))
print("RAID1 two-drive mirror array failure probability:", raid1_failure)
print("RAID5 with six disks failure probability:", raid5_failure)
print("Simplifying assumptions: independent, identical failures; no rebuild-window wear or correlated failures.")
