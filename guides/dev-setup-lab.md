# Setting up a Lab machine
Nearly all campus computing labs have Microsoft Windows installed on them.  **While some labs may be pre-configured to support our environment**, others are not.  You will need to install Cygwin yourself, with a few small changes to make things work.

**BEFORE MOVING FORWARD**, please familiarize yourself with the [Windows](./dev-setup-windows.html) setup in general.  You will need to perform all the steps in that setup document on the lab machines, with some minor alterations, explained below.

## Determining if the machine is already setup
Many lab computer already have Cygwin installed.  It is located in `C:\cygwin64`.  If you have this already, double click on `Cygwin.bat` to launch Cygwin.

**Unfortunately**, most of the Cygwin installations on campus **do not** have development tools installed.  From within Cygwin, enter `g++ --version`.  If you get an error, then machine is not configured and you'll need to proceed to the next steps.  If you get a proper output (version information), the lab machine you are on is likely good - and you can skip the remainder of this document.

## Installing Cygwin
Cygwin is a self-contained system - which means you can install it twice, in two different directories.  Since you are not an Administrator when on the campus lab machines, you will need to download Cygwin and install it to a directory **you do have access to** - I recommend right on the Desktop.

The installation process is exactly the same as described in the [Windows](./dev-setup-windows.html) setup document, aside from the following:

1.  When asked who you are installing this for - select "Just me" - **not** All Users.
2.  When selecting a place to install Cygwin, specify `C:\Users\<your username>\Desktop`
3.  When selecting a download location (packages), specify `C:\Users\<your username>\Downloads`

**Be sure to install all of the necessary programs - `git`, `g++`, `make`, `cmake`, and `gdb`.

I recommend that at the end of the installation, you place a shortcut on your Desktop to open your version of Cygwin.

## Visual Studio Code
May lab machines already have Visual Studio code installed, and if so - there is no need for you to take any action.  

Visual Studio Code can be installed by a non-administrator, so if it is not present on the machine you are on, you may simply install it.