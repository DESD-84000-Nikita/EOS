    #!/bin/bash

	echo -n "Enter year : " 
    read year 
      
    rem=` expr $year % 4` 
    rem1=` expr $year % 100`
	rem2=` expr $year % 400`

    if [  $rem  -eq 0 -a $rem1 -ne 0 -o $rem2 -eq 0 ] 
    then 
      echo "$year is leap year" 
    else 
      echo "$year is not a leap year"
    fi 
