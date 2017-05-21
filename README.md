# Snake <img src="https://images.vexels.com/media/users/3/128762/isolated/preview/1bd09b39b8034b31e0592733f8219f7d-snake-cartoon-circle-icon-by-vexels.png" width="100px" height="100px" > 

#### Simple snake game written in C for the Altera DE0-CV FPGA


### Download
```bash
cd ~
git clone https://github.com/alexanderepstein/Snake
```

### Flash
* First make sure to have the altera monitor program installed with quartus lite 16.0 and the correct board drivers
* Open up the altera monitor program and start a new project
* Designate that the project is written in C
* Add all the files to the compiler
* Give the Altera DE0-CV resets and exceptions
* Download the DE0-CV Computer System onto the board
* Compile and load the program onto the board 
* Press play to start

### Controls
##### The keys are what designate the direction of the snake
* Key3 = Up
* Key2 = Down
* Key1 = Left
* Key0 = Right
##### Collect food to attain the highest score, follow onscreen instructions to start/replay the game
