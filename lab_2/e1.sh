read -p "Enter the radius: " radius
area=$(echo "3.14 * $radius * $radius" | bc)
cimf=$(echo "2 * 3.14 * $radius" | bc)
echo "Area of the Circle is $area"
echo "Circumference of the circle is $cimf"