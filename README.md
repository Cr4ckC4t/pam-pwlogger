# PAM password logger

[![Tested](https://img.shields.io/badge/Debian%2010-tested-green.svg)](https://shields.io/)

## What's this?

A minimalistic pluggable authentication modules (PAM) module that hooks into the linux authentication process to write the username, password and source host into a logfile. To learn more about what PAM is and how it works see [1]. The code is a modified version of this project [2]. Slight modifications for the use with other OS (versions) may be necessary,

## Building it

In order to build the module the `libpam-dev` library is required.
```
apt search libpam
  [...]
  libpam0g-dev/stable,now 1.3.1-5 amd64
    Development files for PAM
  [...]
  
apt install libpam0g-dev
```
After installing the necessary dev files run `make`.
```
make
```

## Usage

**Hint**: tinkering with PAM can easily break your entire authentication, use at own risk.

## Resources
[1] https://documentation.suse.com/sled/15-SP1/html/SLED-all/cha-pam.html

[2] http://www.adeptus-mechanicus.com/codex/logsshp/logsshp.html
