TB = 4
disks = 6
print("RAID0 capacity=%.1f TB usable" % (disks*TB))
print("RAID1 minimum2; capacity=%.1f TB usable" % TB)
print("RAID5 minimum3; capacity=%.1f TB usable" % ((disks-1)*TB))
print("RAID10 minimum4; capacity=%.1f TB usable" % ((disks//2)*TB))
print("RAID6 minimum4; capacity=%.1f TB usable" % ((disks-2)*TB))
