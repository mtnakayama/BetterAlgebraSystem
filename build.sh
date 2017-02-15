cmake .
make
if [ $? -eq 0 ]; then
    make test-verbose
fi
