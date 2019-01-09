# nuaactf 2018 misc

## 1. fs 75pt

### 题目描述

filesystem

```
md5 ./1-fs/fs
MD5 (./1-fs/fs) = 0faf259ebb22650cda05a551c3215f8e
```

### hint

apfs

### flag

```
nuaactf{fs_level0}
```

### 解题思路

apfs

dmg末尾给了12位的密码`Xmas3?theme3`

直接打开dmg得到flag.txt

## 2. rev 100pt

### 题目描述

reverse

```
md5 ./2-rev/rev
MD5 (./2-rev/rev) = 73eb4bb24577589ea27621a9dc8f5a6f
```

### hint

pyc

### flag

```
nuaactf{py_uncompyle}
```

### 解题思路

pyc

```python
with open('rev', 'rb') as f1:
    with open('genflag', 'wb') as f2:
        f2.write(f1.read()[::-1])
```

得到genflag后，modu1e需要改为module

用uncompyle6

```
uncompyle6 -o . genflag
```

参考enc写dec

```python
def enc():
    flag = r'To make it more difficult to calculate the flag by hand, nuaactf{py_uncompyle}, flag is for scripts'
    [print('{:x}'.format(ord(each)+0x32), end='l') for each in flag]
    print()
def dec():
    enc_flag = '86la1l52l9fl93l9dl97l52l9bla6l52l9fla1la4l97l52l96l9bl98l98l9bl95la7l9ela6l52la6la1l52l95l93l9el95la7l9el93la6l97l52la6l9al97l52l98l9el93l99l52l94labl52l9al93la0l96l5el52la0la7l93l93l95la6l98ladla2labl91la7la0l95la1l9fla2labl9el97lafl5el52l98l9el93l99l52l9bla5l52l98la1la4l52la5l95la4l9bla2la6la5l'
    enc_flag = enc_flag[:-1].split('l')
    for each in enc_flag:
        print(chr(int(each, 16)-0x32), end='')
    print()
enc()
dec()
```

得到flag

## 3. plot 125pt

### 题目描述

plot it

```
md5 ./3-plot/plot
MD5 (./3-plot/plot) = f0122a4c37c1b0958a35dc0cbae1cffe
```

### hint

g-code

### flag

```
nuaactf{gcode_plot}
```

### 解题思路

g-code plot

https://ncviewer.com/