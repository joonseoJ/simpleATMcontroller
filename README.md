# simpleATMcontroller

## What is this project?
This is a simple ATM
You can insert card, enter pin number and choose account by console.
After you choose account, you can see balance, deposit or withdraw money or choose other account by console.
Currently, it's not integrated with bank api, pin number will be always correct as long as it's four-digit number.
For security reason, If you enter too many invalid inputs, program will be terminated.

## Which branch should I choose?
Branch is divided by operating system.

Currently It supports Windows and Linux only. I'm not sure this program won't crash on other OS, like MAC.
* If you are on neither Windows nor Linux, or you don't know what your OS is, choose "main" branch.
* Else if you are on Windows, choose "main" or "window"
* Else if you are on Linux, choose "main" or "linux"

## Trouble shooting
### When "make" command returns error
Object files created from another branch could make error. Erase everything inside 'obj' folder and try again.

### I can't deposit or withdraw money
Unit of the dollar is integer. So decimal or number bigger than 2147483647 is not valid.

## How to compile project?
You need <b>g++</b>, <b>make</b> to compile source code.

    git clone $(this window branch url)
    cd simpleATMcontroller
    mkdir obj
    make
After this process, you can see <b>main.exe</b> at the "simpleATMcontroller" folder

## How to run project?
    .\main.exe

## Flow of the project
![image](https://user-images.githubusercontent.com/102952766/162347801-b3d64e51-38c1-448f-b7dd-c001ba6b92b9.png)

