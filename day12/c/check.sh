i=1
while true; do
	./gen;./c;./c1
	if diff c.out c1.out; then
		echo $i
	else
		echo WA
		exit 0
	fi
	i=$(($i+1))
done