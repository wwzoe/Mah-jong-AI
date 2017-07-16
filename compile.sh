cd client
swig -python -lcpointer.i -lcarrays.i client.i
python3 setup.py build_ext --inplace
mv _client.cpython-35m-x86_64-linux-gnu.so _client.so
cd ..
