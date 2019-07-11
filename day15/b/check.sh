i=1
while true; do
	./gen;./b2;./b
	if diff b.out b2.out; then
		echo $i
	else
		exit 0
	fi
	i=$(($i+1))
done