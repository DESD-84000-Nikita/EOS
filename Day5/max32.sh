#!/bin/bash

echo -n "Enter the first no:"
read num1
echo -n "Enter the second no:"
read num2
echo -n "Enter the third no:"
read num3
if [ $num1 -gt $num2 -a $num1 -gt $num3 ]
then
	echo "num1 is greater"
elif [ $num2 -gt $num1 -a $num2 -gt $num3 ]
then
	echo "num2 is greater"
	
else
    echo "num3 is greater"
fi
