for i in `ls -a`; do
	if [ -f $i ]; then 
		if [ ${i##*.} != "cpp" -a $i != "clean.sh" ]; then
			rm $i
		fi
	fi
done
