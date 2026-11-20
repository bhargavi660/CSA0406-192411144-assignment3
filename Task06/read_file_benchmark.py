import argparse, os, time

p = argparse.ArgumentParser()
p.add_argument("file", help="explicit regular file to read")
p.add_argument("--mi-b", type=int, default=64)
args = p.parse_args()
if not os.path.isfile(args.file):
    raise SystemExit("not a regular file")
length = args.mi_b * 1024 * 1024
start = time.monotonic()
with open(args.file,"rb",buffering=0) as f:
    remaining=length
    while remaining:
        data=f.read(min(1024*1024,remaining))
        if not data: break
        remaining -= len(data)
elapsed=time.monotonic()-start
print(f"bytes_read={length-remaining} elapsed_s={elapsed:.6f}")
