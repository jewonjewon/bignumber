#1 bin/sh

# cd /Users/jewon/Documents/GitHub/bignumber/build
# cmake ..
make 

# 검증 수행
cd /Users/jewon/Documents/GitHub/bignumber/build
./main > add_1.py
python3 add_1.py

#rm add_1.py