# brunslipy

Work-in-progress repo for python binding of https://github.com/google/brunsli

## brunslipy

Python binding for `EncodeBrunsli()` and `DecodeBrunsli()`.

#### Install

```
apt-get install git gcc g++ make cmake
# or
yum install git gcc gcc-c++ make cmake

git clone https://github.com/moonsikpark/brunslipy.git
cd brunslipy
make brunsli
cd src/bindings
python3 setup.py install
```

#### Usage

```
# python3.8
Python 3.8.0 (default, Dec  1 2019, 17:12:33) 
[GCC 8.3.1 20190311 (Red Hat 8.3.1-3)] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import brunsli
>>> with open('in.jpg', 'rb') as f:
...     in_file = f.read()
... 
>>> len(in_file)
96145
>>> out_file = brunsli.encode(in_file)
>>> orig_file = brunsli.decode(out_file)
>>> in_file == orig_file
True
>>> with open('out.brn', 'wb') as f:
...     f.write(out_file)
... 
78671
```

## brunsli_wrapper

Wrapper for `EncodeBrunsli()` and `DecodeBrunsli()`.

#### Install

```
apt-get install git gcc g++ make cmake
# or
yum install git gcc gcc-c++ make cmake
git clone https://github.com/moonsikpark/brunslipy.git
cd brunslipy
make
```

#### Usage

```
cd bin
./brunsli_wrapper -e in.jpg out.brn
Convert success! before=96145 after=78671 81.83%

./brunsli_wrapper -d out.brn in.jpg
Convert success! before=78671 after=96145 122.21%
```