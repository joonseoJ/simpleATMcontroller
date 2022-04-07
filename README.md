# simpleATMcontroller

## What is this project?
This is a simple ATM
You can insert card, enter pin number and choose account by console.
After you choose account, you can see balance, deposit or withdraw money or choose other account by console.
Currently, it's not integrated with bank api, pin number will be always correct as long as it's four-digit number.
For security reason, If you enter too many invalid inputs, program will be terminated.

## How to compile project?
You need <b>g++</b>, <b>make</b> to compile source code.

    git clone $(this main branch url)
    cd simpleATMcontroller
    mkdir obj
    make
After this process, you can see <b>main.exe</b> or <b>main</b> at the "simpleATMcontroller" folder

## How to run project?
    .\main.exe or ./main

## Flow of the project
![image](https://user-images.githubusercontent.com/102952766/162131033-8c96c0ee-6930-4148-8750-dca1ddbecb42.png)
