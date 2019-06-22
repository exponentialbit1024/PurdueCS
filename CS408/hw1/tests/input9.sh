cd ..

python3 nnc.py

if [ ! -f output.txt ]; then
    echo "NO OUTPUT FILE"
fi
