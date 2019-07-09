i=1
while true; do
	./gen;./b1;./b
	if diff b.out b1.out; then
		echo $i
	else
		exit 0
	fi
	i=$(($i+1))
done