# OpenCV

This will guide you through installing OpenCV/SimpleCV on the Raspberry Pi

## 1. Setup Camera Hardware

http://www.raspberrypi.org/camera

To ensure that you have the latest firmware update the raspberry pi by running

```
sudo rpi-update
```

and reboot afterwards.

## 2. Install UV4L Driver

First download and import the PGP file to verify the integrity of the packages we're going to install

```
wget http://www.linux-projects.org/listing/uv4l_repo/lrkey.asc && sudo apt-key add ./lrkey.asc
```

We then need to add the repository to `/etc/apt/sources/list`

```
sudo sh -c "echo 'deb http://www.linux-projects.org/listing/uv4l_repo/raspbian/ wheezy main' >> /etc/apt/sources.list"
```

Then we can install the Userland Video 4 Linux Driver for the Raspberry Pi

```
sudo apt-get update
sudo apt-get install uv4l uv4l-raspicam
```

To test that the driver was installed correctly we can run an instance of it

```
uv4l --driver raspicam --auto-video_nr --width 640 --height 480 --encoding jpeg --nopreview
```

and save a image to the current directory using

```
dd if=/dev/video0 of=snapshot.jpeg bs=11M count=1
```

To terminate a running driver, close the applications and kill the corresponding uv4l process:

```
pkill uv4l
```

## 3. Install Libraries
### 3a. Install OpenCV

Building OpenCV from source takes 8-10 hours on the Raspberry Pi (Depending on overclock). It is strongly encouraged that you run this in terminal only mode as "Out of Memory Exceptions" can occur otherwise.

```
sudo apt-get remove ffmpeg x264 libx264-dev
sudo apt-get install libopencv-dev build-essential checkinstall cmake pkg-config yasm libtiff4-dev libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libqt4-dev libgtk2.0-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils ffmpeg
mkdir OpenCV
cd OpenCV
wget https://github.com/Itseez/opencv/archive/2.4.6.2r3.zip
unzip 2.4.6.2r3.zip
rm 2.4.6.2r3.zip
cd opencv-2.4.6.2r3
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
make
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```

Once OpenCV has installed we can build the sample applications that come with OpenCV

```
cd ~/OpenCV/opencv-2.4.6.2r3/samples/c
./build_all.sh
```

The UV4L driver must be running, and we can run it at a higher priority to ensure better performance

```
uv4l --driver raspicam --auto-video_nr --encoding yuv420 --width 320 --height 240 --nopreview
sudo chrt -a -r -p 99 `pgrep uv4l`
```

Try out some of the sample applications and see what happens!

### 3b. Install SimpleCV

First install the necessary dependency packages required by SimpleCV

```
sudo apt-get install ipython python-opencv python-scipy python-numpy python-pygame python-setuptools python-pip 
```

Next download and install SimpleCV itself 

```
sudo pip install https://github.com/sightmachine/SimpleCV/archive/1.3.zip
```

To test that SimpleCV has been installed correctly open a text editor and paste the following

```
from SimpleCV import Camera
# Initialize the camera
cam = Camera()
# Loop to continuously get images
while True:
    # Get Image from camera
    img = cam.getImage()
    # Make image black and white
    img = img.binarize()
    # Draw the text "Hello World" on image
    img.drawText("Hello World!")
    # Show the image
    img.show()
```

The UV4L driver must be running, and we can run it at a higher priority to ensure better performance

```
uv4l --driver raspicam --auto-video_nr --encoding yuv420 --width 320 --height 240 --no-preview
sudo chrt -a -r -p 99 `pgrep uv4l`
```

Save the files as helloworld.py and run it from the terminal

```
python helloworld.py
```

If SimpleCV has installed correctly and an instance of the UV4L driver is running a binary image from the camera should be displayed with the text "Hello World" superimposed over it

### Sources

1. http://linux-projects.org
2. http://raspberrypi.org
3. http://simplecv.org
4. http://opencv.org