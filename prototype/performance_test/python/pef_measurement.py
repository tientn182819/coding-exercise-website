import os, psutil
import time
import resource

# The getpid function only take 0 arg
process = psutil.Process(os.getpid())
print(process)
# time.sleep(5)
print(process.memory_info().rss / 1024 ** 2) 

# Below function return kilobyte
print(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1024)

process_names = [proc.name() for proc in psutil.process_iter()]
# print(process_names)