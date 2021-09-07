echo -n "Enter 1st num: "
read num1

echo -n "Enter 2nd num: "
read num2

# Swap them
num1=$(($num1 + $num2))
num2=$(($num1 - $num2))
num1=$(($num1 - $num2))


echo "After swap"
echo "1st num: $num1"
echo "2nd num: $num2"