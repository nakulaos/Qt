echo "rm all files of directory..."
cd bin
rm -rf *
cd ../build
rm -rf *
echo "generate makefile.txt..."
cmake ..
echo "generate exe..."
cmake --build .
cd ../bin
echo "execute exe..."
./ChineseChess