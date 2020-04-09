## What is QApplication Intro Slider -
QApplication Intro is a widget which can be used in any Qt project to show a neat little slider to show user an overview of your application.
## Features -
* Light weight and customizable. 
* Slides AutoPlay.
* Navigation key binding (arrow keys by default. can be changed in slider.ui file)
* Slides overview using navigation buttons at bottom of slides.
* Pause autoplay on user's gesture with navigation buttons.
## Screenshot - 
![QApplication Intro Slider](https://github.com/keshavbhatt/QtApplicationInto/blob/master/img/1.png?raw=true)
![QApplication Intro Slider](https://github.com/keshavbhatt/QtApplicationInto/blob/master/img/2.png?raw=true)
## How to use -
You just need to add `icons.qrc` , `slider.cpp`, `slider.h`, `slider.ui`, and `slides.qrc` to your project in order to use the widget.

*Note : copy `icons`  and `slides` directory to root of your project.*

After adding these files project structure will look like this:

    ├── icons.qrc
    ├── icons
    │   ├── app.png
    │   ├── arrow-left-circle-line.png
    │   ├── arrow-right-circle-line.png
    │   ├── play-line.png
    │   └── stop-line.png
    ├── slider.cpp
    ├── slider.h
    ├── slider.ui
    ├── slides
    │   ├── 0.html
    │   ├── 1.html
    │   ├── 2.html
    │   ├── 3.html
    │   ├── 4.html
    │   ├── 5.html
    │   ├── 6.html
    │   ├── 7.html
    │   └── images
    │       ├── 1.png
    │       ├── 2.png
    │       ├── 3.png
    │       ├── 4.png
    │       ├── 5.png
    │       ├── 6.png
    │       └── 7.png
    └── slides.qrc
    
I developed this widget for my application [Glate- Google Translator and TTS](https://snapcraft.io/glate) ([Github](https://github.com/keshavbhatt/glate))
Checkout my other applications [here](https://snapcraft.io/search?q=keshavnrj).

> Contribute back if you have made any improvements :)

