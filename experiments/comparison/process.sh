for f in *.avi
do
	echo "Processing $f..."
	./optical-flow -f $f
done
