echo "Building project..."

if pros build-compile-commands 
then
	echo "Build complete."
else
	echo "Something went wrong."
fi

