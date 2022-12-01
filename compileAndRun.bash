# You can choose other image son https://www.vexforum.com/t/a-guide-to-changing-program-icons/78293/8



if ! pros build-compile-commands
then
	exit 1
fi


if ! pros upload 
then
	exit 1
fi

sleep 4s


pros terminal
