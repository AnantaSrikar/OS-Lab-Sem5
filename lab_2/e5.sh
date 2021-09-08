read -p "Enter a number: " num

# While loop. Good old i for interating
i=2
while [ $i -le $(($num - 1)) ]
do
	if [ $(($num % $i)) -eq 0 ]
	then
		echo "$num is not prime!"
		exit
	fi
((i++))
done

echo "$num is prime!"