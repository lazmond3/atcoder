

import sys

n = int(sys.argv[1])
m = int(sys.argv[2])

target_str = str(1/m)[2:][:n]
target = int(target_str)

print(target)
print("answer: " , target % m)

