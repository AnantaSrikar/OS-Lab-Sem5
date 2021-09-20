import os
import sys

os.chdir('/proc')

argc = len(sys.argv)

if(argc != 1 and argc != 3):
	print("Incorrect numbers of arguments of entered")


if(argc == 1):
	# Processor type
	with open('cpuinfo', 'r') as inFPtr:
		print("CPU:" + inFPtr.readlines()[4].split(":")[-1][:-1])

	# Kernel version
	with open('version', 'r') as inFPtr:
		print("Kernel version: " + inFPtr.readline().split(' ')[2])

	# Memory configured
	with open('meminfo', 'r') as inFPtr:
		mem_kb = int(inFPtr.readline().split(' ')[7])
		mem_gb = mem_kb / (1024 * 1024)
		print(f"Memory configured: {mem_gb} GB")

	# System uptime
	with open('uptime', 'r') as inFPtr:
		up_sec = int(inFPtr.readline().split(' ')[0][:-3])
		
		up_min = int(up_sec / 60)
		up_min %= 60

		up_hour = int(up_sec / 3600)
		up_sec %= 60

		print(f"Uptime: {up_hour}:{up_min}:{up_sec}")

elif(argc == 3):
	try:
		read_rate = int(sys.argv[1])
		printout_rate = int(sys.argv[2])

		print(f"Read rate: {read_rate} \t\t\t printout rate: {printout_rate}")

		# Processor times
		with open('stat') as inFPtr:
			stat_vals = inFPtr.readlines()
			
			print("User: " + stat_vals[0].split(" ")[2])
			print("System: " + stat_vals[0].split(" ")[4])
			print("Idle: " + stat_vals[0].split(" ")[5])

			print("Context Switches: " + stat_vals[-6].split(" ")[-1])
			print("Process creation: " + stat_vals[-4].split(" ")[-1])

		# Free memory
		with open('meminfo', 'r') as inFPtr:
			mem_info = inFPtr.readlines()
			
			avail_mem = int(mem_info[2].split(" ")[-2])
			total_mem = int(mem_info[0].split(" ")[-2])

			print(f"Free memory = {(avail_mem / total_mem) * 100} %")
		
		# Disk I/O
		with open('diskstats', 'r') as inFPtr:
			disk_info = inFPtr.readlines()

			print(disk_info)
		

	except ValueError:
		print("Incorrect values entered for rates. Check and try again.")

	except Exception as e:
		print(f"Something went wrong: {e}")