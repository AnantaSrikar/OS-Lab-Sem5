read -p "Enter 1st num: " num1

read -p "Enter 2nd num: " num2

# Swap them
num1=$(($num1 + $num2))
num2=$(($num1 - $num2))
num1=$(($num1 - $num2))


echo "After swap"
echo "1st num: $num1"
echo "2nd num: $num2"