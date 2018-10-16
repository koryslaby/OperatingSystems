import os
import random

for i in range(0, 5):
	num_page_touch = str(random.randint(0,2000))
	print("==================== runing test", i, "===================")
	pid = os.fork()
	if( pid == 0):
		print("number of pages touched", num_page_touch)
		num_of_trials = "5"
		arguments = [" ", num_page_touch, num_of_trials]		
		os.execv("./tlb.exe", arguments)
		os.wait()
	else:
		os.wait()