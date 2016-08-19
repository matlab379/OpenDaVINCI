&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/se-research/OpenDaVINCI/blob/master/odlogo/Logo.png" alt="OpenDaVINCI Logo" width=140 height=140>
# OpenDaVINCI

OpenDaVINCI is a compact middleware OpenDaVINCI written entirely in standard C++.
It runs on a variety of POSIX-compatible OS. And Windows.

You will find its full documentation and getting started guides here: http://docs.opendavinci.org

You will find its API documentation here: http://api.opendavinci.org

You will find different projects that are using OpenDaVINCI here: http://opendavinci.cse.chalmers.se/www/index.html

<a href="https://twitter.com/OpenDaVINCI" class="twitter-follow-button" data-show-count="false" data-size="large">Follow @OpenDaVINCI on Twitter</a>

**Overview build status:**

*Lastest source code deployment:* https://github.com/se-research/OpenDaVINCI/releases/latest

*Latest Docker deployment:* https://hub.docker.com/r/seresearch/opendavinci-ubuntu-amd64/tags/

*Latest Docker simulation deployment:* https://hub.docker.com/r/seresearch/odsimulation/tags/

Architecture  | DragonFlyBSD 4.4 | FreeBSD 10.3 | NetBSD 7.0.1 | OpenBSD 5.9 | Mac OS X
------------- | ---------------- | ------------ | ------------ | ----------- | --------
32bit         | - | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-FreeBSD10-32/badge/icon)](https://github.com/se-research/OpenDaVINCI) | - | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-OpenBSD59-32/badge/icon)](https://github.com/se-research/OpenDaVINCI) | -
64bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-DragonFlyBSD-4.4/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-FreeBSD10/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-NetBSD7.0/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-OpenBSD59/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-MacOSX/badge/icon)](https://github.com/se-research/OpenDaVINCI)

Architecture  | ArchLinux | CentOS 7 | Debian 8.5 | Elementary Freya
------------- | --------- | -------- | ---------- | ----------------
32bit         | -         | -        | -          | -                
64bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-archlinux/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-CentOS7/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-debian-jessie/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-ElementaryFreya/badge/icon)](https://github.com/se-research/OpenDaVINCI)

Architecture  | Ubuntu 14.04 | Ubuntu 15.04 | Ubuntu 15.10 | Ubuntu 16.04
------------- | ------------ | ------------ | ------------ | ------------
32bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-Ubuntu14.04-32/badge/icon)](https://github.com/se-research/OpenDaVINCI) | -            | -            | -
64bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-ubuntu-14.04/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-ubuntu-15.04/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-ubuntu-15.10/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-ubuntu-16.04/badge/icon)](https://github.com/se-research/OpenDaVINCI)

Architecture  | Fedora 24 | openSuSE 13.2 | openSuSE 42.1 | Scientific Linux 7
------------- | --------- | ------------- | ------------- | ------------------
32bit         | -         | -             | -             | -  
64bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-fedora-24/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-opensuse-13.2/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/opendavinci-opensuse-42.1/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-ScientificLinux7/badge/icon)](https://github.com/se-research/OpenDaVINCI)

Architecture  | Windows 7 | Windows 8.1 | Windows 10
------------- | --------- | ----------- | ----------
32bit         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-Windows7/badge/icon)](https://github.com/se-research/OpenDaVINCI) | - | -
64bit         | -         | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-Windows8.1/badge/icon)](https://github.com/se-research/OpenDaVINCI) | [![Build Status](http://opendavinci.cse.chalmers.se:8889/job/OpenDaVINCI-Windows10/badge/icon)](https://github.com/se-research/OpenDaVINCI)

## Using OpenDaVINCI in your Projects

To explore the features of OpenDaVINCI and to use it in your own projects, we provide pre-compiled
packages in .deb and .rpm format for x86, x86_64, and armfh.

### Compiling OpenDaVINCI from sources

You will find information about how to compile OpenDaVINCI from sources here: http://opendavinci.readthedocs.org/en/latest/installation.html

### Compiling OpenDaVINCI with Clang

To compile OpenDaVINCI using Clang, change to your source folder and create a build directory::

    $ cd OpenDaVINCI && mkdir build

Use cmake to create the build scripts for your build folder and specify the Clang toolchain::

    $ cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_TOOLCHAIN_FILE=../cmake/clang-Toolchain.cmake ..

### Using our Docker images

We also provide pre-built Docker images for x86_64 and armhf. These images will be automatically updated whenever
we release new features or patches.

* Ubuntu/x86_64: docker pull seresearch/opendavinci-ubuntu-amd64 (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-amd64/)

* Ubuntu/armhf: docker pull seresearch/opendavinci-ubuntu-armhf (https://registry.hub.docker.com/u/seresearch/opendavinci-ubuntu-armhf/)

### Adding OpenDaVINCI to your Ubuntu 14.04 Linux distribution

To explore the features of OpenDaVINCI and to use it in your own projects, you can add our .deb repository. We provide
packages for x86, x86_64, and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ echo "deb http://opendavinci.cse.chalmers.se/deb/ trusty main" | sudo tee -a /etc/apt/sources.list 

Update your package database:

    $ sudo apt-get update

Install OpenDaVINCI:

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


### Adding OpenDaVINCI to your Ubuntu 15.04 Linux distribution

To explore the features of OpenDaVINCI and to use it in your own projects, you can add our .deb repository. We provide
packages for x86, x86_64, and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ echo "deb http://opendavinci.cse.chalmers.se/deb/ vivid main" | sudo tee -a /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update

Install OpenDaVINCI:

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


### Adding OpenDaVINCI to your Ubuntu 15.10 Linux distribution

To explore the features of OpenDaVINCI and to use it in your own projects, you can add our .deb repository. We provide
packages for x86, x86_64, and armfh.

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ echo "deb http://opendavinci.cse.chalmers.se/deb/ wily main" | sudo tee -a /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update

Install OpenDaVINCI:

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


### Adding OpenDaVINCI to your Debian 8 Linux distribution

Add the public key from our repository:

    $ wget -O - -q http://opendavinci.cse.chalmers.se/opendavinci.cse.chalmers.se.gpg.key | sudo apt-key add -

Add our repository itself to your sources.list:

    $ echo "deb http://opendavinci.cse.chalmers.se/deb/ jessie main" | sudo tee -a /etc/apt/sources.list

Update your package database:

    $ sudo apt-get update

Install OpenDaVINCI:

    $ sudo apt-get install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


### Adding OpenDaVINCI to your CentOS 7 Linux distribution

Add our repository to your sources.list:

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

Update your package database:

    $ sudo yum -y update

Install OpenDaVINCI:

    $ sudo yum install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent
   

### Adding OpenDaVINCI to your Fedora 21 Linux distribution

Add our repository to your sources.list:

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

Update your package database:

    $ sudo yum -y update

Install OpenDaVINCI:

    $ sudo yum install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent
   

### Adding OpenDaVINCI to your Fedora 22 Linux distribution

Add our repository to your sources.list:

    $ cd /etc/yum.repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

Update your package database:

    $ sudo dnf -y upgrade

Install OpenDaVINCI:

    $ sudo dnf install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent


### Adding OpenDaVINCI to your openSuSE 13 Linux distribution

Add our repository to your sources.list:

    $ cd /etc/zypp/repos.d && sudo wget http://opendavinci.cse.chalmers.se/OpenDaVINCI-x86_64.repo

Update your package database:

    $ sudo zypper --no-gpg-checks refresh

Install OpenDaVINCI:

    $ sudo zypper install opendavinci-lib opendavinci-odtools opendavinci-odsupercomponent

![Screenshot](https://github.com/se-research/OpenDaVINCI/blob/master/docs/Screenshot.png)
