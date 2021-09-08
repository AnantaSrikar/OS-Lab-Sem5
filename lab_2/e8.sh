read -p "Enter file-1 name: " file1
read -p "Enter file-2 name: " file2

while read line1
do
	isFound=0

	while read line2
	do
		if [ "$line1" = "$line2" ]
		then
			isFound=1
			break
		fi
	done < $file2
	
	if [ $isFound -ne 1 ]
	then
		echo "$file1 and $file2 are not the same!"
		exit
	fi

done < $file1

echo "$file1 and $file2 are the same!"