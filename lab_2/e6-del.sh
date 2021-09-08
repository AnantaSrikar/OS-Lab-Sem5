# While loop. Good old i for interating
i=1
while [ $i -le 20 ]
do
	rm file$i.txt
((i++))
done