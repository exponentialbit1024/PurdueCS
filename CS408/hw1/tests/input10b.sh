cd ..

python3 nnc.py tests/input8.txt
if [ "$(cat output.txt)" = "INVALID INPUT" ]; then
  echo "TEST PASSED"
else
  echo "TEST FAILED"
fi
