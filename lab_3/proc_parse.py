"""
	/proc parser in Linux

	Author: Srikar
"""

import os
import sys
from time import sleep

def print_vals(val_sums, sample_space):

	time_sum = val_sums['user_time'] + val_sums['system_time'] + val_sums['idle_time']

	print(f"Time spent by CPU:\nUser: {(val_sums['user_time'] / time_sum) * 100}%")
	print(f"System: {(val_sums['system_time'] / time_sum) * 100}%")
	print(f"Idle: {(val_sums['idle_time'] / time_sum) * 100}%")

	print(f"Context switches: {val_sums['cs'] / sample_space}")
	print(f"Processes created: {val_sums['process'] / sample_space}")

	print(f"Amount of free mem = {val_sums['avail_mem'] / (1024 * 1024 * sample_space)} GB")
	print(f"Free memory = {(val_sums['avail_mem'] / (val_sums['total_mem'] * sample_space)) * 100} %")

	print(f"Sectors Read: {val_sums['sec_read'] / sample_space}")
	print(f"Sectors Written: {val_sums['sec_written'] / sample_space}")



def reset_vals(val_sums):
	for i in val_sums.keys():
		val_sums[i] = 0


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

		time = 0

		val_sums = {}

		sample_space = printout_rate / read_rate

		while(True):

			time += read_rate

			if(time == printout_rate):
				
				os.system("clear")
				print(f"Read rate: {read_rate} \t\t\t printout rate: {printout_rate}\n")
				
				time = 0

				print_vals(val_sums, sample_space)
				reset_vals(val_sums)

			# Processor times
			with open('stat') as inFPtr:
				stat_vals = inFPtr.readlines()

				try:
					val_sums['user_time'] += int(stat_vals[0].split(" ")[2])
				except:
					val_sums['user_time'] = int(stat_vals[0].split(" ")[2])

				try:
					val_sums['system_time'] += int(stat_vals[0].split(" ")[4])
				except:
					val_sums['system_time'] = int(stat_vals[0].split(" ")[4])

				try:
					val_sums['idle_time'] += int(stat_vals[0].split(" ")[5])
				except:
					val_sums['idle_time'] = int(stat_vals[0].split(" ")[5])

				# Context switches
				try:
					val_sums['cs'] += int(stat_vals[-6].split(" ")[-1]) - val_sums['prev_cs']
					val_sums['prev_cs'] = int(stat_vals[-6].split(" ")[-1])
				except:
					val_sums['cs'] = 0
					val_sums['prev_cs'] = int(stat_vals[-6].split(" ")[-1])

				# Processes created
				try:
					val_sums['process'] += int(stat_vals[-4].split(" ")[-1]) - val_sums['prev_process']
					val_sums['prev_process'] = int(stat_vals[-4].split(" ")[-1])
				except:
					val_sums['process'] = 0
					val_sums['prev_process'] = int(stat_vals[-4].split(" ")[-1])

			# Free memory
			with open('meminfo', 'r') as inFPtr:
				mem_info = inFPtr.readlines()
				
				avail_mem = int(mem_info[2].split(" ")[-2])
				total_mem = int(mem_info[0].split(" ")[-2])

				try:
					val_sums['avail_mem'] += avail_mem
				except:
					val_sums['avail_mem'] = avail_mem

				try:
					val_sums['total_mem'] += total_mem
				except:
					val_sums['total_mem'] = total_mem
			
			# Disk I/O
			with open('diskstats', 'r') as inFPtr:
				disk_info = inFPtr.readlines()[0].split(" ")

				sec_read = int(disk_info[12])
				sec_written = int(disk_info[16])

				try:
					val_sums['sec_read'] += sec_read - val_sums['prev_read']
					val_sums['prev_read'] = sec_read
				except:
					val_sums['sec_read'] = 0
					val_sums['prev_read'] = sec_read
				
				try:
					val_sums['sec_written'] += sec_written - val_sums['prev_written']
					val_sums['prev_written'] = sec_written
				except:
					val_sums['sec_written'] = 0
					val_sums['prev_written'] = sec_written
				
			sleep(read_rate)
		

	except ValueError:
		print("Incorrect values entered for rates. Check and try again.")

	except Exception as e:
		print(f"Something went wrong: {e}")